#include "Graphics.h"

uint8_t framebuffer[bytes] = {0};

namespace UI {
    void Text(const char text[], uint8_t x, uint8_t y, char bits) {
        for (uint8_t i = 0; text[i] != 0; i++, y += SIZESYM+1) {
            if (DEVICE_Y-y <= SIZESYM+1) {
                x += bits; // 8 bits + 1 zazor
                y = 0;
            }
            gfx::Setpxs(x,y,text[i]);
        }
    }
}

namespace gfx {
    void Setpxs(uint8_t x, uint8_t y, char symbol) {
        uint16_t index = x + (y / 8) * DEVICE_X;

        const uint8_t* data = nullptr;

        for (const Glyph& sym : symbols) {
            if (sym.ch == symbol) {
                data = sym.data;
                break;
            }
        }

        if (data == nullptr) return;

        for (uint8_t j = 0; j < 8; j++) {
            uint8_t mask = 0;
            for (uint8_t i = 0; i < 3; i++) {

                uint8_t bit = (data[i] >> j) & 1;

                mask |= (bit << (i + (y % 8)));
            }
            framebuffer[index++] |= mask;
        }
        ToVRAM();
    }

    void Setpixel(uint8_t x, uint8_t y, uint8_t stat) {
        uint16_t index = x + (y / 8) * DEVICE_X;
        uint8_t mask = 1 << (y % 8);

        if (stat) {
            framebuffer[index] |= mask;
        } else {
            framebuffer[index] &= ~mask;
        }
    }

    void ToVRAM() {
        ByteStart();
        SendByte(DEVICE_WRITE);
        SendByte(PIXELS);
        for (int i = 0; i < bytes; i++) {
            SendByte(framebuffer[i]);
        }
        Stop();
    }

    void clear() {
        for (int i = 0; i < bytes; i++) {
            framebuffer[i] = 0;
        }
        ToVRAM();
    }
}