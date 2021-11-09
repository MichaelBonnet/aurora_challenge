#include "uavprotocol.h"

// TO DO
// Make LCAMsg() and UAVProtocol() jive
// Write Send
// Write Receive

// Constructor
UAVProtocol::UAVProtocol( uint16_t messageID, uint8_t senderID, uint8_t  receiverID, uint32_t  payloadLength, uint8_t * payload ) : 
messageID(messageID), senderID{senderID}, receiverID{receiverID}, payloadLength{payloadLength}, payload{payload} { }

// Copy Constructor
UAVProtocol::UAVProtocol( const UAVProtocol &obj ) : 
messageID(obj.messageID), senderID{obj.senderID}, receiverID{obj.receiverID}, payloadLength{obj.payloadLength}, payload{obj.payload} { }

// (Virtual) Destructor
UAVProtocol::~UAVProtocol() { }

uint16_t UAVProtocol::get_messageID()     const {
    return messageID;
}

uint8_t  UAVProtocol::get_senderID()      const {
    return senderID;
}

uint8_t  UAVProtocol::get_receiverID()    const {
    return receiverID;
}

uint32_t UAVProtocol::get_payloadLength() const {
    return payloadLength;
}

uint8_t * UAVProtocol::get_payload()      const {
    return payload;
}

// Virtual Send function that returns a string containing the message to be send
std::string UAVProtocol::Send() = 0 // const = 0 // { }
        
// Virtual Receive function that acepts a string containing th message received,
// and populates the values of the common fields
void UAVProtocol::Receive( const std::string message ) = 0 // { }