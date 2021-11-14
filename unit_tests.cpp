#include "unit_tests.h"
#include "uavprotocol.h"
#include "lcamsg.h"

#define BITMASK 0x00000000000000FF

// TO DO
// Resolve stoi() going out of range issue for unit_test_1()

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
    
    return lca_payload;
}

void unit_test_0() {

    std::cout << "\n" << "===========================" << std::endl;
    std::cout <<         "======= UNIT TEST 0 =======" << std::endl;
    std::cout <<         "===========================" << "\n" << std::endl;
    
    uint8_t* payloadsend    = create_lca_payload(0b11000111, 0xFFFFFFFFFFFFFFFF);
    uint8_t* payloadreceive = create_lca_payload(0b11000111, 0xFFFFFFFFFFFFFFFF);

    // need to deconstruct the payload from the pointer
    uint message_ = 0;
    int shiftcount = 0;
    uint8_t * payload_ptr = payloadsend;
    for (int i=0; i<9; i++) {
        message_ |= ( htons( payload_ptr[i] ) << shiftcount );
        shiftcount += 8;
    }

    std::string temp = std::to_string(message_);
    std::cout << "payload string is : " << temp << std::endl;
    // std::cout << "payload string is : " << std::bitset<8*sizeof(stoi(temp))>(stoi(temp)) << std::endl;

    

    // for (int i=0; i<9; i++) {
    //     std::cout << atoi(payload_ptr[i]);
    // }
    // std::cout << std::endl;

    LCAMsg *sender   = new LCAMsg(1, 1, 2, 9, payloadsend, 0b11001111, 0xFFFFFFFFFFFFFFFF);
    LCAMsg *receiver = new LCAMsg(1, 1, 2, 9, payloadreceive, 0b11001111, 0xFFFFFFFFFFFFFFFF);
    
    uint message = sender->Send();
    // std::cout << "Sending     : " << message << std::endl;
    // std::cout << "Msg Length  : " << message.length() << std::endl;

    // std::string params = message.substr(0, 9);
    // std::string payload = message.substr(9, std::string::npos);
    // std::cout << "payload is: " << std::bitset<8*sizeof(stoi(payload))>(stoi(payload)) << std::endl;
    // std::cout << "sizeof(0xFFFFFFFFFFFFFFFF) is: " << sizeof(0xFFFFFFFFFFFFFFFF) << std::endl;

    // std::cout << "Msg params  : " << params << std::endl;
    // std::cout << "Msg payload : " << payload << std::endl;


}

void unit_test_1() {
    
    std::cout << "\n" << "===========================" << std::endl;
    std::cout <<         "======= UNIT TEST 1 =======" << std::endl;
    std::cout <<         "===========================" << "\n" << std::endl;
    
    uint8_t* payloadsend    = create_lca_payload(0b11000111, 0xFFFFFFFFFFFFFFFF);
    uint8_t* payloadreceive = create_lca_payload(0b11000111, 0xFFFFFFFFFFFFFFFF);

    LCAMsg *sender   = new LCAMsg(1, 1, 2, 9, payloadsend,    0b11001111, 0xFFFFFFFFFFFFFFFF);
    LCAMsg *receiver = new LCAMsg(1, 1, 2, 9, payloadreceive, 0b11001111, 0xFFFFFFFFFFFFFFFF);
    
    uint message = sender->Send();
    std::cout << "Sending    : " << message << std::endl;
    // std::cout << "Msg size (bytes)  : " << message.size() << std::endl;
    // std::cout << "Msg size (bits)   : " << message.size()*8 << std::endl;

    // std::string str1 = "aaaaaaaa";
    // std::cout << "Str1 size (bytes) : " << str1.size() << std::endl;
    // std::cout << "Str1 size (bits)  : " << str1.size()*8 << std::endl;
    // std::string str2 = "aaaa";
    // std::cout << "Str2 size (bytes) : " << str2.size() << std::endl;
    // std::cout << "Str2 size (bits)  : " << str2.size()*8 << std::endl;

    // for (std::size_t i = 0; i < message.size(); ++i)
    // {
    //     std::cout << std::bitset<8>(message.c_str()[i]);
    // }
    // std::cout << std::endl;
    receiver->Receive(message);
}

void unit_test_2() {
    
    std::cout << "\n" << "===========================" << std::endl;
    std::cout <<         "======= UNIT TEST 2 =======" << std::endl;
    std::cout <<         "===========================" << "\n" << std::endl;
    
    uint8_t* payloadsend = create_lca_payload(0b11000111, 0x5555555555555555);
    uint8_t* payloadreceive = create_lca_payload(0b11000111, 0x5555555555555555);

    LCAMsg *sender   = new LCAMsg(1, 1, 2, 9, payloadsend, 0b11001111, 0x5555555555555555);
    LCAMsg *receiver = new LCAMsg(1, 1, 2, 9, payloadreceive, 0b11001111, 0x5555555555555555);
    
    // std::cout << "MessageID     (expected 1): " << sender->get_messageID() << std::endl;
    // std::cout << "senderID      (expected 1): " << sender->get_senderID() << std::endl;
    // std::cout << "receiverID    (expected 2): " << sender->get_receiverID() << std::endl;
    // std::cout << "payloadLength (expected 9): " << sender->get_payloadLength() << std::endl;

    uint message = sender->Send();
    std::cout << "Sending    : " << message << std::endl;

    // for (std::size_t i = 0; i < message.size(); ++i)
    // {
    //     std::cout << std::bitset<8>(message.c_str()[i]);
    // }
    // std::cout << std::endl;
    receiver->Receive(message);
}

void unit_test_3() {
    
    std::cout << "\n" << "===========================" << std::endl;
    std::cout <<         "======= UNIT TEST 3 =======" << std::endl;
    std::cout <<         "===========================" << "\n" << std::endl;
    
    uint8_t* payloadsend = create_lca_payload(0b11000111, 0x0000000000000000);
    uint8_t* payloadreceive = create_lca_payload(0b11000111, 0x0000000000000000);

    LCAMsg *sender   = new LCAMsg(1, 1, 2, 9, payloadsend, 0b11001111, 0x0000000000000000);
    LCAMsg *receiver = new LCAMsg(1, 1, 2, 9, payloadreceive, 0b11001111, 0x0000000000000000);
    
    uint message = sender->Send();
    std::cout << "Sending    : " << message << std::endl;

    // for (std::size_t i = 0; i < message.size(); ++i)
    // {
    //     std::cout << std::bitset<8>(message.c_str()[i]);
    // }
    // std::cout << std::endl;
    receiver->Receive(message);
}

void unit_test_4() {
    
    std::cout << "\n" << "===========================" << std::endl;
    std::cout <<         "======= UNIT TEST 4 =======" << std::endl;
    std::cout <<         "===========================" << "\n" << std::endl;
    
    uint8_t* payloadsend = create_lca_payload(0b11000111, 0x0000000000000000);
    uint8_t* payloadreceive = create_lca_payload(0b11000111, 0x000000000000000F);

    LCAMsg *sender   = new LCAMsg(1, 1, 2, 9, payloadsend, 0b11001111, 0x0000000000000000);
    LCAMsg *receiver = new LCAMsg(1, 1, 2, 9, payloadreceive, 0b11001111, 0x000000000000000F);
    
    uint message = sender->Send();
    std::cout << "S Sending  : " << message << std::endl;
    uint r_message = receiver->Send();
    std::cout << "R Sending  : " << r_message << std::endl;


    // for (std::size_t i = 0; i < message.size(); ++i)
    // {
    //     std::cout << std::bitset<8>(message.c_str()[i]);
    // }
    // std::cout << std::endl;
    receiver->Receive(message);
}

void unit_test_5() {
    
    std::cout << "\n" << "===========================" << std::endl;
    std::cout <<         "======= UNIT TEST 5 =======" << std::endl;
    std::cout <<         "===========================" << "\n" << std::endl;
    
    uint8_t* payloadsend = create_lca_payload(0b11000111, 0xF000000000000000);
    uint8_t* payloadreceive = create_lca_payload(0b11000111, 0x000000000000000F);

    LCAMsg *sender   = new LCAMsg(1, 1, 2, 9, payloadsend, 0b11001111, 0x0000000000000000);
    LCAMsg *receiver = new LCAMsg(1, 1, 2, 9, payloadreceive, 0b11001111, 0x000000000000000F);
    
    uint message = sender->Send();
    std::cout << "Sending    : " << message << std::endl;

    // for (std::size_t i = 0; i < message.size(); ++i)
    // {
    //     std::cout << std::bitset<8>(message.c_str()[i]);
    // }
    // std::cout << std::endl;
    receiver->Receive(message);
}