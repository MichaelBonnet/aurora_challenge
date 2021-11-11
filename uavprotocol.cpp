#include "uavprotocol.h"

// Constructor
UAVProtocol::UAVProtocol( uint16_t messageID, uint8_t senderID, uint8_t  receiverID, uint32_t  payloadLength, uint8_t * payload ) : 
    messageID(messageID), senderID(senderID), receiverID(receiverID), payloadLength(payloadLength), payload(payload) { }

// Copy Constructor
UAVProtocol::UAVProtocol( const UAVProtocol &obj ) : 
messageID(obj.messageID), senderID(obj.senderID), receiverID(obj.receiverID), payloadLength(obj.payloadLength), payload(obj.payload) { }

// (Virtual) Destructor
UAVProtocol::~UAVProtocol() { }

uint16_t UAVProtocol::get_messageID() const {
    return messageID;
}

uint8_t  UAVProtocol::get_senderID() const {
    return senderID;
}

uint8_t  UAVProtocol::get_receiverID() const {
    return receiverID;
}

uint32_t UAVProtocol::get_payloadLength() const {
    return payloadLength;
}

uint8_t * UAVProtocol::get_payload() const {
    return payload;  // keep in mind this is a pointer
}
