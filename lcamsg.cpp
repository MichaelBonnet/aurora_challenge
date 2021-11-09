#include "lcamsg.h"
#include "uavprotocol.h"

#define LIGHTS_FLAG 0x80 // 1000 0000
#define CAMERA_FLAG 0x40 // 0100 0000
#define ACTION_FLAG 0x3F // 0011 1111

LCAMsg::LCAMsg() {

}

unsigned char LCAMsg::get_lights() {
    return lights_camera_action & LIGHTS_FLAG;
}

unsigned char LCAMsg::get_camera() {
    return lights_camera_action & CAMERA_FLAG;
}

unsigned char LCAMsg::get_action() {
    return lights_camera_action & ACTION_FLAG;
}

std::string LCAMsg::Send() {

}

void LCAMsg::Receive() {

}
