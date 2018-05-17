# GravityPump

https://www.dfrobot.com/product-1698.html

# INTRODUCTION
Gravity: digital peristaltic pump is a new product developed by DFRobot. This is a new member of our water quality monitoring devices. It is an actuator for the liquid system.

DFRobot peristaltic pump integrates a PPM motor driver on the pump, this is a Gravity interface (PH2.0-3P) motor driver. The control signal is compatible with standard servo motor, you can use Arduino, Raspberry Pi, micro:bit and other kinds of microcontrollers to control its direction and flow speed. The tube in the pump head is made up of BPT material, which is anti-acid and long life.
Peristaltic pumps are a kind of positive displacement pump used for delivering small amounts of fluid. The fluid is contained within a flexible tube fitted inside a circular pump casing. When the rotor rotates continuously, the fluid in the tube will be squeezed and deliver to the other side. In this way, the liquid flow rate can be easily accuracy controlled.


(Excerpt from internet)


As a kind of metering pump, peristaltic pump can be conveniently used for quantitative delivery. It has a wide range of application scenarios, such as science experiment, hydroponics, drip irrigation, tropical fish farming, shrimp cylinder environment control, etc. A large number of titration experiments can be automated with this peristaltic pump, such as potentiometric titration, indicator-based colorimetric titration, pH-based titration, and so on. It is great helpful to improve your working efficiency
At the other hand, peristaltic pumps also have a wide range of applications in food, medical and other industries. Making an automatic coffee machine will be a really good idea!


## Arduino Peristaltic Pump
Attention:Since the motor power consumption (about 5W) is a little large, it’s better to add an external power supply on your microcontroller, USB port can only provide 2.5W power supply.
## FEATURES
### Peristaltic pump

### Low noise,
### Low cost,
### Simple structure,
### Easy to maintain,
### Three rotors with moderate pulsation,
### Non-toxic and pollution-free
### Driver board

### Gravity 3Pin digital connector, plug and play
### Servo PPM control signal, driving easily and compatible with Arduino, Raspberry Pi, micro: bit and other controllers.
## SPECIFICATION
### Driver Board

### Input Voltage: 5V-6V
### Maximum Continuous Operating Current: 1.8A
### Peak Current: 2.5A
### Quiescent Current: <1mA (No PPM Signal Input)
### PPM Signal Resolution: 1us
### Positive Pulse Width of the PPM Signal: 500us-2500us
### Forward Pulse Width Range: 500us-1400us (500us: max forward speed)
### Stop Pulse Width Range: 1400us-1600us
### Inverted Pulse Width Range: 1600us-2500us (2500us: max inverted speed)
### PPM Frequency: 50Hz (Servo Control Signal)
### Connector: Gravity PH2.0-3P
### Size: 27.4 x 28.7 mm/1.08 x 1.13 inches
### Peristaltic Pump

### Motor: DC Motor
### Rated Voltage: 6V
### Rated Power: 5W
### Tube Material: BPT
### Tube Specifications: inner diameter 2.5mm, outer diameter 4.5mm
### Pump Head Material: Engineering Plastics
### Pulsation: Three Rollers, Small Pulsation
### Flow: ≥45ml/min (almost 1ml/s)
### Working Conditions: ambient temperature 0 ~ 40 ℃, relative humidity <80%
---

## Function introduction

### void pumpDriver(int speed, unsigned long runTime);
#### the basic pump function, have to given speed in number(0 to 180. 90 for stop,0 and 180 is max speed in each direction.)and runing time in milliseced.
#### 基本功能，有两个参数，第一个是速度参数，0到180，其中90为停止，0和180为两个方向最大速度。第二个是运行时间，以毫秒为单位。
### float timerPump(unsigned long runTime);
#### timer pump function,base on the basic function.the function need to given the running time then the pump will dosing as long as your have given.and return the quantitation. if you have Calibration, the number will be close to result.
#### 定时功能，运行给定时间，并在串口给出输出体积，单位ML。如果进行过校准，则给出的体积数将基本等于理论值。

### float flowPump(float quantitation);
#### quantification setting pump function,base on the basic function.the function need to given a quantification. Then the pump will dosing the quantification in given number. if you have Calibration, the number will be close to result.
#### 流量功能，给定体积数，泵将输出给定的流量，单位ML。如果进行过校准，则给出的体积将基本等于理论值。
### void getFlowRateAndSpeed();
#### flowrate and speed reading from EEPROM
#### 读取功能，读取存储在EEPROM里的速度（0~180）和流量值（ML）
### void stop();
#### stop function. whenever you use this function the pump will stop immediately.
#### 停止功能。使用这个功能将立刻停止水泵的运行。
