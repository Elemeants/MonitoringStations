#include "driver.h"

#include "common.h"

static char ATLAS_BUFFER_RX[32];

void AtlasI2CSensor::setup()
{
    I2CBus.add(this);
    if (this->isConnected())
    {
        logger << LOG_INFO << F("    + ") << sensor_typename() << F("device found") << EndLine;
        this->begin(address());
    }
    else
    {
        logger << LOG_ERROR << F("    ~ ") << sensor_typename() << F("device not found") << EndLine;
    }
}

void AtlasI2CSensor::update()
{
    logger << LOG_INFO << F(" Reading ") << sensor_typename() << F(" sensor with addr 0x") << String(address(), HEX) << EndLine;
    uint8_t attempts = 0;
    while (attempts < 3)
    {
        last_value = send_read();

        switch (status())
        {
        case ATLAS_STATUS_SUCCESS:
            logger << LOG_INFO << F("     + Success value: ") << last_value << EndLine;
            return;
        case ATLAS_STATUS_FAIL:
            logger.log(F("     ~ Error reading"), LOG_INFO);
            break;
        case ATLAS_STATUS_PENDING:
            logger.log(F("     ~ Still reading"), LOG_INFO);
            break;
        case ATLAS_STATUS_NO_DATA:
            logger.log(F("     ~ Error reading"), LOG_INFO);
            break;
        }

        attempts++;
    }
}

void AtlasI2CSensor::registerMeasure()
{
    switch (_type)
    {
    case ATLAS_PH:
        MeasureRegister->addMeasure(last_value, F(ATLAS_PH_JSON_KEY));
        break;
    case ATLAS_EC:
        MeasureRegister->addMeasure(last_value, F(ATLAS_EC_JSON_KEY));
        break;
    }
}

AtlasSensorStatus AtlasI2CSensor::status()
{
    return _status;
}

float AtlasI2CSensor::send_read()
{
    clear_array(ATLAS_BUFFER_RX, array_size(ATLAS_BUFFER_RX));
    _setReg('r', true);
    delay(815);
    requestBytes(ATLAS_BUFFER_RX, array_size(ATLAS_BUFFER_RX));
    uint8_t statusCode = ATLAS_BUFFER_RX[0];
    switch (statusCode)
    {
    case 1:
        _status = ATLAS_STATUS_SUCCESS;
        break;  // OK
    case 2:
        _status = ATLAS_STATUS_FAIL;
        break;  // Fail
    case 254:
        _status = ATLAS_STATUS_PENDING;
        break;  // Pending
    case 255:
        _status = ATLAS_STATUS_NO_DATA;
        break;  // No data
    }
    ATLAS_BUFFER_RX[0] = '0';
    return atof(ATLAS_BUFFER_RX);
}