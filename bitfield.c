#include <stdio.h>
#include <stdint.h>

typedef struct  {
    uint8_t engine_on   : 1;   /* bit 0 — 0 or 1 */
    uint8_t gear        : 3;   /* bits 1-3 — 0 to 7 */
    uint8_t error_code  : 4;   /* bits 4-7 — 0 to 15 */
}EngineStatus;

int main() {
    EngineStatus status = {0};

    status.engine_on  = 1;
    status.gear       = 5;
    status.error_code = 3;

    printf("Engine on  : %d\n", status.engine_on);
    printf("Gear       : %d\n", status.gear);
    printf("Error code : %d\n", status.error_code);
    printf("Size       : %zu byte\n", sizeof(status));

    return 0;
}