package homework7;

/**
 * Created by Connor on 2016/12/26.
 */
import javax.swing.*;
import java.awt.*;

public class _14211383_张博康_7_AddBookUI extends JFrame {
    private _14211383_张博康_7_Controller controller;

    public _14211383_张博康_7_AddBookUI(_14211383_张博康_7_Controller controller) {
        this.controller = controller;

        setTitle("增加书本");
        setSize(340, 250);
        setVisible(true);
        setLocationRelativeTo(null);
        setLayout(new FlowLayout());
        Box baseBox = Box.createVerticalBox();
        // 先加入一个不可见的 Strut，从而使顶部留出一定的空间
        baseBox.add(Box.createVerticalStrut(10));


        // ISBN
        Box isbnBox = Box.createHorizontalBox();
        isbnBox.add(new JLabel("ISBN"));
        isbnBox.add(Box.createHorizontalStrut(20));
        JTextField isbnField = new JTextField(10);
        isbnBox.add(isbnField);
        baseBox.add(isbnBox);
        baseBox.add(Box.createVerticalStrut(5));

        // 书名
        Box titleBox = Box.createHorizontalBox();
        titleBox.add(new JLabel("书名"));
        titleBox.add(Box.createHorizontalStrut(20));
        JTextField titleField = new JTextField(10);
        titleBox.add(titleField);
        baseBox.add(titleBox);
        baseBox.add(Box.createVerticalStrut(5));

        // 价格
        Box priceBox = Box.createHorizontalBox();
        priceBox.add(new JLabel("价格"));
        priceBox.add(Box.createHorizontalStrut(20));
        JTextField priceField = new JTextField(10);
        priceBox.add(priceField);
        baseBox.add(priceBox);
        baseBox.add(Box.createVerticalStrut(5));

        // 类型
        Box typeBox = Box.createHorizontalBox();
        typeBox.add(new JLabel("类型"));
        typeBox.add(Box.createHorizontalStrut(20));
        JComboBox typeField = new JComboBox(new String[]{
                "非教材类计算机图书",
                "教材类图书",
                "连环画类图书",
                "养生类图书",
                "其他"
        });
        typeBox.add(typeField);
        baseBox.add(typeBox);
        baseBox.add(Box.createVerticalStrut(15));

        // 添加和取消按钮
        Box buttonBox = Box.createHorizontalBox();
        JButton addEmployee = new JButton("添加");
        addEmployee.addActionListener((e) -> {
            try {
                controller.addBook(
                        Double.parseDouble(priceField.getText()),
                        titleField.getText(),
                        typeField.getSelectedIndex(),
                        isbnField.getText()
                );
                dispose();
            } catch (Exception except) {
                JOptionPane.showMessageDialog(null, "输入信息不符合格式");
            }
        });
        JButton close = new JButton("取消");
        close.addActionListener((e) -> {
            dispose();
        });

        buttonBox.add(addEmployee);
        buttonBox.add(Box.createHorizontalStrut(40));
        buttonBox.add(close);
        baseBox.add(buttonBox);

        add(baseBox);
    }
}
