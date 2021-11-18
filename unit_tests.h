#include <string>
#include <iomanip>
#include <sstream>
#include <stdio.h>
#include <bitset>

// Demonstrating that base and dervied class initialization behaves as expected

// Demonstrating that:
// (1) Base and derived class constructors initialize as expected
//     (derived constructor calls base constructor)
// (2) Access methods work as expected
//     (non-payload access methods are base class methods)
// (3) All message fields are in network byte order
void unit_test_0();

// Test whether message fields are in network byte order [aka big-endian]
void unit_test_1();

// Test whether the code is agnostic to endianness
// I only have one machine. 
// But, this is sort of forced and therefore covered by
// by the ntohx()/htonx() conversions.

// Base Class "Initialization of common fields"
void unit_test_2();

// Base Class "Access methods for every field"
void unit_test_3();

// Derived Class "Inherits the base class in Problem #1"
// Sort of self-evident.

// Base Class "Access methods for every field"
void unit_test_4();

// A Send function that accepts a string containing the message received,
// and populates the values of the payload fields.
void unit_test_5();

// 
void unit_test_6();

// 
void unit_test_7();

// 
// void unit_test_7();

// 
// void unit_test_8();

// 
// void unit_test_9();