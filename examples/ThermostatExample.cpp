#include <ESP8266WebServer.h>
#include "ThermostatControl.h"

ESP8266WebServer webserver;

void setup() 
{
    webserver.begin();
	ThermostatControl.init(10, 0.1, ThermostatControl.Heat, &webserver);
}

void loop() {
		ThermostatControl.temperature = 11;
		ThermostatControl.task();
}

