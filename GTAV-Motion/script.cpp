#include "script.h"
#include "MotionListener.h"

#include <iostream>
#include <string>
#include <ctime>

void loop() {
	// GTAV native functions!: http://www.dev-c.com/nativedb/func/info/42a8ec77d5150cbe
	/* at the same time, we need to poll Dylan's controller to see if accel or
	brakes should be applied in a similar fashion. (accelerate(), brake()) */
	// TODO: implement buttons here and call accelerate/brake
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
