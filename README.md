# Raspberry Pi Pico: MIDI CC pot.

Connect a pot as a voltage divider to pin 26 of a Raspberry Pi Pico. This script will map it to MIDI continuous controller 32, MIDI channel 1, of the Pico Demo Device device.

It uses a highly similar CMake configuration to the [Raspberry Pi Examples][examples], so should be compilable in a very similar way: I'm just cribbing from the ["Getting started with Raspberry Pi Pico" document][picostart].


## Compilation

You'll need the [Pico SDK][picosdk] installed and its path available as the environment variable `PICO_SDK_PATH`. You'll also require CMake, `arm-none-eabi-gcc`, etc, as per the Pico SDK documentation. Then, from a checkout of this repository:

```
mkdir build
cd build
cmake ..
build pico-midi-pot
```

## Installation

Compliation should generate, in the `build` directory, a `pico-midi-pot.uf2` artefact.

Hokd down the BOOTSEL button on your Pico before you connect it to your computer over USB; then, plug in the USB lead holding down BOOTSEL. RPI-RP2 should appear on your computer as a drive. Copy `pico-midi-pot.uf2` to this drive; it will flash the microcontroller, and immediately unmount,

## Usage

Voltages between 0 and 3.3V entering pin 26 (ie, ADC pin 0) will be mapped to 0-127 on midi continuous controller 32.

## CircuitPython equivalent

A CircuitPython equivalent, using the [Adafruit CircuitPython MIDI library][cpmidi], is included as `midi_pot_micropython.py`. This is primarily included to make comparison between the C++ and Python options easier.


[picosdk]: https://github.com/raspberrypi/pico-sdk
[examples]: https://github.com/raspberrypi/pico-examples/
[picostart]: https://datasheets.raspberrypi.org/pico/getting-started-with-pico.pdf
[circuitpython]: https://circuitpython.org
[cpmidi]: https://github.com/adafruit/Adafruit_CircuitPython_MIDI
