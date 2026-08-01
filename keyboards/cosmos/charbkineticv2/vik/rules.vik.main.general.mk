# Note that we need to wrap *all* of the actual enabling of drivers to only happen when building
# the left side. This is to avoid conflicts with the VIK device on the right half
# Notice the blocks below:
#	ifeq ($(strip $(SPLIT_KEYBOARD)), yes)
#		ifeq ($(strip $(VIK_BUILD_LEFT)), yes)
# 			rules to enable feature
#		endif
#	else
# 		rules to enable feature
#	endif

ifeq ($(strip $(VIK_HAPTIC)), yes)
	ifeq ($(strip $(SPLIT_KEYBOARD)), yes)
		ifeq ($(strip $(VIK_BUILD_LEFT)), yes)
			HAPTIC_ENABLE = yes
			HAPTIC_DRIVER = drv2605l
		endif
	else
		HAPTIC_ENABLE = yes
		HAPTIC_DRIVER = drv2605l
	endif
	OPT_DEFS += -DVIK_HAPTIC
endif

ifeq ($(strip $(VIK_ILI9341)), yes)
	ifeq ($(strip $(SPLIT_KEYBOARD)), yes)
		ifeq ($(strip $(VIK_BUILD_LEFT)), yes)
			BACKLIGHT_ENABLE = yes
			BACKLIGHT_DRIVER = software

			QUANTUM_PAINTER_ENABLE = yes
			QUANTUM_PAINTER_DRIVERS += ili9341_spi
			QUANTUM_PAINTER_LVGL_INTEGRATION = yes
			SRC += keyboards/fingerpunch/src/display/ili9341.c
		endif
	else
		BACKLIGHT_ENABLE = yes
		BACKLIGHT_DRIVER = software

		QUANTUM_PAINTER_ENABLE = yes
		QUANTUM_PAINTER_DRIVERS += ili9341_spi
		QUANTUM_PAINTER_LVGL_INTEGRATION = yes
		SRC += keyboards/fingerpunch/src/display/ili9341.c
	endif

	OPT_DEFS += -DVIK_ILI9341
endif

ifeq ($(strip $(VIK_WEACT_ST7735)), yes)
	ifeq ($(strip $(SPLIT_KEYBOARD)), yes)
		ifeq ($(strip $(VIK_BUILD_LEFT)), yes)
			BACKLIGHT_ENABLE = yes
			BACKLIGHT_DRIVER = software

			QUANTUM_PAINTER_ENABLE = yes
			QUANTUM_PAINTER_DRIVERS += st7735_spi
			QUANTUM_PAINTER_LVGL_INTEGRATION = yes
			SRC += keyboards/fingerpunch/src/display/st7735.c
		endif
	else
		BACKLIGHT_ENABLE = yes
		BACKLIGHT_DRIVER = software

		QUANTUM_PAINTER_ENABLE = yes
		QUANTUM_PAINTER_DRIVERS += st7735_spi
		QUANTUM_PAINTER_LVGL_INTEGRATION = yes
		SRC += keyboards/fingerpunch/src/display/st7735.c
	endif

	OPT_DEFS += -DVIK_WEACT_ST7735
endif

ifeq ($(strip $(VIK_GC9A01)), yes)
	ifeq ($(strip $(SPLIT_KEYBOARD)), yes)
		ifeq ($(strip $(VIK_BUILD_LEFT)), yes)
			QUANTUM_PAINTER_ENABLE = yes
			QUANTUM_PAINTER_DRIVERS += gc9a01_spi
			QUANTUM_PAINTER_LVGL_INTEGRATION = yes
			SRC += keyboards/fingerpunch/src/display/gc9a01.c
		endif
	else
		QUANTUM_PAINTER_ENABLE = yes
		QUANTUM_PAINTER_DRIVERS += gc9a01_spi
		QUANTUM_PAINTER_LVGL_INTEGRATION = yes
		SRC += keyboards/fingerpunch/src/display/gc9a01.c
	endif

	OPT_DEFS += -DVIK_GC9A01
endif

ifeq ($(strip $(VIK_WAVESHARE_22224)), yes)
	ifeq ($(strip $(SPLIT_KEYBOARD)), yes)
		ifeq ($(strip $(VIK_BUILD_LEFT)), yes)
			QUANTUM_PAINTER_ENABLE = yes
			QUANTUM_PAINTER_DRIVERS += st7789_spi
			QUANTUM_PAINTER_LVGL_INTEGRATION = yes
			SRC += keyboards/fingerpunch/src/display/waveshare_22224.c
		endif
	else
		QUANTUM_PAINTER_ENABLE = yes
		QUANTUM_PAINTER_DRIVERS += st7789_spi
		QUANTUM_PAINTER_LVGL_INTEGRATION = yes
		SRC += keyboards/fingerpunch/src/display/waveshare_22224.c
	endif

	OPT_DEFS += -DVIK_WAVESHARE_22224
endif

ifeq ($(strip $(VIK_EC11_EVQWGD001)), yes)
	ENCODER_ENABLE := yes
	OPT_DEFS += -DVIK_EC11_EVQWGD001
endif
