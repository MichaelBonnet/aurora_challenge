// A hypothetical protocol used to communicate with UAVs has the following common fields:

// Bits         Field
// 16           Lights
//  8           Camera
//  8           Action
// 32           Name
// Variable     Payload

#ifndef __UAVPROTOCOL_H
#define __UAVPROTOCOL_H

// ================ //
// === INCLUDES === //
// ================ //

#include <string>
#include <iostream>

// ==================== //
// === DECLARATIONS === //
// ==================== //

// Implement a C++ class that can be used as the base class to develop specific messages later.
// This class should have the following features:

class UAVProtocol {
    private:
        // Initialization of common fields.
        uint16_t  messageID;
        uint8_t   senderID;
        uint8_t   receiverID;
        uint32_t  payloadLength;

    protected:
        uint8_t * payload;

    public:
        // Rule of 3
        UAVProtocol( uint16_t messageID, uint8_t senderID, uint8_t  receiverID, uint32_t  payloadLength );
        UAVProtocol( UAVProtocol &obj);
        virtual ~UAVProtocol();

        // Access methods for each and every common field
        uint16_t  get_messageID()     const;
        uint8_t   get_senderID()      const;
        uint8_t   get_receiverID()    const;
        uint32_t  get_payloadLength() const;
        uint8_t * get_payload()       const;

        // Setters
        void set_messageID(uint16_t messageID_value);
        void set_senderID(uint8_t senderID_value);
        void set_receiverID(uint8_t receiverID_value);
        void set_payloadLength(uint32_t payloadLength_value);
        void set_payload(uint8_t * payload_ptr);

        // virtual size getter to define mallocing in send/receive
        // virtual uint8_t get_size();

        // A virtual Send function that returns a string containing the message to be send
        virtual uint8_t * Send() const = 0;
        
        // Virtual Receive function that accepts a string containing th message received,
        // and populates the values of the common fields
        virtual void Receive( uint8_t * message ) = 0;
};

#endif