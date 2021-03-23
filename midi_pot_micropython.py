import analogio
import board
import digitalio
import time

import usb_midi
import adafruit_midi
from adafruit_midi.control_change import ControlChange

led = digitalio.DigitalInOut(board.LED)
led.direction = digitalio.Direction.OUTPUT

pot = analogio.AnalogIn(board.GP26)

cc_value = 0

midi = adafruit_midi.MIDI(midi_out=usb_midi.ports[1], out_channel=0)

# see https://learn.adafruit.com/grand-central-usb-midi-controller-in-circuitpython/code-usb-midi-in-circuitpython
# for a nice hysteresis function

while True:
    led.value = 1
    # potentiometer.value is between 0 and 1 << 16 so we could >> it by 9 to scale it to MIDI
    new_value = pot.value >> 9
    if (cc_value != new_value):
        cc_value = new_value
        midi.send(ControlChange(32, cc_value))
        led.value = 0

    time.sleep(0.01)