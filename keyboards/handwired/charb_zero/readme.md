# Charb Zero - Charybdis 4x6 with RP2040-Zero

![Charb Zero](../../../images/charb_zero.png)

A split ergonomic keyboard based on the Charybdis 4x6 layout with a PMW3389 trackball on the right side.

## Hardware

- **MCU**: 2x Waveshare RP2040-Zero
- **Layout**: 4x6 split with 6 thumb keys per side
- **Trackball**: PMW3389 (right side only)
- **Communication**: Full-duplex UART via TRRS cable

## Wiring

### Matrix Pins (Both Sides)

| Function | GPIO Pin |
| -------- | -------- |
| Column 0 | GP2      |
| Column 1 | GP3      |
| Column 2 | GP4      |
| Column 3 | GP5      |
| Column 4 | GP6      |
| Column 5 | GP7      |
| Row 0    | GP9      |
| Row 1    | GP10     |
| Row 2    | GP11     |
| Row 3    | GP12     |
| Row 4    | GP13     |

### Split Communication (TRRS)

| Function | GPIO Pin |
| -------- | -------- |
| UART TX  | GP0      |
| UART RX  | GP1      |
| Ground   | GND      |
| Power    | 5V       |

### Trackball (Right Side Only - PMW3389 via SPI1)

| Sensor Pin | GPIO Pin | Function    |
| ---------- | -------- | ----------- |
| MISO       | GP8      | SPI1 RX     |
| SCK        | GP14     | SPI1 SCK    |
| MOSI       | GP15     | SPI1 TX     |
| CS         | GP27     | Chip Select |
| VCC        | 3V3      | Power       |
| GND        | GND      | Ground      |

## Building

```bash
qmk compile -kb handwired/charb_test -km default
```

## Flashing

Put the RP2040-Zero into bootloader mode by:

1. Double-tap the reset button, OR
2. Hold BOOT while pressing RESET

Then copy the `.uf2` file to the mounted drive.

For EEPROM handedness (first time only):

```bash
# Left side
qmk flash -kb handwired/charb_test -km default -bl uf2-split-left

# Right side
qmk flash -kb handwired/charb_test -km default -bl uf2-split-right
```

## Features

- Auto mouse layer (layer 3) - activates when trackball is used
- Caps Word - press both shift keys to enable
- Mod-tap keys for efficient layer access
