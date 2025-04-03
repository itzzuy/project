#ifndef DEVICE_H
#define DEVICE_H

#include <string>
#include <map>

struct Device {
	std::string device;
	std::string ip;
	std::string mac;
	bool state; // on/off
	int thermostat; // thermo temp
};

void initializeDevices(std::map<std::string, Device>& devices);
#endif