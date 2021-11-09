// Implement a C++ class using the base class above to process a message with the following payload:

// Bits     Field
//  1       Lights
//  1       Camera
//  6       Action
// 64       Name

#ifndef __LCAMSG_H
#define __LCAMSG_H

#include <string>
#include "uavprotocol.h"

// The class should have the following features:

// Inherits the base class in Problem #1 (UAVProtocol)
class LCAMsg : public UAVProtocol {
    private:
        // Initialization of all payload fields
        // Bit 7   is lights
        // Bit 6   is camera
        // Bit 0-5 is Action
        unsigned char lights_camera_action;
        unsigned int  name;

    public:
        // Access method for each and every payload field
        unsigned char get_lights();
        unsigned char get_camera();
        unsigned char get_action();
        unsigned int  get_name();

        // A SEnd function that returns a string containing the message to be sent
        std::string Send();

        // A Receive function that accepts a string containing the message received,
        // and populate the values of the payload fields
        void Receive();
};

#endif