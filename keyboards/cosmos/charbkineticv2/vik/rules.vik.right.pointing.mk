# Note that we need to wrap *all* of the actual enabling of drivers to only happen when building
# the right side, or if the left side has no pointing device
# Notice the blocks below:
# ifeq ($(strip $(VIK_POINTING_LEFT)), no)
# 	rules to enable pointing
# endif
# ifeq ($(strip $(VIK_BUILD_RIGHT)), yes)
# 	rules to enable pointing
# endif

ifeq ($(strip $(VIK_AZOTEQ_RIGHT)), yes)
	ifeq ($(strip $(VIK_POINTING_LEFT)), no)
		POINTING_DEVICE_ENABLE := yes
		POINTING_DEVICE_DRIVER := azoteq_iqs5xx
	endif
	ifeq ($(strip $(VIK_BUILD_RIGHT)), yes)
		POINTING_DEVICE_ENABLE := yes
		POINTING_DEVICE_DRIVER := azoteq_iqs5xx
	endif
	VIK_POINTING_RIGHT := yes
	OPT_DEFS += -DVIK_AZOTEQ_RIGHT
	OPT_DEFS += -DVIK_POINTING_RIGHT
endif

ifeq ($(strip $(VIK_CIRQUE_RIGHT)), yes)
	ifeq ($(strip $(VIK_POINTING_LEFT)), no)
		CIRQUE_ENABLE := yes
	endif
	ifeq ($(strip $(VIK_BUILD_RIGHT)), yes)
		CIRQUE_ENABLE := yes
	endif
	VIK_POINTING_RIGHT := yes
	OPT_DEFS += -DVIK_CIRQUE_RIGHT
	OPT_DEFS += -DVIK_POINTING_RIGHT
endif

ifeq ($(strip $(VIK_PER56_CIRQUE_LEDS_RIGHT)), yes)
	ifeq ($(strip $(VIK_POINTING_LEFT)), no)
		CIRQUE_ENABLE := yes
	endif
	ifeq ($(strip $(VIK_BUILD_RIGHT)), yes)
		CIRQUE_ENABLE := yes
	endif
	ENCODER_ENABLE = yes
	VIK_POINTING_RIGHT := yes
	OPT_DEFS += -DVIK_PER56_CIRQUE_LEDS_RIGHT
	OPT_DEFS += -DVIK_POINTING_RIGHT
endif

ifeq ($(strip $(VIK_PER56_PMW3360_LEDS_RIGHT)), yes)
	ifeq ($(strip $(VIK_POINTING_LEFT)), no)
		PMW3360_ENABLE = yes
	endif
	ifeq ($(strip $(VIK_BUILD_RIGHT)), yes)
		PMW3360_ENABLE = yes
	endif
	ENCODER_ENABLE = yes
	VIK_POINTING_RIGHT := yes
	OPT_DEFS += -DVIK_PER56_PMW3360_LEDS_RIGHT
	OPT_DEFS += -DVIK_POINTING_RIGHT
endif

ifeq ($(strip $(VIK_PMW3360_RIGHT)), yes)
	ifeq ($(strip $(VIK_POINTING_LEFT)), no)
		PMW3360_ENABLE = yes
	endif
	ifeq ($(strip $(VIK_BUILD_RIGHT)), yes)
		PMW3360_ENABLE = yes
	endif
	VIK_POINTING_RIGHT := yes
	OPT_DEFS += -DVIK_PMW3360_RIGHT
	OPT_DEFS += -DVIK_POINTING_RIGHT
endif

ifeq ($(strip $(VIK_PROCYON_RIGHT)), yes)
  ifeq ($(strip $(VIK_POINTING_LEFT)), no)
		POINTING_DEVICE_ENABLE := yes
		DIGITIZER_ENABLE := yes
		DIGITIZER_DRIVER := maxtouch
		POINTING_DEVICE_DRIVER := digitizer
	endif
	ifeq ($(strip $(VIK_BUILD_RIGHT)), yes)
		POINTING_DEVICE_ENABLE := yes
		DIGITIZER_ENABLE := yes
    DIGITIZER_DRIVER := maxtouch
		POINTING_DEVICE_DRIVER := digitizer
	endif
	VIK_POINTING_RIGHT := yes
	OPT_DEFS += -DVIK_PROCYON_RIGHT
	OPT_DEFS += -DVIK_POINTING_RIGHT
endif
