// Getting ID from IMU.

#include <SPI.h>
const int CS = 10;
void setup() {
  Serial.begin(115200); delay(1000); // set baud rate, delay to add padding for connection sanity
  SPI.begin(12, 13, 11, CS); // config wire setup
  pinMode(CS, OUTPUT); digitalWrite(CS, HIGH); // high impedence on cs wire means turn off imu
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE3)); // set rules for conversation (1mhz clock, most sig bit first, standardizing clock edge as per spi conventions)
  digitalWrite(CS, LOW); // start convo w imu
  SPI.transfer(0x0F | 0x80); // read (0x80 is read action) register 0x0F (which contains who am i) -> we pass it in like the left most goes in first etc its like a shift reg
  uint8_t id = SPI.transfer(0x00); // blank bit to have the clock tick a second time to push through the response from the imu on miso
  digitalWrite(CS, HIGH); // end convo w imu
  SPI.endTransaction(); // end convo/transaction and release spi so other devices can work
  Serial.printf("WHO_AM_I = 0x%02X\n", id); // print the answer in hex
}
void loop() {}