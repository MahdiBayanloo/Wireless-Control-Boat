#include <Battery.h>

Battery battery(3400, 4200, A0);
/**
 * 1 cell li-ion/li-poly battery wired to A0 before voltage booster, on demand sensing on pin 3, linear mapping function
 * https://github.com/rlogiacco/BatterySense#lesser-than-5v-with-voltage-booster
 **/
void setup() {
  Serial.begin(9600);
  while (!Serial);
  battery.begin(5000, 1.0);
}

void loop() {

  Serial.print("Battery voltage is ");
  Serial.print(battery.voltage());
  Serial.print(" (");
  Serial.print(battery.level());
  Serial.println("%)");
  delay(1000);
}
