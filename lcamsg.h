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
        uint8_t  lights_camera_action;
        uint64_t name;

    public:
        // Semi Rule of 3
        LCAMsg( uint8_t lights_camera_action, uint64_t name );
        LCAMsg( const LCAMsg &obj );
        ~LCAMsg();

        // Access method for each and every payload field
        uint8_t  get_lights() const;
        uint8_t  get_camera() const;
        uint8_t  get_action() const;
        uint64_t get_name()   const;

        // A Send function that returns a string containing the message to be sent
        std::string Send() const;

        // A Receive function that accepts a string containing the message received,
        // and populate the values of the payload fields
        void Receive(const std::string message) const;
};

#endif