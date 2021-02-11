import javax.swing.*;

public class NoLockCounterThread implements Runnable {
    final JSlider slider;
    boolean isIncrement;
    CancellationToken ct;

    int step = 5;

    public NoLockCounterThread(JSlider slider, boolean increment, CancellationToken ct) {
        this.slider = slider;
        this.isIncrement = increment;
        this.ct = ct;
    }

    public void run() {
        while (ct.IsAlive()) {
            if (isIncrement){
                int value = slider.getValue();
                if(value < 90)
                    slider.setValue(value + step);
            }
            else {
                int value = slider.getValue();
                if(value > 10)
                    slider.setValue(value - step);
            }
            System.out.println("Slider value is " + slider.getValue());
            try {
                Thread.sleep(100);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}