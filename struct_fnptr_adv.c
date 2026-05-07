#include <stdio.h>
#include <stdint.h>

/* --- SPI driver --- */
int spi_init(void)                            { printf("SPI init\n");  return 0; }
int spi_read(uint8_t *buf, int len)           { printf("SPI read %d bytes\n", len); return len; }
int spi_write(const uint8_t *buf, int len)    { printf("SPI write %d bytes\n", len); return len; }

/* --- UART driver --- */
int uart_init(void)                           { printf("UART init\n"); return 0; }
int uart_read(uint8_t *buf, int len)          { printf("UART read %d bytes\n", len); return len; }
int uart_write(const uint8_t *buf, int len)   { printf("UART write %d bytes\n", len); return len; }

/* --- Common driver interface --- */
typedef struct {
    const char *name;
    int (*init)(void);
    int (*read)(uint8_t *buf, int len);
    int (*write)(const uint8_t *buf, int len);
} Driver_t;

/* Populate at compile time — no if/else at call site */
Driver_t spi_drv  = { "SPI",  spi_init,  spi_read,  spi_write  };
Driver_t uart_drv = { "UART", uart_init, uart_read, uart_write };

void run_driver(Driver_t *drv) {
    drv->init();
    uint8_t buf[64];
    drv->read(buf, sizeof(buf));
    drv->write(buf, 10);
}

int main(void) {
    run_driver(&spi_drv);
    run_driver(&uart_drv);
    return 0;
}

/*

Result
SPI init
SPI read 64 bytes
SPI write 10 bytes
UART init
UART read 64 bytes
UART write 10 bytes
*/

/*
Major embeded application

Summary Table
Pattern                  Benefit 
State machine               No switch/case, easy to add states
IRQ dispatch table          Clean ISR routing
RTOS task descriptor        Loop-based task registration
CAN/protocol parser         Add message = one table row
Sensor abstraction          Swap hardware without changing app
Boot sequence table         Ordered init with error handling
Fault handler table         Decoupled fault response


*/