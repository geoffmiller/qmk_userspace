# Ergo Skree V1

![Ergo Skree V1](../../../images/ergo_skree_v1.png)

A Kinesis Advantage 2 style split ergonomic keyboard using Raspberry Pi Pico microcontrollers with the Pico Flex breakout board from [TheBigSkree](https://skree.us/products/pico-flex).

## Features

- **Layout**: Kinesis Advantage 2 style (6x6 matrix per side = 72 keys total)
- **MCU**: Raspberry Pi Pico (RP2040) with Pico Flex breakout board
- **Split Communication**: Full-duplex USART via USB-C cross-link cable
- **Handedness**: Determined by solder jumper (GP28)
- **VIA Support**: Yes, for easy keymap customization
- **Future Ready**: Trackball, RGB, OLED, and encoder pins available

## Hardware

### Pico Flex Breakout Board

The Pico Flex from TheBigSkree provides:

- USB-C cross-link for full-duplex serial split communication
- JST-SH connections for OLED, trackball sensors (PMW3360/3389), encoders
- Support for Skree flexible PCBs
- Solder jumper for left/right hand determination

### Pinout

| Function       | GPIO Pins                                  |
| -------------- | ------------------------------------------ |
| Columns        | GP10, GP9, GP11, GP12, GP13, GP14          |
| Rows           | GP18, GP21, GP17, GP20, GP16, GP15 (thumb) |
| UART TX        | GP0                                        |
| UART RX        | GP1                                        |
| Hand Pin       | GP28 (high=left, low=right)                |
| Trackball SCK  | GP2                                        |
| Trackball MOSI | GP3                                        |
| Trackball MISO | GP4                                        |
| Trackball CS   | GP5                                        |
| RGB Data       | GP8                                        |
| Encoder 1 A/B  | GP6, GP7                                   |

## Building

```bash
qmk compile -kb handwired/ergo_skree_v1 -km default
```

## Flashing

1. Hold BOOTSEL button on Pico while plugging in USB (or double-tap reset)
2. Copy the `.uf2` file to the RPI-RP2 drive that appears
3. The Pico will automatically reboot with the new firmware

## Handedness Setup

The Pico Flex has a solder jumper labeled "JMP L/R":

- **Left side**: Solder the jumper to make GP28 HIGH
- **Right side**: Leave the jumper open (GP28 LOW)

## Keymap

The default keymap follows the Kinesis Advantage 2 layout:

- **Base Layer**: Standard QWERTY with Kinesis-style thumb clusters
- **Keypad Layer**: Numpad on the right hand
- **Function Layer**: F-keys, media controls, and navigation

## Future Enhancements

The Pico Flex supports these features (pins reserved in firmware):

- PMW3389 trackball sensor
- RGB underglow (GP8)
- OLED display
- Rotary encoders
