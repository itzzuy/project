#include "protocol.h"
#include <sstream>

std::string processCmd(const std::string& command, std::map<std::string, Device>& devices) {
	std::stringstream response;

	if (command.find("192.168.1.") == 0) {
		std::string ip = command.substr(0, command.find(' '));
		if (devices.find(ip) == devices.end()) {
			return "Device Not Found!!!\n";
		}

		std::string cmd = command.substr(ip.length() + 1);
		if (cmd == "GET / on") {
			devices[ip].state = true;
			response << devices[ip].name << " turned on\n";
		}
		else if (cmd == "GET / off") {
			devices[ip].state = false;
			response << devices[ip].name << " turned off\n";
		}
		else if (cmd == "GET / status") {
			response << devices[ip].name << " is " << (devices[ip].state ? "on" : "off") << std::endl;
		}
		else {
			response << "Unknown command for " << ip << std::endl;
		}
	}
}