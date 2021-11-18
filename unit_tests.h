// ================ //
// === INCLUDES === //
// ================ //

#include <string>
#include <iomanip>
#include <sstream>
#include <stdio.h>
#include <bitset>
#include "lcamsg.h"

// ====================== //
// === THINGS TO TEST === //
// ====================== //

// A) Test whether message fields are in network byte order [aka big-endian]
// B) Test whether the code is agnostic to endianness
//      I only have one machine. 
//      But, this is sort of forced and therefore covered by
//      by the ntohx()/htonx() conversions.
// C) Test that Derived Class "Inherits the base class in Problem #1"
//      Sort of self-evident?
// D) Test that base and dervied class initialization behaves as expected
// E) Base Class "Initialization of common fields"
// F) Base Class "Access methods for each and every field"
// G) Derived Class "Initialization of payload fields"
// H) Derived Class "Access methods for each and every field"
// I) Test that the Send() function returns a string containing the message to be sent
// J) Test that the Receive() function that accepts a string containing the message received,
//    and populates the values of the payload fields.


// ==================================== //
// === HELPER FUNCTION DECLARATIONS === //
// ==================================== //

bool are_LCAMsg_instances_equal(LCAMsg * instance1, LCAMsg * instance2);

// ============================== //
// === UNIT TEST DECLARATIONS === //
// ============================== //

// Tests D, E, F, G, H
void unit_test_0();

// Tests I, J
void unit_test_1();

// 
void unit_test_2( LCAMsg * chain_link_1, LCAMsg * chain_link_2);

// 
void unit_test_3( LCAMsg * chain_link_1, LCAMsg * chain_link_2, LCAMsg * chain_link_3);

// 
void unit_test_4( LCAMsg * sender, LCAMsg * receiver );

// If I had had the time,
// I would have implemented, likely within the classes rather than in my unit tests,
// checking for bad input, like unsigned integers or values that overflow the assigned bits.
// void check_bad_parameters();

// 
void unit_test_9(LCAMsg * sender, LCAMsg * receiver);