#ifndef LOVYANGFX_CONFIG_HPP_
#define LOVYANGFX_CONFIG_HPP_

namespace lgfx
{
// for ESP32
  struct LGFX_Config
  {
// Select the type of SPI  (VSPI_HOST or HSPI_HOST)
// 使用するSPIを VSPI_HOST または HSPI_HOST で設定します。
    static constexpr spi_host_device_t spi_host = VSPI_HOST;

// Set the DMA channel number (1 or 2)
// If you don't want to use DMA, omit it or set it to 0.
// 使用するDMAチャンネルを 1か2で設定します。
// 使用しない場合は省略するか0を設定します。
    static constexpr int dma_channel = 1;

// Set the SPI SCLK pin number
// SPIのSCLKのピン番号を設定します。
    static constexpr int spi_sclk = 18;

// Set the SPI MOSI pin number
// SPIのMOSIのピン番号を設定します。
    static constexpr int spi_mosi = 23;

// Set the SPI MISO pin number
// If you share the SPI bus with an SD card, be sure to set up MISO as well.
// If you don't want to use MISO, omit it or set it to -1.
// SPIのMISOのピン番号を設定します。
// SDカード等と共通のSPIバスを使う場合はMISOも必ず設定してください。
// 使わない場合は省略するか-1を設定します。
    static constexpr int spi_miso = 19;

// Set the data length of SPI communication.
// If you want to use the LCD for RPi, set it to 16.
// SPI通信のデータ長を指定します。
// RaspberryPi用のLCD等を使用する場合に16を指定します。
// 省略時は 8 です。大抵のパネルは8ですので、基本的には省略してください。
    static constexpr int spi_dlen = 8;
  };


/* 
// for SAMD51
  struct LGFX_Config
  {
// Set the SERCOM number of the SPI to be used.
// 使用するSPIのSERCOM番号を設定します。
    static constexpr int sercom_index = 7;

// Set the SERCOM clock source.
// If -1 is specified, it will operate without setting the clock source, so please set it separately.
// SERCOMのクロックソースを設定します。
// -1を指定した場合、クロックソースを設定せずに動作しますので別途設定を行ってください。
    static constexpr int sercom_clksrc = 0;   // -1=notchange / 0=select GCLK0

// Set the operating frequency of the clock source set above.
// Please set the setting value made by Harmony etc. as it is.
// 上記で設定したクロックソースの動作周波数を設定します。
// Harmony等で行った設定値をそのまま設定してください。
    static constexpr int sercom_clkfreq = 120000000;

// Set the SPI SCLK pin number. PORTA = 0x000 / PORTB = 0x100 / PORTC = 0x200 / PORTD = 0x300.
// SPIのSCLKのピン番号を設定します。 PORTA=0x000 / PORTB=0x100 / PORTC=0x200 / PORTD=0x300…
    static constexpr int spi_sclk = 0x0100 | 20; // PORTB 20 (PORTB=0x0100)

// Set the MOSI pin number of SPI.
// SPIのMOSIのピン番号を設定します。
    static constexpr int spi_mosi = 0x0100 | 19; // PORTB 19 (PORTB=0x0100)

// Set the MISO pin number of SPI.
// SPIのMISOのピン番号を設定します。
    static constexpr int spi_miso = 0x0100 | 18; // PORTB 18 (PORTB=0x0100)

// Set the TX Pad used by SPI.
// SPIで使用するTX Padを設定します。
    static constexpr SercomSpiTXPad pad_mosi = SPI_PAD_3_SCK_1;  // PAD_SPI3_TX;

// Set the RX Pad used by SPI.
// SPIで使用するRX Padを設定します。
    static constexpr SercomRXPad    pad_miso = SERCOM_RX_PAD_2;  // PAD_SPI3_RX;
  };
//*/

}

class LGFX : public lgfx::LGFX_SPI<lgfx::LGFX_Config>
{
// Create an instance of the Panel class. Comment out the class that matches your panel.
// Panelクラスのインスタンスを作成します。使用するパネルにあったクラスをコメントアウトしてください。

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
// (If you select the panel class of an integrated LCD product,
// no setting is required as the initial value is set according to the product)
// パネルクラスに各種設定値を代入していきます。
// （LCD一体型製品のパネルクラスを選択した場合は、
//   製品に合った初期値が設定されているので設定は不要です）

// Set the SPI clock during normal operation.
// The ESP32 SPI can only be used with 80MHz divided by an integer.
// The settable value closest to the set value will be used.
// 通常動作時のSPIクロックを設定します。
// ESP32のSPIは80MHzを整数で割った値のみ使用可能です。
// 設定した値に一番近い設定可能な値が使用されます。
    panel.freq_write = 20000000;

// Set the SPI clock for single color fill processing.
// Basically set the same value as freq_write,
// It may work even if you set a higher value.
// 単色の塗り潰し処理時のSPIクロックを設定します。
// 基本的にはfreq_writeと同じ値を設定しますが、
// より高い値を設定しても動作する場合があります。
    panel.freq_fill  = 27000000;

// Set the SPI clock when reading pixel data from the LCD.
// LCDから画素データを読取る際のSPIクロックを設定します。
    panel.freq_read  = 16000000;

// Set the SPI communication mode from 0 to 3.
// SPI通信モードを0~3から設定します。
    panel.spi_mode = 0;

// Set the SPI communication mode when reading data from 0 to 3.
// データ読み取り時のSPI通信モードを0~3から設定します。
    panel.spi_mode_read = 0;

// Set the number of dummy bits when reading pixels.
// Adjust if bit shift occurs when reading pixels.
// 画素読出し時のダミービット数を設定します。
// 画素読出しでビットずれが起きる場合に調整してください。
    panel.len_dummy_read_pixel = 8;

// Set true for panels that can read data, false if not.
// (Example: ST7789 without CS pin cannot be read, so set false.)
// If omitted, it will be true.
// データの読取りが可能なパネルの場合はtrueを、不可の場合はfalseを設定します。
// （例：CSピンのないST7789等は読出し不可のためfalseを設定します。）
// 省略時はtrueになります。
    panel.spi_read = true;

// Read data Set true for panels with MOSI pins.
// (Example: Set true for M5Stack and T-Watch, false for ESP-WROVER-KIT.)
// If omitted, it will be false.
// データの読取りMOSIピンで行うパネルの場合はtrueを設定します。
// （例：M5StackやT-Watchはtrue、ESP-WROVER-KITはfalseを設定します。）
// 省略時はfalseになります。
    panel.spi_3wire = false;

// Set the pin number to which the LCD CS is connected.
// If not used, omit it or set -1.
// LCDのCSを接続したピン番号を設定します。
// 使わない場合は省略するか-1を設定します。
    panel.spi_cs = 14;

// Set the pin number to which the LCD DC is connected.
// LCDのDCを接続したピン番号を設定します。
    panel.spi_dc = 27;

// Set the pin number to which the LCD RST is connected.
// If not used, omit it or set -1.
// LCDのRSTを接続したピン番号を設定します。
// 使わない場合は省略するか-1を設定します。
    panel.gpio_rst = 33;

// Set the pin number to which the LCD backlight is connected.
// If not used, omit it or set -1.
// LCDのバックライトを接続したピン番号を設定します。
// 使わない場合は省略するか-1を設定します。
    panel.gpio_bl  = 32;

// When using the backlight, set the PWM channel number used for brightness control.
// If you do not use PWM brightness control, omit it or set it to -1.
// バックライト使用時、輝度制御に使用するPWMチャンネル番号を設定します。
// PWM輝度制御を使わない場合は省略するか-1を設定します。
    panel.pwm_ch_bl = 7;

// Set whether the output level when the backlight is on is low or high.
// Default is true. Lights up when true = HIGH / Lights up when false = LOW.
// バックライト点灯時の出力レベルがローかハイかを設定します。
// 省略時は true。true=HIGHで点灯 / false=LOWで点灯になります。
    panel.backlight_level = true;

// Set the panel color inversion.
// If set to true, the colors will be inverted. (Example: black and white, blue and yellow)
// If omitted, false. If the screen color is reversed, change the setting.
// パネルの色反転設定です。trueを設定すると色が反転します。(例:黒と白、青と黄色)
// 省略時は false。画面の色が反転している場合は設定を変更してください。
    panel.reverse_invert = false;

// Set the color order of the panel. RGB = true / BGR = false
// Default to false. If red and blue are swapped, change the setting.
// パネルの色順を設定します。  RGB=true / BGR=false
// 省略時はfalse。赤と青が入れ替わっている場合は設定を変更してください。
    panel.rgb_order = false;

// Set the number of pixels (width and height) in the memory of the LCD controller.
// If the settings do not match, the coordinates when using setRotation will shift.
// (Example: ST7735 has 3 types of 132x162 / 128x160 / 132x132)
// LCDコントローラのメモリ上のピクセル数（幅と高さ）を設定します。
// 設定が合っていない場合、setRotationを使用した際の座標がずれます。
// （例：ST7735は 132x162 / 128x160 / 132x132 の３通りが存在します）
    panel.memory_width  = 320;
    panel.memory_height = 240;

// Set the number of pixels (width and height) that can actually be displayed on the panel.
// By default, the default value of the panel class is used.
// パネルの実際に表示可能なピクセル数（幅と高さ）を設定します。
// 省略時はパネルクラスのデフォルト値が使用されます。
    panel.panel_width  = 320;
    panel.panel_height = 240;

// Set the panel offset amount.
// By default, the default value of the panel class is used.
// パネルのオフセット量を設定します。
// 省略時はパネルクラスのデフォルト値が使用されます。
    panel.offset_x = 0;
    panel.offset_y = 0;

// Set the setRotation value immediately after the initialization.
// setRotationの初期化直後の値を設定します。
    panel.rotation = 0;

// If you want to change the orientation when using setRotation, set offset_rotation.
// Set 1 if you want the orientation in setRotation (0) to be the orientation when it is 1.
// setRotationを使用した時の向きを変更したい場合、offset_rotationを設定します。
// setRotation(0)での向きを 1の時の向きにしたい場合、 1を設定します。
    panel.offset_rotation = 0;



// Finally, set the prepared panel settings.
// 最後に、用意したパネル設定をセットします。
    setPanel(&panel);
  }
};

#endif
