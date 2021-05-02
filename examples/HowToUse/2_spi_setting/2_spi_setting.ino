// How to set up the SPI with LovyanGFX
// How to use with LovyanGFX SPI bus and panel settings


#include <LovyanGFX.hpp>

// Create a structure for SPI configuration
// Create a structure for SPI configuration.

// for ESP32 SPI
struct LGFX_Config
{
// You can change the name of the structure from "LGFX_Config"
// But do not change the name and type of the members.
// You can change the structure name "LGFX_Config",
// Make the name and type of each member variable of the structure as in the example.

  // Select the type of SPI  (VSPI_HOST or HSPI_HOST)
  // Set the SPI to use with VSPI_HOST or HSPI_HOST.
  static constexpr spi_host_device_t spi_host = VSPI_HOST;

  // Set the DMA channel number (1 or 2)
  // If you don't want to use DMA, omit it or set it to 0.
  // Set the DMA channel to use with 1 or 2.
  // If not used, omit it or set it to 0.
  static constexpr int dma_channel = 1;

  // Set the SPI SCLK pin number
  // Set the SPI SCLK pin number.
  static constexpr int spi_sclk = 18;

  // Set the SPI MOSI pin number
  // Set the MOSI pin number of SPI.
  static  constexpr  int spi_mosi = 23 ;

  // Set the SPI MISO pin number
  // If you share the SPI bus with an SD card, be sure to set up MISO as well.
  // If you don't want to use MISO, omit it or set it to -1.
  // Set the MISO pin number of SPI.
  // When using the SPI bus common to SD cards, etc., be sure to set MISO as well.
  // If not used, omit it or set -1.
  static constexpr int spi_miso = 19;

  // Set the data length of SPI communication.
  // If you want to use the LCD for RPi, set it to 16.
  // Specify the data length of SPI communication.
  // Specify 16 when using LCD etc. for Raspberry Pi.
  // The default is 8. Most panels are 8, so basically omit them.
  static constexpr int spi_dlen = 8;
};

/* for ESP32 Parallel
struct LGFX_Config
{
  // Select the type of I2S  (I2S_NUM_0 or I2S_NUM_1)
  // Set the I2S to use with I2S_NUM_0 or I2S_NUM_1.
  // The default is I2S_NUM_0.
  static constexpr i2s_port_t i2s_port = I2S_NUM_0;
  // Set the parallel pin number
  // Set various pin numbers for parallel connection.
  static constexpr int gpio_wr  =  4;
  static constexpr int gpio_rd  =  2;
  static constexpr int gpio_rs  = 15;
  static constexpr int gpio_d0  = 12;
  static constexpr int gpio_d1  = 13;
  static constexpr int gpio_d2  = 26;
  static constexpr int gpio_d3  = 25;
  static constexpr int gpio_d4  = 17;
  static constexpr int gpio_d5  = 16;
  static constexpr int gpio_d6  = 27;
  static constexpr int gpio_d7  = 14;
};
//*/
/* 
// for SAMD51 SPI
struct LGFX_Config
{
// Set the SERCOM number of the SPI to be used.
  static constexpr int sercom_index = 5;
// Set the SERCOM clock source.
// If -1 is specified, it will operate without setting the clock source, so please set it separately.
  static constexpr int sercom_clksrc = 0;   // -1=notchange / 0=select GCLK0
// Set the operating frequency of the clock source set above.
// Please set the setting value made by Harmony etc. as it is.
//static constexpr int sercom_clkfreq = 120000000;
  static constexpr int sercom_clkfreq = F_CPU; // In the Seeeduino environment, the CPU clock value can be used with the F_CPU constant.
// Set the pin number on SAMD51 with the port + pin number of SAMD51, not the number for Arduino.
// Set the SPI SCLK pin number. PORTA = 0x000 / PORTB = 0x100 / PORTC = 0x200 / PORTD = 0x300…
  static constexpr int spi_sclk = 0x0100 | 3; // PORTB 3 (PORTB=0x0100)
// Set the MOSI pin number of SPI.
  static constexpr int spi_mosi = 0x0100 | 2; // PORTB 2 (PORTB=0x0100)
// Set the MISO pin number of SPI.
  static constexpr int spi_miso = 0x0100 | 0; // PORTB 0 (PORTB=0x0100)
// Set the TX Pad used by SPI.
  static constexpr SercomSpiTXPad pad_mosi = SPI_PAD_0_SCK_1;  // PAD_SPI0_TX;
// Set the RX Pad used by SPI.
  static constexpr SercomRXPad    pad_miso = SERCOM_RX_PAD_2;  // PAD_SPI0_RX;
  // Specify the data length of SPI communication.
  // Specify 16 when using LCD etc. for Raspberry Pi.
  // The default is 8. Most panels are 8, so basically omit them.
  static constexpr int spi_dlen = 8;
};
//*/

// Create an LGFX_SPI instance with the configuration structure you just created as a template argument.
// Set the prepared configuration structure in the LGFX_SPI class as a template argument and create an instance.
// Use the LGFX_PARALLEL class for parallel connections.
static lgfx::LGFX_SPI<LGFX_Config> lcd;
//static lgfx::LGFX_PARALLEL<LGFX_Config> lcd;


// Create an instance of the Panel class. Comment out the description of the panel you want to use.
// Create an instance of the Panel class. Comment out the description that matches the panel you are using.
//static lgfx::Panel_HX8357B panel;
//static lgfx::Panel_HX8357D panel;
//static lgfx::Panel_ILI9163 panel;
//static lgfx::Panel_ILI9341 panel;
static lgfx::Panel_ILI9342 panel;
//static lgfx::Panel_ILI9486 panel;
//static lgfx::Panel_ILI9486L panel;
//static lgfx::Panel_ILI9488 panel;
//static lgfx::Panel_SSD1351 panel;
//static lgfx::Panel_ST7735  panel;
//static lgfx::Panel_ST7735S panel;
//static lgfx::Panel_ST7789 panel;
//static lgfx::Panel_ST7796 panel;

// If you want to use a touch panel, create an instance of the Touch class.
// When using a touch panel, create an instance of the Touch class.
//static lgfx::Touch_SPI_STMPE610 touch;
//static lgfx::Touch_FT5x06 touch;
//static lgfx::Touch_XPT2046 touch;


void setup(void)
{
// Assign various setting values to the panel class.
// Substitute various setting values ​​for the panel class.

  // Set the SPI clock for normal write operation.
  // Set the SPI clock during normal operation.
  // The ESP32 SPI can only be used with 80MHz divided by an integer.
  // The settable value closest to the set value will be used.
  panel.freq_write = 20000000;

  // Set the SPI clock for fill write operation.
  // It may work even if you set the clock higher than freq_write.
  // Set the SPI clock for single color fill processing.
  // Basically set the same value as freq_write,
  // It may work even if you set a higher value.
  panel.freq_fill  = 27000000;

  // Set the SPI clock for read operation.
  // Set the SPI clock when reading pixel data from the LCD.
  panel.freq_read  = 16000000;

  // Set the SPI mode. (0~3)
  // Set the SPI communication mode from 0 to 3.
  panel.spi_mode = 0;

  // Set the SPI mode when read operation. (0~3)
  // Set the SPI communication mode when reading data from 0 to 3.
  panel.spi_mode_read = 0;

  // Sets the number of dummy bits for pixel readout.
  // Set the number of dummy bits when reading pixels.
  // Adjust if bit shift occurs when reading pixels.
  panel.len_dummy_read_pixel = 8;

  // Set the readability of the data. If reading of the data is not possible, set false.
  // Set whether to read the data. Set to false if unreadable.
  // * Set ST7789 etc. without CS pin to false.
  // If omitted, it will be true.
  panel.spi_read = true;

  // Set to "true" for a panel that uses MOSI pins to read data.
  // Read data Set true for panels with MOSI pins.
  // If omitted, it will be false.
  panel.spi_3wire = false;

  // Set the pin number for connecting the CS pins of the LCD.
  // Set the pin number to which the LCD CS is connected.
  // If not used, omit it or set -1.
  panel.spi_cs = 14;

  // Set the pin number for connecting the D/C pins of the LCD.
  // Set the pin number to which the LCD D / C is connected.
  panel.spi_dc = 27;

  // Set the pin number for connecting the RST pins of the LCD.
  // Set the pin number to which the LCD RST is connected.
  // If not used, omit it or set -1.
  panel.gpio_rst = 33;

  // Set the backlight pin number.
  // Set the pin number to which the LCD backlight is connected.
  // If not used, omit it or set -1.
  panel.gpio_bl  = 32;

  // Set the backlight control PWM channel number.
  // When using the backlight, set the PWM channel number used for brightness control.
  // If you do not use PWM brightness control, omit it or set it to -1.
  panel.pwm_ch_bl = 7;

  // Set the backlight level (rue=turns on HIGH / false=turns on LOW)
  // Set whether the output level when the backlight is on is low or high.
  // Default is true. Lights up when true = HIGH / Lights up when false = LOW.
  panel.backlight_level = true;

  // Set the panel color inversion.
  // Panel color inversion setting. If set to true, the colors will be inverted. (Example: Black becomes white, blue becomes yellow)
  // If omitted, false. If the screen color is reversed, change the setting.
  panel.reverse_invert = false;

  // Set the RGB/BGR color order.
  // Set the color order of the panel. RGB = true / BGR = false
  // Default to false. If red and blue are swapped, change the setting.
  panel.rgb_order = false;

  // Set the internal memory size of the LCD driver.
  // Set the memory size (width and height) in the LCD driver chip.
  // If the settings do not match, the coordinates when using setRotation will shift.
  // (Example: ST7735 has 3 types of 132x162 / 128x160 / 132x132)
  panel.memory_width  = 320;
  panel.memory_height = 240;

  // Set the size of the pixels that can be displayed on the LCD panel.
  // Set the number of pixels (width and height) that the panel can actually display.
  // By default, the default value of the panel class is used.
  panel.panel_width  = 320;
  panel.panel_height = 240;

  // Set the number of offset pixels.
  // Set the panel offset amount.
  // By default, the default value of the panel class is used.
  panel.offset_x = 0;
  panel.offset_y = 0;

  // Set the default rotation number.
  // Set the value immediately after the initialization of setRotation.
  panel.rotation = 0;

  // Set the number of rotation offset number.
  // If you want to change the orientation when using setRotation, set offset_rotation.
  // Set 1 if you want the orientation in setRotation (0) to be the orientation when it is 1.
  panel.offset_rotation = 0;

  // After setting up, you can pass the panel pointer to the lcd.setPanel function.
  // After finishing the setting, pass the pointer of the panel class with the setPanel function of lcd.
  lcd.setPanel(&panel);


/*
  // If you use a touch panel, you will assign various setting values to the touch class.
  // When using the touch panel, assign various setting values ​​to the touch class.
  // for SPI setting.  (XPT2046 / STMPE610)
  // For SPI-connected touch panel
  touch.spi_host = VSPI_HOST;  // VSPI_HOST or HSPI_HOST
  touch.spi_sclk = 18;
  touch.spi_mosi = 23;
  touch.spi_miso = 19;
  touch.spi_cs   =  5;
  touch.freq = 1000000;
  touch.bus_shared = true;  // If the LCD and touch share SPI, set to true.
  // for I2C setting. (FT5x06)
  // For I2C connected touch panel
  touch.i2c_port = I2C_NUM_1;
  touch.i2c_sda  = 21;
  touch.i2c_scl  = 22;
  touch.i2c_addr = 0x38;
  touch.freq = 400000;
  // Set the range obtained from the touch panel
  // (Can be omitted when performing calibration)
  // (This can be omitted if calibration is performed.)
  touch.x_min = 0;
  touch.x_max = 319;
  touch.y_min = 0;
  touch.y_max = 319;
  // After setting up, you can pass the touch pointer to the lcd.setTouch function.
  // After finishing the setting, pass the pointer of the touch class with the setTouch function of lcd.
  lcd.setTouch(&touch);
*/


  // Initializing the SPI bus and panel will make it available.
  // Enabled by performing SPI bus and panel initialization.
  lcd.init();

  if (lcd.width() > 240 || lcd.height() > 240) lcd.setTextSize(2);

  if (lcd.touch())
  {
    if (lcd.width() < lcd.height()) lcd.setRotation(3 & (lcd.getRotation() + 1));

    // Draw the information text.
    // Draw a guide text on the screen.
    lcd.drawString("touch the arrow marker.", 0, lcd.height()>>1);

    // If the touch is enabled, perform calibration. Touch the arrow tips that appear in the four corners of the screen in order.
    // If you use touch, calibrate. Touch the tips of the arrows displayed at the four corners of the screen in order.
    lcd.calibrateTouch(nullptr, 0xFFFFFFU, 0x000000U, 30);

    lcd.clear();
  }
}

uint32_t count = ~0;
void loop(void)
{
  delay(10);
  lcd. startWrite ();
  lcd.setRotation(++count & 7);
  lcd.setColorDepth((count & 8) ? 16 : 24);

  lcd.setTextColor(random(65536));
  lcd. drawNumber ( lcd.getRotation (), 16 , 0 );

  lcd.setTextColor(0xFF0000U);
  lcd.drawString("R", 30, 16);
  lcd.setTextColor(0x00FF00U);
  lcd.drawString("G", 40, 16);
  lcd.setTextColor(0x0000FFU);
  lcd.drawString("B", 50, 16);

  lcd.drawRect(30,30,lcd.width()-60,lcd.height()-60,random(65536));

  lcd.endWrite();

  int32_t x, y;
  if (lcd.getTouch(&x, &y)) {
    lcd.fillRect(x-2, y-2, 5, 5, random(65536));
  }
}