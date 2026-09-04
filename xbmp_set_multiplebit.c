uint8_t n = 0xff;        // 1111 1111

case 0:  // clears 1 bit
n &= ~(1 << 0);   // ~(0000 0001) → clears bit 0
n &= ~(1 << 1);   // ~(0000 0010) → clears bit 1
n &= ~(1 << 2);   // ~(0000 0100) → clears bit 2

case 1:  // clears 2 adjacent bits
n &= ~(3 << 0);   // ~(0000 0011) → clears bits 0,1
n &= ~(3 << 1);   // ~(0000 0110) → clears bits 1,2
n &= ~(3 << 2);   // ~(0000 1100) → clears bits 2,3

case 3:  // clears 3 adjacent bits
n &= ~(7 << 0);   // ~(0000 0111) → clears bits 0,1,2
n &= ~(7 << 1);   // ~(0000 1110) → clears bits 1,2,3
n &= ~(7 << 2);   // ~(0001 1100) → clears bits 2,3,4