// ThermostatControl.h

#ifndef _THERMOSTATCONTROL_h
#define _THERMOSTATCONTROL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#ifdef ARDUINO_ARCH_ESP32
    #include <WebServer.h>
#else
    #include <ESP8266WebServer.h>
#endif
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
    
    #ifdef ARDUINO_ARCH_ESP32
    void init(float sp, float hys, Mode md, WebServer* server);
    #else
    void init(float sp, float hys, Mode md, ESP8266WebServer* server);
    #endif
   
   void task();
   float hysteresis;
   float setpoint;
   float temperature;
   Mode mode;
   OutputCmd output;
   float etaSetpoint;
   float temperatureRate;
    #ifdef ARDUINO_ARCH_ESP32
        WebServer* webserver;//this should probably be a typedef
    #else
        ESP8266WebServer* webserver;
    #endif
   boolean setpointChanged;
   
};

extern ThermostatControlClass ThermostatControl;

#endif

