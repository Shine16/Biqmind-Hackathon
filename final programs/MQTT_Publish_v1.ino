//#include <Esplora.h>

/*
 * ESP8266 (Adafruit HUZZAH) Mosquitto MQTT Publish Example
 * Thomas Varnish (https://github.com/tvarnish), (https://www.instructables.com/member/Tango172)
 * Made as part of my MQTT Instructable - "How to use MQTT with the Raspberry Pi and ESP8266"
 */
#include <ESP8266WiFi.h> // Enables the ESP8266 to connect to the local network (via WiFi)
#include <PubSubClient.h> // Allows us to connect to, and publish to the MQTT broker

const int moistureSen = 14;   //moisture sensor pin (0 = wet, 1 = dry)
const int RelayOut = 12;   //relay output pin
const int lightSen_OutEnable = 4; //enable light sensor output enable pin
const int lightSen = 0;       //ADC input pin for light sensing

const char* ssid = "biqmind-users";
const char* wifi_password = "\"WE ARE A STRONG TEAM OF RND\"";

const char* mqtt_server = "192.168.5.11";     //mqtt server
const char* mqtt_topic = "test";
const char* time_topic="test/time";
const char* pumpOn_topic ="test/pumpOn";
const char* light_topic = "test/light";  //pub adc values
const_char* humidity_topic =" test/dry"; //pub 0 = wet or 1 = dry

// The client id identifies the ESP8266 device. Think of it a bit like a hostname (Or just a name, like Greg).
const char* clientID = "BiqBenser 1";

// Initialise the WiFi and MQTT Client objects
WiFiClient wifiClient;
PubSubClient client(mqtt_server, 1883, wifiClient); // 1883 is the listener port for the Broker

void setup() {

   pinMode(lightSen_OutEnable,OUTPUT);// eanble ambient light sensor ALWAYS
   pinMode(RelayOut,OUTPUT); //relay for motor
   pinMode(moistureSen,INPUT); // comparator from moisture sensor

  // Begin Serial on 115200
  // Remember to choose the correct Baudrate on the Serial monitor!
  // This is just for debugging purposes
  Serial.begin(115200);

  Serial.print("Connecting to ");
  Serial.println(ssid);

  // Connect to the WiFi
  WiFi.begin(ssid, wifi_password);

  // Wait until the connection has been confirmed before continuing
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Debugging - Output the IP Address of the ESP8266
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Connect to MQTT Broker
  // client.connect returns a boolean value to let us know if the connection was successful.
  // If the connection is failing, make sure you are using the correct MQTT Username and Password (Setup Earlier in the Instructable)
  if (client.connect(clientID)) {
    Serial.println("Connected to MQTT Broker!");
    client.subscribe(light_topic);
        client.subscribe(light_topic);
            client.subscribe(light_topic);
  }
  else {
    Serial.println("Connection to MQTT Broker failed...");
  }
  
}

void waterPlant()
{
  digitalWrite(RelayOut,HIGH);
  delay(1000);
  digitalWrite(RelayOut,LOW);
}

int readLightSen()
{
  int val = analogRead(lightSen);
  Serial.println(val);
  return(val);
}

int readMoisture()
{
  int val = digitalRead(moistureSen);
  Serial.println(val);
  return(val);
}

// callback function when MQTT received, check for specific topic and react
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void loop() {

/*
    // PUBLISH to the MQTT Broker (topic = mqtt_topic, defined at the beginning)
    // Here, "Button pressed!" is the Payload, but this could be changed to a sensor reading, for example.
    if (client.publish(mqtt_topic, "BiqBenser is up BRO!")) {
      Serial.println("message sent");
    }
    // Again, client.publish will return a boolean value depending on whether it succeded or not.
    // If the message failed to send, we will try again, as the connection may have broken.
    else {
      Serial.println("Message failed to send. Reconnecting to MQTT Broker and trying again");
      client.connect(clientID);
      delay(10); // This delay ensures that client.publish doesn't clash with the client.connect call
      client.publish(mqtt_topic, "finally connected!!");
    }
     delay(1000);

*/
  readLightSen();
  readMoisture();
  client.loop();

}

void test(){
digitalWrite(4,HIGH);//power on light sensor  
Serial.println(analogRead(0));//light sensor
digitalWrite(12,HIGH);
delay(1000);
digitalWrite(12,LOW);
delay(1000);
Serial.println(digitalRead(14));
Serial.println();


}

