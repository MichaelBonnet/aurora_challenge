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
    std::cout << "\nINSIDE SEND()" << std::endl;
    uint message = 0b0;
    uint shiftcount = 0;

    // Pack messageID
    uint16_t messageID = htons( get_messageID() );
    message |= messageID;
    shiftcount += sizeof(messageID)*8;
    std::cout << "messageID                    is " << messageID << std::endl;
    std::cout << "shiftcount inc for messageID is " << sizeof(messageID)*8 << std::endl;
    std::cout << "sizeof(messageID)            is " << sizeof(messageID) << std::endl;
    // std::cout << "size_t(messageID) is " << size_t(messageID) << std::endl << std::endl;
    // message |= get_messageID();
    // shiftcount += sizeof(get_messageID())*8;
    
    // Pack senderID
    uint8_t senderID = get_senderID();
    message |= (senderID << shiftcount);
    shiftcount += sizeof(senderID)*8;
    // message |= (get_senderID() << shiftcount);
    // shiftcount += sizeof(get_senderID())*8;
    
    // Pack receiverID
    uint8_t receiverID = get_receiverID();
    message |= (receiverID << shiftcount);
    shiftcount += sizeof(receiverID)*8;
    // message |= (get_receiverID() << shiftcount);
    // shiftcount += sizeof(get_receiverID())*8;
    
    // Pack payloadLength
    uint32_t payloadLength = htonl( get_payloadLength() );
    message |= (payloadLength << shiftcount);
    shiftcount += sizeof(payloadLength)*8;
    // message |= (get_payloadLength() << shiftcount);
    // shiftcount += sizeof(get_payloadLength())*8;

    // need to deconstruct the payload from the pointer
    uint8_t * payload_ptr = get_payload();

    std::cout << "get_payloadlength() result is " << get_payloadLength() << std::endl << std::endl;
    // Code segfaults here
    // for (int i=0; i<get_payloadLength(); i++) {
    for (int i=0; i<9; i++) {
        message |= ( payload_ptr[i] << shiftcount );
        // std::cout << "sizeof(payload_ptr[i]*8 = " << sizeof(payload_ptr[i])*8 << std::endl;
        shiftcount += sizeof(payload_ptr[i])*8;
    }
    // std::cout << "just after segfaulting code" << std::endl;
    
    // Pack lights_camera_action
    uint8_t lights_camera_action = get_lights_camera_action();
    message |= (lights_camera_action << shiftcount);
    shiftcount += sizeof(lights_camera_action)*8;
    // message |= (get_lights_camera_action() << shiftcount);
    // shiftcount += sizeof(get_lights_camera_action())*8;
    
    // Pack name
    uint64_t name = htonll( get_name() );
    message |= (name << shiftcount);
    shiftcount += sizeof(name)*8;
    // message |= (get_name() << shiftcount);
    // shiftcount += sizeof(get_name())*8;

    std::cout << "shiftcount after   packing is " << shiftcount << std::endl;
    // std::cout << "in binary: " << std::bitset<208>(message) << std::endl;

    return message;
}

// Receive method
void LCAMsg::Receive(const uint message) const {
    std::cout << "\nINSIDE RECEIVE()" << std::endl;

    uint msg = message;
    // std::cout << "sizeof(msg) is " << sizeof(msg) << std::endl;
    // std::cout << "size_t(msg) is " << size_t(msg) << std::endl;
    uint pre_shiftcount = 208 - 16;
    uint shiftcount = 0;

    std::cout << "step 0 shiftcount = " << shiftcount << std::endl;

    // Extract messageID
    uint16_t msg_messageID = ntohs( ( msg >> (pre_shiftcount - shiftcount) ) & UINT16_FLAG );
    std::cout << "msg_messageID                    is " << msg_messageID << std::endl;
    shiftcount += sizeof(msg_messageID)*8;
    std::cout << "shiftcount inc for msg_messageID is " << sizeof(msg_messageID)*8 << std::endl;
    std::cout << "sizeof(msg_messageID)            is " << sizeof(msg_messageID) << std::endl;
    // std::cout << "size_t(msg_messageID) is " << size_t(msg_messageID) << std::endl << std::endl;
    
    std::cout << "step 1 shiftcount = " << shiftcount << std::endl;

    // Extract senderiD
    uint8_t msg_senderID = ( msg >> (pre_shiftcount - shiftcount) ) & UINT8_FLAG;
    shiftcount += sizeof(msg_senderID)*8;

    std::cout << "step 2 shiftcount = " << shiftcount << std::endl;
    
    // Extract receiverID
    uint8_t msg_receiverID = ( msg >> (pre_shiftcount - shiftcount) ) & UINT8_FLAG;
    shiftcount += sizeof(msg_receiverID)*8;

    std::cout << "step 3 shiftcount = " << shiftcount << std::endl;
    
    // Extract payloadLength
    uint32_t msg_payloadLength = ntohl( ( msg >> (pre_shiftcount - shiftcount) ) & UINT32_FLAG );
    shiftcount += sizeof(msg_payloadLength)*8;

    // Extract payload
    uint32_t payloadlength = msg_payloadLength;
    std::cout << "msg_payloadLength = " << msg_payloadLength << std::endl;
    std::cout << "just before segfault" << std::endl;
    uint8_t * msg_payload = (uint8_t*) malloc(sizeof(uint8_t)*msg_payloadLength);
    // for (int i=0; i<payloadlength; i++) {
    for (int i=0; i<9; i++) {
        msg_payload[i] = ( msg >> (pre_shiftcount - shiftcount) ) & UINT8_FLAG;
        shiftcount += sizeof(msg_payload[i])*8;
    }
    std::cout << "just after segfault" << std::endl;

    std::cout << "step 4 shiftcount = " << shiftcount << std::endl;

    // Extract lights_camera_action
    uint8_t msg_lights_camera_action = ( msg >> (pre_shiftcount - shiftcount) ) & UINT8_FLAG;
    shiftcount += sizeof(msg_lights_camera_action)*8;

    std::cout << "step 5 shiftcount = " << shiftcount << std::endl;
    
    // Extract name
    uint64_t msg_name = ntohll( ( msg >> (pre_shiftcount - shiftcount) ) & UINT64_FLAG );
    shiftcount += sizeof(msg_name)*8;

    std::cout << "step 6 shiftcount = " << shiftcount << std::endl;
    std::cout << "shiftcount after unpacking is " << shiftcount << std::endl;

    // Create new instance out of the info we've extracted
    LCAMsg * msg_ = new LCAMsg(msg_messageID, msg_senderID, msg_receiverID, msg_payloadLength, msg_payload, msg_lights_camera_action, msg_name);
    // LCAMsg msg_(msg_messageID, msg_senderID, msg_receiverID, msg_payloadLength, msg_payload, msg_lights_camera_action, msg_name);

    // std::cout << "segfault checkpoint 0" << std::endl;
    uint msg_message = msg_->Send();
    // std::cout << "\npost msg_->Send()\n";

    std::cout << "ReceivED Message Send Call : " << msg_->Send() << std::endl;
    std::cout << "ReceivER Message Send Call : " << this->Send() << std::endl;
}
