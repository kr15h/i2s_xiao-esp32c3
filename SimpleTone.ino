/*
 This example generates a square wave based tone at a specified frequency
 and sample rate. Then outputs the data using the I2S interface to a
 MAX08357 I2S Amp Breakout board.

 I2S Circuit:
 * XIAO ESP32C3 (https://docs.espressif.com/projects/arduino-esp32/en/latest/api/i2s.html)
 * MAX08357:
   * GND connected GND
   * VIN connected 5V
   * LRC connected to pin D7 (GPIO20)
   * BCLK connected to pin D6 (GPIO21)
   * DIN connected to pin D5 (GPIO7)

 created 17 November 2016
 by Sandeep Mistry
 For ESP extended
 Tomas Pilny
 2nd September 2021
 For XIAO ESP32C3
 Krisjanis Rijnieks
 21 April 2023
 */

#include <I2S.h>
const int frequency = 440; // frequency of square wave in Hz
const int amplitude = 500; // amplitude of square wave
const int sampleRate = 8000; // sample rate in Hz
const int bps = 16;

const int halfWavelength = (sampleRate / frequency); // half wavelength of square wave

int32_t sample = amplitude; // current sample value
int count = 0;

i2s_mode_t mode = I2S_PHILIPS_MODE; // I2S decoder is needed
// i2s_mode_t mode = ADC_DAC_MODE; // Audio amplifier is needed

// Mono channel input
// This is ESP specific implementation -
//   samples will be automatically copied to both channels inside I2S driver
//   If you want to have true mono output use I2S_PHILIPS_MODE and interlay
//   second channel with 0-value samples.
//   The order of channels is RIGH followed by LEFT
//i2s_mode_t mode = I2S_RIGHT_JUSTIFIED_MODE; // I2S decoder is needed

void setup() {

  Serial.begin(115200);
  Serial.println("I2S simple tone");

  if (!I2S.setDataPin(D5)) {
    Serial.println("failed to set DATA, DATA OUT pin");
  }

  if (!I2S.setSckPin(D6)) {
    Serial.println("Failed to set SCK pin");
  }

  if (!I2S.setFsPin(D7)) {
    Serial.println("Failed to set FRAME SELECT pin");
  }

  if (!I2S.setSimplex()) {
    Serial.println("Failed to enter SIMPLEX mode");
  }

  // start I2S at the sample rate with 16-bits per sample
  if (!I2S.begin(mode, sampleRate, bps)) {
    Serial.println("Failed to initialize I2S!");
    while (1); // do nothing
  }
}

void loop() {
    if (count % halfWavelength == 0 ) {
      // invert the sample every half wavelength count multiple to generate square wave
      sample = -1 * sample;
    }

    if(mode == I2S_PHILIPS_MODE || mode == ADC_DAC_MODE){ // write the same sample twice, once for Right and once for Left channel
      I2S.write(sample); // Right channel
      I2S.write(sample); // Left channel
    }else if(mode == I2S_RIGHT_JUSTIFIED_MODE || mode == I2S_LEFT_JUSTIFIED_MODE){
      // write the same only once - it will be automatically copied to the other channel
      I2S.write(sample);
    }

    // increment the counter for the next sample
    count++;
}
