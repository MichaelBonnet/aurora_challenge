#include "lcamsg.h"

// TO DO
// Resolve stoi() going out of range issue for unit_test_1()

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
    uint message = 0;
    int shiftcount = 0;

    // Pack messageID
    message |= get_messageID();
    shiftcount += sizeof(get_messageID())*8;
    
    // Pack senderID
    message |= (get_senderID() << shiftcount);
    shiftcount += sizeof(get_senderID())*8;
    
    // Pack receiverID
    message |= (get_receiverID() << shiftcount);
    shiftcount += sizeof(get_receiverID())*8;
    
    // Pack payloadLength
    message |= (get_payloadLength() << shiftcount);
    shiftcount += sizeof(get_payloadLength())*8;

    // need to deconstruct the payload from the pointer
    uint8_t * payload_ptr = get_payload();
    for (int i=0; i<get_payloadLength(); i++) {
        message |= ( payload_ptr[i] << shiftcount );
        shiftcount += 8;
    }
    
    // Pack lights_camera_action
    message |= (get_lights_camera_action() << shiftcount);
    shiftcount += sizeof(get_lights_camera_action())*8;
    
    // Pack name
    message |= (get_name() << shiftcount);
    shiftcount += sizeof(get_name())*8;

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
    shiftcount += sizeof(msg_messageID)*8;
    
    // Extract senderiD
    uint8_t msg_senderID = (msg << shiftcount) & UINT8_FLAG;
    shiftcount += sizeof(msg_senderID)*8;
    
    // Extract receiverID
    uint8_t msg_receiverID = (msg << shiftcount) & UINT8_FLAG;
    shiftcount += sizeof(msg_receiverID)*8;
    
    // Extract payloadLength
    uint32_t msg_payloadLength = (msg << shiftcount) & UINT32_FLAG;
    shiftcount += sizeof(msg_payloadLength)*8;

    // Extract payload
    int payloadlength = msg_payloadLength;
    uint8_t * msg_payload = (uint8_t*) malloc(sizeof(uint8_t)*msg_payloadLength);
    for (int i=0; i<payloadlength; i++) {
        msg_payload[i] = (msg << shiftcount) & UINT8_FLAG;
        shiftcount += 8;
    }
    
    // Extract lights_camera_action
    uint8_t msg_lights_camera_action = (msg << shiftcount) & UINT8_FLAG;
    shiftcount += sizeof(msg_lights_camera_action)*8;
    
    // Extract name
    uint64_t msg_name = (msg << shiftcount) & UINT64_FLAG;

    // Create new instance out of the info we've extracted
    LCAMsg * msg_ = new LCAMsg(msg_messageID, msg_senderID, msg_receiverID, msg_payloadLength, msg_payload, msg_lights_camera_action, msg_name);

    std::string msg_message = msg_->Send();
    std::cout << "Receiving 1: " << msg_->Send() << std::endl;
    for (std::size_t i = 0; i < msg_message.size(); ++i)
    {
        std::cout << std::bitset<8>(msg_message.c_str()[i]);
    }
    std::cout << std::endl;
    std::cout << "Sending   1: " << this->Send() << std::endl;
    std::string same_message = this->Send();
    for (std::size_t i = 0; i < same_message.size(); ++i)
    {
        std::cout << std::bitset<8>(same_message.c_str()[i]);
    }
    std::cout << std::endl;
}
