// A hypothetical protocol used to communicate with UAVs has the following common fields:

// Bits         Field
// 16           Lights
//  8           Camera
//  8           Action
// 32           Name
// Variable     Payload

#ifndef __UAVPROTOCOL_H
#define __UAVPROTOCOL_H

#include <string>
#include <iostream>

// Implement a C++ class that can be used as the base class to develop specific messages later.
// This class should have the following features:

class UAVProtocol {
    private:
        // Initialization of common fields.
        uint16_t  messageID;
        uint8_t   senderID;
        uint8_t   receiverID;
        uint32_t  payloadLength;
        uint8_t * payload;

    public:
        // Rule of 3
        UAVProtocol( uint16_t messageID, uint8_t senderID, uint8_t  receiverID, uint32_t  payloadLength, uint8_t * payload );
        UAVProtocol( const UAVProtocol &obj);
        virtual ~UAVProtocol();

        // Access methods for each and every common field
        uint16_t  get_messageID()     const;
        uint8_t   get_senderID()      const;
        uint8_t   get_receiverID()    const;
        uint32_t  get_payloadLength() const;
        uint8_t * get_payload()       const;

        // A virtual Send function that returns a string containing the message to be send
        virtual std::string Send() const = 0;
        
        // Virtual Receive function that accepts a string containing th message received,
        // and populates the values of the common fields
        virtual void Receive( const std::string message ) const = 0;

};

#endif