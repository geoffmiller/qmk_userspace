#ifdef SPLIT_KEYBOARD
    #ifdef VIK_POINTING_LEFT
        #ifdef VIK_POINTING_RIGHT
            #define SPLIT_POINTING_ENABLE
            #define POINTING_DEVICE_COMBINED
        #else
            #define SPLIT_POINTING_ENABLE
            #define POINTING_DEVICE_LEFT
        #endif
    #elif defined(VIK_POINTING_RIGHT)
        #define SPLIT_POINTING_ENABLE
        #define POINTING_DEVICE_RIGHT
    #endif
#endif
