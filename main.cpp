#include "uavprotocol.h"
#include "lcamsg.h"
#include "unit_tests.h"

// Please assume that:
// - All messages are sent and received as a stream of binary data,
//      with each byte containing 8 bits of message content.
//      Bits are sent/received from MSB to LSB. 
// - All message fields are in Network Byte Order.
//      The code should be agnostic to endianness.

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

int main(int argc, char const *argv[]) {
    uint8_t* payloadsend = create_lca_payload(0b1100111, 0xFFFFFFFFFFFFFFFF);
    uint8_t* payloadreceive = create_lca_payload(0b1100111, 0xFFFFFFFFFFFFFFFF);

    LCAMsg *sender   = new LCAMsg(1, 1, 2, 9, payloadsend, 0b11001111, 0xFFFFFFFFFFFFFFFF);
    LCAMsg *receiver = new LCAMsg(1, 1, 2, 9, payloadreceive, 0b11001111, 0xFFFFFFFFFFFFFFFF);
    std::string message = sender->Send();
    std::cout << message;
    receiver->Receive(message);
}