//#include <Energia>
#include "Arduino.h"
#include <Wire.h>
#include "IRTrackingCamera.h"

int IRTrackingCamera::_i2cAddress = 0xB0 >> 1;
//SoftwareSerial *SoftwareSerial::active_object = 0;

IRTrackingCamera::IRTrackingCamera()
{
    // don't really need to do anything?
    //_i2cAddress = 0xB0 >> 1;
}

void IRTrackingCamera::initialize()
{
    Wire.begin();
    sendTwoBytesAndDelay(0x30, 0x01, 10);
    sendTwoBytesAndDelay(0x30, 0x08, 10);
    sendTwoBytesAndDelay(0x06, 0x90, 10);
    sendTwoBytesAndDelay(0x08, 0xC0, 10);
    sendTwoBytesAndDelay(0x1A, 0x40, 10);
    sendTwoBytesAndDelay(0x33, 0x33, 10);
    delay(100);
}

void IRTrackingCamera::sendTwoBytesAndDelay(unsigned char b1, unsigned char b2, unsigned long delay_ms)
{
    Wire.beginTransmission(_i2cAddress);
    Wire.write(b1);
    Wire.write(b2);
    Wire.endTransmission();
    delay(delay_ms);
}

void IRTrackingCamera::update()
{
    Wire.beginTransmission(_i2cAddress);
    Wire.write(0x36);
    Wire.endTransmission();

    Wire.requestFrom(_i2cAddress, 16);  // Request 2 byte heading (MSB first)
    int i;

    // clear buffer
    for (i = 0; i < 16; i++) { _buffer[i]=0; }

    i = 0;
    while(Wire.available() && i < 16)
    {
        _buffer[i] = Wire.read();
        i++;
    }

    //PointCount = _buffer[0];

    int highNibs;

    for (i = 0; i < 4; i++)
    {
        Points[i].x = _buffer[3*i + 1];
        Points[i].y = _buffer[3*i + 2];

        highNibs = _buffer[3*i + 3];
        Points[i].x += (highNibs & 0x30) << 4;
        Points[i].y += (highNibs & 0xC0) << 2;
    }

    //return PointCount;
}
