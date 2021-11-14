#include "lcamsg.h"

// TO DO
// Resolve segfaulting due to weird get_payload() things going on
// Network byte order everything
// for reference: https://www.tutorialspoint.com/unix_sockets/network_byte_orders.htm

// #define htonll(x) ((((uint64_t)htonl(x)) << 32) + htonl((x) >> 32))

// #define HTONLL(x) ((1==htonl(1)) ? (x) : (((uint64_t)htonl((x) & 0xFFFFFFFFUL)) << 32) | htonl((uint32_t)((x) >> 32)))
// #define NTOHLL(x) ((1==ntohl(1)) ? (x) : (((uint64_t)ntohl((x) & 0xFFFFFFFFUL)) << 32) | ntohl((uint32_t)((x) >> 32)))

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
uint LCAMsg::Send() const {
    uint message = 0;
    int shiftcount = 0;

    // Pack messageID
    // uint16_t messageID = htons( get_messageID() );
    // message |= messageID;
    message |= get_messageID();
    shiftcount += sizeof(get_messageID())*8;
    
    // Pack senderID
    // uint8_t senderID = htons( get_senderID() );
    // message |= (senderID << shiftcount);
    message |= (get_senderID() << shiftcount);
    shiftcount += sizeof(get_senderID())*8;
    
    // Pack receiverID
    // uint8_t receiverID = htons( get_receiverID() );
    // message |= (receiverID << shiftcount);
    message |= (get_receiverID() << shiftcount);
    shiftcount += sizeof(get_receiverID())*8;
    
    // Pack payloadLength
    // uint32_t payloadLength = htonl( get_payloadLength() );
    // message |= (payloadLength << shiftcount);
    message |= (get_payloadLength() << shiftcount);
    shiftcount += sizeof(get_payloadLength())*8;

    // need to deconstruct the payload from the pointer
    uint8_t * payload_ptr = get_payload();

    std::cout << "get_payloadlength() result is " << get_payloadLength() << std::endl;
    for (int i=0; i<get_payloadLength(); i++) {
        message |= ( htons( payload_ptr[i] ) << shiftcount );
        shiftcount += 8;
    }
    
    // Pack lights_camera_action
    // uint8_t lights_camera_action = htons( get_lights_camera_action() );
    // message |= (lights_camera_action << shiftcount);
    message |= (get_lights_camera_action() << shiftcount);
    shiftcount += sizeof(get_lights_camera_action())*8;
    
    // Pack name
    // uint64_t name = htonl( get_name() );
    // message |= (name << shiftcount);
    message |= (get_name() << shiftcount);
    shiftcount += sizeof(get_name())*8;

    return message;
}

// Receive method
void LCAMsg::Receive(const uint message) const {

    uint msg = message;
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
    // LCAMsg msg_(msg_messageID, msg_senderID, msg_receiverID, msg_payloadLength, msg_payload, msg_lights_camera_action, msg_name);

    // std::cout << "segfault checkpoint 0" << std::endl;
    uint msg_message = msg_->Send();
    // std::cout << "\npost msg_->Send()\n";

    std::cout << "S Receiving: " << msg_->Send() << std::endl;
    std::cout << "R Sending  : " << this->Send() << std::endl;
}
