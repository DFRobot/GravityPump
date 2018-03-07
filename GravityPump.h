#ifndef _GRAVITYPUMP_H_
#define _GRAVITYPUMP_H_
#include <Servo.h>
#include <Arduino.h>

#define RECEIVEDBUFFERLENGTH 20

class GravityPump
{
public:
    GravityPump();
    ~GravityPump();

    void update();
    void setPin(int pin);
    void calFlowRate(int speed = 180);
    void pumpDriver(int speed, unsigned long runTime);
    float timerPump(unsigned long runTime);
    float flowPump(float quantitation);
    void getFlowRateAndSpeed(); 
    void stop();


private:
    Servo _pumpServo;    
    int   _pin;
    bool  _runFlag = false;
    bool  _stopFlag = false;
    int   _pumpSpeed = 180;
    float _flowRate = 0.75; //默认流速
    unsigned long _startTime = 0;
    unsigned long _intervalTime = 0;
    const int _servoStop = 90;
    char _receivedBuffer[RECEIVEDBUFFERLENGTH];   // store the serial command
    byte _receivedBufferIndex = 0;

private:
    byte uartParse();
    bool serialDataAvailable();
    void pumpCalibration(byte mode);
};

#endif
