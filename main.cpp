#include "uavprotocol.h"
#include "lcamsg.h"
#include "unit_tests.h"

// Please assume that:
// - All messages are sent and received as a stream of binary data,
//      with each byte containing 8 bits of message content.
//      Bits are sent/received from MSB to LSB. 
// - All message fields are in Network Byte Order.
//      The code should be agnostic to endianness.

int main(int argc, char const *argv[]) {
    uint8_t* payloadsend = create_lca_payload(0b1100111, 0xFFFFFFFFFFFFFFFF);
    uint8_t* payloadreceive = create_lca_payload(0b1100111, 0xFFFFFFFFFFFFFFFF);

    LCAMsg *sender   = new LCAMsg(1, 1, 2, 9, payloadsend, 0b11001111, 0xFFFFFFFFFFFFFFFF);
    LCAMsg *receiver = new LCAMsg(1, 1, 2, 9, payloadreceive, 0b11001111, 0xFFFFFFFFFFFFFFFF);

    std::string message = sender->Send();
    std::cout << message;
    receiver->Receive(message);
}