#include <spdlog/spdlog.h>
#include "config/config.h"
#if TESTING == 1

#include "TestingInterface.h"


TestingInterface::TestingInterface() {
    logger = spdlog::default_logger();
}

TestingInterface::~TestingInterface()
= default;

void TestingInterface::initialize()
{
	SPDLOG_LOGGER_INFO(logger, "Initializing TESTING...");
	testingSensors.initialize();

	initializeOutputs();
}

void TestingInterface::initializeOutputs() 
{
#if USE_LOGGER == 1
	SPDLOG_LOGGER_INFO(logger, "Initializing LOGGER...");
	sensorLogger.initialize();
#endif
#if USE_RADIO == 1
	SPDLOG_LOGGER_INFO(logger, "Initializing RADIO..."); \
	radio.initialize();
#endif
}

bool TestingInterface::updateInputs()
{
	latestState = std::make_shared<sensorsData>(testingSensors.getLatest());
	
	return true;
}

bool TestingInterface::updateOutputs(std::shared_ptr<sensorsData> data) 
{
#if USE_LOGGER == 1
	if (latestState->outOfData) {
		if (!sensorLogger.queueEmpty()) {
			// Wait for logger to finish
			return false;
		}

		exit(EXIT_SUCCESS);
	}

	sensorLogger.enqueueSensorData(*data);
#endif

#if USE_RADIO == 1
	radio.enqueueSensorData(*data);
#endif

	return true;
}

#if USE_GPIO == 1
void TestingInterface::createNewGpioOutput(std::string name, int pinNbr) 
{
	return; //don't do anything for now
}
void TestingInterface::createNewGpioPwmOutput(std::string name, int pinNbr) 
{
	return; //don't do anything for now
}
#endif

void TestingInterface::calibrateTelemetry() 
{

}


std::shared_ptr<sensorsData> TestingInterface::getLatest()
{
	return latestState;
}

time_point TestingInterface::getCurrentTime()
{
	if (latestState != nullptr) 
	{
		return time_point(std::chrono::duration_cast<time_point::duration>(duration_ns(latestState->timeStamp)));
	} else
	{
		return time_point(std::chrono::duration_cast<time_point::duration>(duration_ns(0)));
	}
}

#endif