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


int batlevel = 50;

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
}

void loop() {

display_battery();
  
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
