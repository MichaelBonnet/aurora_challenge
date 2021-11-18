#include "unit_tests.h"
// #include "uavprotocol.h"
#include "lcamsg.h"

// TO DO
// Write Unit Tests

// Write a unit test framework to verify your implementation above.
// Use your engineering judgment on the scope of your test cases.
// A text print-out should be produced for the result of each test case.

void unit_test_1() {
    
    std::cout << "\n" << "===========================" << std::endl;
    std::cout <<         "======= UNIT TEST 1 =======" << std::endl;
    std::cout <<         "===========================" << "\n" << std::endl;

    LCAMsg *sender   = new LCAMsg(1, 1, 2, 9, 0b11001111, 0xFFFFFFFFFFFFFFFF);
    LCAMsg *receiver = new LCAMsg(1, 1, 2, 9, 0b11001111, 0xFFFFFFFFFFFFFFFF);

    std::cout << "sender messageID     is " << sender->get_messageID() << std::endl;
    std::cout << "sender senderID      is " << unsigned( sender->get_senderID()   ) << std::endl;
    std::cout << "sender receiverID    is " << unsigned( sender->get_receiverID() ) << std::endl;
    std::cout << "sender payloadLength is " << sender->get_payloadLength() << std::endl;
    std::cout << "sender lca           is " << unsigned( sender->get_lights_camera_action() ) << std::endl;
    std::cout << "sender lights        is " << unsigned( sender->get_lights() ) << std::endl;
    std::cout << "sender camera        is " << unsigned( sender->get_camera() ) << std::endl;
    std::cout << "sender action        is " << unsigned( sender->get_action() ) << std::endl;

    receiver->Receive( sender->Send() );
}

void unit_test_2() {
    
    std::cout << "\n" << "===========================" << std::endl;
    std::cout <<         "======= UNIT TEST 2 =======" << std::endl;
    std::cout <<         "===========================" << "\n" << std::endl;

    LCAMsg *sender   = new LCAMsg(1, 1, 2, 9, 0b10111111, 0x5555555555555555);
    LCAMsg *receiver = new LCAMsg(1, 1, 2, 9, 0b10111111, 0x5555555555555555);

    receiver->Receive( sender->Send() );
}

void unit_test_3() {
    
    std::cout << "\n" << "===========================" << std::endl;
    std::cout <<         "======= UNIT TEST 3 =======" << std::endl;
    std::cout <<         "===========================" << "\n" << std::endl;

    LCAMsg *sender   = new LCAMsg(1, 1, 2, 9, 0b00000001, 0x0000000000000000);
    LCAMsg *receiver = new LCAMsg(1, 1, 2, 9, 0b00000001, 0x0000000000000000);

    receiver->Receive( sender->Send() );
}

void unit_test_4() {
    
    std::cout << "\n" << "===========================" << std::endl;
    std::cout <<         "======= UNIT TEST 4 =======" << std::endl;
    std::cout <<         "===========================" << "\n" << std::endl;

}

void unit_test_5() {
    
    std::cout << "\n" << "===========================" << std::endl;
    std::cout <<         "======= UNIT TEST 5 =======" << std::endl;
    std::cout <<         "===========================" << "\n" << std::endl;
    
}

void unit_test_6() {
    
    std::cout << "\n" << "===========================" << std::endl;
    std::cout <<         "======= UNIT TEST 6 =======" << std::endl;
    std::cout <<         "===========================" << "\n" << std::endl;
    
}