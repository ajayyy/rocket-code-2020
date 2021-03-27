#pragma once

#include "config/config.h"


#if USE_GPIO

    #define USE_SV01 1

    #define USE_SV02 1

    #define USE_PWM_SBV01 1

    #define USE_PWM_SBV02 1

    #define USE_PWM_SBV03 1


    #if USE_SV01
        #define SV01_NAME "SV-01"
        #define SV01_PIN 16
        #define SV01_OPEN 1
        #define SV01_CLOSE 0
    #endif

    #if USE_SV02
        #define SV02_NAME "SV-02"
        #define SV02_PIN 16
        #define SV02_OPEN 1
        #define SV02_CLOSE 0
    #endif

    #if USE_PWM_SBV01
        #define SBV01_NAME "SBV01"
        #define SBV01_PIN 12
        #define SBV01_OPEN 150
        #define SBV01_CLOSE 60
    #endif

    #if USE_PWM_SBV02
        #define SBV02_NAME "SBV02"
        #define SBV02_PIN 12
        #define SBV02_OPEN 150
        #define SBV02_CLOSE 60
    #endif

    #if USE_PWM_SBV03
        #define SBV03_NAME "SBV03"
        #define SBV03_PIN 12
        #define SBV03_OPEN 150
        #define SBV03_CLOSE 60
    #endif


#endif
