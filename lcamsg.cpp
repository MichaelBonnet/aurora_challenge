#include "lcamsg.h"

// TO DO
// Add base class stuff to LCAMsg
// Write Send
// Write Receive

#define LIGHTS_FLAG 0x80 // 1000 0000
#define CAMERA_FLAG 0x40 // 0100 0000
#define ACTION_FLAG 0x3F // 0011 1111

// Constructor
LCAMsg::LCAMsg( uint16_t messageID, uint8_t senderID, uint8_t  receiverID, uint32_t  payloadLength, uint8_t * payload, uint8_t lights_camera_action, uint64_t name ) : 
messageID(messageID), senderID{senderID}, receiverID{receiverID}, payloadLength{payloadLength}, payload{payload}, lights_camera_action{lights_camera_action}, name{name} { }

// Copy Constructor
LCAMsg::LCAMsg( const LCAMsg &obj ) : UAVProtocol( obj ), lights_camera_action{obj.lights_camera_action}, name{obj.name} { }

LCAMsg::~LCAMsg() { }

uint8_t LCAMsg::get_lights() const {
    return lights_camera_action & LIGHTS_FLAG;
}

uint8_t LCAMsg::get_camera() const {
    return lights_camera_action & CAMERA_FLAG;
}

uint8_t LCAMsg::get_action() const {
    return lights_camera_action & ACTION_FLAG;
}

uint64_t LCAMsg::get_name()  const {
    return name;
}

std::string LCAMsg::Send() const {
    int message = 0;
    int shiftcount = 0;

    // payload = (uint8_t*) malloc(payloadLength)

    message |= messageID;
    shiftcount += size_t(messageID);
    message |= (senderID << shiftcount);
    shiftcount += size_t(senderID);
    message |= (receiverID << shiftcount);
    shiftcount += size_t(receiverID);
    message |= (payloadLength << shiftcount);
    shiftcount += size_t(payloadLength);
    message |= (lights_camera_action << shiftcount);
    shiftcount += size_t(lights_camera_action);
    message |= (name << shiftcount);
    shiftcount += size_t(name);

    std::string string_message = std::to_string(message);

    return string_message;

}

void LCAMsg::Receive(const std::string message) const {

}
