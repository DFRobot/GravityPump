#include "GravityPump.h"
#include <EEPROM.h>

#define FLOWRATEADDRESS 0x24
#define PUMPSPEEDADDRESS 0x28
#define CALIBRATIONTIME 15
#define ReceivedBufferLength 20

#define EEPROM_write(address, p) {int i = 0; byte *pp = (byte*)&(p);for(; i < sizeof(p); i++) EEPROM.write(address+i, pp[i]);}
#define EEPROM_read(address, p)  {int i = 0; byte *pp = (byte*)&(p);for(; i < sizeof(p); i++) pp[i]=EEPROM.read(address+i);}


GravityPump::GravityPump()
{
}

GravityPump::~GravityPump()
{

}

void GravityPump::setPin(int pin)
{
    this->_pin = pin;
    this->_pumpServo.attach(this->_pin);
}

void GravityPump::getFlowRateAndSpeed()
{
    EEPROM_read(FLOWRATEADDRESS, this->_flowRate);
    delay(5);
    EEPROM_read(PUMPSPEEDADDRESS, this->_pumpSpeed);
}

void GravityPump::update()
{
    pumpDriver(this->_pumpSpeed,this->_intervalTime);
}

void GravityPump::pumpDriver(int speed, unsigned long runTime)
{
    if(this->_stopFlag || millis() - this->_startTime >= runTime)
    {
        this->_runFlag = false;
        this->_stopFlag = false;
        this->_pumpServo.write(this->_servoStop);
        this->_startTime = millis() + runTime;
    }
    else
    {
        this->_pumpServo.write(speed);
    }    
}

float GravityPump::flowPump(float quantitation)
{
    unsigned long runTime = 0;
    if(!this->_runFlag)
    {
        this->_runFlag = true;
        this->_intervalTime = 1000*(quantitation / this->_flowRate);
        this->_startTime = millis();
        return this->_intervalTime; 
    }
    return 0;
}

float GravityPump::timerPump(unsigned long runTime)
{
    if(!this->_runFlag)
    {
        this->_runFlag = true;
        this->_intervalTime = runTime*1000;
        this->_startTime = millis();
        return (this->_flowRate*runTime);
    }
    return 0;
}

void GravityPump::stop()
{
    this->_stopFlag = true;
    this->_runFlag = false;
}

void GravityPump::calFlowRate(int speed)
{
   	//给定时间内看有多少流量？
	//在串口中输入相应液体体积。
	//how much quantitation in given time?
	//please input the ok in serial to start cal
	//wait for the input "OK"
	//Pump 5ml in some secs
	//please input the actual mumber in serial
	//waiting for input actual number 
	//cal end
    this->_pumpSpeed = speed;
    if(serialDataAvailable() > 0)
    {
        pumpCalibration(uartParse());
    }
}

bool GravityPump::serialDataAvailable()
{
  char receivedChar;
  static unsigned long receivedTimeOut = millis();
  while (Serial.available()>0) 
  {   
    if (millis() - receivedTimeOut > 1000U) 
    {
      this->_receivedBufferIndex = 0;
      memset(this->_receivedBuffer,0,RECEIVEDBUFFERLENGTH);
    }
    receivedTimeOut = millis();
    receivedChar = Serial.read();
    if (receivedChar == '\n' || this->_receivedBufferIndex==ReceivedBufferLength-1){
		this->_receivedBufferIndex = 0;
		strupr(this->_receivedBuffer);
		return true;
    }
    else{
      this->_receivedBuffer[this->_receivedBufferIndex] = receivedChar;
      this->_receivedBufferIndex++;
    }
  }
  return false;
}

byte GravityPump::uartParse()
{
  byte modeIndex = 0;
  if(strstr(this->_receivedBuffer, "STARTCAL") != NULL) 
      modeIndex = 1;
  else if(strstr(this->_receivedBuffer, "SETCAL:") != NULL) 
      modeIndex = 2;
  return modeIndex;
}

void GravityPump::pumpCalibration(byte mode)
{
    char *receivedBufferPtr;
    float quantification = 0;
    
    switch(mode)
    {
      case 1:
      {
        this->_stopFlag = false;
        this->_startTime = millis();
        this->_intervalTime = (CALIBRATIONTIME*1000);
        Serial.println(F("Calibration starting..."));
      }
      break;
      case 2: 
      {
        receivedBufferPtr=strstr(this->_receivedBuffer, "SETCAL:");
        receivedBufferPtr+=strlen("SETCAL:");
        quantification = strtod(receivedBufferPtr,NULL);
        Serial.print(F("Quantification:"));
        Serial.println(quantification);
        this->_flowRate = quantification/float(CALIBRATIONTIME);
        EEPROM_write(FLOWRATEADDRESS, this->_flowRate);
        delay(10);
        EEPROM_write(PUMPSPEEDADDRESS, this->_pumpSpeed);
        Serial.print(F("PumpSpeed:"));
        Serial.println(this->_pumpSpeed);
        Serial.print(F("FlowRate:"));
        Serial.print(this->_flowRate);
        Serial.println(F("ml/s,\r\nCalibration Finish!"));
      }
      break;
    }
}