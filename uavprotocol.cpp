#include "uavprotocol.h"

uint16_t UAVProtocol::get_messageID()     const {

}

uint8_t  UAVProtocol::get_senderID()      const {

}

uint8_t  UAVProtocol::get_receiverID()    const {

}

uint32_t UAVProtocol::get_payloadLength() const {

}

uint8_t * UAVProtocol::get_payload()      const {

}

// Virtual Send function that returns a string containing the message to be send
std::string UAVProtocol::Send() const {

}
        
// Virtual Receive function that acepts a string containing th message received,
// and populates the values of the common fields
void UAVProtocol::Receive( const std::string message ) {

}