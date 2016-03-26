#include "MotionListener.h"

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