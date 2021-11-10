#include "unit_tests.h"
#include "uavprotocol.h"
#include "lcamsg.h"

// Write a unit test framework to verify your implementation above.
// Use your engineering judgment on the scope of your test cases.
// A text print-out should be produced for the result of each test case.

uint8_t* create_lca_payload(uint8_t lights_camera_action, uint64_t name) {
    int payloadlength = size_t(lights_camera_action)+size_t(name);
    uint8_t * lca_payload = (uint8_t*) malloc(sizeof(uint8_t)*payloadlength);

    *lca_payload = 0 | lights_camera_action;
    lca_payload += 1;
    for (int i=1; i<payloadlength; i++) {
        *lca_payload = (name & (BYTE_0_TO_7_64 >> (sizeof(uint8_t)*(i-1))) ) >> (size_t(name) - sizeof(uint8_t)*(payloadlength-i));
        lca_payload += 1;
    }

    return lca_payload;
}

void unit_test_1() {
    uint8_t* payloadsend = create_lca_payload(0b1100111, 0xFFFFFFFFFFFFFFFF);
    uint8_t* payloadreceive = create_lca_payload(0b1100111, 0xFFFFFFFFFFFFFFFF);

    LCAMsg *sender   = new LCAMsg(1, 1, 2, 9, payloadsend, 0b11001111, 0xFFFFFFFFFFFFFFFF);
    LCAMsg *receiver = new LCAMsg(1, 1, 2, 9, payloadreceive, 0b11001111, 0xFFFFFFFFFFFFFFFF);

    std::stringstream stream;
    
    std::string message = sender->Send();
    // std::cout << std::hex << message;
    stream << "0x" << std::hex << stoi(message);
    std::string result( stream.str() );
    std::cout << result;
    receiver->Receive(message);
}