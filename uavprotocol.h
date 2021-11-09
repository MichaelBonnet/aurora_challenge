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

// Implement a C++ class that can be used as the base class to develop specific messages later.
// This class should have the following features:

class UAVProtocol {
    private:
        // Initialization of common fields.
        unsigned short int messageID;
        unsigned char      senderID;
        unsigned char      receiverID;
        unsigned int       payloadLength;
        char*              payload;

    public:
        // Access methods for each and every common field
        unsigned short int get_messageID();
        unsigned char      get_senderID();
        unsigned char      get_receiverID();
        unsigned int       get_payloadLength();
        char*              get_payload();

        // A virtual Send function that returns a string containing the message to be send
        virtual std::string Send();
        
        // Virtual Receive function that accepts a string containing th message received,
        // and populates the values of the common fields
        virtual void Receive();

};

#endif