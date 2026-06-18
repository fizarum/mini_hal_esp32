## minimalistic HAL for esp32
This is a small collection of utils to simplify usage of some peripheral. Its very small at this moment and will by updated & expanded in future.

### ADC (oneshot)
First, you have to create adc unit, this can be done by __adc_oneshot_create_unit()__. Now, you can configure adc channel by __adc_oneshot_configure()__. Note, you can have several adc channels on same unit. In such case you have to call once __adc_oneshot_create_unit()__ and __adc_oneshot_configure()__ for each channel.
And, finally, to read value from adc channels call: __adb_oneshot_read_value()__

When you completed with adc and resources can be released call: __adc_oneshot_destroy_unit()__

Note! You can check info about adc units and channels in datasheet, for esp32 its: https://documentation.espressif.com/esp32_datasheet_en.pdf (page 70, IO_MUX table)

Here is an example with 2 channels (x & y coords in joystick):

```c
#include "adc_hal.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"

// for x (GPIO_25): ADC2_CH8
// for y (GPIO_26): ADC2_CH9
#define ADC_XY_UNIT ADC_UNIT_2
#define ADC_X_CHAN ADC_CHANNEL_8
#define ADC_Y_CHAN ADC_CHANNEL_9

adc_oneshot_unit_handle_t adc_unit_handle_xy;
int x, y;

void app_main() {
  adc_oneshot_create_unit(ADC_XY_UNIT, &adc_unit_handle_xy);

  // configure adc channels for x & y
  adc_oneshot_configure(adc_unit_handle_xy, ADC_X_CHAN, ADC_BITWIDTH_DEFAULT,
                        ADC_ATTEN_DB_12);

  adc_oneshot_configure(adc_unit_handle_xy, ADC_Y_CHAN, ADC_BITWIDTH_DEFAULT,
                        ADC_ATTEN_DB_12);

  while (1) {
    adb_oneshot_read_value(adc_unit_handle_xy, ADC_X_CHAN, &x);
    adb_oneshot_read_value(adc_unit_handle_xy, ADC_Y_CHAN, &y);

    ESP_LOGI("TAG", "%d x %d", x, y);

    vTaskDelay(pdMS_TO_TICKS(20));
  }

  // cleanup adc handle
  adc_oneshot_destroy_unit(adc_unit_handle_xy);
}
```