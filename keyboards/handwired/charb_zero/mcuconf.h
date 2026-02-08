// Copyright 2025 Geoff (@geoffmiller)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <mcuconf.h>

/* Enable SPI1 for PMW3389 trackball sensor */
#undef RP_SPI_USE_SPI1
#define RP_SPI_USE_SPI1 TRUE
