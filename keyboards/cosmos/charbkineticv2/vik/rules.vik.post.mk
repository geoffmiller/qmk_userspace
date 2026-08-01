ifeq ($(strip $(PMW3360_ENABLE)), yes)
    POINTING_DEVICE_ENABLE := yes
    POINTING_DEVICE_DRIVER := pmw3360
    QUANTUM_LIB_SRC += spi_master.c
    OPT_DEFS += -DVIK_TRACKBALL_ENABLE
endif

ifeq ($(strip $(CIRQUE_ENABLE)), yes)
    MOUSEKEY_ENABLE := yes  # not required, but enabling for mouse button keys
    POINTING_DEVICE_ENABLE := yes
    POINTING_DEVICE_DRIVER = cirque_pinnacle_spi
    OPT_DEFS += -DCIRQUE_ENABLE
endif

ifeq ($(strip $(QUANTUM_PAINTER_ENABLE)), yes)
    SRC += keyboards/fingerpunch/src/display/fp_display.c
endif
