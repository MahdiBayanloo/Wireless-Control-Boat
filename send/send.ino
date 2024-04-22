/*
* Arduino Wireless Communication Tutorial
*     Example 2 - Transmitter Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
* 
*/
#include <SoftwareSerial.h>
#include <Wire.h>
//#include <SPI.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (A4 = SDA, A5 = SCL)
// Reset pin # (or -1 if sharing Arduino reset pin)
#define OLED_RESET     4
//See datasheet for Address
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);



#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


RF24 radio(9, 10); // CE, CSN
const byte addresses[][6] = {"00001", "00002"};
int batlevel = 0;

void setup() {
  //Begin serial communication with Serial Monitor
  Serial.begin(115200);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();

  
  pinMode(12, OUTPUT);
  radio.begin();
  radio.openWritingPipe(addresses[1]); // 00002
  radio.openReadingPipe(1, addresses[0]); // 00001
  radio.setPALevel(RF24_PA_MIN);
}

void loop() {
  delay(5);

  radio.stopListening();
  int potValue = analogRead(A0);
  
  int angleValue = map(potValue, 0, 1023, 0, 255);
  radio.write(&angleValue, sizeof(angleValue));

  delay(5);
  radio.startListening();
  while (!radio.available());
  radio.read(&batlevel, sizeof(batlevel));
  display_battery();
  //delay(1000);
}



void display_battery()
{
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(20, 0);
  display.print("Bat:");
  display.print(batlevel);
  display.print("%");
  display.drawRect(14, 20, 80, 40, WHITE);
  display.drawRect(94, 30, 10, 20, WHITE);
  display.fillRect(14, 20, (int)(8 * (batlevel) / 10), 40, WHITE);
  display.display();
  delay(2000);
}
