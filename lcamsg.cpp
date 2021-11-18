#include "lcamsg.h"

// TO DO
// Write Unit Tests

// Default Constructor
LCAMsg::LCAMsg( uint16_t messageID, uint8_t senderID, uint8_t receiverID, uint32_t payloadLength, uint8_t lights_camera_action, uint64_t name ) : 
    UAVProtocol( messageID, senderID, receiverID, payloadLength ), lights_camera_action(lights_camera_action), name(name) {
        create_lca_payload(lights_camera_action, name);
}

// Copy Constructor
LCAMsg::LCAMsg( const LCAMsg &obj ) : UAVProtocol( obj ), lights_camera_action(obj.lights_camera_action), name(obj.name) { }

// Destructor
LCAMsg::~LCAMsg() { }

// Getter methods

uint8_t LCAMsg::get_lights() const {
    return (lights_camera_action & LIGHTS_FLAG) >> 7;
}

uint8_t LCAMsg::get_camera() const {
    return (lights_camera_action & CAMERA_FLAG) >> 6;
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

void LCAMsg::set_lights_camera_action(uint8_t lca_value) {
    lights_camera_action = lca_value;
}

void LCAMsg::set_name(uint64_t name_value) {
    name = name_value;
}

// uint8_t LCAMsg::get_size() {
//     return UAVProtocol::get_size();
// }

void LCAMsg::create_lca_payload(uint8_t lights_camera_action, uint64_t name) {
    int payloadlength = sizeof(lights_camera_action)+sizeof(name);
    uint8_t * lca_payload = (uint8_t*) malloc(sizeof(uint8_t)*payloadlength);

    lca_payload[0] = 0 | lights_camera_action;
    uint64_t bitmask = 0x00000000000000FF;

    for (int i=1; i<payloadlength; i++) {
        uint64_t segment = name & (bitmask << 8*(i-1));
        uint8_t  reduced_segment = segment >> 8*(i-1);
        lca_payload[i] = reduced_segment;
    }
    
    payload = lca_payload;
}

// Send method
uint8_t * LCAMsg::Send() const {

    // std::cout << "ENTER SEND()" << std::endl;

    uint8_t * ptr = ( uint8_t * ) malloc (256);
    uint8_t * message = ptr;

    // Pack messageID
    uint16_t messageID = htons( get_messageID() );
    memcpy( message, &messageID, sizeof(uint16_t) );
    message += sizeof(uint16_t);
    // std::cout << "Sent messageID                    is " << ntohs( messageID ) << std::endl;
    
    // Pack senderID
    uint8_t senderID = get_senderID();
    memcpy( message, &senderID, sizeof(uint8_t) );
    message += sizeof(uint8_t);
    // std::cout << "Sent senderID                     is " << unsigned( get_senderID() ) << std::endl;
    
    // Pack receiverID
    uint8_t receiverID = get_receiverID();
    memcpy( message, &receiverID, sizeof(uint8_t) );
    message += sizeof(uint8_t);
    // std::cout << "Sent receiverID                   is " << unsigned( receiverID ) << std::endl;
    
    // Pack payloadLength
    uint32_t payloadLength = htonl( get_payloadLength() );
    memcpy( message, &payloadLength, sizeof(uint32_t) );
    message += sizeof(uint32_t);
    // std::cout << "Sent payloadLength                is " << ntohl( payloadLength ) << std::endl;

    // need to deconstruct the payload from the pointer
    uint8_t * payload_ptr = get_payload();

    for (int i=0; i<ntohl( payloadLength ); i++) {
        memcpy( message, &payload_ptr[i], sizeof(uint8_t) );
        message += sizeof(uint8_t);
    }
    
    // Pack lights_camera_action
    uint8_t lights_camera_action = get_lights_camera_action();
    memcpy( message, &lights_camera_action, sizeof(uint8_t) );
    message += sizeof(uint8_t);
    // std::cout << "Sent lights_camera_action         is " << unsigned( lights_camera_action ) << std::endl;
    
    // Pack name
    uint64_t name = htonll( get_name() );
    memcpy( message, &name, sizeof(uint64_t) );
    message += sizeof(uint64_t);
    // std::cout << "Sent name                         is " << ntohll( name ) << std::endl;

    // std::cout << "EXIT  SEND()" << std::endl;

    return ptr;
}

// Receive method
void LCAMsg::Receive( uint8_t * message ) {
    // std::cout << "\nENTER RECEIVE()" << std::endl;

    uint8_t * msg = message;

    // Extract messageID
    uint16_t msg_messageID;
    memcpy(&msg_messageID, msg, sizeof(uint16_t));
    msg += sizeof(uint16_t);
    msg_messageID = ntohs(msg_messageID);
    // std::cout << "Received msg_messageID            is " << msg_messageID << std::endl;

    // Extract senderID
    uint8_t msg_senderID;
    memcpy(&msg_senderID, msg, sizeof(uint8_t));
    msg += sizeof(uint8_t);
    // std::cout << "Received msg_senderID             is " << unsigned( msg_senderID ) << std::endl;
    
    // Extract receiverID
    uint8_t msg_receiverID;
    memcpy(&msg_receiverID, msg, sizeof(uint8_t));
    msg += sizeof(uint8_t);
    // std::cout << "Received msg_receiverID           is " << unsigned( msg_receiverID ) << std::endl;
    
    // Extract payloadLength
    uint32_t msg_payloadLength;
    memcpy(&msg_payloadLength, msg, sizeof(uint32_t));
    msg += sizeof(uint32_t);
    msg_payloadLength = ntohl(msg_payloadLength);
    // std::cout << "Received msg_payloadLength        is " << msg_payloadLength << std::endl;

    // Extract payload
    uint8_t * msg_payload = (uint8_t*) malloc(sizeof(uint8_t)*9);
    for (int i=0; i<msg_payloadLength; i++) {
        memcpy(&msg_payload[i], msg, sizeof(uint8_t));
        msg += sizeof(uint8_t);
    }

    // Extract lights_camera_action
    uint8_t * payload_ptr = msg_payload;

    uint8_t msg_lights_camera_action;
    memcpy(&msg_lights_camera_action, msg_payload, sizeof(uint8_t));
    msg_payload += sizeof(uint8_t);
    // std::cout << "Received msg_lights_camera_action is " << unsigned( msg_lights_camera_action ) << std::endl;
    
    // Extract name
    uint64_t msg_name;
    memcpy(&msg_name, msg_payload, sizeof(uint64_t));
    msg_payload += sizeof(uint64_t);
    // std::cout << "Received msg_name                 is " << ntohll( msg_name ) << std::endl;

    // Create new instance out of the info we've extracted
    // LCAMsg * msg_ = new LCAMsg(msg_messageID, msg_senderID, msg_receiverID, msg_payloadLength, msg_lights_camera_action, msg_name);

    // msg_->Send();
    // this->Send();
    // std::cout << "EXIT  RECEIVE()" << std::endl;
}
