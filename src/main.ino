
/*
 * 
 *    ESP32 c3        CC1101
 *    -----         ------
 *    20   <-------> GDO2
 *    4  <-------> SCK
 *    3v3 <-------> VCC
 *    6  <-------> MOSI
 *    5  <-------> MISO
 *    2   <-------> CSn
 *    GND <-------> GND
 * 
 */

 #include "DieselHeaterRF.h"
 #include "WiFi.h"
 #include "PubSubClient.h"
 #define HEATER_POLL_INTERVAL  4000
 const char* ssid = "HunorCar";
 const char* password = "Jucymucy8581";
 uint32_t heaterAddr; // Heater address is a 32 bit unsigned int. Use the findAddress() to get your heater's address.
 
 DieselHeaterRF heater;
 heater_state_t state;
 int led = 8;
 WiFiClient wifiClient;
PubSubClient client(wifiClient);
char Gauge;
long lastMsg = 0;
char msg[50];
int value = 0;
const char user[] = "xnjcqaux:xnjcqaux";
const char pass[] = "ZvX_UPUj2x6uOH0T4ZNv3glsL7JrYEZ2";
const char broker[] = "hawk.rmq.cloudamqp.com";
int port = 1883;
const char TOPIC[] = "tele/diesel/temp";
const char TOPIC2[] = "tele/diesel/level";
const char TOPIC3[] = "tele/diesel/state";
const char TOPIC4[] = "tele/diesel/address";
 
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "Diesel-";   // Create a random client ID
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str(), user, pass)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");   // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
 void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}


 void setup() {
 
   Serial.begin(460800);
   delay(1000); 
   initWiFi();
   client.setServer(broker, port);
   Serial.println("Started pairing");
   heater.begin();
   pinMode(led, OUTPUT);
   //heaterAddr = "123456";
 
   heaterAddr = heater.findAddress(60000UL);
 
   if (heaterAddr) {
     Serial.print("Got address: ");
     Serial.println(heaterAddr, HEX);
     heater.setAddress(heaterAddr);
     // Store the address somewhere, eg. NVS
   } else {
     Serial.println("Failed to find a heater");   
     while(1) {}
   }
   
 }
 
 void loop() {
  if (!client.connected()) reconnect(); // check if client is connected
  client.loop();
  digitalWrite(led, HIGH);   // turn the LED on
  delay(1000);   // wait for a second
  digitalWrite(led, LOW);    // turn the LED off
  delay(1000);      
  client.publish(TOPIC4, String(heaterAddr, 0).c_str() );
  client.publish(TOPIC3, String(state.state, 0).c_str() );
  Serial.print("Got address: ");
  Serial.println(heaterAddr, HEX);
  heater.sendCommand(HEATER_CMD_WAKEUP);
 
   if (heater.getState(&state)) {
    Serial.printf("State: %d, Power: %d, Voltage: %f, Ambient: %d, Case: %d, Setpoint: %d, PumpFreq: %f, Auto: %d, RSSI: %d\n", state.state, state.power, state.voltage, state.ambientTemp, state.caseTemp, state.setpoint, state.pumpFreq, state.autoMode, state.rssi); 
   } else {
     Serial.println("Failed to get the state");
   }
   
   delay(HEATER_POLL_INTERVAL);
 
 }
 