#ifndef LOVYANGFX_CONFIG_HPP_
#define LOVYANGFX_CONFIG_HPP_

namespace lgfx
{
// for ESP32
  struct LGFX_Config
  {
// Set the SPI to use with VSPI_HOST or HSPI_HOST.
    static constexpr spi_host_device_t spi_host = VSPI_HOST;

// Set the DMA channel to use with 1 or 2.
// If not used, omit it or set it to 0.
    static constexpr int dma_channel = 1;

// Set the SPI SCLK pin number.
    static constexpr int spi_sclk = 18;

// Set the MOSI pin number of SPI.
    static  constexpr  int spi_mosi = 23 ;

// Set the MISO pin number of SPI.
// Be sure to set MISO when using the SPI bus common to SD cards.
// If not used, omit it or set -1.
    static constexpr int spi_miso = 19;

// Specify the data length of SPI communication.
// Specify 16 when using LCD etc. for Raspberry Pi.
// The default is 8. Most panels are 8, so basically omit them.
    static constexpr int spi_dlen = 8;
  };


/* 
// for SAMD51
  struct LGFX_Config
  {
// Set the SERCOM number of the SPI to be used.
    static constexpr int sercom_index = 7;
// Set the SERCOM clock source.
// If -1 is specified, it will operate without setting the clock source, so please set it separately.
    static constexpr int sercom_clksrc = 0;   // -1=notchange / 0=select GCLK0
// Set the operating frequency of the clock source set above.
// Please set the setting value made by Harmony etc. as it is.
    static constexpr int sercom_clkfreq = 120000000;
// Set the SPI SCLK pin number. PORTA = 0x000 / PORTB = 0x100 / PORTC = 0x200 / PORTD = 0x300…
    static constexpr int spi_sclk = 0x0100 | 20; // PORTB 20 (PORTB=0x0100)
// Set the MOSI pin number of SPI.
    static constexpr int spi_mosi = 0x0100 | 19; // PORTB 19 (PORTB=0x0100)
// Set the MISO pin number of SPI.
    static constexpr int spi_miso = 0x0100 | 18; // PORTB 18 (PORTB=0x0100)
// Set the TX Pad used by SPI.
    static constexpr SercomSpiTXPad pad_mosi = SPI_PAD_3_SCK_1;  // PAD_SPI3_TX;
// Set the RX Pad used by SPI.
    static constexpr SercomRXPad    pad_miso = SERCOM_RX_PAD_2;  // PAD_SPI3_RX;
  };
//*/

}

class LGFX : public lgfx::LGFX_SPI<lgfx::LGFX_Config>
{
// Create an instance of the Panel class. Comment out the class that matches the panel you are using.

//   ★ If the model is compatible with LCD integrated products, you can select from here.
//  lgfx::Panel_DDUINO32_XS panel;
//  lgfx::Panel_LoLinD32 panel;
//  lgfx::Panel_M5Stack panel;
//  lgfx::Panel_M5StickC panel;
//  lgfx::Panel_ODROID_GO panel;
//  lgfx::Panel_TTGO_TS panel;
//  lgfx::Panel_TTGO_TWatch panel;
//  lgfx::Panel_WioTerminal panel;

//   ★ If the model is not compatible, you can select from here.
//  lgfx::Panel_HX8357B panel;
//  lgfx::Panel_HX8357D panel;
//  lgfx::Panel_ILI9163 panel;
//  lgfx::Panel_ILI9341 panel;
  lgfx::Panel_ILI9342 panel;
//  lgfx::Panel_ILI9486 panel;
//  lgfx::Panel_ILI9488 panel;
//  lgfx::Panel_SSD1351 panel;
//  lgfx::Panel_ST7789 panel;
//  lgfx::Panel_ST7735S panel;

public:
  LGFX(void) : lgfx::LGFX_SPI<lgfx::LGFX_Config>()
  {
// Substitute various setting values ​​for the panel class.
// (If you select the panel class for LCD integrated products,
// No    setting is required as the initial value is set according to the product)

// Set the SPI clock during normal operation.
// The ESP32 SPI can only be used with 80MHz divided by an integer.
// The settable value closest to the set value will be used.
    panel.freq_write = 20000000;

// Set the SPI clock for single color fill processing.
// Basically set the same value as freq_write, but
// It may work even if you set a higher value.
    panel.freq_fill  = 27000000;

// Set the SPI clock when reading pixel data from the LCD.
    panel.freq_read  = 16000000;

// Set the SPI communication mode from 0 to 3.
    panel.spi_mode = 0;

// Set the SPI communication mode when reading data from 0 to 3.
    panel.spi_mode_read = 0;

// Set the number of dummy bits when reading pixels.
// Adjust if bit shift occurs when reading pixels.
    panel.len_dummy_read_pixel = 8;

// Set true for panels that can read data, false if not.
// (Example: ST7789 without CS pin cannot be read, so set false.)
// If omitted, it will be true.
    panel.spi_read = true;

// Read data Set true for panels that use MOSI pins.
// (Example: Set true for M5Stack and T-Watch, false for ESP-WROVER-KIT.)
// If omitted, it will be false.
    panel.spi_3wire = false;

// Set the pin number to which the LCD CS is connected.
// If not used, omit it or set -1.
    panel.spi_cs = 14;

// Set the pin number to which the LCD DC is connected.
    panel.spi_dc = 27;

// Set the pin number to which the LCD RST is connected.
// If not used, omit it or set -1.
    panel.gpio_rst = 33;

// Set the pin number to which the LCD backlight is connected.
// If not used, omit it or set -1.
    panel.gpio_bl  = 32;

// When using the backlight, set the PWM channel number used for brightness control.
// If you do not use PWM brightness control, omit it or set it to -1.
    panel.pwm_ch_bl = 7;

// Set whether the output level when the backlight is on is low or high.
// Default is true. Lights up when true = HIGH / Lights up when false = LOW.
    panel.backlight_level = true;

// Set the initial value of invertDisplay. If set to true, it will be inverted.
// If omitted, false. If the screen brightness is reversed, change the setting.
    panel.invert = false;

// Set the color order of the panel. RGB = true / BGR = false
// Default to false. If red and blue are swapped, change the setting.
    panel.rgb_order = false;

// Set the number of pixels (width and height) in the memory of the LCD controller.
// If the settings do not match, the coordinates when using setRotation will shift.
// (Example: ST7735 has 3 types of 132x162 / 128x160 / 132x132)
    panel.memory_width  = 320;
    panel.memory_height = 240;

// Set the number of pixels (width and height) that can actually be displayed on the panel.
// If omitted, the default value of the panel class is used.
    panel.panel_width  = 320;
    panel.panel_height = 240;

// Set the panel offset amount.
// If omitted, the default value of the panel class is used.
    panel.offset_x = 0;
    panel.offset_y = 0;

// Set the value immediately after the initialization of setRotation.
    panel.rotation = 0;

// If you want to change the orientation when using setRotation, set offset_rotation.
// Set 1 if you want the orientation in setRotation (0) to be the orientation of 1.
    panel.offset_rotation = 0;



// Finally, set the prepared panel settings.
    setPanel(&panel);
  }
};

#endif