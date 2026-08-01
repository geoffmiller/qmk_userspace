# See https://github.com/sadekbaroudi/vik

# rules.mk options
# VIK_ENABLE
# VIK_HAPTIC
# VIK_ILI9341
# VIK_PER56_CIRQUE_LEDS
# VIK_PER56_PMW3360_LEDS
# VIK_PMW3360
# VIK_WEACT_ST7735
# VIK_GC9A01
# VIK_WAVESHARE_22224
# VIK_AZOTEQ
# VIK_EC11_EVQWGD001
# VIK_CIRQUE
# VIK_TRACKPOINT

# rules.mk options for split right half
# VIK_CIRQUE_RIGHT
# VIK_PER56_CIRQUE_LEDS_RIGHT
# VIK_PER56_PMW3360_LEDS_RIGHT
# VIK_PMW3360_RIGHT
# VIK_AZOTEQ_RIGHT
# VIK_EC11_EVQWGD001_RIGHT

VIK_PATH=$(KEYBOARD_PATH_1)/vik

# Up front rules
include $(VIK_PATH)/rules.vik.pre.mk

# Include the unibody / split left VIK features
include $(VIK_PATH)/rules.vik.main.general.mk
include $(VIK_PATH)/rules.vik.main.pointing.mk

### Begin VIK right half support, if there is a VIK module on the right half
### IMPORTANT: not all modules can work on the slave half, which is a QMK limitation
###            only those that work will be handled here
ifeq ($(strip $(SPLIT_KEYBOARD)), yes)
	include $(VIK_PATH)/rules.vik.right.general.mk
	include $(VIK_PATH)/rules.vik.right.pointing.mk
endif

# Include any post processing that's dependent on everything else
include $(VIK_PATH)/rules.vik.post.mk
