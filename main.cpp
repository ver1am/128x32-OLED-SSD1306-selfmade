#include <avr/io.h>
// #include "FastSerial.cpp"
#include "Delay.cpp"
#include "Buttons.h"
#include "Graphics.h"
#include "Random.h"

static uint8_t x = 0;
static uint8_t y = 0;

// 0
//3 1
// 2

void fun(uint8_t dir) {
    switch (dir) {
        case 0:
            x++;
            break;
        case 1:
            y++;
            break;
        case 2:
            x--;
            break;
        case 3:
            y--;  
            break; 
    }
    gfx::Setpixel(x,y);
    gfx::ToVRAM();
}

int main() {
    TWSR = 0x00; // Прескалер = 1
    TWBR = 72;   // Стабильные 100 кГц на частоте 16 МГц

    // FastSerial::begin(9600);
    btn::setup();
    rng::init(0);

    // INIT
    ByteStart();
    for (uint8_t byte : init) {
        SendByte(byte);
    }
    Stop();

    gfx::clear();
    gfx::Setpxs(0,0,rng::rng(48,57));
    // UI::Text("A1234567890",0,0,9);

    while (1) {
        btn::hold(BLUE_LEVO,fun,0);
        btn::hold(BLUE_PRAVO,fun,2);
        btn::hold(RED_LEVO,fun,1);
        btn::hold(RED_PRAVO,fun,3);
        delay_ms(100);
    }
}