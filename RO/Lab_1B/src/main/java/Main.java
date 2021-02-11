import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class Main {

    static int leftPriority = 1;
    static int rightPriority = 1;
    static JLabel leftLabel;
    static JLabel rightLabel;

    static Thread incThread;
    static Thread decThread;

    static CancellationToken incToken;
    static CancellationToken decToken;

    public static void main(String[] args) {
        JFrame frame = new JFrame();//creating instance of JFrame

        JSlider slider = createSlider(frame);
        JButton[] buttons = createButtons(frame, slider);
        initialiseFrame(frame);
    }

    private static JButton[] createButtons(JFrame frame, JSlider slider){
        JButton[] buttons = new JButton[4];
        buttons[0] = new JButton("ПУСК 1");
        buttons[1] = new JButton("СТОП 1");
        buttons[2] = new JButton("ПУСК 2");
        buttons[3] = new JButton("СТОП 2");

        buttons[0].setBounds(100,200,100, 40);
        buttons[1].setBounds(100,250,100, 40);
        buttons[2].setBounds(400,200,100, 40);
        buttons[3].setBounds(400,250,100, 40);

        buttons[0].addActionListener(ae -> { // possible new thread
            leftPriority = 9;
            buttons[2].setEnabled(false);
            buttons[3].setEnabled(false);
            leftLabel.setText(String.valueOf(leftPriority));
            incThread = initialiseThreads(slider, true);
            incThread.run();

        });
        buttons[1].addActionListener(ae -> {
            if (leftPriority > 0) {
                buttons[2].setEnabled(true);
                buttons[3].setEnabled(true);
                leftPriority = 0;
                leftLabel.setText(String.valueOf(leftPriority));
                incToken.cancel();
            }
        });
        buttons[2].addActionListener(ae -> {
            rightPriority = 9;
            buttons[0].setEnabled(false);
            buttons[1].setEnabled(false);
            rightLabel.setText(String.valueOf(rightPriority));
            decThread = initialiseThreads(slider, false);
            decThread.run();
        });
        buttons[3].addActionListener(ae -> {
            if (rightPriority > 0) {
                rightPriority = 0;
                buttons[0].setEnabled(true);
                buttons[1].setEnabled(true);
                rightLabel.setText(String.valueOf(rightPriority));
                decToken.cancel();
            }
        });

        for (var button : buttons){
            frame.add(button);
        }
        return buttons;
    }

    private static JSlider createSlider(JFrame frame) {
        var slider = new JSlider(JSlider.VERTICAL, 0, 100, 50);
        slider.setBounds(200, 100, 200, 400);
        frame.add(slider);
        return slider;
    }

    private static void createLabels(JFrame frame) {
        leftLabel = new JLabel(String.valueOf(leftPriority));
        rightLabel = new JLabel(String.valueOf(rightPriority));

        leftLabel.setBounds(100, 300, 100, 50);
        rightLabel.setBounds(400, 300, 100, 50);
        leftLabel.setBackground(Color.GREEN);
        rightLabel.setBackground(Color.GREEN);

        leftLabel.setVerticalAlignment(JLabel.CENTER);
        leftLabel.setHorizontalAlignment(JLabel.CENTER);

        rightLabel.setVerticalAlignment(JLabel.CENTER);
        rightLabel.setHorizontalAlignment(JLabel.CENTER);

        frame.add(leftLabel);
        frame.add(rightLabel);
    }

    private static void initialiseFrame(JFrame frame){
        createLabels(frame);
        frame.setSize(600,600);
        frame.setLayout(null);//using no layout managers
        frame.setVisible(true);//making the frame visible
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }

    private static Thread initialiseThreads(JSlider slider, boolean increment) {
        CancellationToken ct = new CancellationToken();
        incThread = new Thread(new NoLockCounterThread(slider, increment, ct));
        incThread.setPriority(1);
        incThread.setDaemon(true);
        if(increment)
            incToken = ct;
        else
            decToken = ct;
        return incThread;
    }
}