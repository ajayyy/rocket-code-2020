#include "stdafx.h"
#include "RocketSM.h"


#include<thread>
#include<chrono>
#include<unordered_map>
#include"ReadSensors.h"



#include <iostream>
using namespace std;

int main(void)
{

	Sensors Sensors_read;

	std::thread thread1 = std::thread(&Sensors::add_value, &Sensors_read, 10);

    typedef std::unordered_map<std::string, std::thread> ThreadMap;
    ThreadMap tm_;

    thread1.detach();
    tm_["thread1"] = std::move(thread1);


	bool loop = true;

	int value;

	int old_value = -1;


	RocketSM RocketSM;
	while (loop) {
		value = Sensors_read.get_value();

		if (value != old_value)
		{
			std::cout << value << "\n";
			// Create Rocket object with macro support
			// RocketSMData* data = new RocketSMData();
			// data->speed = 100;
			// RocketSM.Apogee(data);
			


			if (value == 1)
			{
				RocketSM.Apogee();
			}


			// if we want to add some data with the event
			// RocketSMData* data2 = new RocketSMData();
			// data2->speed = 200;
			// RocketSM.Apogee(data2);

			if (value == 2)
			{
				RocketSM.Touchdown();
			}

			old_value = value;
		}
		
		RocketSM.ExecuteCurrentState();




    	// when we want to kill the read sensors thread
    	if (false) {
	    	ThreadMap::const_iterator it = tm_.find("thread1");
	    	it->second.std::thread::~thread(); // thread not killed
	        tm_.erase("thread1");
	        std::cout << "Thread " << "thread1" << " killed:" << std::endl;
	        loop = false;
	    	
    	}
	}


	return 0;
}
