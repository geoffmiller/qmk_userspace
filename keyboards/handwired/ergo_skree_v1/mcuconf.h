// Copyright 2025 Geoff (@geoffmiller)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <mcuconf.h>

/* Enable SPI0 for future PMW3360/3389 trackball sensor support
 * Pico Flex trackball pins: SCK=GP2, MOSI=GP3, MISO=GP4, SS=GP5
 */
#undef RP_SPI_USE_SPI0
#define RP_SPI_USE_SPI0 TRUE
