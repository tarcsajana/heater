
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

 #define HEATER_POLL_INTERVAL  4000
 
 uint32_t heaterAddr; // Heater address is a 32 bit unsigned int. Use the findAddress() to get your heater's address.
 
 DieselHeaterRF heater;
 heater_state_t state;
 int led = 8;
 void setup() {
 
   Serial.begin(460800);
   Serial.println("Started pairing, press and hold the pairing button on the heater's LCD panel...");
   //heater.begin();
   pinMode(led, OUTPUT);
   
 
   //heaterAddr = heater.findAddress(60000UL);
 
  // if (heaterAddr) {
  //   Serial.print("Got address: ");
  //   Serial.println(heaterAddr, HEX);
  //   heater.setAddress(heaterAddr);
     // Store the address somewhere, eg. NVS
  // } else {
  //   Serial.println("Failed to find a heater");   
  //   while(1) {}
  // }
   
 }
 
 void loop() {
 
   
  digitalWrite(led, HIGH);   // turn the LED on
  delay(1000);   // wait for a second
  digitalWrite(led, LOW);    // turn the LED off
  delay(1000);       
  //heater.sendCommand(HEATER_CMD_WAKEUP);
 
   //if (heater.getState(&state)) {
   //  Serial.printf("State: %d, Power: %d, Voltage: %f, Ambient: %d, Case: %d, Setpoint: %d, PumpFreq: %f, Auto: %d, RSSI: %d\n", state.state, state.power, state.voltage, state.ambientTemp, state.caseTemp, state.setpoint, state.pumpFreq, state.autoMode, state.rssi); 
   //} else {
  //   Serial.println("Failed to get the state");
   //}
   
   //delay(HEATER_POLL_INTERVAL);
 
 }