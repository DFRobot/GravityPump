#include "GravityPump.h"
#include "Button.h"

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
    {
        pump.calFlowRate();
    }
    else
    {
        if(run)
        {
            run = false;
            // Serial.println(pump.flowPump(6.6));
            Serial.println(pump.timerPump(120000));
        }

    }
    if(button.click())
    {
        Serial.println("click");
        pump.stop();
    }
    if(button.press())
    {
        Serial.println(pump.flowPump(100));
        Serial.println("press");
    }
}