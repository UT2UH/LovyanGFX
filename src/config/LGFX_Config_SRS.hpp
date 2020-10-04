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

  struct Panel_SRS : public Panel_ILI9341
  {
    Panel_SRS(void) {
      freq_write = 40000000;
      freq_read  = 20000000;
      freq_fill  = 80000000;
      spi_3wire = true;
      spi_cs =  32;
      spi_dc = 27;
      rotation = 1;
      gpio_rst = 33;
      gpio_bl = -1;
      pwm_ch_bl = 7;
    }
  };
}

class LGFX : public lgfx::LGFX_SPI<lgfx::LGFX_Config>
{
public:
  LGFX(void) : lgfx::LGFX_SPI<lgfx::LGFX_Config>()
  {
    static lgfx::Panel_SRS panel;

    setPanel(&panel);
  }
};

#endif
