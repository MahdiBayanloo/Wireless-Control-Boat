/*
* Arduino Wireless Communication Tutorial
*     Example 2 - Receiver Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Battery.h>


Battery battery(3400, 4200, A0);


RF24 radio(9, 10); // CE, CSN
const byte addresses[][6] = {"00001", "00002"};
boolean buttonState = 0;

int led = 3;           // the PWM pin the LED is attached to

void setup() {
  Serial.begin(9600);
  while (!Serial);
  battery.begin(5000, 1.0);

  pinMode(led, OUTPUT);
  radio.begin();
  radio.openWritingPipe(addresses[0]); // 00001
  radio.openReadingPipe(1, addresses[1]); // 00002
  radio.setPALevel(RF24_PA_MIN);
}

void loop() {
  delay(5);
  radio.startListening();
  if ( radio.available()) {
    while (radio.available()) {
      int angleV = 0;
      radio.read(&angleV, sizeof(angleV));
      //Serial.println(angleV);
      analogWrite(led, angleV);
    }
    delay(5);
    radio.stopListening();
    int batlevel = battery.level();
    radio.write(&batlevel, sizeof(batlevel));
 }
}
