#include "uavprotocol.h"
#include "lcamsg.h"
#include "unit_tests.h"

// TO DO
// Write Unit Tests

// Please assume that:
// - All messages are sent and received as a stream of binary data,
//      with each byte containing 8 bits of message content.
//      Bits are sent/received from MSB to LSB. 
// - All message fields are in Network Byte Order.
//      The code should be agnostic to endianness.

int main(int argc, char const *argv[]) {

    // Explanation
    unit_test_0();
    
    // Explanation
    unit_test_1();
    
    // Instances for testing
    LCAMsg * chain_link_1 = new LCAMsg( 0xffff, 0xff, 0xff, 0x9, 0b11111111, 0xFFFFFFFFFFFFFFFF );
    LCAMsg * chain_link_2 = new LCAMsg( 0x0000, 0x00, 0x00, 0x9, 0b00000000, 0x0000000000000000 );
    LCAMsg * chain_link_3 = new LCAMsg( 0xff88, 0xf8, 0xf8, 0x9, 0b00000100, 0xFFFFFFFF88888888 );

    std::cout << "\n*******************************************" << std::endl;
    std::cout << "**** Testing Double Send/Receive Cases ****" << std::endl;
    std::cout << "*******************************************" << std::endl;

    unit_test_3( chain_link_1, chain_link_2, chain_link_3 );
    unit_test_3( chain_link_1, chain_link_3, chain_link_2 );
    unit_test_3( chain_link_2, chain_link_3, chain_link_1 );
    unit_test_3( chain_link_2, chain_link_1, chain_link_3 );
    unit_test_3( chain_link_3, chain_link_2, chain_link_1 );
    unit_test_3( chain_link_3, chain_link_1, chain_link_2 );


    std::cout << "\n*******************************************" << std::endl;
    std::cout << "**** Testing Single Send/Receive Cases ****" << std::endl;
    std::cout << "*******************************************" << std::endl;

    unit_test_2( chain_link_1, chain_link_2 );
    unit_test_2( chain_link_2, chain_link_1 );
    unit_test_2( chain_link_2, chain_link_3 );
    unit_test_2( chain_link_3, chain_link_2 );
    unit_test_2( chain_link_1, chain_link_1 );
    unit_test_2( chain_link_3, chain_link_3 );

    // Testing Max and Min Value Potential Edge Cases

    std::cout << "\n********************************************************" << std::endl;
    std::cout << "**** Testing Max and Min Value Potential Edge Cases ****" << std::endl;
    std::cout << "********************************************************" << std::endl;

    LCAMsg * sender_max_to_min   = new LCAMsg( 0xffff, 0xff, 0xff, 0x9, 0b11111111, 0xFFFFFFFFFFFFFFFF );
    LCAMsg * receiver_max_to_min = new LCAMsg( 0x0000, 0x00, 0x00, 0x9, 0b00000000, 0x0000000000000000 );

    LCAMsg * sender_min_to_max   = new LCAMsg( 0x0000, 0x00, 0x00, 0x9, 0b00000000, 0x0000000000000000 );
    LCAMsg * receiver_min_to_max = new LCAMsg( 0xffff, 0xff, 0xff, 0x9, 0b11111111, 0xFFFFFFFFFFFFFFFF );

    unit_test_2( sender_max_to_min, receiver_max_to_min );
    unit_test_2( sender_min_to_max, receiver_min_to_max );

    std::cout << "\nEnd of main and unit tests\n" << std::endl;
    
}