# Point devices left
ifeq ($(strip $(VIK_AZOTEQ)), yes)
	ifeq ($(strip $(SPLIT_KEYBOARD)), yes)
		ifeq ($(strip $(VIK_BUILD_LEFT)), yes)
			POINTING_DEVICE_ENABLE := yes
			POINTING_DEVICE_DRIVER := azoteq_iqs5xx
		endif
	else
		POINTING_DEVICE_ENABLE := yes
		POINTING_DEVICE_DRIVER := azoteq_iqs5xx
	endif
	VIK_POINTING_LEFT := yes
	OPT_DEFS += -DVIK_AZOTEQ
	OPT_DEFS += -DVIK_POINTING_LEFT
endif

ifeq ($(strip $(VIK_CIRQUE)), yes)
	ifeq ($(strip $(SPLIT_KEYBOARD)), yes)
		ifeq ($(strip $(VIK_BUILD_LEFT)), yes)
			CIRQUE_ENABLE := yes
		endif
	else
		CIRQUE_ENABLE := yes
	endif
	VIK_POINTING_LEFT := yes
	OPT_DEFS += -DVIK_CIRQUE
	OPT_DEFS += -DVIK_POINTING_LEFT
endif

ifeq ($(strip $(VIK_PER56_CIRQUE_LEDS)), yes)
	ifeq ($(strip $(SPLIT_KEYBOARD)), yes)
		ifeq ($(strip $(VIK_BUILD_LEFT)), yes)
			CIRQUE_ENABLE = yes
		endif
	else
		CIRQUE_ENABLE = yes
	endif
	VIK_POINTING_LEFT := yes
	ENCODER_ENABLE = yes
	OPT_DEFS += -DVIK_PER56_CIRQUE_LEDS
	OPT_DEFS += -DVIK_POINTING_LEFT
endif

ifeq ($(strip $(VIK_PER56_PMW3360_LEDS)), yes)
	ifeq ($(strip $(SPLIT_KEYBOARD)), yes)
		ifeq ($(strip $(VIK_BUILD_LEFT)), yes)
			PMW3360_ENABLE = yes
		endif
	else
		PMW3360_ENABLE = yes
	endif
	VIK_POINTING_LEFT := yes
	ENCODER_ENABLE = yes
	OPT_DEFS += -DVIK_PER56_PMW3360_LEDS
	OPT_DEFS += -DVIK_POINTING_LEFT
endif

ifeq ($(strip $(VIK_PMW3360)), yes)
	ifeq ($(strip $(SPLIT_KEYBOARD)), yes)
		ifeq ($(strip $(VIK_BUILD_LEFT)), yes)
			PMW3360_ENABLE = yes
		endif
	else
		PMW3360_ENABLE = yes
	endif
	VIK_POINTING_LEFT := yes
	OPT_DEFS += -DVIK_PMW3360
	OPT_DEFS += -DVIK_POINTING_LEFT
endif

ifeq ($(strip $(VIK_PROCYON)), yes)
	ifeq ($(strip $(SPLIT_KEYBOARD)), yes)
		ifeq ($(strip $(VIK_BUILD_LEFT)), yes)
			POINTING_DEVICE_ENABLE := yes
			DIGITIZER_ENABLE := yes
			DIGITIZER_DRIVER := maxtouch
			POINTING_DEVICE_DRIVER := digitizer
		endif
	else
		POINTING_DEVICE_ENABLE := yes
		DIGITIZER_ENABLE := yes
    DIGITIZER_DRIVER := maxtouch
		POINTING_DEVICE_DRIVER := digitizer
	endif
	VIK_POINTING_LEFT := yes
	OPT_DEFS += -DVIK_PROCYON
	OPT_DEFS += -DVIK_POINTING_LEFT
endif

ifeq ($(strip $(VIK_TRACKPOINT)), yes)
   ###### OVERALL FINDINGS SO FAR
   # AVR interrupt mode doesn't work for RP2040, as it requires PAL_MODE_OUTPUT_OPENDRAIN, which isn't provided for RP2040
   # https://github.com/qmk/qmk_firmware/blob/master/docs/feature_ps2_mouse.md#interrupt-version-arm-chibios-idinterrupt-version-chibios
   # https://github.com/qmk/qmk_firmware/pull/22615#issuecomment-1841537237

   # USART mode won't work, since the pins on the VIK controllers don't use USART for GPIO 1 and GPIO 2
   # https://github.com/qmk/qmk_firmware/blob/master/docs/feature_ps2_mouse.md#usart-version-idusart-version

   # The only thing that's left is busywait, which is not recommended by QMK, and also requires PAL_MODE_OUTPUT_OPENDRAIN
   # https://github.com/qmk/qmk_firmware/blob/master/docs/feature_ps2_mouse.md#busywait-version-idbusywait-version

   # So, our only option is to use two consecutive pins, which means we can't even use the VIK connector unless GPIO AD1 and AD2
   #   are consecutive, as defined by the RP2040 vendor driver, check QMK docs

   # Options are:
   # 1) hand wire from VIK module to a PCB with consecutive GPIO available (assuming RP2040), or hand wire to any two GPIO for non-RP2040 controllers. This also requires a bodge for 3.3v (untested) or a logic level conversion between 3.3v and 5v if using a 3.3v controller
   # 2) figure out an alternative way to get a driver working in QMK with PAL_MODE_OUTPUT_OPENDRAIN on an RP2040 (I don't even know if this is possible)
   ######

   ###### Actual VIK logic and options below:
   # Uncomment these two lines, and one of the modes to test the various options, see:
   # https://discord.com/channels/939959680611020840/1179500491525328926/1189474876386459678
   # PS2_MOUSE_ENABLE = yes
   # PS2_ENABLE = yes

   # Busywait mode: https://github.com/qmk/qmk_firmware/blob/master/docs/feature_ps2_mouse.md#busywait-version-idbusywait-version
   # PS2_DRIVER = busywait

   # If using this mode, also see: keyboards/fingerpunch/svlinky/halconf.h
   # ARM interrupt mode: https://github.com/qmk/qmk_firmware/blob/master/docs/feature_ps2_mouse.md#interrupt-version-arm-chibios-idinterrupt-version-chibios
   # PS2_DRIVER = interrupt

   # RP2040 pio / vendor mode: https://github.com/qmk/qmk_firmware/blob/master/docs/feature_ps2_mouse.md#rp2040-pio-version-idrp2040-pio-version
   # PS2_DRIVER = vendor

   OPT_DEFS += -DVIK_TRACKPOINT
endif
