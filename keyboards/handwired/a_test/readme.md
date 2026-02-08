# a_test - Cosmos Dactyl 7x5 with Trackball

![Cosmos Trackball Split Keyboard](../../../images/a_test_render.png)
![Wiring](../../../images/a_test_wiring.png)

A handwired 5×7 split ergonomic keyboard generated with the [Cosmos Dactyl generator](https://ryanis.cool/cosmos/beta#cm:CpQCChYSBRCASyAnEgUQkEEgExICIAASADgxChYSBRCAVyAnEgUQkE0gExICIAASADgdCi4SCRCAYyAnQICAKBIJEJBZIBNAgIAoEgYgAECAgCgSBxCwL0CAgCg4CECA8KQBChkSBRCAbyAnEgUQkGUgExICIAASAxCwOzgKCigSCBCAFyAnQIBQEggQkHEgE0CAWBIFIABAgFASA0CAUDgeQICGivABCiESBRCAIyAnEgQQECATEgYQoIAKIAASAhAwODJAgIaK8AIKFRIFEIA/ICcSChAQIBNAI0iAhh44RQolEhAQECATQOui/QFI2YaekO4BEg8gAED/h4i5B0jZhp6AngQ4WRgAQOiFoK7wVUjcoJdgCpUBCj4SERAgQIKD2LMBSIOdvKP5AVAdEhFAmoSGyAVIh52EnsDwAVCqARITCIAoEEBAqJiGuBxIh52EHlDyAlCafQocEhQQMECYg8CMsFhIh52EnpD/AlC6BDCAIFDofAobEhQQQCAAMMgBQJmUm5ADSIDAruDYAjCWIDgAGAoiBRDIASAAMIAwQNuRpJzwN0iEj5TWoHgQAiILCMMBEMMBGAAg0AU4AoIBAgQCWEdoAA==).

## Hardware

- **Controllers**: 2× Raspberry Pi Pico (RP2040)
- **Keys**: 70 total (5 rows × 7 columns per side)
- **Trackball**: PMW3389 on the right side via SPI0
- **Communication**: Full-duplex USART via TRRS cable
- **Handedness**: EE_HANDS (stored in EEPROM)
- **Diodes**: COL2ROW
- **Features**: Auto-mouse layer, Caps Word, NKRO

## Wiring

### Matrix Pins (Both Sides)

| Function | GPIO Pin |
| -------- | -------- |
| Column 0 | GP4      |
| Column 1 | GP5      |
| Column 2 | GP6      |
| Column 3 | GP7      |
| Column 4 | GP8      |
| Column 5 | GP9      |
| Column 6 | GP10     |
| Row 0    | GP11     |
| Row 1    | GP12     |
| Row 2    | GP13     |
| Row 3    | GP14     |
| Row 4    | GP15     |

### Split Communication (TRRS)

| Function | GPIO Pin |
| -------- | -------- |
| UART TX  | GP0      |
| UART RX  | GP1      |

### Trackball (Right Side Only - PMW3389 via SPI0)

| Sensor Pin | GPIO Pin | Function    |
| ---------- | -------- | ----------- |
| SCK        | GP18     | SPI0 SCK    |
| MOSI       | GP19     | SPI0 TX     |
| MISO       | GP20     | SPI0 RX     |
| CS         | GP21     | Chip Select |
| VCC        | 3V3      | Power       |
| GND        | GND      | Ground      |

## Flashing

### Initial Setup (One-time)

To ensure the correct handedness for each side, use the specific keymaps for each half. This stores the handedness in EEPROM so it persists across firmware updates.

**Flash Left Side:**
Connect the left half in bootloader mode and run:

```bash
qmk flash -kb handwired/a_test -km force_left
```

**Flash Right Side:**
Connect the right half in bootloader mode and run:

```bash
qmk flash -kb handwired/a_test -km force_right
```

### Regular Updates

After the initial setup, you can flash the default keymap to either side (or both) and they will remember their handedness:

```bash
qmk flash -kb handwired/a_test -km default
```

**Note:** You only need to use `force_left` or `force_right` again if you clear the EEPROM or perform a factory reset.

### Entering Bootloader Mode

Enter the bootloader in 3 ways:

- **Bootmagic reset**: Hold down ESC (top left key) and plug in the keyboard
- **Physical reset button**: Double-tap the reset button on the Pico
- **Keycode in layout**: Press the key mapped to `QK_BOOT` (available on Layer 1 left thumb and Layer 2 right thumb)

## Keymap Layouts

### Layer 0 (Base Layer)

```
Left Half:                                          Right Half:
┌─────┬─────┬─────┬─────┬─────┬─────┬─────┐      ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┐
│ ESC │  `  │  1  │  2  │  3  │  4  │  5  │      │  6  │  7  │  8  │  9  │  0  │  -  │  =  │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┤      ├─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│ TAB │  Q  │  W  │  E  │  R  │  T  │BTN1 │      │BTN1 │  Y  │  U  │  I  │  O  │  P  │  \  │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┤      ├─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│LSHFT│  A  │  S  │  D  │  F  │  G  │BTN2 │      │VOL+ │  H  │  J  │  K  │  L  │  ;  │ '⇧  │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┤      ├─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│LSHFT│ Z⌃  │  X  │  C  │  V  │  B  │MUTE │      │VOL- │  N  │  M  │  ,  │  .  │  /  │RSHFT│
├─────┼─────┼─────┼─────┼─────┼─────┼─────┤      ├─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│  ✗  │  ✗  │ ALT │ GUI │ SPC │LT1⏎ │  ✗  │      │  ✗  │LT2⏎ │BSPC │ GUI │ ALT │  ✗  │  ✗  │
└─────┴─────┴─────┴─────┴─────┴─────┴─────┘      └─────┴─────┴─────┴─────┴─────┴─────┴─────┘

Legend:
  Z⌃   = Hold: Left Ctrl, Tap: Z
  '⇧   = Hold: Right Shift, Tap: '
  LT1⏎ = Hold: Layer 1, Tap: Enter
  LT2⏎ = Hold: Layer 2, Tap: Enter
  BTN1/BTN2 = Mouse Buttons 1 & 2
  ✗    = No key
```

### Layer 1 (Navigation & Brackets)

```
Left Half:                                          Right Half:
┌─────┬─────┬─────┬─────┬─────┬─────┬─────┐      ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┐
│ TO0 │     │     │     │     │     │     │      │     │     │     │  (  │  )  │     │ TO1 │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┤      ├─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │     │     │     │     │     │      │     │     │     │  [  │  ]  │     │     │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┤      ├─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│CAPS │     │     │     │     │     │     │      │     │     │     │  {  │  }  │     │     │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┤      ├─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│CAPS │     │     │     │     │     │BOOT │      │     │  ←  │  ↓  │  ↑  │  →  │     │     │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┤      ├─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│  ✗  │  ✗  │     │     │     │     │  ✗  │      │  ✗  │  ←  │  ↓  │  ↑  │  →  │  ✗  │  ✗  │
└─────┴─────┴─────┴─────┴─────┴─────┴─────┘      └─────┴─────┴─────┴─────┴─────┴─────┴─────┘
```

### Layer 2 (Function Keys & Mouse)

```
Left Half:                                          Right Half:
┌─────┬─────┬─────┬─────┬─────┬─────┬─────┐      ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┐
│ TO0 │     │ F1  │ F2  │ F3  │ F4  │ F5  │      │ F6  │ F7  │ F8  │ F9  │ F10 │ F11 │ TO2 │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┤      ├─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │     │ M↑  │     │     │     │      │     │     │     │     │     │     │     │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┤      ├─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│CAPS │ M←← │ M←  │ M↓  │ M→  │ M→→ │     │      │     │WHL↓ │WHL↑ │     │     │     │     │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┤      ├─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│CAPS │     │     │     │     │     │     │      │BOOT │  ←  │  ↓  │  ↑  │  →  │     │     │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┤      ├─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│  ✗  │  ✗  │     │     │     │     │  ✗  │      │  ✗  │BTN1 │BTN2 │     │     │  ✗  │  ✗  │
└─────┴─────┴─────┴─────┴─────┴─────┴─────┘      └─────┴─────┴─────┴─────┴─────┴─────┴─────┘

Legend:
  M↑/↓/←/→ = Mouse cursor movement
  M←← / M→→ = Mouse left/right (double speed)
  WHL↓ / WHL↑ = Mouse wheel down/up
```

### Layer 3 (Auto-Mouse Layer)

Automatically activated by trackball movement.

```
Left Half:                                          Right Half:
┌─────┬─────┬─────┬─────┬─────┬─────┬─────┐      ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┐
│     │     │     │     │     │     │     │      │     │     │     │     │     │     │     │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┤      ├─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │     │     │BTN1 │BTN1 │BTN1 │      │     │     │     │     │     │     │     │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┤      ├─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │WHL← │WHL↓ │WHL↑ │WHL→ │BTN2 │      │     │     │     │     │     │     │     │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┤      ├─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │     │     │     │     │     │      │     │     │     │     │     │     │     │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┤      ├─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│  ✗  │  ✗  │     │     │     │     │  ✗  │      │  ✗  │     │     │     │     │  ✗  │  ✗  │
└─────┴─────┴─────┴─────┴─────┴─────┴─────┘      └─────┴─────┴─────┴─────┴─────┴─────┴─────┘

Legend:
  WHL↑/↓/←/→ = Mouse wheel up/down/left/right
  BTN1/BTN2 = Mouse buttons 1 and 2
```

## Features

### Caps Word

Press both shift keys simultaneously to activate Caps Word mode. This capitalizes letters until you press space, enter, or any non-letter key.

### Auto-Mouse Layer

Moving the trackball automatically activates Layer 3 (mouse layer) for easy access to mouse buttons and scroll wheels.

## Components

- **Microcontrollers**: 2× Raspberry Pi Pico
- **Trackball Sensor**: PMW3389 (high-precision optical sensor)
- **Switches**: 70× mechanical switches (your choice)
- **Diodes**: 70× 1N4148 diodes
- **TRRS Cable**: For connecting the two halves
