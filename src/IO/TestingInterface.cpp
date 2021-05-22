#include "config/config.h"
#if TESTING == 1

#include "TestingInterface.h"


TestingInterface::TestingInterface()
= default;

TestingInterface::~TestingInterface()
= default;

void TestingInterface::initialize()
{
	std::cout << "Initializing TESTING...\n";
	testingSensors.initialize();

	initializeOutputs();
}

void TestingInterface::initializeOutputs() 
{
#if USE_LOGGER == 1
	std::cout << "Initializing LOGGER...\n";
	logger.initialize();
#endif
#if USE_RADIO == 1
	std::cout << "Initializing RADIO...\n";
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
		if (!logger.queueEmpty()) {
			// Wait for logger to finish
			return false;
		}

		exit(EXIT_SUCCESS);
	}

	logger.enqueueSensorData(*data);
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