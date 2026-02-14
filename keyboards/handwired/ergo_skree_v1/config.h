// Copyright 2025 Geoff (@geoffmiller)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* Key matrix size */
#define MATRIX_ROWS 12
#define MATRIX_COLS 6

/* Full-duplex USART serial for split communication (Pico Flex cross-link) */
#define SERIAL_USART_FULL_DUPLEX
#define SERIAL_USART_TX_PIN GP0
#define SERIAL_USART_RX_PIN GP1
#define SERIAL_PIO_USE_PIO0
#define SERIAL_USART_TIMEOUT 100
#define SERIAL_USART_SPEED 921600
#define SERIAL_USART_PIN_SWAP

/* Handedness determined by solder jumper on Pico Flex (JMP L/R) */
/* High = Left, Low = Right */
#define SPLIT_HAND_PIN GP28

/* Split transport settings */
#define SPLIT_TRANSPORT_MIRROR
#define SPLIT_USB_TIMEOUT 5000

/* Master side is right (has USB connection typically) */
#define MASTER_RIGHT

/* Bootmagic key positions - hold key while plugging in to enter bootloader */
/* Left side: row 0, col 0 (the ` key) */
#define BOOTMAGIC_ROW 0
#define BOOTMAGIC_COLUMN 0
/* Right side: row 0, col 0 LOCAL (the 6 key) */
#define BOOTMAGIC_ROW_RIGHT 0
#define BOOTMAGIC_COLUMN_RIGHT 0

/* Trackball support - SPI0 configuration (both sides have trackball)
 * Wiring on Pico Flex: SCK=GP2, MOSI=GP3, MISO=GP4, SS=GP5
 */
#define SPLIT_POINTING_ENABLE
#define POINTING_DEVICE_COMBINED
#define SPI_DRIVER SPID0
#define SPI_SCK_PIN GP2
#define SPI_MOSI_PIN GP3
#define SPI_MISO_PIN GP4
#define POINTING_DEVICE_CS_PIN GP5

/* PMW3360 sensor settings */
#define PMW33XX_CS_PIN GP5
/* Rotation and inversion handled per-side in keymap.c */

/* Mouse settings */
#define MOUSE_EXTENDED_REPORT           /* Enable 16-bit mouse reports for smoother movement */

/* Auto mouse layer - automatically activate mouse layer when trackball moves */
#define POINTING_DEVICE_AUTO_MOUSE_ENABLE
#define AUTO_MOUSE_DEFAULT_LAYER 3

/* Double-tap reset for RP2040 UF2 bootloader */
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 1000U

// Timeless Home Row Mods (urob/pgetreuer config)
#define TAPPING_TERM 250
#define PERMISSIVE_HOLD
#define FLOW_TAP_TERM 150
#define CHORDAL_HOLD
#define SPECULATIVE_HOLD
