#pragma once

#include "config/config.h"
#if TESTING == 1

#include "data/sensorsData.h"

#include "IO/Interface.h"
#include "IO/TestingSensors.h"
#include "IO/Logger.h"
#include "IO/Radio.h"
#include <queue>
#include <string>

class TestingInterface : public Interface
{
public:
	TestingInterface();
	~TestingInterface();

	void initialize();
	
	bool isInitialized();
	void calibrateTelemetry();

	// to get the latest rocket state. return a pointer to latestState
	std::shared_ptr<sensorsData> getLatest();

	bool updateInputs();
	bool updateOutputs(std::shared_ptr<sensorsData> data);

	#if USE_GPIO == 1
	void createNewGpioOutput(std::string name, int pinNbr);
	void createNewGpioPwmOutput(std::string name, int pinNbr);
	#endif

	time_point getCurrentTime();

private:
	void initializeOutputs();

	std::shared_ptr<sensorsData> latestState;

	TestingSensors testingSensors;

	time_point latestTime;

#if USE_LOGGER == 1
	Logger logger;
#endif

#if USE_RADIO == 1
	Radio radio;
#endif
};

#endif