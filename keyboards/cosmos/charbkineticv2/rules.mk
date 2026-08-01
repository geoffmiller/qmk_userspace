# Add VIK configuration here (e.g. VIK_PMW3360_RIGHT=yes to use a trackball)

VIK_ENABLE = yes

# Explicitly enable PMW3389 for this board's right-side trackball.
POINTING_DEVICE_ENABLE = yes
POINTING_DEVICE_DRIVER = pmw3389

include $(KEYBOARD_PATH_1)/vik/rules.mk
