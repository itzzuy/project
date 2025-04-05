#include "protocol.h"
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>

std::vector<std::string> split(const std::string& s) {
    std::istringstream iss(s);
    std::vector<std::string> tokens;
    std::string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

std::string processCmd(const std::string& command, std::map<std::string, Device>& devices) {
    std::stringstream response;
    // Split the command into tokens.
    std::vector<std::string> tokens = split(command);

    // Check for minimum three tokens: Method, Target, Action.
    if (tokens.size() < 3) {
        response << "Invalid command format\n";
        return response.str();
    }

    std::string method = tokens[0];
    std::string target = tokens[1];
    std::string action = tokens[2];

    // Only GET is supported.
    if (method != "GET") {
        response << "Unsupported method: " << method << "\n";
        return response.str();
    }

    // ******************** Lights Commands ************************
    // Group command for all lights: /lights
    if (target == "/lights") {
        for (auto& entry : devices) {
            // Assume devices with "Light" in their name are lights.
            if (entry.second.device.find("Light") != std::string::npos) {
                if (action == "on") {
                    entry.second.state = true;
                    response << entry.second.device << " (" << entry.second.ip << ") turned on\n";
                }
                else if (action == "off") {
                    entry.second.state = false;
                    response << entry.second.device << " (" << entry.second.ip << ") turned off\n";
                }
                else if (action == "status") {
                    response << entry.second.device << " (" << entry.second.ip << ") is "
                        << (entry.second.state ? "on" : "off") << "\n";
                }
                else {
                    response << "Unknown action for lights: " << action << "\n";
                }
            }
        }
        return response.str();
    }
    // Individual command for Light1: /light1
    else if (target == "/light1") {
        bool found = false;
        for (auto& entry : devices) {
            if (entry.second.device == "Light1") {
                found = true;
                if (action == "on") {
                    entry.second.state = true;
                    response << "Light1 (" << entry.second.ip << ") turned on\n";
                }
                else if (action == "off") {
                    entry.second.state = false;
                    response << "Light1 (" << entry.second.ip << ") turned off\n";
                }
                else if (action == "status") {
                    response << "Light1 (" << entry.second.ip << ") is "
                        << (entry.second.state ? "on" : "off") << "\n";
                }
                else {
                    response << "Unknown action for Light1: " << action << "\n";
                }
                break;
            }
        }
        if (!found)
            response << "Light1 not found\n";
        return response.str();
    }
    // Individual command for Light2: /light2
    else if (target == "/light2") {
        bool found = false;
        for (auto& entry : devices) {
            if (entry.second.device == "Light2") {
                found = true;
                if (action == "on") {
                    entry.second.state = true;
                    response << "Light2 (" << entry.second.ip << ") turned on\n";
                }
                else if (action == "off") {
                    entry.second.state = false;
                    response << "Light2 (" << entry.second.ip << ") turned off\n";
                }
                else if (action == "status") {
                    response << "Light2 (" << entry.second.ip << ") is "
                        << (entry.second.state ? "on" : "off") << "\n";
                }
                else {
                    response << "Unknown action for Light2: " << action << "\n";
                }
                break;
            }
        }
        if (!found)
            response << "Light2 not found\n";
        return response.str();
    }

    // Individual command for Thermostat1: /thermostat1
    else if (target == "/thermostat1") {
        bool found = false;
        for (auto& entry : devices) {
            if (entry.second.device == "Thermostat1") {
                found = true;
                if (action == "status") {
                    response << "Thermostat1 (" << entry.second.ip << ") is "
                        << (entry.second.state ? "on" : "off")
                        << " and set to " << entry.second.thermostat << "°C\n";
                }
                else if (action == "set") {
                    if (tokens.size() >= 4) {
                        int newTemp = std::stoi(tokens[3]);
                        entry.second.thermostat = newTemp;
                        response << "Thermostat1 (" << entry.second.ip << ") set to " << newTemp << "°C\n";
                    }
                    else {
                        response << "Temperature value missing for Thermostat1\n";
                    }
                }
                else if (action == "on") {
                    entry.second.state = true;
                    response << "Thermostat1 (" << entry.second.ip << ") turned on\n";
                }
                else if (action == "off") {
                    entry.second.state = false;
                    response << "Thermostat1 (" << entry.second.ip << ") turned off\n";
                }
                else {
                    response << "Unknown action for Thermostat1: " << action << "\n";
                }
                break;
            }
        }
        if (!found)
            response << "Thermostat1 not found\n";
        return response.str();
    }

    // ******************** Camera Commands ************************
    // Individual command for Camera1: /camera1
    else if (target == "/camera1") {
        bool found = false;
        for (auto& entry : devices) {
            if (entry.second.device == "Camera1") {
                found = true;
                if (action == "on") {
                    entry.second.state = true;
                    response << "Camera1 (" << entry.second.ip << ") turned on\n";
                }
                else if (action == "off") {
                    entry.second.state = false;
                    response << "Camera1 (" << entry.second.ip << ") turned off\n";
                }
                else if (action == "status") {
                    response << "Camera1 (" << entry.second.ip << ") is "
                        << (entry.second.state ? "on" : "off") << "\n";
                }
                else {
                    response << "Unknown action for Camera1: " << action << "\n";
                }
                break;
            }
        }
        if (!found)
            response << "Camera1 not found\n";
        return response.str();
    }
    // Group command for all cameras: /cameras
    else if (target == "/cameras") {
        for (auto& entry : devices) {
            if (entry.second.device.find("Camera") != std::string::npos) {
                if (action == "on") {
                    entry.second.state = true;
                    response << entry.second.device << " (" << entry.second.ip << ") turned on\n";
                }
                else if (action == "off") {
                    entry.second.state = false;
                    response << entry.second.device << " (" << entry.second.ip << ") turned off\n";
                }
                else if (action == "status") {
                    response << entry.second.device << " (" << entry.second.ip << ") is "
                        << (entry.second.state ? "on" : "off") << "\n";
                }
                else {
                    response << "Unknown action for cameras: " << action << "\n";
                }
            }
        }
        return response.str();
    }

    // Fallback: Explicit IP Commands 
    else if (target.find("192.168.1.") == 0) {  // Assuming IP commands for devices on the lights subnet.
        std::string ip = target;
        if (devices.find(ip) == devices.end()) {
            return "Device not found\n";
        }
        if (action == "/on") {
            devices[ip].state = true;
            response << devices[ip].device << " (" << devices[ip].ip << ") turned on\n";
        }
        else if (action == "/off") {
            devices[ip].state = false;
            response << devices[ip].device << " (" << devices[ip].ip << ") turned off\n";
        }
        else if (action == "/status") {
            response << devices[ip].device << " (" << devices[ip].ip << ") is "
                << (devices[ip].state ? "on" : "off") << "\n";
        }
        else {
            response << "Unknown action for " << ip << "\n";
        }
        return response.str();
    }
    else {
        response << "Invalid target: " << target << "\n";
    }

    return response.str();
}
