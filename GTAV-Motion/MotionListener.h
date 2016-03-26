#include "Leap.h"
#include "util.h"

class MotionListener : public Leap::Listener {
public:
	virtual void onConnect(const Leap::Controller&);
	virtual void onFrame(const Leap::Controller&);
};