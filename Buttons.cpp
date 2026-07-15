#include <avr/io.h>
#include "Buttons.h"

const char Pins = 4;

bool pinsls[Pins] = {0};

void setup() {
    for (char i = 3; i < 7; i++) {
        DDRD &= ~(1 << i);
        PORTD |= (1 << i);
    }
}

void press(char pin,void(*fun)()) {
    bool& ls = pinsls[pin - START_PIN];

    bool IsPressed = !(PIND & (1 << pin));

    if (IsPressed && !ls) {
        ls = true;
        fun();
    }
    if (!IsPressed) ls = false;
}

void hold(char pin,void(*fun)()) {
    if (!(PIND & (1 << pin))) fun();
}