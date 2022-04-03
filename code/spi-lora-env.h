/* 
 * spi-lora-env.h
 * written by edward kneller
 * 
 */

// include catch clause
#ifndef SPI_LORA_ENV_H
#define SPI_LORA_ENV_H

// ensure sys inclusions
#include <xc.h>
#include "sys-cfg-env.h"

// constant defs
// Max number of octets the LORA Rx/Tx FIFO can hold
#define LORA_FIFO_SIZE 255

// This is the maximum number of bytes that can be carried by the LORA.
// We use some for headers, keeping fewer for RadioHead messages
#define LORA_MAX_PAYLOAD_LEN LORA_FIFO_SIZE

// The length of the headers we add.
// The headers are inside the LORA's payload
#define LORA_HEADER_LEN 4

// This is the maximum message length that can be supported by this driver. 
// Can be pre-defined to a smaller size (to save SRAM) prior to including this header
// Here we allow for 1 byte message length, 4 bytes headers, user data and 2 bytes of FCS
#ifndef LORA_MAX_MESSAGE_LEN
 #define LORA_MAX_MESSAGE_LEN (LORA_MAX_PAYLOAD_LEN - LORA_HEADER_LEN)
#endif

// The crystal oscillator frequency of the module
#define LORA_FXOSC 32000000.0

// The Frequency Synthesizer step = LORA_FXOSC / 2^^19
#define LORA_FSTEP  (LORA_FXOSC / 524288)

// register names in lora mode
#define LORA_REG_00_FIFO                                0x00
#define LORA_REG_01_OP_MODE                             0x01
#define LORA_REG_02_RESERVED                            0x02
#define LORA_REG_03_RESERVED                            0x03
#define LORA_REG_04_RESERVED                            0x04
#define LORA_REG_05_RESERVED                            0x05
#define LORA_REG_06_FRF_MSB                             0x06
#define LORA_REG_07_FRF_MID                             0x07
#define LORA_REG_08_FRF_LSB                             0x08
#define LORA_REG_09_PA_CONFIG                           0x09
#define LORA_REG_0A_PA_RAMP                             0x0a
#define LORA_REG_0B_OCP                                 0x0b
#define LORA_REG_0C_LNA                                 0x0c
#define LORA_REG_0D_FIFO_ADDR_PTR                       0x0d
#define LORA_REG_0E_FIFO_TX_BASE_ADDR                   0x0e
#define LORA_REG_0F_FIFO_RX_BASE_ADDR                   0x0f
#define LORA_REG_10_FIFO_RX_CURRENT_ADDR                0x10
#define LORA_REG_11_IRQ_FLAGS_MASK                      0x11
#define LORA_REG_12_IRQ_FLAGS                           0x12
#define LORA_REG_13_RX_NB_BYTES                         0x13
#define LORA_REG_14_RX_HEADER_CNT_VALUE_MSB             0x14
#define LORA_REG_15_RX_HEADER_CNT_VALUE_LSB             0x15
#define LORA_REG_16_RX_PACKET_CNT_VALUE_MSB             0x16
#define LORA_REG_17_RX_PACKET_CNT_VALUE_LSB             0x17
#define LORA_REG_18_MODEM_STAT                          0x18
#define LORA_REG_19_PKT_SNR_VALUE                       0x19
#define LORA_REG_1A_PKT_RSSI_VALUE                      0x1a
#define LORA_REG_1B_RSSI_VALUE                          0x1b
#define LORA_REG_1C_HOP_CHANNEL                         0x1c
#define LORA_REG_1D_MODEM_CONFIG1                       0x1d
#define LORA_REG_1E_MODEM_CONFIG2                       0x1e
#define LORA_REG_1F_SYMB_TIMEOUT_LSB                    0x1f
#define LORA_REG_20_PREAMBLE_MSB                        0x20
#define LORA_REG_21_PREAMBLE_LSB                        0x21
#define LORA_REG_22_PAYLOAD_LENGTH                      0x22
#define LORA_REG_23_MAX_PAYLOAD_LENGTH                  0x23
#define LORA_REG_24_HOP_PERIOD                          0x24
#define LORA_REG_25_FIFO_RX_BYTE_ADDR                   0x25
#define LORA_REG_26_MODEM_CONFIG3                       0x26

#define LORA_REG_27_PPM_CORRECTION                      0x27
#define LORA_REG_28_FEI_MSB                             0x28
#define LORA_REG_29_FEI_MID                             0x29
#define LORA_REG_2A_FEI_LSB                             0x2a
#define LORA_REG_2C_RSSI_WIDEBAND                       0x2c
#define LORA_REG_31_DETECT_OPTIMIZ                      0x31
#define LORA_REG_33_INVERT_IQ                           0x33
#define LORA_REG_37_DETECTION_THRESHOLD                 0x37
#define LORA_REG_39_SYNC_WORD                           0x39

#define LORA_REG_40_DIO_MAPPING1                        0x40
#define LORA_REG_41_DIO_MAPPING2                        0x41
#define LORA_REG_42_VERSION                             0x42

#define LORA_REG_4B_TCXO                                0x4b
#define LORA_REG_4D_PA_DAC                              0x4d
#define LORA_REG_5B_FORMER_TEMP                         0x5b
#define LORA_REG_61_AGC_REF                             0x61
#define LORA_REG_62_AGC_THRESH1                         0x62
#define LORA_REG_63_AGC_THRESH2                         0x63
#define LORA_REG_64_AGC_THRESH3                         0x64


// reg 01 op mode                                  0x01
#define LORA_LONG_RANGE_MODE                       0x80
#define LORA_ACCESS_SHARED_REG                     0x40
#define LORA_LOW_FREQUENCY_MODE                    0x08
#define LORA_MODE                                  0x07
#define LORA_MODE_SLEEP                            0x00
#define LORA_MODE_STDBY                            0x01
#define LORA_MODE_FSTX                             0x02
#define LORA_MODE_TX                               0x03
#define LORA_MODE_FSRX                             0x04
#define LORA_MODE_RXCONTINUOUS                     0x05
#define LORA_MODE_RXSINGLE                         0x06
#define LORA_MODE_CAD                              0x07

// LORA_REG_09_PA_CONFIG                           0x09
#define LORA_PA_SELECT                             0x80
#define LORA_MAX_POWER                             0x70
#define LORA_OUTPUT_POWER                          0x0f

// LORA_REG_0A_PA_RAMP                             0x0a
#define LORA_LOW_PN_TX_PLL_OFF                     0x10
#define LORA_PA_RAMP                               0x0f
#define LORA_PA_RAMP_3_4MS                         0x00
#define LORA_PA_RAMP_2MS                           0x01
#define LORA_PA_RAMP_1MS                           0x02
#define LORA_PA_RAMP_500US                         0x03
#define LORA_PA_RAMP_250US                         0x00
#define LORA_PA_RAMP_125US                         0x05
#define LORA_PA_RAMP_100US                         0x06
#define LORA_PA_RAMP_62US                          0x07
#define LORA_PA_RAMP_50US                          0x08
#define LORA_PA_RAMP_40US                          0x09
#define LORA_PA_RAMP_31US                          0x0a
#define LORA_PA_RAMP_25US                          0x0b
#define LORA_PA_RAMP_20US                          0x0c
#define LORA_PA_RAMP_15US                          0x0d
#define LORA_PA_RAMP_12US                          0x0e
#define LORA_PA_RAMP_10US                          0x0f

// LORA_REG_0B_OCP                                 0x0b
#define LORA_OCP_ON                                0x20
#define LORA_OCP_TRIM                              0x1f

// LORA_REG_0C_LNA                                 0x0c
#define LORA_LNA_GAIN                              0xe0
#define LORA_LNA_GAIN_G1                           0x20
#define LORA_LNA_GAIN_G2                           0x40
#define LORA_LNA_GAIN_G3                           0x60                
#define LORA_LNA_GAIN_G4                           0x80
#define LORA_LNA_GAIN_G5                           0xa0
#define LORA_LNA_GAIN_G6                           0xc0
#define LORA_LNA_BOOST_LF                          0x18
#define LORA_LNA_BOOST_LF_DEFAULT                  0x00
#define LORA_LNA_BOOST_HF                          0x03
#define LORA_LNA_BOOST_HF_DEFAULT                  0x00
#define LORA_LNA_BOOST_HF_150PC                    0x11

// LORA_REG_11_IRQ_FLAGS_MASK                      0x11
#define LORA_RX_TIMEOUT_MASK                       0x80
#define LORA_RX_DONE_MASK                          0x40
#define LORA_PAYLOAD_CRC_ERROR_MASK                0x20
#define LORA_VALID_HEADER_MASK                     0x10
#define LORA_TX_DONE_MASK                          0x08
#define LORA_CAD_DONE_MASK                         0x04
#define LORA_FHSS_CHANGE_CHANNEL_MASK              0x02
#define LORA_CAD_DETECTED_MASK                     0x01

// LORA_REG_12_IRQ_FLAGS                           0x12
#define LORA_RX_TIMEOUT                            0x80
#define LORA_RX_DONE                               0x40
#define LORA_PAYLOAD_CRC_ERROR                     0x20
#define LORA_VALID_HEADER                          0x10
#define LORA_TX_DONE                               0x08
#define LORA_CAD_DONE                              0x04
#define LORA_FHSS_CHANGE_CHANNEL                   0x02
#define LORA_CAD_DETECTED                          0x01

// LORA_REG_18_MODEM_STAT                          0x18
#define LORA_RX_CODING_RATE                        0xe0
#define LORA_MODEM_STATUS_CLEAR                    0x10
#define LORA_MODEM_STATUS_HEADER_INFO_VALID        0x08
#define LORA_MODEM_STATUS_RX_ONGOING               0x04
#define LORA_MODEM_STATUS_SIGNAL_SYNCHRONIZED      0x02
#define LORA_MODEM_STATUS_SIGNAL_DETECTED          0x01

// LORA_REG_1C_HOP_CHANNEL                         0x1c
#define LORA_PLL_TIMEOUT                           0x80
#define LORA_RX_PAYLOAD_CRC_IS_ON                  0x40
#define LORA_FHSS_PRESENT_CHANNEL                  0x3f

// LORA_REG_1D_MODEM_CONFIG1                       0x1d
#define LORA_BW                                    0xf0

#define LORA_BW_7_8KHZ                             0x00
#define LORA_BW_10_4KHZ                            0x10
#define LORA_BW_15_6KHZ                            0x20
#define LORA_BW_20_8KHZ                            0x30
#define LORA_BW_31_25KHZ                           0x40
#define LORA_BW_41_7KHZ                            0x50
#define LORA_BW_62_5KHZ                            0x60
#define LORA_BW_125KHZ                             0x70
#define LORA_BW_250KHZ                             0x80
#define LORA_BW_500KHZ                             0x90
#define LORA_CODING_RATE                           0x0e
#define LORA_CODING_RATE_4_5                       0x02
#define LORA_CODING_RATE_4_6                       0x04
#define LORA_CODING_RATE_4_7                       0x06
#define LORA_CODING_RATE_4_8                       0x08
#define LORA_IMPLICIT_HEADER_MODE_ON               0x01

// LORA_REG_1E_MODEM_CONFIG2                       0x1e
#define LORA_SPREADING_FACTOR                      0xf0
#define LORA_SPREADING_FACTOR_64CPS                0x60
#define LORA_SPREADING_FACTOR_128CPS               0x70
#define LORA_SPREADING_FACTOR_256CPS               0x80
#define LORA_SPREADING_FACTOR_512CPS               0x90
#define LORA_SPREADING_FACTOR_1024CPS              0xa0
#define LORA_SPREADING_FACTOR_2048CPS              0xb0
#define LORA_SPREADING_FACTOR_4096CPS              0xc0
#define LORA_TX_CONTINUOUS_MOE                     0x08

#define LORA_PAYLOAD_CRC_ON                        0x04
#define LORA_SYM_TIMEOUT_MSB                       0x03

// LORA_REG_4B_TCXO                                0x4b
#define LORA_TCXO_TCXO_INPUT_ON                    0x10

// LORA_REG_4D_PA_DAC                              0x4d
#define LORA_PA_DAC_DISABLE                        0x04
#define LORA_PA_DAC_ENABLE                         0x07


#define LORA_TX_PWR 13
#define LORA_FREQUENCY 915.0

#define LORA_ARDUINO_ADDRESS 69
#define LORA_MONITOR_ADDRESS 70

// global variables
uint8_t _mode;

enum {
    _txHeaderTo = LORA_ARDUINO_ADDRESS,
    _txHeaderFrom = LORA_MONITOR_ADDRESS,
    _txHeaderId,
    _txHeaderFlags
};

enum {
    LoraModeIdle,
    LoraModeSleep,
    LoraModeTX
};

// func decs
void lora_init();
void lora_write(uint8_t, uint8_t);
void lora_burst_write(uint8_t, uint8_t[], uint8_t);
uint8_t lora_read(uint8_t);

void lora_set_idle(void);
void lora_set_sleep(void);
void lora_set_tx(void);

void lora_send(uint8_t[], uint8_t);

// initialize lora module
void lora_init() {
    // set pins output
    _TRISA8 = 0; // RFEN
    _TRISB4 = 0; // RFRST
    _TRISA4 = 0; // RFINT
    _TRISA9 = 0; // RFCS
    
    // set pins non-od
    _ODA8 = 0; // RFEN
    _ODB4 = 0; // RFRST
    _ODA4 = 0; // RFINT
    _ODA9 = 0; // RFCS
    
    // set states
    RFEN = 1; // enable rf regulator
    RFRST = 1; // hold rf reset high
    RFCS = 1; // set rf chip select high
    
    __delay_ms(100); // setup time
    
    // set sleep mode
    lora_write(LORA_REG_01_OP_MODE, LORA_MODE_SLEEP | LORA_LONG_RANGE_MODE);
    __delay_ms(10); // wait for sleep mode
    
    // check if in sleep mode
    if (lora_read(LORA_REG_01_OP_MODE) != (LORA_MODE_SLEEP | LORA_LONG_RANGE_MODE)) {
     while (1); // trap if fail
    }
    
    // set up fifo
    lora_write(LORA_REG_0E_FIFO_TX_BASE_ADDR, 0);
    lora_write(LORA_REG_0F_FIFO_RX_BASE_ADDR, 0);
    
    lora_set_idle(); // set idle mode
    
    // set modem config
    lora_write(0x1D, 0x72);
    lora_write(0x1E, 0x74);
    lora_write(0x26, 0x04);
    
    // set preamble length
    lora_write(LORA_REG_20_PREAMBLE_MSB, 0);
    lora_write(LORA_REG_21_PREAMBLE_LSB, 8);
    
    // set frequency
    uint8_t _usingHFport;
    uint32_t frf = (LORA_FREQUENCY * 1000000.0) / LORA_FSTEP;
    lora_write(LORA_REG_06_FRF_MSB, (frf >> 16) & 0xff);
    lora_write(LORA_REG_07_FRF_MID, (frf >> 8) & 0xff);
    lora_write(LORA_REG_08_FRF_LSB, frf & 0xff);
    _usingHFport = (LORA_FREQUENCY >= 779.0);
    
    // set power
    lora_write(LORA_REG_4D_PA_DAC, LORA_PA_DAC_DISABLE);
    lora_write(LORA_REG_09_PA_CONFIG, LORA_PA_SELECT | (LORA_TX_PWR - 5));
}

// write bytes to lora module
void lora_write(uint8_t address, uint8_t data) {
    address = address | 0x80; // set msb to 1 for write
    
    RFCS = 0; // select chip
    __delay_us(1);
    spi1_write(address); // send address
    spi1_write(data); // send byte
    RFCS = 1; // deselect chip
}

// write multiple bytes
void lora_burst_write(uint8_t address, uint8_t *data, uint8_t length) {
    int i; // index variable
    address = address | 0x80; // set msb to 1 for write
    
    RFCS = 0; // select chip
    __delay_us(1);
    spi1_write(address); // send address
    for (i = 0; i < length; i++) {
        spi1_write(data[i]); // send each byte of data
    }
    RFCS = 1; // deselect chip
}

// read byte from lora module
uint8_t lora_read(uint8_t address) {
    uint8_t data; // buffer
    
    address = address & 0x7F; // set msb to 0 for read
    
    RFCS = 0; // select chip
    spi1_write(address); // send address
    data = spi1_read(); // read byte
    RFCS = 1; // deselect chip
    return data;
}

// set rfm95 to idle mode
void lora_set_idle(void) {
    if (_mode != LoraModeIdle) {
        lora_write(LORA_REG_01_OP_MODE, LORA_MODE_STDBY);
        _mode = LoraModeIdle;
    }
}

// set rfm95 to sleep mode
void lora_set_sleep(void) {
    if (_mode != LoraModeSleep) {
        lora_write(LORA_REG_01_OP_MODE, LORA_MODE_SLEEP);
        _mode = LoraModeSleep;
    }
}

// set rfm95 to tx mode
void lora_set_tx(void) {
    if (_mode != LoraModeTX) {
        lora_write(LORA_REG_01_OP_MODE, LORA_MODE_TX);
        _mode = LoraModeTX;
    }
}

// sends a message
void lora_send(uint8_t data[], uint8_t length) {
    lora_set_idle(); // set idle mode
    
    // set address to start of fifo buffer
    lora_write(LORA_REG_0D_FIFO_ADDR_PTR, 0);
    
    // write headers
    lora_write(LORA_REG_00_FIFO, _txHeaderTo);
    lora_write(LORA_REG_00_FIFO, _txHeaderFrom);
    lora_write(LORA_REG_00_FIFO, _txHeaderId);
    lora_write(LORA_REG_00_FIFO, _txHeaderFlags);
    
    // write data and payload length
    lora_burst_write(LORA_REG_00_FIFO, data, length);
    lora_write(LORA_REG_22_PAYLOAD_LENGTH, length + LORA_HEADER_LEN);
    
    lora_set_tx(); // start tx
    __delay_ms(100); // wait for tx
    lora_set_sleep(); // sleep for power use reduction
}
#endif


