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
        //AIRPLANE

        Frame frame = controller.frame();
        for (Hand hands : frame.hands()) {
            String handType = hands.isLeft() ? "Left Hand" : "Right Hand";


            double temp = (double) hands.palmPosition().getX();
            double temp2 = (double) hands.palmPosition().getZ();

            if (temp < -50.00) {
                System.out.println("Roll Left!!!");
            } else if (temp > 50.00) {
                System.out.println("Roll Right!!!");
            }
            if(temp2 < -70.00){
                System.out.println("Pitch Down");
            }
            if(temp2> 70.00){
                System.out.println("Pitch Up");
            }
        }
    }
}


public class AirplaneControls {
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

