#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <driver/spi_master.h>
#include <esp_err.h>
#include <hal/spi_types.h>
#include <string.h>

static bool spi_init(spi_host_device_t host, uint8_t mosi, uint8_t sclk) {
  spi_bus_config_t bus_config = {
      .sclk_io_num = sclk,
      .mosi_io_num = mosi,
      .miso_io_num = -1,
      .quadwp_io_num = -1,
      .quadhd_io_num = -1,
      .max_transfer_sz = 0,
      .flags = SPICOMMON_BUSFLAG_SLAVE,
  };

  return spi_bus_initialize(host, &bus_config, SPI_DMA_CH_AUTO) == ESP_OK;
}

static bool spi_add_device(spi_device_handle_t* handle, spi_host_device_t host,
                           const int8_t cs, const int freq) {
  spi_device_interface_config_t dev_config;
  memset(&dev_config, 0, sizeof(dev_config));

  dev_config.clock_speed_hz = freq;
  dev_config.queue_size = 7;
  dev_config.mode = 3;
  dev_config.flags = SPI_DEVICE_NO_DUMMY;

  dev_config.spics_io_num = cs >= 0 ? cs : -1;

  return spi_bus_add_device(host, &dev_config, handle) == ESP_OK;
}

#ifdef __cplusplus
}
#endif