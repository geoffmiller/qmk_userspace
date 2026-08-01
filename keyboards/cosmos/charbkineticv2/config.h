// You shouldn't need to edit any of this.

#pragma once

#include "keyboards/cosmos/charbkineticv2/vik/config.vik.pre.h"

#define EE_HANDS

#define VIK_SPI_DRIVER   SPID1
#define VIK_SPI_SCK_PIN  GP14
#define VIK_SPI_MOSI_PIN GP15
#define VIK_SPI_MISO_PIN GP12
#define VIK_SPI_CS       GP13
#define VIK_I2C_DRIVER   I2CD1
#define VIK_I2C_SDA_PIN  GP18
#define VIK_I2C_SCL_PIN  GP19
#define VIK_GPIO_1       GP26
#define VIK_GPIO_2       GP27
#define VIK_WS2812_DI_PIN GP2

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET

#define SPLIT_USB_DETECT
#define SERIAL_USART_FULL_DUPLEX
#define SERIAL_USART_PIN_SWAP
#define SERIAL_USART_TX_PIN GP0
#define SERIAL_USART_RX_PIN GP1

#define SPI_DRIVER SPID1
#define SPI_SCK_PIN GP14
#define SPI_MISO_PIN GP12
#define SPI_MOSI_PIN GP15

#define POINTING_DEVICE_CS_PIN GP13
#define PMW33XX_CS_PIN POINTING_DEVICE_CS_PIN
#define PMW33XX_CPI 1800
#define PMW33XX_CS_DIVISOR 8

#define SPLIT_POINTING_ENABLE
#define POINTING_DEVICE_RIGHT
#define ROTATIONAL_TRANSFORM_ANGLE 90
// #define POINTING_DEVICE_INVERT_X // Optional: Inverts trackball X
#define POINTING_DEVICE_INVERT_Y // Inverts trackball Y axis

/* Mouse settings */
#define MOUSE_EXTENDED_REPORT           /* Enable 16-bit mouse reports for smoother movement */

/* Auto mouse layer - automatically activate mouse layer when trackball moves */
#define POINTING_DEVICE_AUTO_MOUSE_ENABLE
#define AUTO_MOUSE_DEFAULT_LAYER 3

// Timeless Home Row Mods (urob/pgetreuer config)
#define TAPPING_TERM 250
#define PERMISSIVE_HOLD
#define FLOW_TAP_TERM 150
#define CHORDAL_HOLD
#define SPECULATIVE_HOLD

#include "keyboards/cosmos/charbkineticv2/vik/config.vik.post.h"
