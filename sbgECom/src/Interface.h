#ifndef _INTERFACE_H
#define _INTERFACE_H
#include "rocketState.h"
#include "IO/SBGData.h"
#include "IO/SBGSensor.h"
#include "IO/Logger.h"
#include "IO/Input.h"
#include "IO/IO.h"
#include <queue>

#ifdef TESTING
#include "IO/TestingSensors.h"
#endif // TESTING

class Interface {
public:
	Interface();
	~Interface();

	// not used yet
	void initializeSensors();

	// to get the latest rocket state. return a pointer to latestState
	rocketState* getLatest();

	// loop over each sensor and update the latestState
	void update();

private:
	rocketState latestState;
	

#ifdef TESTING
	TestingSensors testingSensors;
#else
    SBGSensor mySbgSensor;
	Input input;
#endif

#ifndef NO_LOGS
	Logger logger;
#endif

};


#endif
