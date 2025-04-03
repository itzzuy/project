#include "device.h"

void initializeDevices(std::map<std::string, Device>& devices) {
	// 192.168.1.0/24 for lights
	devices["192.168.1.10"] = { "Light1", "192.168.1.10", "00:1A:2B:3C:4D:5E", false, 0 };
	devices["192.168.1.10"] = { "Light2", "192.168.2.10", "00:1A:2B:3C:4D:5E", false, 0 };

	devices["192.168.2.10"] = { "Thermostat1", "192.168.2.10", "00:1A:2B:3C:4D:60", true, 22 };

	devices["192.168.3.10"] = { "Camera1", "192.168.3.10", "00:1A:2B:3C:4D:61", false, 0 };
	
}