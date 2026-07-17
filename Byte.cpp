#include "Byte.h"

void waitcmp() {
    while(!(TWCR & (1 << TWINT)));
}

void ByteStart() {
    TWCR = (1 << TWSTA) | (1 << TWEN) | (1 << TWINT);
    waitcmp();
}

void SendByte(char byte) {
    TWDR = byte;
    TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA);
    waitcmp();
}

void Stop() {
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
    while (TWCR & (1 << TWSTO));
}