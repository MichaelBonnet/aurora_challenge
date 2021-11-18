// ================ //
// === INCLUDES === //
// ================ //

#include "lcamsg.h"

// =================== //
// === DEFINITIONS === //
// =================== //

// Default Constructor
LCAMsg::LCAMsg( uint16_t messageID, uint8_t senderID, uint8_t receiverID, uint32_t payloadLength, uint8_t lights_camera_action, uint64_t name ) : 
    UAVProtocol( messageID, senderID, receiverID, payloadLength ), lights_camera_action(lights_camera_action), name(name) {
        create_lca_payload(lights_camera_action, name);
}

// Copy Constructor
LCAMsg::LCAMsg( LCAMsg &obj ) : UAVProtocol( obj ), lights_camera_action(obj.lights_camera_action), name(obj.name) { }

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

    uint8_t *  payload_ptr = lca_payload;
    memcpy( &payload_ptr, &lights_camera_action, sizeof(uint8_t) );
    payload_ptr += sizeof(uint8_t);

    uint64_t * name_ptr = &name;
    memcpy( &payload_ptr, &name, sizeof(uint64_t) );
    payload_ptr += sizeof(uint64_t);
    
    payload = lca_payload;
}

// Send method
uint8_t * LCAMsg::Send() const {

    uint8_t * ptr = ( uint8_t * ) malloc (26);
    uint8_t * message = ptr;

    // Pack messageID
    uint16_t messageID = htons( get_messageID() );
    memcpy( message, &messageID, sizeof(uint16_t) );
    message += sizeof(uint16_t);
    
    // Pack senderID
    uint8_t senderID = get_senderID();
    memcpy( message, &senderID, sizeof(uint8_t) );
    message += sizeof(uint8_t);
    
    // Pack receiverID
    uint8_t receiverID = get_receiverID();
    memcpy( message, &receiverID, sizeof(uint8_t) );
    message += sizeof(uint8_t);
    
    // Pack payloadLength
    uint32_t payloadLength = htonl( get_payloadLength() );
    memcpy( message, &payloadLength, sizeof(uint32_t) );
    message += sizeof(uint32_t);

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
    
    // Pack name
    uint64_t name = htonll( get_name() );
    memcpy( message, &name, sizeof(uint64_t) );
    message += sizeof(uint64_t);

    return ptr;
}

// Receive method
void LCAMsg::Receive( uint8_t * message ) {

    uint8_t * msg = message;

    // Extract messageID
    uint16_t msg_messageID;
    memcpy(&msg_messageID, msg, sizeof(uint16_t));
    msg_messageID = ntohs(msg_messageID);
    msg += sizeof(uint16_t);

    // Extract senderID
    uint8_t msg_senderID;
    memcpy(&msg_senderID, msg, sizeof(uint8_t));
    msg += sizeof(uint8_t);
    
    // Extract receiverID
    uint8_t msg_receiverID;
    memcpy(&msg_receiverID, msg, sizeof(uint8_t));
    msg += sizeof(uint8_t);
    
    // Extract payloadLength
    uint32_t msg_payloadLength;
    memcpy(&msg_payloadLength, msg, sizeof(uint32_t));
    msg_payloadLength = ntohl(msg_payloadLength);
    msg += sizeof(uint32_t);

    // Extract payload
    uint8_t * msg_payload = (uint8_t*) malloc(sizeof(uint8_t)*msg_payloadLength);
    uint8_t * payload_ptr = msg_payload;
    for (int i=0; i<msg_payloadLength; i++) {
        memcpy(&msg_payload[i], msg, sizeof(uint8_t));
        msg += sizeof(uint8_t);
    }

    // Extract lights_camera_action
    uint8_t msg_lights_camera_action;
    memcpy(&msg_lights_camera_action, msg, sizeof(uint8_t));
    msg += sizeof(uint8_t);
    
    // Extract name
    uint64_t msg_name;
    memcpy(&msg_name, msg, sizeof(uint64_t));
    msg_name = ntohll(msg_name);
    msg += sizeof(uint64_t);

    set_messageID( msg_messageID );
    set_senderID( msg_senderID );
    set_receiverID( msg_receiverID );
    set_payloadLength( msg_payloadLength );
    set_payload( msg_payload );
    set_lights_camera_action( msg_lights_camera_action );
    set_name( msg_name );
}
