#include "lcamsg.h"

// TO DO
// Test Send
// Test Receive
// Figure out how to manage the Payload field for the base class

// Constructor
LCAMsg::LCAMsg( uint16_t messageID, uint8_t senderID, uint8_t receiverID, uint32_t payloadLength, uint8_t * payload, uint8_t lights_camera_action, uint64_t name ) : 
    UAVProtocol( messageID, senderID, receiverID, payloadLength, payload ), lights_camera_action(lights_camera_action), name(name) { }

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

uint64_t LCAMsg::get_name() const {
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

    uint8_t * msg_payload = (uint8_t*) malloc(sizeof(uint8_t)*msg_payloadLength);
    shiftcount = 0;

    *msg_payload = 0 | msg_lights_camera_action;
    msg_payload += 1;
    for (int i=1; i<msg_payloadLength; i++) {
        *msg_payload = (msg_name & (BYTE_0_TO_7_64 >> (sizeof(uint8_t)*(i-1))) ) >> (size_t(msg_name) - sizeof(uint8_t)*(msg_payloadLength-i));
        msg_payload += 1;
    }

    LCAMsg * msg_ = new LCAMsg(msg_messageID, msg_senderID, msg_receiverID, msg_payloadLength, msg_payload, msg_lights_camera_action, msg_name);

}
