#include "script.h"
#include "Leap.h"

#include <string>
#include <ctime>

#pragma warning(disable : 4244 4305) // double <-> float conversions

float steerBias = 0.0;

void update_steer_bias() {
	// TODO: retrieve latest steer bias from game and update steerBias
	return;
}

void turn_right() {
	update_steer_bias();
	steerBias = steerBias + .05;
	steerBias = steerBias > 1.0 ? 1.0 : steerBias;
}

void turn_left() {
	update_steer_bias();
	steerBias = steerBias - .05;
	steerBias = steerBias < -1.0 ? -1.0 : steerBias;
}

void accelerate() {
	// TODO: implement
	return;
}

void brake() {
	// TODO: implement
	return;
}

void loop() {
	float initialSteerBias = steerBias;
	/*
	GTAV native functions!: http://www.dev-c.com/nativedb/func/info/42a8ec77d5150cbe
	*/
	/* somehow Harsha's code needs to end up calling turn_right or turn_left.
	in this loop we should poll frames from the motion detector and see if
	a turn is necessary. turn_right/_left will update steerBias which is
	then sent to the game as below. */
	/* at the same time, we need to poll Dylan's controller to see if accel or
	brakes should be applied in a similar fashion. (accelerate(), brake()) */
	// TODO: implement motion detection here and call turn_right/_left
	// TODO: implement buttons here and call accelerate/brake
	/* How to tell if someone is turning? Could use Hand.grabStrength() to see
	 * if player is gripping the wheel and could track translation of the hand
	 * between frames to see if significant movement has been made. */
	// If something has affected the steerBias during this iteration...
	if (initialSteerBias != steerBias) {
		// ...set the steer bias of the vehicle the current player ped is currently in.
		VEHICLE::SET_VEHICLE_STEER_BIAS(
			PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0),
			steerBias
			);
	}
}

void main() {	
	while (true) {
		WAIT(0);
		// check to make sure player exists and it makes sense for them to be driving
		if (!ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID()) ||
			!PLAYER::IS_PLAYER_CONTROL_ON(PLAYER::PLAYER_ID()) ||
			ENTITY::IS_ENTITY_DEAD(PLAYER::PLAYER_PED_ID()) ||
			PLAYER::IS_PLAYER_BEING_ARRESTED(PLAYER::PLAYER_ID(), TRUE))
			continue;
		loop();
	}
}

void ScriptMain() {
	srand(GetTickCount());
	main();
}
