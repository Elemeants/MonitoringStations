#if !defined(DEVICES_FONA_GPRS_API_H)
#define DEVICES_FONA_GPRS_API_H

#include <WString.h>
#include <HardwareSerial.h>

#include "config.h"

#define GSM_SERIAL_BAUDRATE 38400

extern HardwareSerial &GSM_SerialPort;
extern uint8_t GSM_ResetPin;

typedef enum
{
    GPRS_NET_NOT_REGISTERED,
    GPRS_NET_REGISTERED,
    GPRS_NET_SEARCHING,
    GPRS_NET_DENIED,
    GPRS_NET_UNKNOWN,
    GPRS_NET_REGISTERED_ROAMING,
} GPRSNetworkStatus_e;

typedef enum
{
    GPRS_CONNECTED,
    GPRS_NOT_CONNECTED,
    GPRS_SEARCHING,
} GPRSStatus_e;

typedef enum
{
    HTTP_POST,
    HTTP_GET
} HTTP_METHOD_e;

typedef enum
{
    HTTP_ERROR = 0,
    HTTP_OK = 200,
    HTTP_NO_CONTENT = 204,
    HTTP_BAD_REQUEST = 400,
    HTTP_NOT_FOUND = 404,
    HTTP_NETWORK_ERROR = 601,
    HTTP_DNS_ERROR = 603,
} HTTP_STATUS_CODE_e;

typedef struct
{
    struct
    {
        GPRSStatus_e status;
        uint8_t rssi;
    } gsm;

    struct
    {
        bool is_enabled;
        uint8_t state;
        GPRSNetworkStatus_e status;
    } gprs;

    struct
    {
        char ccid[16];
    } sim;
} GSM_Status_t;
extern GSM_Status_t GSM_Status;

const __FlashStringHelper *GPRSNetworkStatusToStr(GPRSNetworkStatus_e st);
const __FlashStringHelper *GPRSStatusToStr(GPRSStatus_e st);
const __FlashStringHelper *http_method_to_str(HTTP_METHOD_e method);

void GSM_Init();
void GSM_GPRSInit();
void GSM_PrintStatus();

namespace HTTP
{
uint8_t http_raw(HTTP_METHOD_e method, char *url, uint8_t *buffer, uint16_t length);

uint8_t post(char *url, uint8_t *data, uint16_t lenght);
uint8_t get(char *url, uint8_t *buffer, uint16_t lenght);
}  // namespace HTTP

#endif  // DEVICES_FONA_GPRS_API_H
