
#define SETBIT(N, POS1, POS2)      ((N) |=  ((1 << (POS1)) | (1 << (POS2))))
#define CLEARBIT(N, POS1, POS2)    ((N) &= ~((1 << (POS1)) | (1 << (POS2))))
#define TOGGLE(N, POS1, POS2)      ((N) ^=  ((1 << (POS1)) | (1 << (POS2))))
#define IS_BIT_SET(N, POS1, POS2)  ((N)  &  ((1 << (POS1)) | (1 << (POS2))))


uint8_t reg = 0x00;

SETBIT(reg, 2, 5);          // reg = 0b00100100
CLEARBIT(reg, 2, 5);        // reg = 0b00000000
TOGGLE(reg, 2, 5);          // reg = 0b00100100
if (IS_BIT_SET(reg, 2, 5))  // true if either bit2 or bit5 is set
    printf("set\n");
	