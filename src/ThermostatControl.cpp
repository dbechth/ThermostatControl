#include "ThermostatControl.h"
#include "ThermostatIndex.h"
#include "ThermostatIndexNew.h"

#define Task5M  (60000 * 5)


void IDX()
{
    ThermostatControl.webserver->send(200, "text/html", ThermostatIndex);
}

void IDXnew()
{
    ThermostatControl.webserver->send(200, "text/html", ThermostatIndexNew);
}

void getSetpoint()
{
    ThermostatControl.webserver->send(200, "text/plain", String(ThermostatControl.setpoint));
}

void setSetpoint()
{
    int setpoint = ThermostatControl.webserver->arg("setpoint").toInt();
    if (!(setpoint < 35 || setpoint > 250))
    {
        ThermostatControl.setpoint = setpoint;
        ThermostatControl.setpointChanged = true;
    }
    else if (setpoint == 1 || setpoint == -1)
    {
        ThermostatControl.setpoint += setpoint;
        ThermostatControl.setpointChanged = true;
    }
    getSetpoint();
}

void getTemperature()
{
    ThermostatControl.webserver->send(200, "text/plain", String(ThermostatControl.temperature));
}

void ThermostatControlClass::init(float sp, float hys, Mode md, ESP8266WebServer *server)
{
   webserver = server;
   hysteresis = hys;
   setpoint = sp;
   mode = md;
   output = cmdOff;
   State = ThermostatControlClass::tshsHeatOff;
   ThermostatControl.setpointChanged = false;
   //webserver->on("/", IDXnew);
   webserver->on("/thermostat", IDX);
   webserver->on("/setSetpoint", setSetpoint);
   webserver->on("/getTemperature", getTemperature);
   webserver->on("/getSetpoint", getSetpoint);

}

void ThermostatControlClass::task()
{
   if (setpoint >500)
   {
      setpoint = 500;
   }

   if (setpoint <34.0)
   {
      setpoint = 34.0;
   }

   float highSetpoint = setpoint + hysteresis;
   float lowSetpoint = setpoint - hysteresis;
   float verylowSetpoint = setpoint - (hysteresis*4);
   
   switch (mode)
   {
      case Off:
         output = cmdOff;
         break;

      case Cool:
         if (temperature <= lowSetpoint)
         {
            output = cmdOff;
         }

         if (temperature >= highSetpoint)
         {
            output = cmdCool;
         }
         break;

      case Heat:
         if (temperature <= lowSetpoint)
         {
            output = cmdHeat;
         }

         if (temperature >= highSetpoint)
         {
            output = cmdOff;
         }
         break;
      case HeatCool:
          if (temperature < lowSetpoint)
          {
              output = cmdHeat;
          }
          else if (temperature > highSetpoint)
          {
              output = cmdCool;
          }
          else
          {
              output = cmdOff;
          }
          break;
      case TwoStageHeat:

          switch (State)
          {
          case ThermostatControlClass::tshsHeatOff:

              output = cmdOff;

              if (temperature <= lowSetpoint)
              {
                  State = ThermostatControlClass::tshsHeatOnLow;
              }
              break;
          case ThermostatControlClass::tshsHeatOnLow:

              output = cmdHeatLow;

              if (temperature <= verylowSetpoint)
              {
                  State = ThermostatControlClass::tshsHeatOnHigh;
              }
              else if (temperature >= highSetpoint)
              {
                  State = ThermostatControlClass::tshsHeatOff;
              }

              break;
          case ThermostatControlClass::tshsHeatOnHigh:

              output = cmdHeat;

              if (temperature > setpoint)
              {
                  State = ThermostatControlClass::tshsHeatOnLow;
              }

              break;
          default:
              State = ThermostatControlClass::tshsHeatOnHigh;
              break;
          }

          break;

      default:
         output = cmdHeat;
         break;
   }


}


ThermostatControlClass ThermostatControl;

