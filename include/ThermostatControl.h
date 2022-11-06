// ThermostatControl.h

#ifndef _THERMOSTATCONTROL_h
#define _THERMOSTATCONTROL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include <ESP8266WebServer.h>

class ThermostatControlClass
{
 protected:
     enum TwoStageHeatStates
     {
         tshsHeatOff,
         tshsHeatOnLow,
         tshsHeatOnHigh
     };

     TwoStageHeatStates State;

 public:
    enum Mode
    {
       Off,
       Heat,
       Cool,
       HeatCool,
       TwoStageHeat
    };

    enum OutputCmd
    {
        cmdOff,
        cmdHeat,
        cmdCool,
        cmdHeatLow
    };

   void init(float sp, float hys, Mode md, ESP8266WebServer* server);
   void task();
   float hysteresis;
   float setpoint;
   float temperature;
   Mode mode;
   OutputCmd output;
   float etaSetpoint;
   float temperatureRate;
   ESP8266WebServer* webserver;
   boolean setpointChanged;
   
};

extern ThermostatControlClass ThermostatControl;

#endif

