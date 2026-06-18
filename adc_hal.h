#pragma once

#include <esp_adc/adc_oneshot.h>

#ifdef __cplusplus
extern "C" {
#endif

static bool adc_oneshot_create_unit(adc_unit_t unit,
                                    adc_oneshot_unit_handle_t* handle) {
  adc_oneshot_unit_init_cfg_t config = {
      .unit_id = unit,
      .clk_src = ADC_RTC_CLK_SRC_DEFAULT,
  };
  return adc_oneshot_new_unit(&config, handle) == ESP_OK;
}

static bool adc_oneshot_configure(adc_oneshot_unit_handle_t handle,
                                  adc_channel_t channel,
                                  adc_bitwidth_t bitwidth,
                                  adc_atten_t attenuation) {
  adc_oneshot_chan_cfg_t config = {
      .bitwidth = bitwidth,
      .atten = attenuation,
  };
  return adc_oneshot_config_channel(handle, channel, &config) == ESP_OK;
}

static bool adc_oneshot_destroy_unit(adc_oneshot_unit_handle_t handle) {
  return adc_oneshot_del_unit(handle) == ESP_OK;
}

static bool adb_oneshot_read_value(adc_oneshot_unit_handle_t handle,
                                   adc_channel_t channel, int* out_value) {
  return adc_oneshot_read(handle, channel, out_value) == ESP_OK;
}

#ifdef __cplusplus
}
#endif
