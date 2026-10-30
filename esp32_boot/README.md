# Boot Documentation

Started by soldering header pins to IMU and ESP, and then wired IMU->ESP to enable SPI communication protocol.
Needed power (supply, ground):
    voltage in; VIN->3V3
    ground; GND->GND
SPI follows 4 wires, which we can assign to semi-arbitrary pins on the ESP (we will have to specifiy which is which on boot):
    clock (syncing the signals, each board has a shift register composed of d flipflops - fundies clock / typically SCK); SCL->12
    master out slave in (bits from esp to imu / MOSI); SDA->11
    master in slave out (bits from imu to esp / MISO); SDO->13
    chip select (picks which device (IMU/radio/etc) is listening to instructions/acting like off so the other can be used); CS->10
ESP has a default factory demo of printing out RGB at 115200 baud rate, changed sampling rate on the Arduino IDE to match and read
Once all of this was working, ran boot.ino to test that the IMU could be seen and
