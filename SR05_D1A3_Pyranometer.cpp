#include "SR05_D1A3_Pyranometer.h"

SR05_D1A3_Pyranometer::SR05_D1A3_Pyranometer(uint8_t slave_id, HardwareSerial &serial, int baudrate) {
    _slave_id = slave_id;
    _serial = &serial;
    _baudrate = baudrate;
}

void SR05_D1A3_Pyranometer::begin() {
    _serial->begin(_baudrate);
    node.begin(_slave_id, *_serial);
}

float SR05_D1A3_Pyranometer::readIrradiance() {
    uint8_t result;
    result = node.readHoldingRegisters(0x0002, 2); // Reading 2 registers for irradiance (32-bit float)
    if (result == node.ku8MBSuccess) {
        union {
            uint32_t i;
            float f;
        } data;
        data.i = ((uint32_t)node.getResponseBuffer(0) << 16) | node.getResponseBuffer(1);
        return data.f;
    } else {
        return -1; // Error code
    }
}

float SR05_D1A3_Pyranometer::readTemperature() {
    uint8_t result;
    result = node.readHoldingRegisters(0x0006, 1); // Reading 1 register for temperature (16-bit integer)
    if (result == node.ku8MBSuccess) {
        int16_t raw_temp = node.getResponseBuffer(0);
        return raw_temp * 0.01;  // Convert to °C
    } else {
        return -1; // Error code
    }
}
