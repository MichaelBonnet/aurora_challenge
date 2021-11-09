#include "lcamsg.h"

// TO DO
// Make LCAMsg() and UAVProtocol() jive
// Write Send
// Write Receive

#define LIGHTS_FLAG 0x80 // 1000 0000
#define CAMERA_FLAG 0x40 // 0100 0000
#define ACTION_FLAG 0x3F // 0011 1111

// Constructor
LCAMsg::LCAMsg( uint8_t lights_camera_action, uint64_t name ) {
    lights_camera_action = lights_camera_action;
    name = name;
}

// Copy Constructor
LCAMsg::LCAMsg( const LCAMsg &obj ) {
    lights_camera_action = obj.lights_camera_action;
    name = obj.name;
}

LCAMsg::~LCAMsg() { }

uint8_t LCAMsg::get_lights() const {
    return lights_camera_action & LIGHTS_FLAG;
}

uint8_t LCAMsg::get_camera() const {
    return lights_camera_action & CAMERA_FLAG;
}

uint8_t LCAMsg::get_action() const {
    return lights_camera_action & ACTION_FLAG;
}

uint64_t LCAMsg::get_name()  const {
    return name;
}

std::string LCAMsg::Send() const {

}

void LCAMsg::Receive(const std::string message) const {

}
