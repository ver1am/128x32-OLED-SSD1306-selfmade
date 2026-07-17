#include <avr/io.h>

namespace rng {
    void init(uint8_t pin) {
        ADMUX = (1 << REFS0) | pin;
        ADCSRA = (1 << ADEN);
    }

    uint16_t rng(uint16_t min,uint16_t max) {
        ADCSRA |= (1 << ADSC);
        while (ADCSRA & (1 << ADSC));
        uint16_t raw = ADC;
        return (raw % (max - min + 1)) + min;
    }
}