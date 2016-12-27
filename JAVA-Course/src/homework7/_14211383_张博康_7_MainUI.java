package homework7;

/**
 * Created by Connor on 2016/12/26.
 */
import javax.swing.*;
import java.awt.*;

public class _14211383_张博康_7_MainUI extends JFrame {
    public _14211383_张博康_7_Controller controller;

    public _14211383_张博康_7_MainUI() {
        controller = new _14211383_张博康_7_Controller();
        InitUI();
    }

    private void InitUI() {
        setLayout(new FlowLayout());
        Box baseBox = Box.createVerticalBox();
        // 先加入一个不可见的 Strut，从而使顶部留出一定的空间
        baseBox.add(Box.createVerticalStrut(40));

        // 增加书本窗口按钮
        JButton addBook = new JButton("增加书本");
        addBook.setMinimumSize(new Dimension(200, 80));
        addBook.addActionListener((e) -> {
            new _14211383_张博康_7_AddBookUI(controller);
        });
        baseBox.add(addBook);
        baseBox.add(Box.createVerticalStrut(40));

        // 策略维护窗口按钮
        JButton strategy = new JButton("策略维护");
        strategy.setMinimumSize(new Dimension(200, 80));
        strategy.addActionListener((e) -> {
            new _14211383_张博康_7_StrategiesUI(controller);
        });
        baseBox.add(strategy);
        baseBox.add(Box.createVerticalStrut(40));

        // 购买书本窗口按钮
        JButton buyBook = new JButton("购买书本");
        buyBook.setMinimumSize(new Dimension(200, 80));
        buyBook.addActionListener((e) -> {
            new _14211383_张博康_7_BuyUI(controller);
        });
        baseBox.add(buyBook);
        baseBox.add(Box.createVerticalStrut(40));

        add(baseBox);
    }

    public static void run (final JFrame f, final int width, final int height) {
        SwingUtilities.invokeLater(() -> {
            f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            f.setSize(width, height);
            f.setVisible(true);
        });
    }

    public static void main(String[] args) {
        run(new _14211383_张博康_7_MainUI(), 400, 280);
    }
}
