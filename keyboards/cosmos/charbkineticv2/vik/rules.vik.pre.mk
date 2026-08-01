VIK_POINTING_LEFT ?= no
VIK_POINTING_RIGHT ?= no

ifeq ($(strip $(VIK_RGB_ONLY)), yes)
	OPT_DEFS += -DVIK_RGB_ONLY
endif
