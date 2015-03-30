// Do not remove the include below
#include "ardumeteo.h"
#include "ESP8266Client.h"
#include "PubSubClient.h"
#include "SoftwareSerialLocal.h"
#include "dht.h"
#define DHT22_PIN 6

SensorsData sensorData;
uint16_t sensorMask;
//MQTT Server IP Address

dht DHT;
int count;
int time2send;
SoftwareSerialLocal wifiPort(10, 11); // RX, TX
void(* resetFunc) (void) = 0;//declare reset function at address 0

char *ftoa(char *a, double f, int precision)
{
  long p[] = {0,10,100,1000,10000,100000,1000000,10000000,100000000};

  char *ret = a;
  long heiltal = (long)f;
  itoa(heiltal, a, 10);
  while (*a != '\0') a++;
  *a++ = '.';
  long desimal = abs((long)((f - heiltal) * p[precision]));
  itoa(desimal, a, 10);
  return ret;
}

void clearScr(){
  for( int i=0;i<50;i++){
    Serial.println("\n");
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  // handle message arrived
  Serial.println("Call back");
  Serial.write(payload, length);
  Serial.println();
}

ESP8266Client esp8266;
PubSubClient client(ardumeteo_server, 1883, callback, esp8266);


void DHT22_Read()
{
	Serial.print("DHT22, \t");
		  int chk = DHT.read22(DHT22_PIN);
		  switch (chk)
		  {
		    case DHTLIB_OK:
				Serial.print("OK,\t");
				break;
		    case DHTLIB_ERROR_CHECKSUM:
				Serial.print("Checksum error,\t");
				break;
		    case DHTLIB_ERROR_TIMEOUT:
				Serial.print("Time out error,\t");
				break;
		    default:
				Serial.print("Unknown error,\t");
				break;
		  }
		  // DISPLAY DATA
		  Serial.print(DHT.humidity, 1);
		  Serial.print(",\t");
		  Serial.println(DHT.temperature, 1);
}

void setup() {
  Serial.begin(9600);
  Serial.println("Starting up");

  //Set Software serial reference to library
  wifiPort.begin(9600);
  esp8266.setSerial( &wifiPort );
  if( esp8266.connectAP(WIFI_SSID,WIFI_PASSWORD) ){
    Serial.println("Connected to Wifi");
  }else{
    Serial.println("Error Connecting to Wifi");
    Serial.println("No need to continue Reset!!!");
    delay(3000);
    count =0;
    clearScr();
    resetFunc();
  }

  time2send=0;
  Serial.println("End Setup");
}
void publishData(SensorsData sensorData,uint16_t sensorMask)
{
	uint16_t i;
	char message_str[40];
	char value_str[8];
	double value_f;
	char topic_str[32];
	if(!sensorMask)
		return;
	sprintf(message_str,"");
	for(i=0x0001;i<0x0100;i=i<<1)
	{
		if(sensorMask & i)
		{
			switch(i)
			{
			case TEMPb:
				value_f = sensorData.temp;
				break;
			case HUMYb:
				value_f = sensorData.humy;
				break;
			case PRESb:
				value_f = sensorData.pres;
				break;
			case WINDb:
				value_f = sensorData.wind;
				break;
			case LUMYb:
				value_f = sensorData.light;
			}
			ftoa(value_str,value_f,1);
			strcat(message_str,value_str);
		}
		else
			strcat(message_str,"0");

		if(i==0x0080)
			strcat(message_str,".");
		else
			strcat(message_str,",");
	}

	sprintf(topic_str,"ARDUMETEO/%s/%04X",ARDUMETEO_USER,sensorMask);
	Serial.println("TOPIC: " + String(topic_str) + "\r\nMESSAGE: " + String(message_str) + "\r\n");
	client.publish(topic_str,message_str);

}

void loop() {

	if(time2send == 0)
	{
		/* -- Insert here the reading routines for you sensors -- */
			DHT22_Read();
			sensorData.temp = DHT.temperature;
			sensorData.humy = DHT.humidity;
			sensorMask = TEMPb | HUMYb;
		/* ------------------------------------------------------ */
		Serial.print("Sending message number " + String(count++) + "\r\n");
		if(client.connect(CLIENT_NAME,ARDUMETEO_USER,MQTT_PASSWORD))
		{
			time2send = SEND_INTERVAL; // resetting sending interval for next send
			Serial.println("Client Connected");

			/* -- Add here a line for every sensor you have data to publish -- */

			publishData(sensorData,sensorMask);

			/* --------------------------------------------------------------- */
			client.loop();
			client.disconnect();
		}
		else
		{
			time2send = 30; //retrying in 30 seconds
			Serial.println("Error connecting to server.");
		}
	}
	else
	{
		if(time2send % 10 == 0)
		{
			Serial.print(time2send);
			Serial.println(" seconds to next send.");
		}
	}

	 delay(1000);
	 time2send--;
}
