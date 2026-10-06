#include <stdio.h>
#include <stdint.h>
#include <string.h>

/* cpy1: byte pointer view        -> host order */
void cpy1(uint8_t *dest, uint32_t n)
{
    const uint8_t *src = (const uint8_t *)&n;

    for (int i = 0; i < 4; i++)
    {
        dest[i] = src[i];
    }
}

/* cpy2: union                    -> host order */
void cpy2(uint8_t *dest, uint32_t n)
{
    union
    {
        uint32_t value;
        uint8_t  d[4];
    } t;

    t.value = n;
    dest[0] = t.d[0];
    dest[1] = t.d[1];
    dest[2] = t.d[2];
    dest[3] = t.d[3];
}

/* cpy3: shift loop               -> little-endian always */
void cpy3(uint8_t *dest, uint32_t n)
{
    for (int i = 0; i < 4; i++)
    {
        dest[i] = (uint8_t)(n >> (8 * i));
    }
}

/* cpy4: mask + pointer increment -> little-endian always */
void cpy4(uint8_t *dest, uint32_t n)
{
    for (int i = 0; i < 4; i++)
    {
        *dest++ = (uint8_t)(n & 0xFFu);
        n >>= 8;
    }
}

/* cpy5: memcpy                   -> host order */
void cpy5(uint8_t *dest, uint32_t n)
{
    memcpy(dest, &n, sizeof n);
}

/* cpy6: reverse bytes + memcpy   -> big-endian on a little-endian host */
void cpy6(uint8_t *dest, uint32_t n)
{
    uint32_t be = ((n & 0x000000FFu) << 24) |
                  ((n & 0x0000FF00u) << 8)  |
                  ((n & 0x00FF0000u) >> 8)  |
                  ((n & 0xFF000000u) >> 24);

    memcpy(dest, &be, sizeof be);
}

/* cpy7: BYTEx macros             -> little-endian always */
#define BYTE0(x) ((uint8_t)( (x)        & 0xFFu))
#define BYTE1(x) ((uint8_t)(((x) >> 8)  & 0xFFu))
#define BYTE2(x) ((uint8_t)(((x) >> 16) & 0xFFu))
#define BYTE3(x) ((uint8_t)(((x) >> 24) & 0xFFu))

void cpy7(uint8_t *dest, uint32_t n)
{
    dest[0] = BYTE0(n);
    dest[1] = BYTE1(n);
    dest[2] = BYTE2(n);
    dest[3] = BYTE3(n);
}

/* ================= DEMO ================= */

static void show(const char *name, const uint8_t *b)
{
    printf("%-5s %02x %02x %02x %02x\n", name, b[0], b[1], b[2], b[3]);
}

int main(void)
{
    const uint32_t n = 0x12345678u;
    uint8_t dest[4];

    cpy1(dest, n); show("cpy1", dest);
    cpy2(dest, n); show("cpy2", dest);
    cpy3(dest, n); show("cpy3", dest);
    cpy4(dest, n); show("cpy4", dest);
    cpy5(dest, n); show("cpy5", dest);
    cpy6(dest, n); show("cpy6", dest);
    cpy7(dest, n); show("cpy7", dest);

    return 0;
}
