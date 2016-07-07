/**
 * Created by HarshaGoli on 3/25/16.
 */

import com.leapmotion.leap.*;
import javax.xml.bind.Marshaller;
import java.io.IOException;
class LeapListener extends Listener {
    public void onInit(Controller controller) {
        System.out.println("Initialized");
    }

    public void onConnect(Controller controller) {
        System.out.println("Connected to Motion Sensor");
        controller.enableGesture(Gesture.Type.TYPE_SWIPE);
        controller.enableGesture(Gesture.Type.TYPE_CIRCLE);
        controller.enableGesture(Gesture.Type.TYPE_KEY_TAP);
        controller.enableGesture(Gesture.Type.TYPE_SCREEN_TAP);
    }

    public void onDisconnect(Controller controller) {
        System.out.println("Sensor Disconnect");
    }

    public void onExit(Controller controller) {
        System.out.println("Exited");
    }

    public void onFrame(Controller controller) {
        //GUN
        Frame frame = controller.frame();
        Finger prevFinger = new Finger();
        for(Finger finger : frame.fingers()){
            if("TYPE_INDEX".equals(finger.type().name())){
                if((finger.tipPosition().getY()-prevFinger.tipPosition().getY()) > 70) {
                    System.out.println("SHOOT");
                }
            }
            prevFinger = finger;
        }
    }
}

public class GunMotion {
    public static void main(String[] args) {
        LeapListener listener = new LeapListener();
        Controller controller = new Controller();
        controller.addListener(listener);
        // Keep this process running until Enter is pressed
        System.out.println("Press Enter to quit...");
        try {
            System.in.read();
        } catch (IOException e) {
            e.printStackTrace();
        }
        controller.removeListener(listener);
    }
}
