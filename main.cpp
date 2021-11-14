#include "uavprotocol.h"
#include "lcamsg.h"
#include "unit_tests.h"

// TO DO
// Resolve segfaulting due to weird get_payload() things going on
// Network byte order everything
// for reference: https://www.tutorialspoint.com/unix_sockets/network_byte_orders.htm

// Please assume that:
// - All messages are sent and received as a stream of binary data,
//      with each byte containing 8 bits of message content.
//      Bits are sent/received from MSB to LSB. 
// - All message fields are in Network Byte Order.
//      The code should be agnostic to endianness.

int main(int argc, char const *argv[]) {
    // unit_test_0();
    // unit_test_1();
    unit_test_2();
    // unit_test_3();
    // unit_test_4();
    // unit_test_5();
}