#ifndef SR05_D1A3_PYRANOMETER_H
#define SR05_D1A3_PYRANOMETER_H

#include <Arduino.h>
#include <ModbusMaster.h>

class SR05_D1A3_Pyranometer {
public:
    SR05_D1A3_Pyranometer(uint8_t slave_id, HardwareSerial &serial, int baudrate = 9600);
    void begin();
    float readIrradiance();
    float readTemperature();

private:
    ModbusMaster node;
    uint8_t _slave_id;
    HardwareSerial *_serial;
    int _baudrate;
    void modbusSetup();
};

#endif
