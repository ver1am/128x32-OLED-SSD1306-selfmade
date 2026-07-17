#define BLUE_LEVO 3
#define BLUE_PRAVO 4
#define RED_LEVO 5
#define RED_PRAVO 6

#define START_PIN BLUE_LEVO

const static uint8_t Pins = 4;

static bool pinsls[Pins] = {0};

namespace btn {
    void setup() {
        for (char i = 3; i < 7; i++) {
            DDRD &= ~(1 << i);
            PORTD |= (1 << i);
        }
    }

    template <typename F, typename... Args>
    void press(char pin,F fun,Args... args) {
        bool& ls = pinsls[pin - START_PIN];

        bool IsPressed = !(PIND & (1 << pin));

        if (IsPressed && !ls) {
            ls = true;
            fun(args...);
        }
        if (!IsPressed) ls = false;
    }

    template <typename F, typename... Args>
    void hold(char pin,F fun, Args... args) {
        if (!(PIND & (1 << pin))) fun(args...);
    }
}