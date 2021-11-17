#include "uavprotocol.h"

// Constructor
UAVProtocol::UAVProtocol( uint16_t messageID, uint8_t senderID, uint8_t  receiverID, uint32_t  payloadLength, uint8_t * payload ) : 
    messageID(messageID), senderID(senderID), receiverID(receiverID), payloadLength(payloadLength), payload(payload) {
        // std::cout << "Base Constructor messageID     is " << messageID << std::endl;
        // std::cout << "Base Constructor senderID      is " << +senderID << std::endl;
        // std::cout << "Base Constructor receiverID    is " << +receiverID << std::endl;
        // std::cout << "Base Constructor payloadLength is " << payloadLength << std::endl;
    }

// Copy Constructor
UAVProtocol::UAVProtocol( const UAVProtocol &obj ) : 
messageID(obj.messageID), senderID(obj.senderID), receiverID(obj.receiverID), payloadLength(obj.payloadLength), payload(obj.payload) { }

// (Virtual) Destructor
UAVProtocol::~UAVProtocol() { }

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

uint8_t UAVProtocol::get_size() {
    uint8_t size = sizeof( get_payloadLength() ) + 
                   sizeof( get_payloadLength() ) + 
                   sizeof( get_messageID()     ) + 
                   sizeof( get_senderID()      ) + 
                   sizeof( get_receiverID()    );
    
    std::cout << "size is " << size << std::endl;
    return size;
}
