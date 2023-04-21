# I2S XIAO_ESP32C3 Example

Some were struggling, did research, here is an example. 

## You Need

- [XIAO ESP32C3 board](https://wiki.seeedstudio.com/XIAO_ESP32C3_Getting_Started/)
- [Adafruit I2S MAX98357A breakout](https://learn.adafruit.com/adafruit-max98357-i2s-class-d-mono-amp/raspberry-pi-wiring)
- [Arduino I2S built-in library](https://docs.arduino.cc/learn/built-in-libraries/i2s)
- [ESP32 I2S API guide](https://docs.espressif.com/projects/arduino-esp32/en/latest/api/i2s.html)
- [ESP32 Arduino boards library by Espressif](https://github.com/espressif/arduino-esp32)

## Wiring

- GND connected GND
- VIN connected 5V
- LRC connected to pin D7 (GPIO20)
- BCLK connected to pin D6 (GPIO21)
- DIN connected to pin D5 (GPIO7)

## Conclusions

This is just how to get I2S working with the setup above. The innovative aspects of a project are up to you.

## License

[WTFPL](http://www.wtfpl.net/) – Do What the F*** You Want to Public License