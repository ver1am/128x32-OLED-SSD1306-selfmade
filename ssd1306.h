#define DEVICE_X 128
#define DEVICE_Y 32

#define DEVICE_WRITE ((0x3C << 1) | 0)
#define SETTINGS 0x00
#define PIXELS 0x40
#define PAGES 0x20
#define SETCOLUMN 0x21
#define SETPAGE 0x22 // ex. 0x22, 0x00, 0x07
#define MUX 0xA8 // ex. 0xA8 0x1F
#define COMPINS 0xDA

#define CONTRAST 0x81 // ex. 0x81, 0x7F // 0x81, 0xFF
#define HRZ 0x00
#define VRL 0x01
#define TURN_OFF 0xAE
#define TURN_ON 0xAF
#define POMP 0x8D
#define POMP_ON 0x14
#define POMP_OFF 0x10
#define ROTATE_I 0xC8
#define ROTATE__ 0xA1

#define PAGE_MODE 0x02

const uint8_t init[] = {
    DEVICE_WRITE,
    SETTINGS,
    TURN_OFF,
    PAGES,
    HRZ,
    
    MUX,
    0x1F,

    COMPINS,
    0x02,

    SETPAGE,
    0x00,
    0x03,
    SETCOLUMN,
    0,
    DEVICE_X-1,
    POMP,
    POMP_ON,
    TURN_ON,
};