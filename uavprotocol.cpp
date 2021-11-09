#include "uavprotocol.h"

unsigned short int UAVProtocol::get_messageID() {

}

unsigned char UAVProtocol::get_senderID() {

}

unsigned char UAVProtocol::get_receiverID() {

}

unsigned int  UAVProtocol::get_payloadLength() {

}

char* UAVProtocol::get_payload() {

}

// Virtual Send function that returns a string containing the message to be send
std::string UAVProtocol::Send() {

}
        
// Virtual Receive function that acepts a string containing th message received,
// and populates the values of the common fields
void UAVProtocol::Receive() {

}