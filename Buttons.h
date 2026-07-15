#define BLUE_LEVO 3
#define BLUE_PRAVO 4
#define RED_LEVO 5
#define RED_PRAVO 6

#define START_PIN BLUE_LEVO

void setup();
void press(char pin, void(*fun)());
void hold(char pin, void(*fun)());