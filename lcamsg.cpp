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
    UAVProtocol( messageID, senderID, receiverID, payloadLength, payload ), lights_camera_action(lights_camera_action), name(name) { 
        // std::cout << "Derived Constructor messageID     is " << messageID << std::endl;
        // std::cout << "Derived Constructor senderID      is " << senderID << std::endl;
        // std::cout << "Derived Constructor receiverID    is " << receiverID << std::endl;
        // std::cout << "Derived Constructor payloadLength is " << payloadLength << std::endl;
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

// uint8_t LCAMsg::get_size() {
//     return UAVProtocol::get_size();
// }

// Send method
uint8_t * LCAMsg::Send() {

    std::cout << "ENTER SEND()" << std::endl;

    uint8_t * ptr = ( uint8_t * ) malloc (26);
    // std::cout << "this->get_size()" << this->get_size() << std::endl;

    uint8_t * message = ptr;

    // Pack messageID
    uint16_t messageID = htons( get_messageID() );
    memcpy( message, &messageID, sizeof(uint16_t) );
    message += sizeof(uint16_t);
    std::cout << "Sent messageID                    is " << ntohs( messageID ) << std::endl;
    
    // Pack senderID
    uint8_t senderID = get_senderID();
    memcpy( message, &senderID, sizeof(uint8_t) );
    message += sizeof(uint8_t);
    std::cout << "Sent senderID                     is " << unsigned( get_senderID() ) << std::endl;
    
    // Pack receiverID
    uint8_t receiverID = get_receiverID();
    memcpy( message, &receiverID, sizeof(uint8_t) );
    message += sizeof(uint8_t);
    std::cout << "Sent receiverID                   is " << unsigned( receiverID ) << std::endl;
    
    // Pack payloadLength
    uint32_t payloadLength = htonl( get_payloadLength() );
    memcpy( message, &payloadLength, sizeof(uint32_t) );
    message += sizeof(uint32_t);
    std::cout << "Sent payloadLength                is " << ntohl( payloadLength ) << std::endl;

    // need to deconstruct the payload from the pointer
    uint8_t * payload_ptr = get_payload();

    // std::cout << "get_payloadlength() result (htonl) is " << htonl( get_payloadLength() ) << std::endl;
    // std::cout << "get_payloadlength() result         is " << get_payloadLength() << std::endl;
    // for (int i=0; i<get_payloadLength(); i++) {
    // int payloadpackingiterations = 0;
    for (int i=0; i<ntohl( payloadLength ); i++) {
        memcpy( message, &payload_ptr[i], sizeof(uint8_t) );
        message += sizeof(uint8_t);
        // payloadpackingiterations++;
    }
    // std::cout << "payloadpackingiterations is " << payloadpackingiterations << std::endl;
    
    // Pack lights_camera_action
    uint8_t lights_camera_action = get_lights_camera_action();
    memcpy( message, &lights_camera_action, sizeof(uint8_t) );
    message += sizeof(uint8_t);
    std::cout << "Sent lights_camera_action         is " << unsigned( lights_camera_action ) << std::endl;
    
    // Pack name
    uint64_t name = htonll( get_name() );
    memcpy( message, &name, sizeof(uint64_t) );
    message += sizeof(uint64_t);
    std::cout << "Sent name                         is " << ntohll( name ) << std::endl;

    std::cout << "EXIT  SEND()" << std::endl;

    return message;
}

// Receive method
void LCAMsg::Receive( uint8_t * message ) {
    std::cout << "\nENTER RECEIVE()" << std::endl;

    uint8_t * msg = message;

    // Extract messageID
    uint16_t msg_messageID;
    memcpy(&msg_messageID, msg, sizeof(uint16_t));
    msg += sizeof(uint16_t);
    // std::cout << "Received msg_messageID            is " << ntohs( msg_messageID ) << std::endl;
    std::cout << "Received msg_messageID            is " << msg_messageID << std::endl;

    // Extract senderiD
    uint8_t msg_senderID;
    memcpy(&msg_senderID, msg, sizeof(uint8_t));
    msg += sizeof(uint8_t);
    std::cout << "Received msg_senderID             is " << unsigned( msg_senderID ) << std::endl;
    
    // Extract receiverID
    uint8_t msg_receiverID;
    memcpy(&msg_receiverID, msg, sizeof(uint8_t));
    msg += sizeof(uint8_t);
    std::cout << "Received msg_receiverID           is " << unsigned( msg_receiverID ) << std::endl;
    
    // Extract payloadLength
    uint32_t msg_payloadLength;
    memcpy(&msg_payloadLength, msg, sizeof(uint32_t));
    msg += sizeof(uint32_t);
    std::cout << "Received msg_payloadLength        is " << msg_payloadLength << std::endl;

    // Extract payload
    // uint8_t * msg_payload = (uint8_t*) malloc(sizeof(uint8_t)*msg_payloadLength);
    uint8_t * msg_payload = (uint8_t*) malloc(sizeof(uint8_t)*9);
    // for (int i=0; i<msg_payloadlength; i++) {
    for (int i=0; i<9; i++) {
        memcpy(&msg_payload[i], msg, sizeof(uint8_t));
        msg += sizeof(uint8_t);
    }

    // Extract lights_camera_action
    uint8_t msg_lights_camera_action;
    memcpy(&msg_lights_camera_action, msg, sizeof(uint8_t));
    msg += sizeof(uint8_t);
    std::cout << "Received msg_lights_camera_action is " << unsigned( msg_lights_camera_action ) << std::endl;
    
    // Extract name
    uint64_t msg_name;
    memcpy(&msg_name, msg, sizeof(uint64_t));
    msg += sizeof(uint64_t);
    std::cout << "Received msg_name                 is " << msg_name << std::endl;

    // Create new instance out of the info we've extracted
    LCAMsg * msg_ = new LCAMsg(msg_messageID, msg_senderID, msg_receiverID, msg_payloadLength, msg_payload, msg_lights_camera_action, msg_name);
    // LCAMsg msg_(msg_messageID, msg_senderID, msg_receiverID, msg_payloadLength, msg_payload, msg_lights_camera_action, msg_name);

    msg_->Send();
    this->Send();
    std::cout << "EXIT  RECEIVE()" << std::endl;
}
