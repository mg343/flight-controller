// Getting ID from IMU.
// Started by soldering header pins to IMU and ESP, and then wired IMU->ESP to enable SPI communication protocol.
// Needed power (supply, ground):
//     voltage in; VIN->3V3
//     ground; GND->GND
// SPI follows 4 wires, which we can assign to semi-arbitrary pins on the ESP (we will have to specifiy which is which on boot):
//     clock (syncing the signals, each board has a shift register composed of d flipflops - fundies clock / typically SCK); SCL->12
//     master out slave in (bits from esp to imu / MOSI); SDA->11
//     master in slave out (bits from imu to esp / MISO); SDO->13
//     chip select (orchestrates )
// ESP had a default factory demo of printing out RGB at 115200, changed sampling rate on the Arduino IDE to match and read

#include <SPI.h>
const int CS = 10;
void setup() {
  Serial.begin(115200); delay(1000);
  SPI.begin(12, 13, 11, CS);
  pinMode(CS, OUTPUT); digitalWrite(CS, HIGH);
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE3));
  digitalWrite(CS, LOW);
  SPI.transfer(0x0F | 0x80);
  uint8_t id = SPI.transfer(0x00);
  digitalWrite(CS, HIGH);
  SPI.endTransaction();
  Serial.printf("WHO_AM_I = 0x%02X\n", id);
}
void loop() {}