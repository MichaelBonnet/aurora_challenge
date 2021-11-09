#include "lcamsg.h"

// TO DO
// Redefinition error for default constructor between lcamsg.h and lcamsg.cpp
// Test Send
// Test Receive
// Figure out how to manage the Payload field for the base class

#define LIGHTS_FLAG 0x80 // 1000 0000
#define CAMERA_FLAG 0x40 // 0100 0000
#define ACTION_FLAG 0x3F // 0011 1111

#define UINT8_FLAG  0xFF
#define UINT16_FLAG 0xFFFF
#define UINT32_FLAG 0xFFFFFFFF
#define UINT64_FLAG 0xFFFFFFFFFFFFFFFF

// Constructor
LCAMsg::LCAMsg( uint16_t messageID, uint8_t senderID, uint8_t receiverID, uint32_t payloadLength, uint8_t * payload, uint8_t lights_camera_action, uint64_t name ) : UAVProtocol( messageID, senderID, receiverID, payloadLength, payload ), lights_camera_action(lights_camera_action), name(name) { }

// Copy Constructor
LCAMsg::LCAMsg( const LCAMsg &obj ) : UAVProtocol( obj ), lights_camera_action(obj.lights_camera_action), name(obj.name) { }

// Destructor
LCAMsg::~LCAMsg() { }

// Getter methods
uint8_t LCAMsg::get_lights() const {
    return lights_camera_action & LIGHTS_FLAG;
}

uint8_t LCAMsg::get_camera() const {
    return lights_camera_action & CAMERA_FLAG;
}

uint8_t LCAMsg::get_action() const {
    return lights_camera_action & ACTION_FLAG;
}

uint8_t LCAMsg::get_lights_camera_action() const {
    return lights_camera_action;
}

uint64_t LCAMsg::get_name()  const {
    return name;
}

// Send method
std::string LCAMsg::Send() const {
    int message = 0;
    int shiftcount = 0;

    // Pack messageID
    message |= get_messageID();
    shiftcount += size_t(get_messageID());
    
    // Pack senderID
    message |= (get_senderID() << shiftcount);
    shiftcount += size_t(get_senderID());
    
    // Pack receiverID
    message |= (get_receiverID() << shiftcount);
    shiftcount += size_t(get_receiverID());
    
    // Pack payloadLength
    message |= (get_payloadLength() << shiftcount);
    shiftcount += size_t(get_payloadLength());
    
    // Pack lights_camera_action
    message |= (get_lights_camera_action() << shiftcount);
    shiftcount += size_t(get_lights_camera_action());
    
    // Pack name
    message |= (get_name() << shiftcount);
    shiftcount += size_t(get_name());

    // Convert to string, then return that string
    std::string string_message = std::to_string(message);

    return string_message;

}

// Receive method
void LCAMsg::Receive(const std::string message) const {
    uint msg = std::stoi(message);
    int shiftcount = 0;

    // Extract messageID
    uint16_t msg_messageID = msg & UINT16_FLAG;
    shiftcount += size_t(UINT16_FLAG);
    
    // Extract senderiD
    uint8_t msg_senderID = (msg >> shiftcount) & UINT8_FLAG;
    shiftcount += size_t(UINT8_FLAG);
    
    // Extract receiverID
    uint8_t msg_receiverID = (msg >> shiftcount) & UINT8_FLAG;
    shiftcount += size_t(UINT8_FLAG);
    
    // Extract payloadLength
    uint32_t msg_payloadLength = (msg >> shiftcount) & UINT32_FLAG;
    shiftcount += size_t(UINT32_FLAG);
    
    // Extract lights_camera_action
    uint8_t msg_lights_camera_action = (msg >> shiftcount) & UINT8_FLAG;
    shiftcount += size_t(UINT8_FLAG);
    
    // Extract name
    uint64_t msg_name = (msg >> shiftcount) & UINT64_FLAG;

    // LCAMsg * msg_ = new LCAMsg(msg_messageID, msg_senderID, msg_receiverID, msg_payloadLength, msg_lights_camera_action, msg_name);

}
