// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef _ardumeteo_H_
#define _ardumeteo_H_
#include "Arduino.h"
//add your includes for the project ardumeteo here
#define ARDUMETEO_USER 	"your_username" // Here insert your Ardumeteo username
#define MQTT_PASSWORD 	"your_password"	// Here insert the password you provided to Ardumeteo at subscription time
#define SEND_INTERVAL 	600			// Here insert the send interval of MQTT to Ardumeteo server, don't go less then 600 seconds or you'll be banned
#define WIFI_SSID		"your_ssi"
#define WIFI_PASSWORD	"your_wifipassword"
#define CLIENT_NAME		"ardumeteoClient"
#define TEMPERATURE_S	"TEMP"
#define HUMIDITY_S		"HUMY"
#define PRESSURE_S		"PRESS"
#define SENS_0			0
#define SENS_1			1


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
