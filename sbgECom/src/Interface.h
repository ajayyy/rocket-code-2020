#ifndef _INTERFACE_H
#define _INTERFACE_H
#include "rocketState.h"



class Interface
{
public:
	Interface();
	~Interface();

	void initializeSensors();

	// to get the latest rocket state 
	rocketState getLatest();
	void update();
private:

	
};


#endif
