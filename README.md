# aurora_challenge

Files for the C++ programming challenge sent to me by [Aurora Flight Sciences](https://www.aurora.aero/) during my application process.

**Resolved Issues**

- Fixed issue where `stoi( )` would go out of range on super large `to_string( )`-ified bit streams ... by just no longer doing it with a string. I believe I misread the project spec - while the `Send( )` and `Receive( )` specs in parts 1 and 2 say "string", I believe they mean "string of bits", as the *instructions* at the start of the spec document state "All messages are sent and received as a stream of binary data". So, by just doing it with a big `uint` rather than an `std::string`, I avoided the `stoi( )` issue entirely.

**Current Issues**

- **Bit Extraction Error Causing Segfaulting** - Need to resolve weird extraction issue causing large values, especially in `LCAMsg.get_payloadLength( )`, which gets an extremely large value causing a segfault in `LCAMsg.Send( )` calls on `LCAMsg.Receive( )`-created instances (in `unit_test_1( )`, where the payload is of max size), as `LCAMsg.get_payloadLength( )` is used as a continuation condition when packing the pointer for the payload
  - Basically, I'm pretty certain that I'm unpacking the bits somehow improperly leading to extremely large/nonexistent values, despite the `LCAMsg.Send( )` call results being identical.
- **Wrapping Bit Packing with Host<->Network Byte Order Conversions** - Need to wrap everything in `hton`/`ntoh` for endianness agnosticism - shouldn't be too hard but I want to resolve the other issues first.
  - Potential issue is that while there exists `htons`/`ntohs` for 16-bit, `htonl`/`ntohl` for 32-bit, and `htonll`/`ntohll` for 64-bit, I need an 8-bit version for my `uint8_t` class fields like `senderID` and `receiverID`.
