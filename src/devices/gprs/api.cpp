#include "api.h"

#include "modules/adafruit_fona/Adafruit_FONA.h"
#include "common.h"

#define GPRS_NS_HOST "internet.itelcel.com"
#define GPRS_NS_USR "webgprs"
#define GPRS_NS_PSS "webgprs2002"

static Adafruit_FONA gsm_device = Adafruit_FONA(GSM_ResetPin);
static GPRSNetworkStatus_e gprs_net_status;
static GPRSStatus_e gprs_status = GPRS_NOT_CONNECTED;
static float gprs_battery_percent;
static bool isEnabledGPRS;

GSM_Status_t GSM_Status;

static void GSM_CheckStatus()
{
    bool log_error = false;
    uint16_t battery_percent = 0;

    gsm_device.getBattPercent(&battery_percent);
    gprs_battery_percent = battery_percent;

    uint8_t status = gsm_device.getNetworkStatus();
    switch (status)
    {
    case 0:
        gprs_net_status = GPRS_NET_NOT_REGISTERED;
        log_error = true;
        break;
    case 1:
        gprs_net_status = GPRS_NET_REGISTERED;
        break;
    case 2:
        gprs_net_status = GPRS_NET_SEARCHING;
        break;
    case 3:
        gprs_net_status = GPRS_NET_DENIED;
        log_error = true;
        break;
    case 4:
        gprs_net_status = GPRS_NET_UNKNOWN;
        log_error = true;
        break;
    case 5:
        gprs_net_status = GPRS_NET_REGISTERED_ROAMING;
        break;
    default:
        break;
    }
    if (log_error)
    {
        logger << LOG_INFO << F(" GPRS Network Status: ") << GPRSNetworkStatusToStr(gprs_net_status) << EndLine;
    }
}

void GSM_Init()
{
    gsm_device.setGPRSNetworkSettings(F(GPRS_NS_HOST), F(GPRS_NS_USR), F(GPRS_NS_PSS));
    GSM_SerialPort.begin(GSM_SERIAL_BAUDRATE);

    uint8_t attempts = 0;
    bool isBegined = false;
    while (!isBegined && attempts < 3)
    {
        gprs_status = GPRS_SEARCHING;
        isBegined = gsm_device.begin(GSM_SerialPort);
        if (isBegined)
        {
            gprs_status = GPRS_CONNECTED;
            logger << LOG_MASTER << F("      └-- GPRS device is beginned") << EndLine;
        }
        else
        {
            logger << LOG_ERROR << F("        └-- Can't initialize GPRS device") << EndLine;
            gprs_status = GPRS_NOT_CONNECTED;
            delay(1000);
        }
        attempts++;
    }
}

void GSM_GPRSInit()
{
    if (gprs_status == GPRS_NOT_CONNECTED)
    {
        return;
    }
    uint8_t attempts = 0;
    isEnabledGPRS = false;
    while (!isEnabledGPRS && attempts < 3)
    {
        gsm_device.enableGPRS(false);
        gsm_device.enableGPRS(true);
        isEnabledGPRS = !gsm_device.GPRSstate();
        if (isEnabledGPRS)
        {
            logger << LOG_MASTER << F("      └-- GPRS network is beginned") << EndLine;
        }
        else
        {
            logger << LOG_ERROR << F("      └-- Can't initialize GPRS network") << EndLine;
            delay(1000);
        }
        attempts++;
    }
}

const __FlashStringHelper *GPRSNetworkStatusToStr(GPRSNetworkStatus_e st)
{
    switch (st)
    {
    case GPRS_NET_NOT_REGISTERED:
        return F("Not registrated");
    case GPRS_NET_REGISTERED:
        return F("Registrated");
    case GPRS_NET_SEARCHING:
        return F("Searching");
    case GPRS_NET_DENIED:
        return F("Denied");
    case GPRS_NET_UNKNOWN:
        return F("Unknown");
    case GPRS_NET_REGISTERED_ROAMING:
        return F("Registrated [Roaming]");
    default:
        return F("Unknown");
    }
}

const __FlashStringHelper *GPRSStatusToStr(GPRSStatus_e st)
{
    switch (st)
    {
    case GPRS_CONNECTED:
        return F("Connected");
    case GPRS_NOT_CONNECTED:
        return F("Disconnected");
    case GPRS_SEARCHING:
        return F("Searching");
    default:
        return F("Unknown");
    }
}

static void http_read_response(uint16_t expected_lenght, uint8_t *buffer, uint16_t buff_len)
{
    if (!buffer)
    {
        return;
    }
    uint16_t index = 0;
    while (expected_lenght > 0)
    {
        while (gsm_device.available())
        {
            char resp = gsm_device.read();
            buffer[index] = resp;
            expected_lenght--;
            index++;
            if ((buff_len - index) <= 0 || expected_lenght <= 0)
            {
                return;
            }
        }
    }
}

const __FlashStringHelper *http_method_to_str(HTTP_METHOD_e method)
{
    switch (method)
    {
    case HTTP_GET:
        return F("GET");
    case HTTP_POST:
        return F("POST");
    default:
        return F("");
    }
}

uint8_t HTTP::http_raw(HTTP_METHOD_e method, char *url, uint8_t *buffer, uint16_t buffer_len)
{
    GSM_PrintStatus();
    logger << LOG_INFO << F(" Sending http request [") << http_method_to_str(method) << F("]") << EndLine;
    logger << LOG_INFO << F("         HOST: ") << url << EndLine;

    if (method == HTTP_POST)
    {
        logger << LOG_INFO << F("         BODY: ") << (char *)buffer << EndLine;
    }

    uint16_t status_code = 0;
    uint16_t data_lenght = 0;

    uint8_t attempts = 0;
    while (attempts < 3)
    {
        bool success = false;

        switch (method)
        {
        case HTTP_POST:
            success = gsm_device.HTTP_POST_start(url,
                                                 F("application/json"),
                                                 buffer,
                                                 buffer_len,
                                                 &status_code,
                                                 &data_lenght);
            gsm_device.HTTP_POST_end();
            break;
        case HTTP_GET:
            success = gsm_device.HTTP_GET_start(url, &status_code, &data_lenght);
            http_read_response(data_lenght, buffer, buffer_len);
            if (success)
            {
                logger << LOG_INFO << F("         RESPONSE: ") << (char *)buffer << EndLine;
            }
            gsm_device.HTTP_GET_end();
            break;
        }

        if (success)
        {
            break;
        }
        attempts++;
    }

    switch (status_code)
    {
    case HTTP_ERROR:
        logger << LOG_ERROR << F("         STATUS: CAN'T SEND REQUEST") << EndLine;
        break;
    case HTTP_OK:
        logger << LOG_INFO << F("         STATUS: OK") << EndLine;
        break;
    case HTTP_NO_CONTENT:
        logger << LOG_INFO << F("         STATUS: OK, NO CONTENT") << EndLine;
        break;
    case HTTP_BAD_REQUEST:
        logger << LOG_ERROR << F("         STATUS: BAD REQUEST") << EndLine;
        break;
    case HTTP_NOT_FOUND:
        logger << LOG_ERROR << F("         STATUS: NOT FOUND 404") << EndLine;
        break;
    case HTTP_NETWORK_ERROR:
        logger << LOG_ERROR << F("         STATUS: NETWORK ERROR") << EndLine;
        break;
    case HTTP_DNS_ERROR:
        logger << LOG_ERROR << F("         STATUS: HOST ERROR") << EndLine;
        break;
    default:
        logger << LOG_ERROR << F("         STATUS: Unkown status code (") << status_code << F(")") << EndLine;
        break;
    }

    return status_code;
}

uint8_t HTTP::post(char *url, uint8_t *data, uint16_t lenght)
{
    return http_raw(HTTP_POST, url, data, lenght);
}

uint8_t HTTP::get(char *url, uint8_t *buffer, uint16_t lenght)
{
    return http_raw(HTTP_GET, url, buffer, lenght);
}

void GSM_PrintStatus()
{
    logger << LOG_INFO << F("          └-- GSM STATUS ") << EndLine;
    logger << LOG_INFO << F("                    GSM: ") << GPRSStatusToStr(GSM_Status.gsm.status) << EndLine;
    logger << LOG_INFO << F("                   RSSI: ") << GSM_Status.gsm.rssi << F(" dB") << EndLine;
    logger << LOG_INFO << F("                EN GPRS: ") << (GSM_Status.gprs.is_enabled ? F("Detached") : F("Attached")) << EndLine;
    logger << LOG_INFO << F("                   GPRS: ") << GPRSNetworkStatusToStr(GSM_Status.gprs.status) << EndLine;
    logger << LOG_INFO << F("                    NET: ") << GSM_Status.gprs.state << EndLine;
    logger << LOG_INFO << F("                   CCID: ") << GSM_Status.sim.ccid << EndLine;
}
