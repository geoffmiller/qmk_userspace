# Charb Zero Wiring Guide

This document describes the wiring for the Charb Zero split keyboard using two Waveshare RP2040-Zero microcontrollers with a PMW3360 trackball on the right side.

## Overview

- **Left side**: 5 rows × 6 columns (30 keys)
- **Right side**: 5 rows × 6 columns (30 keys) + PMW3360 trackball
- **Communication**: Full-duplex UART via TRRS cable
- **Master**: Right side (has trackball)

---

## RP2040-Zero Pinout Reference

Based on the Waveshare RP2040-Zero:

```
                    ┌─────────────────┐
              5V ───┤ 5V         GP0  ├─── UART TX
             GND ───┤ GND        GP1  ├─── UART RX
             3V3 ───┤ 3V3        GP2  ├─── Column 0
    (ADC3)  GP29 ───┤ GP29       GP3  ├─── Column 1
    (ADC2)  GP28 ───┤ GP28       GP4  ├─── Column 2
    (ADC1)  GP27 ───┤ GP27       GP5  ├─── Column 3 (Right: Trackball CS)
    (ADC0)  GP26 ───┤ GP26       GP6  ├─── Column 4
  (SPI1 TX) GP15 ───┤ GP15       GP7  ├─── Column 5
 (SPI1 SCK) GP14 ───┤ GP14       GP8  ├─── (Right: Trackball MISO)
                    │                 │
                    │    [USB-C]      │
                    │                 │
             GP25 ───┤ GP25       GP9  ├─── Row 0
             GP24 ───┤ GP24      GP10  ├─── Row 1
             GP23 ───┤ GP23      GP11  ├─── Row 2
             GP22 ───┤ GP22      GP12  ├─── Row 3
             GP21 ───┤ GP21      GP13  ├─── Row 4
             GP20 ───┤ GP20            │
             GP19 ───┤ GP19            │
             GP18 ───┤ GP18            │
             GP17 ───┤ GP17            │
                    └─────────────────┘
```

---

## Left Side Wiring

### Matrix Pins

| Function | GPIO Pin | Notes         |
| -------- | -------- | ------------- |
| Column 0 | GP2      | Matrix column |
| Column 1 | GP3      | Matrix column |
| Column 2 | GP4      | Matrix column |
| Column 3 | GP5      | Matrix column |
| Column 4 | GP6      | Matrix column |
| Column 5 | GP7      | Matrix column |
| Row 0    | GP9      | Number row    |
| Row 1    | GP10     | QWERTY row    |
| Row 2    | GP11     | ASDF row      |
| Row 3    | GP12     | ZXCV row      |
| Row 4    | GP13     | Thumb row     |

### TRRS Connection (Left Side)

| Function | GPIO Pin | TRRS Pin      |
| -------- | -------- | ------------- |
| UART TX  | GP0      | → Right RX    |
| UART RX  | GP1      | ← Right TX    |
| Ground   | GND      | Common ground |
| Power    | 5V       | TRRS sleeve   |

---

## Right Side Wiring

### Matrix Pins

| Function | GPIO Pin | Notes         |
| -------- | -------- | ------------- |
| Column 0 | GP2      | Matrix column |
| Column 1 | GP3      | Matrix column |
| Column 2 | GP4      | Matrix column |
| Column 3 | GP5      | Matrix column |
| Column 4 | GP6      | Matrix column |
| Column 5 | GP7      | Matrix column |
| Row 0    | GP9      | Number row    |
| Row 1    | GP10     | YUIOP row     |
| Row 2    | GP11     | HJKL row      |
| Row 3    | GP12     | NM,. row      |
| Row 4    | GP13     | Thumb row     |

### Trackball (PMW3360) - Right Side Only

| Sensor Pin | GPIO Pin | RP2040 Function |
| ---------- | -------- | --------------- |
| MISO       | GP8      | SPI1 RX         |
| SCK        | GP14     | SPI1 SCK        |
| MOSI       | GP15     | SPI1 TX         |
| CS (SS)    | GP27     | Chip Select     |
| VCC        | 3V3      | 3.3V Power      |
| GND        | GND      | Ground          |

> **Note**: The PMW3360 uses the SPI1 peripheral on the RP2040-Zero.

### TRRS Connection (Right Side)

| Function | GPIO Pin | TRRS Pin      |
| -------- | -------- | ------------- |
| UART TX  | GP0      | → Left RX     |
| UART RX  | GP1      | ← Left TX     |
| Ground   | GND      | Common ground |
| Power    | 5V       | TRRS sleeve   |

---

## TRRS Cable Wiring

The UART lines must be **crossed** between the two halves:

```
Left Side                    Right Side
─────────                    ──────────
GP0 (TX) ──────────────────► GP1 (RX)
GP1 (RX) ◄────────────────── GP0 (TX)
GND ◄──────────────────────► GND
5V ◄───────────────────────► 5V
```

### TRRS Jack Pinout

| TRRS Position | Signal |
| ------------- | ------ |
| Tip           | TX     |
| Ring 1        | RX     |
| Ring 2        | VCC    |
| Sleeve        | GND    |

---

## Matrix Wiring Diagram

```
        COL0   COL1   COL2   COL3   COL4   COL5
        (GP2)  (GP3)  (GP4)  (GP5)  (GP6)  (GP7)
         │      │      │      │      │      │
ROW0 ────┼──D───┼──D───┼──D───┼──D───┼──D───┼──D─── (GP9)
(GP9)    │      │      │      │      │      │
         │      │      │      │      │      │
ROW1 ────┼──D───┼──D───┼──D───┼──D───┼──D───┼──D─── (GP10)
(GP10)   │      │      │      │      │      │
         │      │      │      │      │      │
ROW2 ────┼──D───┼──D───┼──D───┼──D───┼──D───┼──D─── (GP11)
(GP11)   │      │      │      │      │      │
         │      │      │      │      │      │
ROW3 ────┼──D───┼──D───┼──D───┼──D───┼──D───┼──D─── (GP12)
(GP12)   │      │      │      │      │      │
         │      │      │      │      │      │
ROW4 ────┼──D───┼──D───┼──D───┼──D───┼──D───┼──D─── (GP13)
(GP13)   │      │      │      │      │      │

D = Diode (cathode towards row, COL2ROW configuration)
```

---

## Notes

1. **Diode Direction**: COL2ROW - cathode (black band) towards the row pin
2. **Handedness**: Uses EE_HANDS - flash left/right handedness to EEPROM
3. **Hot Swap Warning**: Always disconnect USB before connecting/disconnecting TRRS cable
4. **Trackball Orientation**: Default config has -90° rotation and X inversion - adjust in `config.h` if needed
