// Had I had the time,
// I probably would have at least experimented with 
// making actual Sender/Transmitter and Receiver objects,
// to see how it might change the behavior or spec of Send() and Receive().


// ================ //
// === INCLUDES === //
// ================ //

#include "uavprotocol.h"

// =================== //
// === DEFINITIONS === //
// =================== //

// Constructor
UAVProtocol::UAVProtocol( uint16_t messageID, uint8_t senderID, uint8_t  receiverID, uint32_t  payloadLength ) : 
    messageID(messageID), senderID(senderID), receiverID(receiverID), payloadLength(payloadLength), payload(0) { }

// Copy Constructor
UAVProtocol::UAVProtocol( UAVProtocol &obj ) : 
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

// Setter methods

void UAVProtocol::set_messageID(uint16_t messageID_value) {
    messageID = messageID_value;
}

void UAVProtocol::set_senderID(uint8_t senderID_value) {
    senderID = senderID_value;
}

void UAVProtocol::set_receiverID(uint8_t receiverID_value) {
    receiverID = receiverID_value;
}

void UAVProtocol::set_payloadLength(uint32_t payloadLength_value) {
    payloadLength = payloadLength_value;
}

void UAVProtocol::set_payload(uint8_t * payload_ptr) {
    payload = payload_ptr;
}

// uint8_t UAVProtocol::get_size() {
//     uint8_t size = sizeof( get_payloadLength() ) + 
//                    sizeof( get_messageID()     ) + 
//                    sizeof( get_senderID()      ) + 
//                    sizeof( get_receiverID()    );
    
//     std::cout << "size is " << size << std::endl;
//     return size;
// }

// uint8_t * Send() {};

// void Receive( uint8_t * message ) {};
