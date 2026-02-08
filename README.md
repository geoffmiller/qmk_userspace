# QMK Userspace - Geoff's Keyboards

This repository contains my personal QMK keyboard configurations using the QMK Userspace feature. It includes multiple handwired split ergonomic keyboards, all featuring RP2040-based controllers and PMW3389 trackball sensors.

## Keyboards

| Keyboard                                                    | Keys | Controller          | Split            | Trackball  | VIA |
| ----------------------------------------------------------- | ---- | ------------------- | ---------------- | ---------- | --- |
| [a_test](keyboards/handwired/a_test/)                       | 70   | Raspberry Pi Pico   | ✅ UART / TRRS   | Right side | ❌  |
| [charb_zero](keyboards/handwired/charb_zero/)               | 60   | RP2040-Zero         | ✅ UART / TRRS   | Right side | ❌  |
| [ergo_skree_v1](keyboards/handwired/ergo_skree_v1/)         | 72   | Pi Pico + Pico Flex | ✅ USART / USB-C | Both sides | ✅  |
| [pmw3389_tb_tester](keyboards/handwired/pmw3389_tb_tester/) | 1    | RP2040-Zero         | ❌               | Yes        | ❌  |

### [a_test](keyboards/handwired/a_test/) - Cosmos Dactyl 7x5

![Cosmos Trackball Split Keyboard](./images/a_test_render.png)

A handwired 5×7 split ergonomic keyboard generated with the [Cosmos Dactyl generator](https://ryanis.cool/cosmos/beta). 70 keys, PMW3389 trackball on the right side, full-duplex USART over TRRS, auto-mouse layer, and Caps Word.

### [charb_zero](keyboards/handwired/charb_zero/) - Charybdis 4x6

![Charb Zero](./images/charb_zero.png)

A Charybdis-style 4×6 split ergonomic keyboard. 60 keys, PMW3389 trackball on the right side, full-duplex USART over TRRS, auto-mouse layer, and Caps Word.

### [ergo_skree_v1](keyboards/handwired/ergo_skree_v1/) - Kinesis Advantage Style

![Ergo Skree V1](./images/ergo_skree_v1.png)

A Kinesis Advantage 2 style split ergo using the [Pico Flex](https://skree.us/products/pico-flex) breakout board from TheBigSkree. 72 keys, PMW3389 trackball on both sides, full-duplex USART over USB-C cross-link, VIA support, auto-mouse layer, and Caps Word.

### [pmw3389_tb_tester](keyboards/handwired/pmw3389_tb_tester/) - Trackball Test Jig

A minimal single-key test board for verifying PMW3389 trackball sensor wiring and functionality. Not a daily-driver — just a hardware verification jig.

---

## Setup

### Prerequisites

1. Install QMK CLI:

   ```bash
   python3 -m pip install --user qmk
   ```

2. Setup QMK:
   ```bash
   qmk setup
   ```

### Using this Userspace

1. Clone this repository:

   ```bash
   git clone https://github.com/geoffmiller/cosmo-trackball-split.git ~/qmk_userspace
   cd ~/qmk_userspace
   ```

2. Set QMK userspace:

   ```bash
   qmk config user.overlay_dir="$(realpath .)"
   ```

## Flashing

Each keyboard's README has specific flashing instructions. The general pattern is:

```bash
qmk flash -kb handwired/<keyboard_name> -km default
```

### Entering Bootloader Mode

- **Bootmagic reset**: Hold down ESC (top left key) and plug in the keyboard
- **Physical reset button**: Briefly press the button on the back of the controller
- **Keycode in layout**: Press the key mapped to `QK_BOOT` if available in your keymap

### Split Keyboard Handedness

For keyboards using **EE_HANDS** (a_test, charb_zero), flash handedness once using the `force_left` / `force_right` keymaps. After that, the default keymap can be flashed to either side. You only need to re-flash handedness if you clear EEPROM.

For **ergo_skree_v1**, handedness is determined by a solder jumper on GP28 — no special keymap needed.

## Additional Resources

- [QMK Firmware Documentation](https://docs.qmk.fm/)
- [QMK Build Environment Setup](https://docs.qmk.fm/#/getting_started_build_tools)
- [QMK Newbs Guide](https://docs.qmk.fm/#/newbs)
- [Ryan is cool's Cosmos Generator](https://ryanis.cool/cosmos/beta)
- [TheBigSkree Pico Flex](https://skree.us/products/pico-flex)

## License
