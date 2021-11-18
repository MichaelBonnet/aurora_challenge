#include "uavprotocol.h"

// Constructor
UAVProtocol::UAVProtocol( uint16_t messageID, uint8_t senderID, uint8_t  receiverID, uint32_t  payloadLength ) : 
    messageID(messageID), senderID(senderID), receiverID(receiverID), payloadLength(payloadLength), payload(0) { }

// Copy Constructor
UAVProtocol::UAVProtocol( const UAVProtocol &obj ) : 
messageID(obj.messageID), senderID(obj.senderID), receiverID(obj.receiverID), payloadLength(obj.payloadLength), payload(obj.payload) { }

// (Virtual) Destructor
UAVProtocol::~UAVProtocol() { }

// Getter methods

uint16_t UAVProtocol::get_messageID() const {
    return messageID;
}

uint8_t UAVProtocol::get_senderID() const {
    return senderID;
}

uint8_t UAVProtocol::get_receiverID() const {
    return receiverID;
}

uint32_t UAVProtocol::get_payloadLength() const {
    return payloadLength;
}

uint8_t * UAVProtocol::get_payload() const {
    return payload;  // keep in mind this is a pointer
}

// uint8_t UAVProtocol::get_size() {
//     uint8_t size = sizeof( get_payloadLength() ) + 
//                    sizeof( get_messageID()     ) + 
//                    sizeof( get_senderID()      ) + 
//                    sizeof( get_receiverID()    );
    
//     std::cout << "size is " << size << std::endl;
//     return size;
// }
