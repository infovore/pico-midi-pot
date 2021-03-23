# Raspberry Pi Pico: MIDI CC pot.

Connect a pot as a voltage divider to pin 26 of a Raspberry Pi Pico. This script will map it to MIDI continuous controller 32, MIDI channel 1, of the Pico Demo Device device.

It uses a highly similar CMake configuration to the [Raspberry Pi Examples][examples], so should be compilable in a very similar way: I'm just cribbing from the ["Getting started with Raspberry Pi Pico" document][picostart].

[examples]: https://github.com/raspberrypi/pico-examples/
[picostart]: https://datasheets.raspberrypi.org/pico/getting-started-with-pico.pdf
