#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <string>
#include <map>
#include "device.h"

// Process client cmd and return responses
std::string processCmd(const std::string& command, std::map<std::string, Device>& devices);

#endif