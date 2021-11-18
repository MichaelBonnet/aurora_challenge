// Implement a C++ class using the base class above to process a message with the following payload:

// Bits     Field
//  1       Lights
//  1       Camera
//  6       Action
// 64       Name

#ifndef __LCAMSG_H
#define __LCAMSG_H

#include <cstring>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <arpa/inet.h>
#include "uavprotocol.h"

#define LIGHTS_FLAG 0b10000000 // 1000 0000
#define CAMERA_FLAG 0b01000000 // 0100 0000
#define ACTION_FLAG 0b00111111 // 0011 1111

#define UINT8_FLAG  0xFF
#define UINT16_FLAG 0xFFFF
#define UINT32_FLAG 0xFFFFFFFF
#define UINT64_FLAG 0xFFFFFFFFFFFFFFFF

// The class should have the following features:

// Inherits the base class in Problem #1 (UAVProtocol)
class LCAMsg : public UAVProtocol {
    private:
        // Initialization of all payload fields
        // Bit 7   is lights
        // Bit 6   is camera
        // Bit 0-5 is action
        uint8_t  lights_camera_action;
        uint64_t name;

    public:
        // Semi Rule of 3
        LCAMsg( uint16_t messageID, uint8_t senderID, uint8_t receiverID, uint32_t payloadLength, uint8_t lights_camera_action, uint64_t name );
        LCAMsg( const LCAMsg &obj );
        ~LCAMsg();

        // Access method for each and every payload field
        uint8_t  get_lights() const;
        uint8_t  get_camera() const;
        uint8_t  get_action() const;
        uint8_t  get_lights_camera_action() const;
        uint64_t get_name()   const;

        // size getter to define mallocing in send/receive
        // uint8_t get_size();

        // creates payload from the given derived class parameters
        void create_lca_payload(uint8_t lights_camera_action, uint64_t name);

        // A Send function that returns a string containing the message to be sent
        uint8_t * Send() const;

        // A Receive function that accepts a string containing the message received,
        // and populate the values of the payload fields
        void Receive( uint8_t * message ) const;
};

#endif