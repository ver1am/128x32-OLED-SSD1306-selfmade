#include <avr/io.h>
#include "ssd1306.h" // Driver
#include "Byte.h" // I2C Wire

const short bytes = (DEVICE_X * DEVICE_Y) / 8;

#define SIZESYM 3

struct Glyph {
    char ch;
    uint8_t data[SIZESYM];
};

const Glyph symbols[] = {
    {'A', {0x3F, 0xC8, 0x3F}},
    {'1', {0x20, 0x40, 0xFF}},
    {'2', {0x67,0x89,0x71}},
    {'3', {0x91,0x91,0x6E}},
    {'4', {0xF0, 0x10,0xFF}},
    {'5', {0xF1,0x91,0x9F}},
    {'6', {0xFF,0x91,0x9F}},
    {'7', {0x84,0x8F,0xF4}},
    {'8', {0xFF,0x91,0xFF}},
    {'9', {0xF1,0x91,0xFF}},
    {'0', {0xFF,0x81,0xFF}} // Б абушка я это писал час 17.07.26 и с тем что ниже и функциями
};

namespace UI {
    void Text(const char text[], uint8_t x = 0, uint8_t y = 0,char bits = -9);
}

namespace gfx {
    void Setpxs(uint8_t x, uint8_t y, char symbol);
    void Setpixel(uint8_t x, uint8_t y, uint8_t stat = 1);
    void ToVRAM();
    void clear();
}