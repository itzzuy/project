# Smart Home Network Automation System

## Overview

The Smart Home Network Automation System is a C++ based application designed to simulate the control of smart home devices such as lights, thermostats, and security cameras. This system leverages socket programming, multithreading, and a custom HTTP-like protocol to allow real-time control and status monitoring of devices on different subnets.

This project was built with modular design principles to promote scalability, maintainability, and ease-of-use. The application supports both individual device control and group commands, all while providing clear feedback that includes the device’s IP address.

## Features

- **Device Control:**  
  - **Lights:** Turn on, turn off, and check status for individual lights (Light1, Light2) or all lights as a group.
  - **Thermostat:** Set the temperature, turn the device on/off, and check its status.
  - **Cameras:** Turn on, turn off, and check status for individual cameras or all cameras as a group.
  
- **Network Simulation:**  
  - Devices are organized into subnets (e.g., lights on 192.168.1.x, thermostat on 192.168.2.x, cameras on 192.168.3.x).
  
- **Custom Protocol:**  
  - A simple, token-based command parser that supports commands like:
    - `GET /lights on`
    - `GET /light1 off`
    - `GET /thermostat1 set 25`
    - `GET /camera1 status`
    - Also supports fallback IP-based commands: `GET 192.168.1.10 /on`
    
- **Multithreaded Server:**  
  - Uses Winsock and multithreading to handle multiple client connections concurrently.

## File Structure

- **device.h / device.cpp:**  
  Defines the `Device` struct and initializes the device database (IP, MAC, state, etc.).

- **protocol.h / protocol.cpp:**  
  Contains the command processing logic. Commands are parsed and routed based on device type (lights, thermostat, cameras) with both individual and group commands supported.

- **server.cpp:**  
  Implements the server application using Winsock. The server listens on a specified port, handles incoming connections in separate threads, and processes commands using the protocol logic.

- **client.cpp:**  
  A simple client application that connects to the server, accepts user commands in a loop, and displays server responses. The client keeps prompting for commands until the user types `exit`.

### Compilation

Open your terminal or command prompt and compile the project files. For example, if using Visual Studio's Developer Command Prompt:

```bash
cl /EHsc /W4 device.cpp protocol.cpp server.cpp /link ws2_32.lib
cl /EHsc /W4 device.cpp protocol.cpp client.cpp /link ws2_32.lib
