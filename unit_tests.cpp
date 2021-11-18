#include "unit_tests.h"
// #include "uavprotocol.h"
#include "lcamsg.h"

// TO DO
// Write Unit Tests

// Write a unit test framework to verify your implementation above.
// Use your engineering judgment on the scope of your test cases.
// A text print-out should be produced for the result of each test case.

// void unit_test_1() {
    
//     std::cout << "\n" << "===========================" << std::endl;
//     std::cout <<         "======= UNIT TEST 1 =======" << std::endl;
//     std::cout <<         "===========================" << "\n" << std::endl;

//     LCAMsg *sender   = new LCAMsg(1, 1, 2, 9, 0b11001111, 0xFFFFFFFFFFFFFFFF);
//     LCAMsg *receiver = new LCAMsg(1, 1, 2, 9, 0b11001111, 0xFFFFFFFFFFFFFFFF);

//     std::cout << "sender messageID     is " << sender->get_messageID() << std::endl;
//     std::cout << "sender senderID      is " << unsigned( sender->get_senderID()   ) << std::endl;
//     std::cout << "sender receiverID    is " << unsigned( sender->get_receiverID() ) << std::endl;
//     std::cout << "sender payloadLength is " << sender->get_payloadLength() << std::endl;
//     std::cout << "sender lca           is " << unsigned( sender->get_lights_camera_action() ) << std::endl;
//     std::cout << "sender lights        is " << unsigned( sender->get_lights() ) << std::endl;
//     std::cout << "sender camera        is " << unsigned( sender->get_camera() ) << std::endl;
//     std::cout << "sender action        is " << unsigned( sender->get_action() ) << std::endl;

//     receiver->Receive( sender->Send() );
// }

void unit_test_0() {

    std::cout << "\n" << "===========================" << std::endl;
    std::cout <<         "======= UNIT TEST 0 =======" << std::endl;
    std::cout <<         "===========================" << std::endl << std::endl;

    std::cout
    << "Demonstrating that:" << std::endl 
    << "(1) Base and derived class constructors initialize as expected" << std::endl
    << "    (derived constructor calls base constructor)" << std::endl
    << "(2) Access methods work as expected" << std::endl
    << "    (non-payload access methods are base class methods)" << std::endl
    << "(3) All message fields are in network byte order" << std::endl << std::endl;

    LCAMsg * message = new LCAMsg(0xFFEE, 0xFE, 0xEF, 0x9, 0xBF, htonll(0xFFEEDDCCBBAA9988) );

    std::cout << "Initalization: LCAMsg(0xFFEE, 0xFE, 0xEF, 0x9, 0xBF, htonll(0xFFEEDDCCBBAA9988) )" << std::endl << std::endl;
    std::cout << "Expected messageID     : 0xffee,             Actual messageID     : " << "0x" << std::hex << message->get_messageID()     << std::endl;
    std::cout << "Expected senderID      : 0xfe,               Actual senderID      : " << "0x" << std::hex << unsigned( message->get_senderID()   )      << std::endl;
    std::cout << "Expected receiverID    : 0xef,               Actual receiverID    : " << "0x" << std::hex << unsigned( message->get_receiverID() )  << std::endl;
    std::cout << "Expected payloadLength : 0x9,                Actual payloadLength : " << "0x" << std::hex << message->get_payloadLength() << std::endl;
    std::cout << "Expected lights        : 1,                  Actual lights        : " << unsigned( message->get_lights() )        << std::endl;
    std::cout << "Expected camera        : 0,                  Actual camera        : " << unsigned( message->get_camera() )        << std::endl;
    std::cout << "Expected action        : 63,                 Actual action        : " << unsigned( message->get_action() )        << std::endl;
    std::cout << "Expected name          : 0xFFEEDDCCBBAA9988, Actual name          : " << "0x" << std::hex << message->get_name()          << std::endl << std::endl;

}

// Test whether message fields are in network byte order [aka big-endian]
void unit_test_1() {

    std::cout << "\n" << "===========================" << std::endl;
    std::cout <<         "======= UNIT TEST 1 =======" << std::endl;
    std::cout <<         "===========================" << std::endl << std::endl;

    LCAMsg *sender   = new LCAMsg(1, 1, 2, 9, 0b10111111, 0x5555555555555555);
    LCAMsg *receiver = new LCAMsg(0, 0, 0, 9, 0b00000000, 0x0000000000000000);

    std::cout << "Sender Initialization   : LCAMsg(1, 1, 2, 9, 0b10111111, 0x5555555555555555)" << std::endl;
    std::cout << "Receiver Initialization : LCAMsg(0, 0, 0, 9, 0b00000000, 0x0000000000000000) (\"Blank\" Object)" << std::endl;

    std::cout << "Sender messageID     : " << sender->get_messageID() << std::endl;
    std::cout << "Sender senderID      : " << sender->get_senderID() << std::endl;
    std::cout << "Sender receiverID    : " << sender->get_receiverID() << std::endl;
    std::cout << "Sender lights        : " << sender->get_lights() << std::endl;
    std::cout << "Sender camera        : " << sender->get_camera() << std::endl;
    std::cout << "Sender action        : " << sender->get_action() << std::endl;
    std::cout << "Sender name          : " << sender->get_name() << std::endl;

    std::cout << "Receiver Pre-Receiving Sender Message" << std::endl << std::endl;
    std::cout << "Receiver messageID     : " << receiver->get_messageID() << std::endl;
    std::cout << "Receiver senderID      : " << receiver->get_senderID() << std::endl;
    std::cout << "Receiver receiverID    : " << receiver->get_receiverID() << std::endl;
    std::cout << "Receiver lights        : " << receiver->get_lights() << std::endl;
    std::cout << "Receiver camera        : " << receiver->get_camera() << std::endl;
    std::cout << "Receiver action        : " << receiver->get_action() << std::endl;
    std::cout << "Receiver name          : " << receiver->get_name() << std::endl;

    receiver->Receive( sender->Send() );

    std::cout << "Receiver Post-Receiving Sender Message" << std::endl << std::endl;
    std::cout << "Receiver messageID     : " << receiver->get_messageID() << std::endl;
    std::cout << "Receiver senderID      : " << receiver->get_senderID() << std::endl;
    std::cout << "Receiver receiverID    : " << receiver->get_receiverID() << std::endl;
    std::cout << "Receiver lights        : " << receiver->get_lights() << std::endl;
    std::cout << "Receiver camera        : " << receiver->get_camera() << std::endl;
    std::cout << "Receiver action        : " << receiver->get_action() << std::endl;
    std::cout << "Receiver name          : " << receiver->get_name() << std::endl;

}

void unit_test_2() {
    
    std::cout << "\n" << "===========================" << std::endl;
    std::cout <<         "======= UNIT TEST 2 =======" << std::endl;
    std::cout <<         "===========================" << "\n" << std::endl;

    LCAMsg *sender   = new LCAMsg(1, 1, 2, 9, 0b10111111, 0x5555555555555555);
    LCAMsg *receiver = new LCAMsg(0, 0, 0, 9, 0b00000000, 0x0000000000000000);


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