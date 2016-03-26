#include "script.h"
#include "keyboard.h"

#include <string>
#include <ctime>

#pragma warning(disable : 4244 4305) // double <-> float conversions

Ped player;
Vehicle playerVehicle;
float steerBias = 0.0;

void main() {	
	while (true) {
		/**
			Call functions in this script which steer the vehicle more left or
			more right. Using this primitive:
			http://www.dev-c.com/nativedb/func/info/42a8ec77d5150cbe
			VEHICLE::SET_VEHICLE_STEER_BIAS(Vehicle vehicle, float value)
			value is between -1.0 and 1.0, with -1.0 being full left and 1.0 
			being full right.
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
		VEHICLE::SET_VEHICLE_STEER_BIAS(playerVehicle, steerBias);
		WAIT(0);
	}
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

void update_steer_bias() {
	// TODO: retrieve latest steer bias from game and update steerBias
	return;
}

void ScriptMain() {
	player = PLAYER::PLAYER_PED_ID();
	playerVehicle = PED::GET_VEHICLE_PED_IS_IN(player, 0); // 0 = CurrentVehicle, 1 = LastVehicle
	// note: after looking at it for long enough, "player" ceases to look like a word
	srand(GetTickCount());
	main();
}
