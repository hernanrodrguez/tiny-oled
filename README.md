# TinyOLED

TinyOLED is an Arduino library for using Display OLED 128x32 0.91 I2C SSD1306 with AtTiny85.

Note that you need to use Spence Konde's ATTiny Core for these routines to work; otherwise you'll get errors such as:
```bash
error: 'PIN_USI_CL' was not declared in this scope
error: 'PIN_USI_SCL' was not declared in this scope
```
For more information about the ATTiny Core, take a look at [the repository](https://github.com/SpenceKonde/ATTinyCore).
Also, this library uses the TinyI2CMaster library. You can find the repository in [this link](https://github.com/technoblogy/tiny-i2c).

## Usage

```cpp
TinyOled.init();
TinyOled.printString("Hello World!");
```

## License
[Creative Commons Attribution 4.0 International License](http://creativecommons.org/licenses/by/4.0/)