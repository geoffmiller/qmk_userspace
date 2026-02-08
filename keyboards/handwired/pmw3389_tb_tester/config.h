// Copyright 2025 Geoff (@geoffmiller)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* Minimal 1x1 matrix for QMK compatibility */
#define MATRIX_ROWS 1
#define MATRIX_COLS 1

/* SPI1 configuration for PMW3389 trackball
 * Using same pinout as charb_zero:
 * MISO = GP8
 * SCK  = GP15 (SPI1 SCK)
 * MOSI = GP14 (SPI1 TX)
 * CS   = GP27
 */
#define SPI_DRIVER SPID1
#define SPI_SCK_PIN GP15
#define SPI_MOSI_PIN GP14
#define SPI_MISO_PIN GP8
#define POINTING_DEVICE_CS_PIN GP27

/* Trackball rotation and inversion (adjust based on physical orientation) */
#define ROTATIONAL_TRANSFORM_ANGLE -90
#define POINTING_DEVICE_INVERT_X

/* Double-tap reset for RP2040 UF2 bootloader */
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 1000U
