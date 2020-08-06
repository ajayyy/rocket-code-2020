#include "Rocket.h"
#include <iostream>
#include <bitset>
#include "rocketState.h"

Rocket::Rocket() :
	StateMachine(ST_MAX_STATES) {
}
	
// Apogee external event
// void Rocket::Apogee(RocketSMData* data)
void Rocket::Apogee() {
	BEGIN_TRANSITION_MAP			              			// - Current State -
		TRANSITION_MAP_ENTRY (ST_DESCENT)					// ST_FLIGHT
		TRANSITION_MAP_ENTRY (EVENT_IGNORED)				// ST_DESCENT
		TRANSITION_MAP_ENTRY (EVENT_IGNORED)				// ST_GROUND
	END_TRANSITION_MAP(NULL)
	// END_TRANSITION_MAP(data)

	// CANNOT_HAPPEN
}

// Touchdown external event
void Rocket::Touchdown() {
	BEGIN_TRANSITION_MAP			              			// - Current State -
		TRANSITION_MAP_ENTRY (EVENT_IGNORED)				// ST_FLIGHT
		TRANSITION_MAP_ENTRY (ST_GROUND)					// ST_DESCENT
		TRANSITION_MAP_ENTRY (EVENT_IGNORED)				// ST_GROUND
	END_TRANSITION_MAP(NULL)
}

// Code for each state. Do not put while in them. The right function according to the current state
// will be call in the main loop. 

// code for the flight state
STATE_DEFINE(Rocket, Flight, RocketSMData) {
	rocketInterface.update();
	rocketData = rocketInterface.getLatest();
	detectExternEvent(rocketData);

	// showInfo(rocketData);
	
	std::cout << "Flight \n";
	// InternalEvent(ST_DESCENT);
}

// code for the Descent state
STATE_DEFINE(Rocket, Descent, RocketSMData) {
	// showInfo(data);
	std::cout << "Descent \n";
	// InternalEvent(ST_GROUND);

	rocketInterface.update();
	rocketData = rocketInterface.getLatest();

	detectExternEvent(rocketData);
	// showInfo(rocketData);

	// perform the descent processing here
	// transition to Flight via an internal event
	// InternalEvent(ST_FLIGHT);
}

// STATE_DEFINE(RocketSM, Ground, RocketSMData)

// code for the ground state
STATE_DEFINE(Rocket, Ground, RocketSMData) {
	std::cout << "Ground \n";
	rocketInterface.update();
	rocketData = rocketInterface.getLatest();
	
	detectExternEvent(rocketData);

	// showInfo(rocketData);

}

// Exit action when WaitForDeceleration state exits.
EXIT_DEFINE(Rocket, ExitFlight) {
	std::cout << "RocketSM::ExitFlight\n";

}

// Exit action when WaitForDeceleration state exits.
EXIT_DEFINE(Rocket, ExitDescent) {
	std::cout << "RocketSM::ExitDescent\n";

}

void Rocket::detectExternEvent(const rocketState* data) {
	int eventNbr = data->inputEventNumber;
	switch (eventNbr)
	{
	case 0:
		Apogee();
		break;
	case 1:
		Touchdown();
		break;
	default:
		break;
	}
}

void Rocket::showInfo(const rocketState* data) {
	printf("Barometer: %f\tGps: longitude %f\t latitude %f\t altitude %f\t Velocity: N %f\tE %f\tD %f\tSolutionStatus %d\t%d\n",
		data->sbg.barometricAltitude,
		data->sbg.gpsLatitude, data->sbg.gpsLongitude, data->sbg.gpsAltitude,
		data->sbg.velocityN, data->sbg.velocityE, data->sbg.velocityD,
		data->sbg.solutionStatus,
		(data->sbg.solutionStatus) & 0b1111
		);
	// std::cout << std::bitset<32>(data->sbg.solutionStatus) << "\n";
}

void Rocket::updateRocket() {
	
	ExecuteCurrentState(NULL);
}