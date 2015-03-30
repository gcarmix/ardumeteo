// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef _ardumeteo_H_
#define _ardumeteo_H_
#include "Arduino.h"
//add your includes for the project ardumeteo here
#define ARDUMETEO_USER 	"cyanprince" // Here insert your Ardumeteo username
#define MQTT_PASSWORD 	"password"	// Here insert the password you provided to Ardumeteo at subscription time
#define SEND_INTERVAL 	60			// Here insert the send interval of MQTT to Ardumeteo server, don't go less then 600 seconds or you'll be banned
#define WIFI_SSID		"Telecom-82514429"
#define WIFI_PASSWORD	"supercalifragilisti12345"
#define CLIENT_NAME		"ardumeteoClient"
#define TEMPERATURE_S	"TEMP"
#define HUMIDITY_S		"HUMY"
#define PRESSURE_S		"PRES"
#define TEMPb	0x0001
#define HUMYb	0x0002
#define PRESb	0x0004
#define WINDb	0x0008
#define LUMYb	0x0010


typedef struct SensorsData
{
	double temp;
	double humy;
	double pres;
	double wind;
	double light;
};

byte ardumeteo_server[] = { 37, 187, 60, 11 }; // This is the IP address of the Ardumeteo server

//end of add your includes here
#ifdef __cplusplus
extern "C" {
#endif
void loop();
void setup();
#ifdef __cplusplus
} // extern "C"
#endif

//add your function definitions for the project ardumeteo here




//Do not add code below this line
#endif /* _ardumeteo_H_ */
