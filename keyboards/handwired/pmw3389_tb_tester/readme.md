# PMW3389 Trackball Tester

A simple test keyboard for verifying PMW3389 trackball sensor functionality using the Waveshare RP2040-Zero.

## Hardware

- **MCU**: Waveshare RP2040-Zero
- **Sensor**: PMW3389 optical trackball sensor

## Wiring

| PMW3389 Pin | RP2040-Zero Pin | Function    |
| ----------- | --------------- | ----------- |
| MISO        | GP8             | SPI1 RX     |
| MOSI        | GP14            | SPI1 TX     |
| SCK         | GP15            | SPI1 SCK    |
| CS          | GP27            | Chip Select |
| GND         | GND             | Ground      |
| VCC         | 3V3             | 3.3V Power  |

## Building and Flashing

```bash
# Build firmware
qmk compile -kb handwired/pmw3389_tb_tester -km default

# Flash firmware (hold BOOT button, connect USB, release)
qmk flash -kb handwired/pmw3389_tb_tester -km default
```

## Testing

Once flashed, the trackball should move the mouse cursor. You can also use QMK Toolbox or `hid_listen` to view debug output if console is enabled.
