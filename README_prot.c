

### Difference between UART, SPI, CAN, I2C?
    Feature          UART               SPI                      I2C                      CAN
    -----------      ----------------   ----------------------   ----------------------   ----------------------
    Wires            2 (TX, RX)         4 (MOSI,MISO,SCK,CS)     2 (SDA, SCL)             2 (CANH, CANL)
    Speed            up to ~5 Mbps      up to 100mhz            100k / 400k / 1MHz/3mhz       125k / 250k / 500k / 1Mbps
    Topology         Point-to-point     1 master, multi slave    Multi master+slave        Multi master (bus)
    Addressing       None               Chip Select per slave    7-bit address             11-bit / 29-bit ID
    Synchronous      No (async)         Yes                      Yes                      No (async)
    Error handling   None               None                     ACK only                 CRC, ACK, error frames
    Use case         Debug, GPS, BT     Flash, ADC, display      Sensors, EEPROM           Automotive ECUs, OBD


### What is I2C clock stretching?
    Slave holds SCL line LOW to pause the master while preparing data.
    Master must wait until slave releases SCL.
    Some I2C masters do not support clock stretching -- check datasheet!

## Communication Protocol

### i2c Communication

    +-------+----------+---+----------+---+--------+---+---+
    |   S   | ADDR[7:1]|R/W|  A/NA    |  DATA[7:0] | A |P  |
    +-------+----------+---+----------+---+--------+---+---+

    Field       Bits    Driven by       Description
    -------     ----    ----------      ---------------------------
    S             -     Master          START condition
    ADDR        [7:1]   Master          7-bit slave address
    R/W          [0]    Master          0 = Write, 1 = Read
    A/NA          -     Slave           ACK after address
    DATA        [7:0]   Master(W)/      8 data bits, MSB first
                        Slave(R)
    A/NA          -     Slave(W)/       ACK after data byte
                        Master(R)
    P             -     Master          STOP condition


#### what is i2c clock Speed

    Mode            Speed       Notes
    -----------     --------    ---------------------------
    Standard        100 kHz     All devices supported
    Fast            400 kHz     MPU-6050, SSD1306 supported
    Fast mode+      1 MHz       SSD1306 (some variants)
    High speed      3.4 MHz     Rare, special hw needed

    Pull-up resistors:
    100 kHz  ->  4.7 kohm typical
    400 kHz  ->  2.2 kohm typical
    1 MHz    ->  1.0 kohm typical

### what is Dominat and reccesive

Differential signaling on CAN_H and CAN_L lines:

State       CAN_H       CAN_L       Differential (H-L)
---------   -------     -------     ------------------
Dominant    3.5 V       1.5 V       +2.0 V  (logic 0)
Recessive   2.5 V       2.5 V        0.0 V  (logic 1)

Dominant wins on bus (wired-AND): any node sending 0 pulls bus dominant.


### Expalin CAN frame
---
Type                Description
----------------    ----------------------------------------
Data Frame          Carries actual data (most common)
Remote Frame        Requests data from another node (RTR=1)
Error Frame         Signals a detected error on the bus
Overload Frame      Requests delay between frames
------

+-----+-------------+-----+-----+-----+-----+----------+-----------+-----+-----+
| SOF |   ID[10:0]  | RTR | IDE | r0  | DLC |   DATA   |  CRC+DEL  | ACK | EOF |
+-----+-------------+-----+-----+-----+-----+----------+-----------+-----+-----+
  1 b      11 b       1 b   1 b   1 b   4 b   0-64 b      15+1 b    1+1b   7 b

* Data: 0 to 8 bytes (0 to 64 bits)

Field       Bits    Value           Description
-------     ----    -----           ----------------------------------
SOF           1     0 (dom)         Start of frame, sync all nodes
ID         [10:0]   0x000-0x7FF     Message priority + identifier
RTR           1     0=Data, 1=Rmt  Remote Transmission Request
IDE           1     0               0 = Standard frame (11-bit ID)
r0            1     0 (dom)         Reserved, always dominant
DLC         [3:0]   0-8             Number of data bytes
DATA        0-64b   payload         Actual data, MSB first
CRC          15b    calculated      CRC over SOF+ID+ctrl+data
CRC DEL       1     1 (rec)         CRC delimiter, always recessive
ACK slot      1     0 (dom)         Receiver pulls dominant = ACK
ACK DEL       1     1 (rec)         ACK delimiter
EOF           7     1111111 (rec)   End of frame
IFS           3     111 (rec)       Intermission (bus idle)

---
### UART Communication

One UART frame = 1 start bit + data bits + optional parity + stop bit(s)

IDLE  Start   D0   D1   D2   D3   D4   D5   D6   D7   Parity  Stop  IDLE
----+       +----+----+----+----+----+----+----+----+--------+------+----
    |       |                                                 |      |
    +-------+                                                 +------+
      LOW                   data bits (LSB first)              HIGH

+------+------+----+----+----+----+----+----+----+----+--------+------+
| IDLE | STRT | D0 | D1 | D2 | D3 | D4 | D5 | D6 | D7 |  PAR  | STOP |
+------+------+----+----+----+----+----+----+----+----+--------+------+
         1 b   <-------- 5 to 9 data bits -------->   0 or 1b  1-2 b

Field       Bits    Value       Description
-------     ----    -----       ----------------------------------
IDLE          -     1 (HIGH)    Line idle state
Start         1     0 (LOW)     Signals start of frame
Data        5-9     payload     LSB sent first (D0 first)
Parity      0-1     E/O/N       Even, Odd, or None
Stop        1-2     1 (HIGH)    End of frame, line returns HIGH

---


### what are the ADC Formulas?

    Resolution = Vref / 2^n

    Example — 12-bit ADC:

    Resolution = 5V / 4096 = 1.22 mV

    Vout = (ADC_value / (2^n - 1)) x Vref
    ```

    - `ADC_value` — raw ADC output (0 to 4095 for 12-bit)
    - `2^n - 1` — max count = 4095
    - `Vref` — reference voltage = 5V

    Examples:

    | ADC Value | Calculation         | Result      |
    |-----------|---------------------|-------------|
    | 4095      | 4095 x 5 / 4095     | 5.00 V (max)|
    | 2048      | 2048 x 5 / 4095     | ~2.50 V     |
    | 0         | 0 x 5 / 4095        | 0.00 V (min)|


### ADC groups w.r.t AUTOSAR

    ADC Groups
    AUTOSAR organizes ADC channels into Groups
    
    Group is a collection of one or more channels that are converted together.
    Each group has a trigger source (SW or HW)
    Each group has a conversion mode (one-shot or continuous)
    Each group has a result buffer (linear or circular)

    2. Conversion Modes
    Mode          Description
    One-shot       Single conversion per trigger, then stops
    Continuous     Keeps converting in a loop until explicitly stopped
    Scan           Converts all channels in the group sequentially

    3. Trigger Sources
    Trigger Source        Macro / Config Value      Description
    Software trigger      ADC_TRIGG_SRC_SW          Trigger via Adc_StartGroupConversion()
    Hardware trigger       ADC_TRIGG_SRC_HW         Timer, PWM event, or external pin

    4. Notification (Callback)
    Each group can have a notification function (callback) registered in configuration.
    It is called at end-of-conversion (similar to an ISR-driven callback).
    /* Example notification function prototype */
    void AdcGroup0_ConversionComplete(void);

### ADC API Reference

SW TRIGGERED FLOW
    Adc_Init(&AdcConfig)
        |
        v
Adc_SetupResultBuffer(Group0, resultBuffer)
// Tells the ADC driver where to store conversion results.
// Links Group0 to your result array in RAM.
        |
        v
Adc_EnableGroupNotification(Group0)
// Registers a callback to fire when Group0 conversion completes.
// Enables interrupt-based notification instead of polling.
        |
        v
Adc_StartGroupConversion(Group0)
// Triggers the ADC hardware to begin sampling all channels in Group0.
// Software initiates the conversion (SW-triggered mode).
        |
        v
    [HW converts all channels in Group0]
// ADC hardware samples each channel sequentially/simultaneously.
// Stores raw digital results into the linked resultBuffer.
        |
        v
    [Notification callback fires]
// ISR or callback function is invoked automatically by the driver.
// Signals application that all Group0 results are ready to read.
        |
        v
Adc_ReadGroup(Group0, resultBuffer)
// Copies converted ADC values from driver buffer into application buffer.
// Returns status; resultBuffer now holds valid channel readings.
        |
        v
    Use result in application logic
// Process ADC values: scaling, threshold check, control decisions, etc.
// e.g., temperature = (resultBuffer[0] * VREF) / ADC_RESOLUTION




## AUTOSAR SPI Key Concepts

    Master                          Slave
    ------                          -----
    SCLK  -----------------------------> SCLK
    MOSI  -----------------------------> MOSI
    MISO  <----------------------------- MISO
    CS    -----------------------------> CS
    GND   ------------------------------ GND

    CS pulled LOW by master to select slave.

- **Channel** — Basic data unit. Holds a buffer of data elements to be transferred.
- **Job** — A sequence of one or more Channels sharing the same CS (Chip Select).
- **Sequence** — A group of one or more Jobs. Unit of transmission triggered by SW.
- **EB Buffer** — External Buffer; pointer to user-provided RAM buffer (dynamic).
- **IB Buffer** — Internal Buffer; statically allocated inside the SPI driver.
- **Hw Unit** — Physical SPI peripheral (e.g., QSPI0, QSPI2 on AURIX TriCore).


### List SPI MODES 

SPI Modes (CPOL + CPHA)
```
| Mode | CPOL | CPHA | Clock Idle | Sample On    |
|------|------|------|------------|--------------|
|  0   |  0   |  0   |    LOW     | Rising edge  |
|  1   |  0   |  1   |    LOW     | Falling edge |
|  2   |  1   |  0   |    HIGH    | Falling edge |
|  3   |  1   |  1   |    HIGH    | Rising edge  |
```

## What is SPI Synchronous vs Asynchronous or trnasimission mode?
    SPI bus is always clocked, hardware sync is not negotiable
    Sync vs Async is a software architecture choice, not a hardware one
    DMA frees CPU but driver design decides if SW is truly async
    Best architecture is async driver as base with sync wrapper on top
    In RTOS, task pends on semaphore, ISR gives on transfer complete
    Prefer sync for boot sequences, short commands, and simple debug scenarios
    Prefer async with DMA for flash bulk ops, frame buffers, and RTOS multitasking


## list SPI API
SPI SW TRIGGERED FLOW
    Spi_Init(&SpiConfig)
        |
        v
Spi_SetupEB(Channel0, srcBuffer, destBuffer, length)
// Tells the SPI driver source (TX) and destination (RX) buffers.
// Links Channel0 to your data arrays in RAM with transfer length.
        |
        v
Spi_EnableJobNotification(Job0)
// Registers a callback to fire when Job0 transmission completes.
// Enables interrupt-based notification instead of polling.
        |
        v
Spi_AsyncTransmit(Sequence0)
// Triggers the SPI hardware to begin transmitting Sequence0.
// Software initiates the transfer (SW-triggered async mode).
        |
        v
    [HW transmits all channels in Sequence0]
// SPI hardware shifts out TX bytes and simultaneously captures RX bytes.
// Handles chip select (CS) assertion/de-assertion automatically per job.
        |
        v
    [Job/Sequence notification callback fires]
// ISR or callback function is invoked automatically by the driver.
// Signals application that all Sequence0 bytes are sent and received.
        |
        v
Spi_ReadIB(Channel0, destBuffer)
// Copies received SPI bytes from driver internal buffer to app buffer.
// Returns status; destBuffer now holds valid RX data from slave device.
        |
        v
    Use result in application logic
// Process RX data: parse sensor response, decode register values, etc.
// e.g., sensorVal = (destBuffer[0] << 8) | destBuffer[1]

## what is SPI Synchronous vs Asynchronous ?

| #  | Point                                                                              |
|----|------------------------------------------------------------------------------------|
| 1  | SPI bus is always clocked, hardware sync is not negotiable                         |
| 2  | Sync vs Async is a software architecture choice, not a hardware one                |
| 3  | DMA frees CPU but driver design decides if SW is truly async                       |
| 4  | Best architecture is async driver as base with sync wrapper on top                 |
| 5  | In RTOS, task pends on semaphore, ISR gives on transfer complete                   |
| 6  | Prefer sync for boot sequences, short commands, and simple debug scenarios         |
| 7  | Prefer async with DMA for flash bulk ops, frame buffers, and RTOS multitasking     |

### UART REGISTERS
```markdown
## STM32 Register Reference Table

### RCC — Reset & Clock Control

| Register        | Bit Used   | What it does                                      |
|-----------------|------------|---------------------------------------------------|
| RCC->AHBENR     | Bit 17     | Enable GPIOA clock (STM32F072)                    |
| RCC->AHBENR     | Bit 18     | Enable GPIOB clock (STM32F072)                    |
| RCC->AHBENR     | Bit 19     | Enable GPIOC clock (STM32F072)                    |
| RCC->IOPENR     | Bit 0      | Enable GPIOA clock (STM32G0xx)                    |
| RCC->IOPENR     | Bit 1      | Enable GPIOB clock (STM32G0xx)                    |
| RCC->IOPENR     | Bit 2      | Enable GPIOC clock (STM32G0xx)                    |
| RCC->APBENR1    | Bit 17     | Enable USART2 peripheral clock                    |

---

### GPIO — General Purpose I/O (GPIOA)

| Register        | Bit Used   | What it does                                      |
|-----------------|------------|---------------------------------------------------|
| GPIOA->MODER    | Pin x 2    | Set pin mode: 00=Input 01=Output 10=AltFunc 11=Analog |
| GPIOA->AFR[0]   | Bit 8      | Set AF1 (USART2 TX) on PA2                        |
| GPIOA->AFR[0]   | Bit 12     | Set AF1 (USART2 RX) on PA3                        |
| GPIOA->BSRR     | Bit 5      | Set PA5 HIGH — LED ON                             |
| GPIOA->BSRR     | Bit 21     | Reset PA5 LOW — LED OFF                           |
| GPIOA->ODR      | Bit 5      | Toggle PA5 using XOR (commented out)              |

---

### USART2 — Universal Async Receiver Transmitter

| Register        | Bit Used   | What it does                                      |
|-----------------|------------|---------------------------------------------------|
| USART2->BRR     | 0x682      | Set baud rate to 9600 @ 16MHz                     |
| USART2->CR1     | Bit 0      | UE — Enable USART2 peripheral                     |
| USART2->CR1     | Bit 2      | RE — Enable Receiver                              |
| USART2->CR1     | Bit 3      | TE — Enable Transmitter                           |
| USART2->CR1     | Bit 5      | RXNEIE — Enable RX not empty interrupt            |
| USART2->ISR     | Bit 5      | RXNE flag — 1 = new data received                 |
| USART2->ISR     | Bit 7      | TXE flag — 1 = TX register empty, ready to send  |
| USART2->RDR     | —          | Read received byte from here                      |
| USART2->TDR     | —          | Write byte here to transmit                       |

---
