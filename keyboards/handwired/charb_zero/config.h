// Copyright 2025 Geoff (@geoffmiller)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* Key matrix size */
#define MATRIX_ROWS 10
#define MATRIX_COLS 6

/* Full-duplex USART serial for split communication */
#define SERIAL_USART_FULL_DUPLEX
#define SERIAL_USART_TX_PIN GP0
#define SERIAL_USART_RX_PIN GP1

/* Handedness stored in EEPROM */
#define EE_HANDS

/* Split transport settings */
#define SPLIT_TRANSPORT_MIRROR
#define SPLIT_USB_TIMEOUT 5000

/* Trackball - Right side only using PMW3389 sensor */
#define SPLIT_POINTING_ENABLE
#define POINTING_DEVICE_RIGHT

/* SPI1 configuration for PMW3389 trackball
 * Wiring: MISO=GP8, SCK=GP15, MOSI=GP14, CS=GP27
 */
#define SPI_DRIVER SPID1
#define SPI_SCK_PIN GP15
#define SPI_MOSI_PIN GP14
#define SPI_MISO_PIN GP8
#define POINTING_DEVICE_CS_PIN GP27

/* Trackball rotation and inversion (adjust based on physical orientation) */
#define ROTATIONAL_TRANSFORM_ANGLE -45
#define POINTING_DEVICE_INVERT_X

/* Auto mouse layer - automatically activate mouse layer when trackball moves */
#define POINTING_DEVICE_AUTO_MOUSE_ENABLE
#define AUTO_MOUSE_DEFAULT_LAYER 3

/* Double-tap reset for RP2040 UF2 bootloader */
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 1000U
