#include "script.h"

#include <string>
#include <ctime>

#pragma warning(disable : 4244 4305) // double <-> float conversions

Ped player;
Vehicle playerVehicle;
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

void main() {	
	while (true) {
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
		// TODO: implement motion detection here
		// TODO: implement buttons here
		// TODO: figure out which natives control acceleration/braking
		// If something has affected the steerBias during this iteration...
		if (initialSteerBias != steerBias) {
			// ...set the steer bias of the vehicle the current player ped is currently in.
			VEHICLE::SET_VEHICLE_STEER_BIAS(
				PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0),
				steerBias
			);
		}
		WAIT(0);
	}
}

void ScriptMain() {
	srand(GetTickCount());
	main();
}
