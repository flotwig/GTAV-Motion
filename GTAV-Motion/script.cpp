#include "script.h"
#include "Leap.h"
#include <iostream>
#include <string>
#include <ctime>

#pragma warning(disable : 4244 4305) // double <-> float conversions

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

class MotionListener : public Leap::Listener {
public:
	virtual void onConnect(const Leap::Controller&);
	virtual void onFrame(const Leap::Controller&);
};

void MotionListener::onConnect(const Leap::Controller& controller) {
	std::cout << "Connected" << std::endl;
}

void MotionListener::onFrame(const Leap::Controller& controller) {
	//All the frame shit goes on here
	const Leap::Frame frame = controller.frame();
	for (auto &hands : frame.hands()){
		float temp = hands.palmPosition().x;
		if (temp < -50.00) {
			turn_left();
			std::cout << "Turning Left" << std::endl;
		}
		else if (temp > 50.00) {
			turn_right();
			std::cout << "Turning Right" << std::endl;

		}

	}
}

void loop() {
	// GTAV native functions!: http://www.dev-c.com/nativedb/func/info/42a8ec77d5150cbe
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
	// Vehicle playerVehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(),0);
}

void main() {

	MotionListener listener;
	Leap::Controller controller;
	controller.addListener(listener);
	while (true) {
		WAIT(0);
		loop();
	}
	controller.removeListener(listener);
}

void ScriptMain() {
	srand(GetTickCount());
	main();
}
