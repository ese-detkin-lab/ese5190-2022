// @author: Ruturaj A. Nanoti
// @brief: Some Register definitions for the APDS9960 Sensor.

#ifndef APDS_REGISTERS_H
#define APDS_REGISTERS_H


#define APDS_ADDRESS ((volatile uint8_t)(0x39))

// Defining the register and specific bits in those registers for the APDS Protocol

// ENABLE REGISTER (0X80)
#define APDS_ENABLE_REGISTER ((volatile uint8_t)(0x80))
#define APDS_ENABLE_PON ((volatile uint8_t)(1u << 0)) // Power ON bit
#define APDS_ENABLE_AEN ((volatile uint8_t)(1u << 1)) // Ambient light sensor enable bit
#define APDS_ENABLE_PEN ((volatile uint8_t)(1u << 2)) // Proximity enable bit


// ATIME REGISTER (0X81)
#define ATIME_REGISTER ((volatile uint8_t)(0x81))

// WAIT TIME REGISTER (0X83)
#define WAIT_TIME_REGISTER ((volatile uint8_t)(0x83))
#define WAIT_TIME_REGISTER_WTIME ((volatile uint8_t)(0xF6))

// PERS REGISTER (0X8C)
#define PERS_REGISTER ((volatile uint8_t)(0x8C))
#define PERS_REGISTER_PERS ((volatile uint8_t)(1u << 0 | 1u << 1))

// CONFIG REGISTER (0x90)
#define CONFIG_REGISTER ((volatile uint8_t)(0x90))
#define CONFIG_REGISTER_CPSIEN ((volatile uint8_t)(1u << 6))


// CONTROL REGISTER ONE (0x8F)
#define APDS_CONTROL_ONE_REGISTER ((volatile uint8_t)(0x8F))
#define APDS_CONTROL_ONE_LDRIVE ((volatile uint8_t)(0u << 7 | 0u << 6)) // Set LED Drive current to 100 mA
#define APDS_CONTROL_ONE_PGAIN ((volatile uint8_t)(1u << 3 | 0u << 2)) // Set Proximity gain to 4x
#define APDS_CONTROL_ONE_AGAIN ((volatile uint8_t)(0u << 1 | 1u << 0)) // Set ALS and color gain to 4x

// STATUS REGISTER (0X93)
#define STATUS_REGISTER ((volatile uint8_t)(0x93))
#define STATUS_REGISTER_PVALID ((volatile uint8_t)(1u << 1)) // Mask this with actual read value to check
                                                              // the status.
#define STATUS_REGISTER_AVALID ((volatile uint8_t)(1u << 0)) // Mask this with actual read value to check
                                                              // the status.

// ID REGISTER (0X92)
#define ID_REGISTER ((volatile uint8_t)(0x92))

// RGBC DATA REGISTERS (0X94-0X9B)
#define RGBC_DATA_REGISTER_CDATAL ((volatile uint8_t)(0x94))
#define RGBC_DATA_REGISTER_CDATAH ((volatile uint8_t)(0x95))
#define RGBC_DATA_REGISTER_RDATAL ((volatile uint8_t)(0x96))
#define RGBC_DATA_REGISTER_RDATAH ((volatile uint8_t)(0x97))
#define RGBC_DATA_REGISTER_GDATAL ((volatile uint8_t)(0x98))
#define RGBC_DATA_REGISTER_GDATAH ((volatile uint8_t)(0x99))
#define RGBC_DATA_REGISTER_BDATAL ((volatile uint8_t)(0x9A))
#define RGBC_DATA_REGISTER_BDATAH ((volatile uint8_t)(0x9B))


// PROXIMITY DATA REGISTER (0X9C)
#define PROXIMITY_DATA_REGISTER ((volatile uint8_t)(0x9C))

#endif
