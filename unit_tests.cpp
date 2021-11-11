#include "unit_tests.h"
#include "uavprotocol.h"
#include "lcamsg.h"

#define BITMASK 0x00000000000000FF

// Write a unit test framework to verify your implementation above.
// Use your engineering judgment on the scope of your test cases.
// A text print-out should be produced for the result of each test case.

uint8_t* create_lca_payload(uint8_t lights_camera_action, uint64_t name) {
    int payloadlength = sizeof(lights_camera_action)+sizeof(name);
    uint8_t * lca_payload = (uint8_t*) malloc(sizeof(uint8_t)*payloadlength);

    lca_payload[0] = 0 | lights_camera_action;
    uint64_t bitmask = BITMASK;

    for (int i=1; i<payloadlength; i++) {
        uint64_t segment = name & (bitmask << 8*(i-1));
        uint8_t  reduced_segment = segment >> 8*(i-1);
        lca_payload[i] = reduced_segment;
    }

    // for (int i=0; i<payloadlength; i++){
    //     std::cout << i << "th payload segment is " << std::bitset<8>(lca_payload[i])  << std::endl;
    // }
    
    return lca_payload;
}

void unit_test_1() {
    
    std::cout << "\n" << "===========================" << std::endl;
    std::cout <<         "======= UNIT TEST 1 =======" << std::endl;
    std::cout <<         "===========================" << std::endl;
    
    uint8_t* payloadsend    = create_lca_payload(0b11000111, 0xFFFFFFFFFFFFFFFF);
    uint8_t* payloadreceive = create_lca_payload(0b11000111, 0xFFFFFFFFFFFFFFFF);

    LCAMsg *sender   = new LCAMsg(1, 1, 2, 9, payloadsend, 0b11001111, 0xFFFFFFFFFFFFFFFF);
    LCAMsg *receiver = new LCAMsg(1, 1, 2, 9, payloadreceive, 0b11001111, 0xFFFFFFFFFFFFFFFF);

    // std::stringstream stream;

    // uint8_t* retrieved_payload = sender->get_payload();
    // for (int i=0; i<sizeof(payloadsend); i++) {
    //     std::cout << retrieved_payload[i] << std::endl;
    //     // std::cout << i << "th payload element is " << 
    // }
    // std::string payloads( stream.str() );
    // std::cout << "payload is" << payloads << std::endl;
    
    std::string message = sender->Send();
    std::cout << "Sending    : " << message << std::endl;

    for (std::size_t i = 0; i < message.size(); ++i)
    {
        // std::cout << std::bitset<8>(message.c_str()[i]) << std::endl;
        std::cout << std::bitset<8>(message.c_str()[i]);
    }
    std::cout << std::endl;
    receiver->Receive(message);
    // LCAMsg received = LCAMsg(msg_);

    // std::string message = sender->Send();
    // std::cout << "Sent     Message: " << "0x" << std::hex << stoi(message) << std::endl;
    // std::cout << "Sent     Message: " << "0b" << std::bitset<sizeof(payloadsend)>(stoi(message)) << std::endl;
    // std::string result( stream.str() );
    // std::cout << result;
    // receiver->Receive(message);
}

void unit_test_2() {
    
    std::cout << "\n" << "===========================" << std::endl;
    std::cout <<         "======= UNIT TEST 2 =======" << std::endl;
    std::cout <<         "===========================" << "\n" << std::endl;
    
    uint8_t* payloadsend = create_lca_payload(0b11000111, 0x5555555555555555);
    uint8_t* payloadreceive = create_lca_payload(0b11000111, 0x5555555555555555);

    LCAMsg *sender   = new LCAMsg(1, 1, 2, 9, payloadsend, 0b11001111, 0x5555555555555555);
    LCAMsg *receiver = new LCAMsg(1, 1, 2, 9, payloadreceive, 0b11001111, 0x5555555555555555);

    // std::stringstream stream;

    // uint8_t* retrieved_payload = sender->get_payload();
    // for (int i=0; i<sizeof(payloadsend); i++) {
    //     std::cout << retrieved_payload[i] << std::endl;
    //     // std::cout << i << "th payload element is " << 
    // }
    // std::string payloads( stream.str() );
    // std::cout << "payload is" << payloads << std::endl;
    
    std::string message = sender->Send();
    std::cout << "Sending    : " << message << std::endl;

    for (std::size_t i = 0; i < message.size(); ++i)
    {
        // std::cout << std::bitset<8>(message.c_str()[i]) << std::endl;
        std::cout << std::bitset<8>(message.c_str()[i]);
    }
    std::cout << std::endl;
    receiver->Receive(message);
    // LCAMsg received = LCAMsg(msg_);

    // std::cout << "Sent     Message: " << "0x" << std::hex << stoi(message) << std::endl;
    // std::cout << "Sent     Message: " << "0b" << std::bitset<sizeof(payloadsend)*8>(stoi(message)) << std::endl;
    // std::cout << "0b" << std::bitset<sizeof(payloadsend)>(stoi(message)) << std::endl;
    // std::string result( stream.str() );
    // std::cout << result;
    // receiver->Receive(message);
}

void unit_test_3() {
    
    std::cout << "\n" << "===========================" << std::endl;
    std::cout <<         "======= UNIT TEST 3 =======" << std::endl;
    std::cout <<         "===========================" << "\n" << std::endl;
    
    uint8_t* payloadsend = create_lca_payload(0b11000111, 0x0000000000000000);
    uint8_t* payloadreceive = create_lca_payload(0b11000111, 0x0000000000000000);

    LCAMsg *sender   = new LCAMsg(1, 1, 2, 9, payloadsend, 0b11001111, 0x0000000000000000);
    LCAMsg *receiver = new LCAMsg(1, 1, 2, 9, payloadreceive, 0b11001111, 0x0000000000000000);

    // std::stringstream stream;

    // uint8_t* retrieved_payload = sender->get_payload();
    // for (int i=0; i<sizeof(payloadsend); i++) {
    //     std::cout << retrieved_payload[i] << std::endl;
    //     // std::cout << i << "th payload element is " << 
    // }
    // std::string payloads( stream.str() );
    // std::cout << "payload is" << payloads << std::endl;
    
    std::string message = sender->Send();
    std::cout << "Sending    : " << message << std::endl;

    for (std::size_t i = 0; i < message.size(); ++i)
    {
        // std::cout << std::bitset<8>(message.c_str()[i]) << std::endl;
        std::cout << std::bitset<8>(message.c_str()[i]);
    }
    std::cout << std::endl;
    receiver->Receive(message);
    // LCAMsg received = LCAMsg(msg_);

    // std::cout << "Sent     Message: " << "0x" << std::hex << stoi(message) << std::endl;
    // std::cout << "Sent     Message: " << "0b" << std::bitset<sizeof(payloadsend)*8>(stoi(message)) << std::endl;
    // std::cout << "0b" << std::bitset<sizeof(payloadsend)>(stoi(message)) << std::endl;
    // std::string result( stream.str() );
    // std::cout << result;
    // receiver->Receive(message);
}

void unit_test_4() {
    
    std::cout << "\n" << "===========================" << std::endl;
    std::cout <<         "======= UNIT TEST 4 =======" << std::endl;
    std::cout <<         "===========================" << "\n" << std::endl;
    
    uint8_t* payloadsend = create_lca_payload(0b11000111, 0x0000000000000000);
    uint8_t* payloadreceive = create_lca_payload(0b11000111, 0x000000000000000F);

    LCAMsg *sender   = new LCAMsg(1, 1, 2, 9, payloadsend, 0b11001111, 0x0000000000000000);
    LCAMsg *receiver = new LCAMsg(1, 1, 2, 9, payloadreceive, 0b11001111, 0x000000000000000F);

    // std::stringstream stream;

    // uint8_t* retrieved_payload = sender->get_payload();
    // for (int i=0; i<sizeof(payloadsend); i++) {
    //     std::cout << retrieved_payload[i] << std::endl;
    //     // std::cout << i << "th payload element is " << 
    // }
    // std::string payloads( stream.str() );
    // std::cout << "payload is" << payloads << std::endl;
    
    std::string message = sender->Send();
    std::cout << "Sending    : " << message << std::endl;

    for (std::size_t i = 0; i < message.size(); ++i)
    {
        // std::cout << std::bitset<8>(message.c_str()[i]) << std::endl;
        std::cout << std::bitset<8>(message.c_str()[i]);
    }
    std::cout << std::endl;
    receiver->Receive(message);
    // LCAMsg received = LCAMsg(msg_);

    // std::cout << "Sent     Message: " << "0x" << std::hex << stoi(message) << std::endl;
    // std::cout << "Sent     Message: " << "0b" << std::bitset<sizeof(payloadsend)*8>(stoi(message)) << std::endl;
    // std::cout << "0b" << std::bitset<sizeof(payloadsend)>(stoi(message)) << std::endl;
    // std::string result( stream.str() );
    // std::cout << result;
    // receiver->Receive(message);
}