#include "GravityPump.h"
#include "Button.h"//https://github.com/DFRobot/Button

GravityPump pump;
Button button;
bool run = true;
int debug = 0;

void setup()
{
    pump.setPin(9);
    button.init(2);
    Serial.begin(115200);
    pump.getFlowRateAndSpeed();
}

void loop()
{
    pump.update();
    button.update();
    if (debug)
    //in debug mode the pump will do calibation.
    //if set the debug mode off then the function works.
    {
        pump.calFlowRate();
    }
    else
    {
        if(run)
        {
            //switch the function by using Comments.
            run = false;
            // Serial.println(pump.flowPump(6.6));
            //just put the number in ml then the pump will dosing the numbers of liquid to you.
            //and you can find the numbers from serial port.
            Serial.println(pump.timerPump(120000));
            //just put the number in milisecend then the pump will dosing the time of numbers for you.
            //and you can find the numbers from serial port.
        }

    }
    if(button.click())
    {
        //Serial.println("click");
        //when you click the button the pump will stop immediately
        pump.stop();
    }
    if(button.press())
    {
        Serial.println(pump.flowPump(100));
        //when you press the button the pump will continue working.
        //Serial.println("press");
    }
}
