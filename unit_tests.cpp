// TO DO
// Write Unit Tests

// REQUIREMENTS
// Write a unit test framework to verify your implementation above.
// Use your engineering judgment on the scope of your test cases.
// A text print-out should be produced for the result of each test case.

// ================ //
// === INCLUDES === //
// ================ //

#include "unit_tests.h"

// =================================== //
// === HELPER FUNCTION DEFINITIONS === //
// =================================== //

bool are_LCAMsg_instances_equal(LCAMsg * instance1, LCAMsg * instance2) {

    // LCAMsg * new_instance1 = new LCAMsg(*instance1);
    // LCAMsg * new_instance2 = new LCAMsg(*instance2); 
    
    int failure_count = 0;

    if ( instance1->get_messageID() != instance2->get_messageID() ) {
        std::cout << "field 1 not equal" << std::endl;
        failure_count++;
        // return false;
    }
    if ( instance1->get_senderID() != instance2->get_senderID() ) {
        std::cout << "field 2 not equal" << std::endl;
        failure_count++;
        // return false;
    }
    if ( instance1->get_receiverID() != instance2->get_receiverID() ) {
        std::cout << "field 3 not equal" << std::endl;
        failure_count++;
        // return false;
    }
    if ( instance1->get_payloadLength() != instance2->get_payloadLength() ) {
        std::cout << "field 4 not equal" << std::endl;
        failure_count++;
        // return false;
    }
    if ( instance1->get_lights_camera_action() != instance2->get_lights_camera_action() ) {
        std::cout << "field 5 not equal" << std::endl;
        // std::cout << "instance1->get_lights_camera_action() is " << instance1->get_lights_camera_action() << std::endl;
        // std::cout << "instance2->get_lights_camera_action() is " << instance2->get_lights_camera_action() << std::endl;
        failure_count++;
        // return false;
    }
    if ( instance1->get_name() != instance2->get_name() ) {
        std::cout << "field 6 not equal" << std::endl;
        std::cout << "instance1->get_name() is " << instance1->get_name() << std::endl;
        std::cout << "instance2->get_name() is " << instance2->get_name() << std::endl;
        failure_count++;
        // return false;
    }

    if (failure_count == 0) {
        return true;
    }
    else {
        return false;
    }

}

// ============================= //
// === UNIT TEST DEFINITIONS === //
// ============================= //

void unit_test_0() {

    std::cout << "\n" << "==============================================" << std::endl;
    std::cout <<         "=== Initialization and Access Methods Test ===" << std::endl;
    std::cout <<         "==============================================" << std::endl << std::endl;

    // std::cout
    // << "Demonstrating that:" << std::endl 
    // << "(1) Base and derived class constructors initialize as expected" << std::endl
    // << "    (derived constructor calls base constructor)" << std::endl
    // << "(2) Access methods work as expected" << std::endl
    // << "    (non-payload access methods are base class methods)" << std::endl
    // << "(3) All message fields are in network byte order" << std::endl << std::endl;

    LCAMsg * message = new LCAMsg(0xFFEE, 0xFE, 0xEF, 0x9, 0b10111111, 0xFFEEDDCCBBAA9988 );

    std::cout << "Initalization: LCAMsg(0xFFEE, 0xFE, 0xEF, 0x9, 0b10111111, 0xFFEEDDCCBBAA9988 )" << std::endl << std::endl;
    std::cout << "Expected messageID     : 0xffee,              Actual messageID     : " << "0x" << std::hex << message->get_messageID()     << std::endl;
    std::cout << "Expected senderID      : 0xfe,                Actual senderID      : " << "0x" << std::hex << unsigned( message->get_senderID()   )      << std::endl;
    std::cout << "Expected receiverID    : 0xef,                Actual receiverID    : " << "0x" << std::hex << unsigned( message->get_receiverID() )  << std::endl;
    std::cout << "Expected payloadLength : 0x9,                 Actual payloadLength : " << "0x" << std::hex << message->get_payloadLength() << std::endl;
    std::cout << "Expected lights        : 1,                   Actual lights        : " << unsigned( message->get_lights() )        << std::endl;
    std::cout << "Expected camera        : 0,                   Actual camera        : " << unsigned( message->get_camera() )        << std::endl;
    std::cout << "Expected action        : 0b00111111 (= 0x3f), Actual action        : " << unsigned( message->get_action() )        << std::endl;
    std::cout << "Expected name          : 0xffeeddccbbaa9988,  Actual name          : " << "0x" << std::hex << message->get_name()          << std::endl << std::endl;

}

// Tests Send() and Receive()
void unit_test_1() {

    std::cout << "\n" << "=================================" << std::endl;
    std::cout <<         "=== Send() and Receive() Test ===" << std::endl;
    std::cout <<         "=================================" << std::endl << std::endl;

    LCAMsg *sender   = new LCAMsg(1, 1, 2, 9, 0b10111111, 0x5555555555555555);
    LCAMsg *receiver = new LCAMsg(0, 0, 0, 9, 0b00000000, 0x0000000000000000);

    std::cout << "Sender Initialization   : LCAMsg(1, 1, 2, 9, 0b10111111, 0x5555555555555555)" << std::endl;
    std::cout << "Receiver Initialization : LCAMsg(0, 0, 0, 9, 0b00000000, 0x0000000000000000) (\"Blank\" Object)" << std::endl;

    std::cout << "Sender messageID     : " << sender->get_messageID() << std::endl;
    std::cout << "Sender senderID      : " << unsigned( sender->get_senderID() ) << std::endl;
    std::cout << "Sender receiverID    : " << unsigned( sender->get_receiverID() ) << std::endl;
    std::cout << "Sender lights        : " << unsigned( sender->get_lights() ) << std::endl;
    std::cout << "Sender camera        : " << unsigned( sender->get_camera() ) << std::endl;
    std::cout << "Sender action        : " << unsigned( sender->get_action() ) << std::endl;
    std::cout << "Sender name          : " << "0x" << std::hex << sender->get_name() << std::endl << std::endl;

    std::cout << "Receiver Pre-Receiving Sender Message" << std::endl << std::endl;
    std::cout << "Receiver messageID     : " << receiver->get_messageID() << std::endl;
    std::cout << "Receiver senderID      : " << unsigned( receiver->get_senderID() ) << std::endl;
    std::cout << "Receiver receiverID    : " << unsigned( receiver->get_receiverID() ) << std::endl;
    std::cout << "Receiver lights        : " << unsigned( receiver->get_lights() ) << std::endl;
    std::cout << "Receiver camera        : " << unsigned( receiver->get_camera() ) << std::endl;
    std::cout << "Receiver action        : " << unsigned( receiver->get_action() ) << std::endl;
    std::cout << "Receiver name          : " << "0x" << std::hex << receiver->get_name() << std::endl << std::endl;

    receiver->Receive( sender->Send() );

    std::cout << "Receiver Post-Receiving Sender Message" << std::endl << std::endl;
    std::cout << "Receiver messageID     : " << receiver->get_messageID() << std::endl;
    std::cout << "Receiver senderID      : " << unsigned( receiver->get_senderID() ) << std::endl;
    std::cout << "Receiver receiverID    : " << unsigned( receiver->get_receiverID() ) << std::endl;
    std::cout << "Receiver lights        : " << unsigned( receiver->get_lights() ) << std::endl;
    std::cout << "Receiver camera        : " << unsigned( receiver->get_camera() ) << std::endl;
    std::cout << "Receiver action        : " << unsigned( receiver->get_action() ) << std::endl;
    std::cout << "Receiver name          : " << "0x" << std::hex << receiver->get_name() << std::endl;

}

void unit_test_2( LCAMsg * chain_link_1, LCAMsg * chain_link_2 ) {
    
    std::cout << "\n" << "================================" << std::endl;
    std::cout <<         "=== 2 Instance Equality Test ===" << std::endl;
    std::cout <<         "================================" << std::endl << std::endl;

    LCAMsg * instance1 = new LCAMsg(*chain_link_1);
    LCAMsg * instance2 = new LCAMsg(*chain_link_2);

    instance2->Receive( instance1->Send() );
    if ( are_LCAMsg_instances_equal(instance1, instance2) == 1 ) {
        // std::cout << "1 to 2 send success" << std::endl;
        std::cout << "2 Instance Equality Test Success" << std::endl;
    }
    else {
        std::cout << "Send() or Receive() failure" << std::endl;
        std::cout << "2 Instance Equality Test Failure" << std::endl;
    }
}

void unit_test_3( LCAMsg * chain_link_1, LCAMsg * chain_link_2, LCAMsg * chain_link_3 ) {
    
    std::cout << "\n" << "================================" << std::endl;
    std::cout <<         "=== 3 Instance Chaining Test ===" << std::endl;
    std::cout <<         "================================" << std::endl << std::endl;

    LCAMsg * instance1 = new LCAMsg(*chain_link_1);
    LCAMsg * instance2 = new LCAMsg(*chain_link_2);
    LCAMsg * instance3 = new LCAMsg(*chain_link_3);

    int success_count = 0;
    
    std::cout << "Instance 1 Send()ing to Instance 2 Receive()" << std::endl;
    instance2->Receive( instance1->Send() );
    if ( are_LCAMsg_instances_equal(instance1, instance2) == 1 ) {
        // std::cout << "1 to 2 send success" << std::endl;
        success_count++;
    }
    else {
        std::cout << "1->2 send failure" << std::endl;
        std::cout << "3 Instance Chaining Test Failure" << std::endl;
    }

    std::cout << "Instance 2 Send()ing to Instance 3 Receive()" << std::endl;
    instance3->Receive( instance2->Send() );
    if ( are_LCAMsg_instances_equal(instance2, instance3) == 1 )  { //&&
    //    (  are_LCAMsg_instances_equal(instance1, instance3) == 1 )) {
        // std::cout << "2 to 3 send success" << std::endl;
        success_count++;
    }
    else {
        std::cout << "2->3 send failure" << std::endl;
        std::cout << "3 Instance Chaining Test Failure" << std::endl;
    }
    
    if (success_count == 2) {
        std::cout << "3 Instance Chaining Test Success" << std::endl;
    } 

}

// I added this "unit test" because it seems like given what seems to be the use case of this system,
// making sure a message's intended recipient is the thing receiving it seems like a good idea.
// I didn't have time to implement it as a member function of UAVProtocol or LCAMsg,
// nor to figure out how to integrate this into other unit tests,
// but I made a basic version to show it crossed my mind.
void unit_test_4( LCAMsg * sender, LCAMsg * receiver ) {

    std::cout << "\n" << "=====================================" << std::endl;
    std::cout <<         "=== Sender/Receiver Matching Test ===" << std::endl;
    std::cout <<         "=====================================" << std::endl << std::endl;

    LCAMsg * new_sender   = new LCAMsg(*sender);
    LCAMsg * new_receiver = new LCAMsg(*receiver);

    uint16_t sender_senderID   = new_sender->get_senderID();
    uint16_t sender_receiverID = new_sender->get_receiverID();

    uint16_t receiver_senderID   = new_receiver->get_senderID();
    uint16_t receiver_receiverID = new_receiver->get_receiverID();

    if ( (sender_senderID == receiver_senderID) && (sender_receiverID == receiver_receiverID) ) {
        std::cout << "Sender and Receiver Match" << std::endl;
    }
    else {
        std::cout << "Sender and Receiver DO NOT Match" << std::endl;
    }
}

// Test whether message fields are in network byte order [aka big-endian]
void unit_test_9( LCAMsg * sender, LCAMsg * receiver ) {

    std::cout << "\n" << "===========================" << std::endl;
    std::cout <<         "======= UNIT TEST 9 =======" << std::endl;
    std::cout <<         "===========================" << std::endl << std::endl;

    LCAMsg * sender_copy   = new LCAMsg(*sender);
    LCAMsg * receiver_copy = new LCAMsg(*receiver);

    std::cout << "Sender messageID     : " << sender->get_messageID() << std::endl;
    std::cout << "Sender senderID      : " << unsigned( sender->get_senderID()   )   << std::endl;
    std::cout << "Sender receiverID    : " << unsigned( sender->get_receiverID() )   << std::endl;
    std::cout << "Sender lights        : " << unsigned( sender->get_lights()     )   << std::endl;
    std::cout << "Sender camera        : " << unsigned( sender->get_camera()     )   << std::endl;
    std::cout << "Sender action        : " << unsigned( sender->get_action()     )   << std::endl;
    std::cout << "Sender name          : " << "0x" << std::hex << sender->get_name() << std::endl << std::endl;

    std::cout << "Receiver Before Receiving Sender Message" << std::endl << std::endl;
    std::cout << "Receiver messageID     : " << receiver->get_messageID() << std::endl;
    std::cout << "Receiver senderID      : " << unsigned( receiver->get_senderID()   )   << std::endl;
    std::cout << "Receiver receiverID    : " << unsigned( receiver->get_receiverID() )   << std::endl;
    std::cout << "Receiver lights        : " << unsigned( receiver->get_lights()     )   << std::endl;
    std::cout << "Receiver camera        : " << unsigned( receiver->get_camera()     )   << std::endl;
    std::cout << "Receiver action        : " << unsigned( receiver->get_action()     )   << std::endl;
    std::cout << "Receiver name          : " << "0x" << std::hex << receiver->get_name() << std::endl << std::endl;

    receiver->Receive( sender->Send() );

    std::cout << "Receiver After Receiving Sender Message" << std::endl << std::endl;
    std::cout << "Receiver messageID     : " << receiver->get_messageID() << std::endl;
    std::cout << "Receiver senderID      : " << unsigned( receiver->get_senderID()   )   << std::endl;
    std::cout << "Receiver receiverID    : " << unsigned( receiver->get_receiverID() )   << std::endl;
    std::cout << "Receiver lights        : " << unsigned( receiver->get_lights()     )   << std::endl;
    std::cout << "Receiver camera        : " << unsigned( receiver->get_camera()     )   << std::endl;
    std::cout << "Receiver action        : " << unsigned( receiver->get_action()     )   << std::endl;
    std::cout << "Receiver name          : " << "0x" << std::hex << receiver->get_name() << std::endl;

}