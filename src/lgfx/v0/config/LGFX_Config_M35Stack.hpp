#ifndef LOVYANGFX_CONFIG_HPP_
#define LOVYANGFX_CONFIG_HPP_

namespace lgfx
{
  struct LGFX_Config
  {
    static constexpr spi_host_device_t spi_host = VSPI_HOST;
    static constexpr int dma_channel = 1;
    static constexpr int spi_mosi = 23;
    static constexpr int spi_miso = 19;
    static constexpr int spi_sclk = 18;
  };
}

class LGFX : public lgfx::LGFX_SPI<lgfx::LGFX_Config>
{
  struct Panel_default : public lgfx::Panel_ILI9488
  {
    Panel_default(void) {
      spi_3wire = false;
      spi_cs   = 5;
      spi_dc   = 32;
      gpio_rst = 0;
      gpio_bl  = -1;
      pwm_ch_bl = -1;
      freq_write = 40000000;
      freq_read  = 16000000;
      freq_fill  = 40000000;
      backlight_level = false;
    }
  };

public:

  LGFX(void) : lgfx::LGFX_SPI<lgfx::LGFX_Config>()
  {
    static Panel_default panel;

    setPanel(&panel);
  }

};

#endif
