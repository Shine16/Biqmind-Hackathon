#include <ESP8266WiFi.h> // Enables the ESP8266 to connect to the local network (via WiFi)
#include <PubSubClient.h> // Allows us to connect to, and publish to the MQTT broker

//mosquitto_sub -t plant


//mosquitto_sub -t sensor_data/create
//mosquitto_pub -t test -m '1'


#define BAUD_RATE 9600
const int ledPin = 0; // This code uses the built-in led for visual feedback that the button has been pressed

const char* ssid = "Linksys14645";
const char* wifi_password = "a44tdx6abs";

const char* mqtt_server = "DESKTOP-P53SOTH";//home
const char* mqtt_sub = "water";
const char* mqtt_pub = "plant";
const char* clientID = "plant1";

WiFiClient wifiClient;
PubSubClient client(mqtt_server, 1883, wifiClient); // 1883 is the listener port for the Broker

// These constants won't change. They're used to give names to the pins used:
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
int sensorread;


void callback(char* topic, byte* payload, unsigned int length) {
    Serial.print("Message arrived in topic: "); Serial.println(topic);
    Serial.print("Message:");
    for (int i = 0; i < length; i++) {   Serial.print((char)payload[i]);    }
    Serial.println(); Serial.println("-----------------------");
}




void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(BAUD_RATE);
  WiFi.begin(ssid, wifi_password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);     
  }
  client.setCallback(callback);
  
  if (client.connect(clientID)){ //can without pw
    client.subscribe(mqtt_sub);
    client.publish(mqtt_pub, "Connected!");
   }

     
  pinMode(12,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(16,OUTPUT);
  digitalWrite(12,HIGH);
  digitalWrite(4,LOW);
  digitalWrite(16,LOW);
 
}

void loop() {
    client.loop();//check


  //soil sensor?
   digitalWrite(12,HIGH);
  digitalWrite(4,LOW);
  sensorread=analogRead(analogInPin);
  Serial.println(sensorread);
   delay(500);
/* 
  digitalWrite(12,LOW);
  digitalWrite(4,HIGH);
  //ambience sensor
delay(3000);
 
  sensorread=analogRead(analogInPin);delay(100);
  Serial.println(sensorread);
  Serial.println();
  Serial.println();
  delay(3000);
 */
  
}
