
 

#include <ESP8266WiFi.h> // Enables the ESP8266 to connect to the local network (via WiFi)
#include <PubSubClient.h> // Allows us to connect to, and publish to the MQTT broker
 

const int moistureSen = 14;   //moisture sensor pin (0 = wet, 1 = dry)
const int RelayOut = 12;   //relay output pin
const int lightSen_OutEnable = 4; //enable light sensor output enable pin
const int lightSen = 0;       //ADC input pin for light sensing



#define BAUD_RATE 9600

 

const int ledPin = 0; // This code uses the built-in led for visual feedback that the button has been pressed


// WiFi
// Make sure to update this for your own WiFi network!
const char* ssid = "biqmind-users";
const char* wifi_password = "\"WE ARE A STRONG TEAM OF RND\"";

//const char* mqtt_server = "DESKTOP-P53SOTH"; 
const char* mqtt_server = "192.168.5.11";     //mqtt server
const char* mqtt_topic = "test";
const char* time_topic = "MQTT-test";
const char* pumpOn_topic = "MQTT-test";
const char* humid_topic = "sensor_data/create";    /*pub 0 = wet or 1 = dry */
const char* light_topic = "sensor_data/create";    /* pub adc values */
const char* clientID = "BiqBenser 1";

// Initialise the WiFi and MQTT Client objects
WiFiClient wifiClient;
PubSubClient client(mqtt_server, 1883, wifiClient); // 1883 is the listener port for the Broker

void callback(char* topic, byte* payload, unsigned int length) {
 
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);

  
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
     
  }
  
  waterPlant();
  Serial.println();
  Serial.println("-----------------------");


    
}

 
void setup() {
 
  // Begin Serial on 115200
  // Remember to choose the correct Baudrate on the Serial monitor!
  // This is just for debugging purposes
  Serial.begin(115200);

   pinMode(lightSen_OutEnable,OUTPUT);// eanble ambient light sensor ALWAYS
   pinMode(RelayOut,OUTPUT); //relay for motor
   pinMode(moistureSen,INPUT); // comparator from moisture sensor



  //Later get ssid and password from arduino!
  // Connect to the WiFi
  WiFi.begin(ssid, wifi_password);

  //feedback to arduino!
  // Wait until the connection has been confirmed before continuing
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

   //feedback to arduino!
   // Debugging - Output the IP Address of the ESP8266
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  
  //client.setServer(mqttServer, mqttPort);????
  client.setCallback(callback);

 
  if (client.connect(clientID)) {
    Serial.println("Connected to MQTT Broker!");
    client.subscribe(pumpOn_topic);
    client.subscribe(mqtt_topic);
    client.publish(mqtt_topic, "finally connected!!");
    
  }
  else {
    Serial.println("Connection to MQTT Broker failed...");
  }

  
 
 // client.subscribe(mqtt_topic);
 
}
 
void loop() {
  client.loop();
  delay(1000);
  /*if(readMoisture()==1){
   if (client.publish(humid_topic, "1")) {
      Serial.println("message sent humid 1");
    }
    // Again, client.publish will return a boolean value depending on whether it succeded or not.
    // If the message failed to send, we will try again, as the connection may have broken.
    else {
      Serial.println("Message failed to send. Reconnecting to MQTT Broker and trying again");
      client.connect(clientID);
      client.subscribe(pumpOn_topic);
      delay(10); // This delay ensures that client.publish doesn't clash with the client.connect call
      client.publish(humid_topic, "1");
    }
  }
  else{
      if(client.publish(humid_topic, "0") )
      Serial.println("message sent humid 0");
    
    // Again, client.publish will return a boolean value depending on whether it succeded or not.
    // If the message failed to send, we will try again, as the connection may have broken.
    else {
      Serial.println("Message failed to send. Reconnecting to MQTT Broker and trying again");
      client.connect(clientID);
      client.subscribe(pumpOn_topic);
      delay(10); // This delay ensures that client.publish doesn't clash with the client.connect call
      client.publish(humid_topic, "0");
    }
  }*/
  test();
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
  Serial.println("Light = ");
  Serial.println(val);
  return(val);
}

int readMoisture()
{
  int val = digitalRead(moistureSen);
  Serial.println("Humid = ");
  Serial.println(val);
  return(val);
}


//HW test code
void test(){
    digitalWrite(4,HIGH);//power on light sensor  
    Serial.println(analogRead(0));//light sensor
        Serial.println(digitalRead(14));
    Serial.println();
    digitalWrite(12,HIGH);
    delay(1000);
    digitalWrite(12,LOW);
    delay(1000);


}

