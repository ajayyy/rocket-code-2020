#pragma once

#include "data/SBGData.h"
#include "data/UOSMData.h"
#include "data/GpioData.h"
#include <unordered_map>
#include "helpers/Types.h"

//all the informations about the rocket that the state machine will need
struct sensorsData
{
    bool isInitialized() const;

    uint64_t timeStamp = 0;
    uint16_t currentStateNo = 0;
    eventType eventNumber = -1;

#if USE_SBG == 1
    sbgData sbg;
    bool sbgIsInitialized = 0;
#endif

#if USE_GPIO == 1
    GpioData gpioData;
    bool gpioIsInitialized = 0;
#endif

#if USE_LOGGER
    bool loggerIsInitialized = 0;
#endif

#if USE_SOCKET_CLIENT
    bool clientIsInitialized = 0;
#endif

#if USE_INPUT
    bool inputIsInitialized = 0;
#endif

#if USE_RADIO
    bool radioIsInitialized = 0;
#endif

#if TESTING == 1
    bool outOfData = false;
#endif
};
