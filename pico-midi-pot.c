#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include "pico/binary_info.h"

#include "bsp/board.h"
#include "tusb.h"

enum  {
  BLINK_NOT_MOUNTED = 250,
  BLINK_MOUNTED = 1000,
  BLINK_SUSPENDED = 2500,
};

static uint32_t blink_interval_ms = BLINK_NOT_MOUNTED;
const uint LED_PIN = PICO_DEFAULT_LED_PIN;

void led_blinking_task(void);
void midi_task(void);

int prevValue = 0;

int main() {
  board_init();

  tusb_init();

  stdio_init_all();

  adc_init();

  adc_gpio_init(26);
  adc_select_input(0);

  while (1)
  {
    tud_task(); // tinyusb device task
    led_blinking_task();
    midi_task();
  }
}

//--------------------------------------------------------------------+
// Device callbacks
//--------------------------------------------------------------------+

// Invoked when device is mounted
void tud_mount_cb(void)
{
  blink_interval_ms = BLINK_MOUNTED;
}

// Invoked when device is unmounted
void tud_umount_cb(void)
{
  blink_interval_ms = BLINK_NOT_MOUNTED;
}

// Invoked when usb bus is suspended
// remote_wakeup_en : if host allow us  to perform remote wakeup
// Within 7ms, device must draw an average of current less than 2.5 mA from bus
void tud_suspend_cb(bool remote_wakeup_en)
{
  (void) remote_wakeup_en;
  blink_interval_ms = BLINK_SUSPENDED;
}

// Invoked when usb bus is resumed
void tud_resume_cb(void)
{
  blink_interval_ms = BLINK_MOUNTED;
}

//--------------------------------------------------------------------+
// MIDI Task
//--------------------------------------------------------------------+

void midi_task(void)
{
  static uint32_t start_ms = 0;

  // throttle CCs
  if (board_millis() - start_ms < 10) return; // not enough time
  start_ms += 10;

  uint16_t result = adc_read(); // 12 bit result
  int output = result >> 5; // 7 bit CC value

  if(output == prevValue) {
    return;
  }

  // Send CC on jack 0 for controller 32, output value the 7-bit version of the pot.
  tudi_midi_write24(0, 0xB0, 32, output);
  prevValue = output;
}

//--------------------------------------------------------------------+
// BLINKING TASK
//--------------------------------------------------------------------+
void led_blinking_task(void)
{
  static uint32_t start_ms = 0;
  static bool led_state = false;

  // Blink every interval ms
  if ( board_millis() - start_ms < blink_interval_ms) return; // not enough time
  start_ms += blink_interval_ms;

  board_led_write(led_state);
  led_state = 1 - led_state; // toggle
}
