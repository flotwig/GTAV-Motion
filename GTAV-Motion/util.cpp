#include "script.h"

BOOL send_control(int control) {
	return CONTROLS::_SET_CONTROL_NORMAL(0, control, 1.0);
}

BOOL player_can_control_car() {
	return !(!ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID()) ||
		!PLAYER::IS_PLAYER_CONTROL_ON(PLAYER::PLAYER_ID()) ||
		ENTITY::IS_ENTITY_DEAD(PLAYER::PLAYER_PED_ID()) ||
		PLAYER::IS_PLAYER_BEING_ARRESTED(PLAYER::PLAYER_ID(), TRUE));
}

void turn_right() {
	if (!player_can_control_car()) return;
	send_control(64); // VehicleMoveRightOnly
}

void turn_left() {
	if (!player_can_control_car()) return;
	send_control(63); // VehicleMoveLeftOnly
}

void accelerate() {
	if (!player_can_control_car()) return;
	send_control(71); // VehicleAccelerate
}

void brake() {
	if (!player_can_control_car()) return;
	send_control(72); // VehicleBrake
}