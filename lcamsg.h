// Implement a C++ class using the base class above to process a message with the following payload:

// Bits     Field
//  1       Lights
//  1       Camera
//  6       Action
// 64       Name

#ifndef __LCAMSG_H
#define __LCAMSG_H

#include <string>
#include <iostream>
#include <stdlib.h>
#include <stdint.h>
#include "uavprotocol.h"

#define LIGHTS_FLAG 0x80 // 1000 0000
#define CAMERA_FLAG 0x40 // 0100 0000
#define ACTION_FLAG 0x3F // 0011 1111

#define UINT8_FLAG  0xFF
#define UINT16_FLAG 0xFFFF
#define UINT32_FLAG 0xFFFFFFFF
#define UINT64_FLAG 0xFFFFFFFFFFFFFFFF

#define BYTE_0_TO_7_64   0xFF00000000000000
// #define BYTE_8_TO_15_64  0x00FF000000000000
// #define BYTE_16_TO_23_64 0x0000FF0000000000
// #define BYTE_24_TO_31_64 0x000000FF00000000
// #define BYTE_32_TO_39_64 0x00000000FF000000
// #define BYTE_40_TO_47_64 0x0000000000FF0000
// #define BYTE_48_TO_55_64 0x000000000000FF00
#define BYTE_55_TO_63_64 0x00000000000000FF

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
        // LCAMsg( uint16_t messageID, uint8_t senderID, uint8_t receiverID, uint32_t payloadLength, uint8_t * payload, uint8_t lights_camera_action, uint64_t name ) : UAVProtocol( messageID, senderID, receiverID, payloadLength, payload );
        LCAMsg( uint16_t messageID, uint8_t senderID, uint8_t receiverID, uint32_t payloadLength, uint8_t * payload, uint8_t lights_camera_action, uint64_t name );
        LCAMsg( const LCAMsg &obj );
        ~LCAMsg();

        // Access method for each and every payload field
        uint8_t  get_lights() const;
        uint8_t  get_camera() const;
        uint8_t  get_action() const;
        uint8_t  get_lights_camera_action() const;
        uint64_t get_name()   const;

        // A Send function that returns a string containing the message to be sent
        std::string Send() const;

        // A Receive function that accepts a string containing the message received,
        // and populate the values of the payload fields
        void Receive( const std::string message ) const;
};

#endif