#include <avr/io.h>
#include "FastSerial.cpp"
#include "Delay.cpp"
#include "Buttons.h"
#include "Byte.h"
#include "ssd1306.h"

char framebuffer[(DEVICE_X * DEVICE_Y) / 8] = {0}; // 512

inline void setupoled() {
    ByteStart();
    SendByte(DEVICE_WRITE);
    SendByte(SETTINGS);
    SendByte(TURN_OFF);
    SendByte(PAGES);
    SendByte(HRZ);
    SendByte(POMP);
    SendByte(POMP_ON);
    SendByte(TURN_ON);
    Stop();
}

void Setpixel(uint8_t x, uint8_t y, uint8_t stat = 1) {
    // Вычисляем индекс байта в буфере
    uint16_t index = x + (y / 8) * DEVICE_X;
    // Вычисляем битовую маску для конкретного пикселя в байте
    uint8_t mask = 1 << (y % 8);

    if (stat) {
        framebuffer[index] |= mask;   // Устанавливаем бит (включаем пиксель)
    } else {
        framebuffer[index] &= ~mask;  // Сбрасываем бит (выключаем пиксель)
    }
}

void ToVRAM() {
    ByteStart();
    SendByte(DEVICE_WRITE);
    SendByte(PIXELS);
    for (int i = 0; i < ((DEVICE_X * DEVICE_Y) / 8); i++) {
        SendByte(framebuffer[i]);
    }
    Stop();
}

void clear() {
    for (int i = 0; i < (DEVICE_X * DEVICE_Y) / 8; i++) {
        framebuffer[i] = 0;
    }
    ToVRAM();
}

void printS() {
    FastSerial::print("KNOPKA");
}

int main() {
    TWSR = 0x00; // Прескалер = 1
    TWBR = 72;   // Стабильные 100 кГц на частоте 16 МГц
    FastSerial::begin(9600);
    setup();
    setupoled();
    clear();
    Setpixel(64,0);
    Setpixel(64,16);
    Setpixel(96,16);
    // for (int i = 0; i < DEVICE_X; i++) {
    //     Setpixel(i,0);
    // }
    ToVRAM();
    while (1) {
        press(BLUE_LEVO,printS);
        press(BLUE_PRAVO,printS);
        delay_ms(100);
    }
}