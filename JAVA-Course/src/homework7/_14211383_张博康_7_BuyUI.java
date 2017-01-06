package homework7;

/**
 * Created by Connor on 2016/12/26.
 */
import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableModel;
import java.awt.*;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.util.Vector;

public class _14211383_张博康_7_BuyUI extends JFrame {
    private _14211383_张博康_7_Controller controller;
    private _14211383_张博康_7_ShoppingCarUI shoppingCart;
    // UI组件
    private JPanel panel1;
    private JTable bookTable;
    private DefaultTableModel bookTableModel;
    private JTextField isbnField;
    private JSpinner numberField;
    private JButton buyButton;
    private JButton concealButton;

    _14211383_张博康_7_BuyUI(_14211383_张博康_7_Controller controller) {
        this.controller = controller;
        this.shoppingCart = new _14211383_张博康_7_ShoppingCarUI();
        controller.getSale().registerObserver(shoppingCart);

        InitUI();
        InitAction();
    }

    private void InitAction() {
        // 点击购买按钮调用controller相关函数
        buyButton.addActionListener(e -> {
            try {
                if ((int)numberField.getValue() == 0)
                    JOptionPane.showMessageDialog(null, "购买本书至少为一");
                else {
                    controller.buyBook(isbnField.getText(), (int) numberField.getValue());
                    JOptionPane.showMessageDialog(null, "添加购物车成功");
                    isbnField.setText("");
                    numberField.setValue(0);
                }
            } catch (Exception except) {
                JOptionPane.showMessageDialog(null, "添加失败，无该书本信息");
            }
        });

        concealButton.addActionListener(e -> {
            setVisible(false);
        });

        // 在关闭窗口时移除原购物车窗口的listen
        addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent e) {
                super.windowClosing(e);
                controller.getSale().removeObserver(shoppingCart);
            }
        });
    }

    private void InitUI() {
        setTitle("购买图书");
        setVisible(true);
        setSize(400, 480);
        setLocationRelativeTo(null);
        setDefaultCloseOperation(HIDE_ON_CLOSE);

        // 设置图形化UI
        panel1 = new JPanel();
        panel1.setLayout(new BorderLayout(0, 0));
        final JPanel panel2 = new JPanel();
        panel2.setLayout(new BorderLayout(0, 0));
        panel1.add(panel2, BorderLayout.CENTER);
        final JPanel panel3 = new JPanel();
        panel3.setLayout(new BorderLayout(0, 0));
        panel2.add(panel3, BorderLayout.CENTER);
        final JScrollPane scrollPane1 = new JScrollPane();
        panel3.add(scrollPane1, BorderLayout.CENTER);

        // 设置书本显示表格
        bookTableModel = new DefaultTableModel();
        bookTable = new JTable(bookTableModel);
        bookTableModel.addColumn("ISBN");
        bookTableModel.addColumn("书名");
        bookTableModel.addColumn("价格");
        bookTableModel.addColumn("书本类型");
        scrollPane1.setViewportView(bookTable);
        // 加载已有书本
        for (Vector<Object> x : controller.getBooks()) {
            bookTableModel.addRow(x);
        }


        final JPanel panel4 = new JPanel();
        panel4.setLayout(new GridBagLayout());
        panel1.add(panel4, BorderLayout.SOUTH);
        final JPanel spacer1 = new JPanel();
        GridBagConstraints gbc;
        gbc = new GridBagConstraints();
        gbc.gridx = 2;
        gbc.gridy = 0;
        gbc.fill = GridBagConstraints.HORIZONTAL;
        panel4.add(spacer1, gbc);
        final JPanel spacer2 = new JPanel();
        gbc = new GridBagConstraints();
        gbc.gridx = 1;
        gbc.gridy = 4;
        gbc.fill = GridBagConstraints.VERTICAL;
        panel4.add(spacer2, gbc);
        isbnField = new JTextField();
        gbc = new GridBagConstraints();
        gbc.gridx = 3;
        gbc.gridy = 1;
        gbc.weightx = 3.0;
        gbc.anchor = GridBagConstraints.WEST;
        gbc.fill = GridBagConstraints.HORIZONTAL;
        panel4.add(isbnField, gbc);
        final JLabel label1 = new JLabel();
        label1.setText("ISBN编号");
        gbc = new GridBagConstraints();
        gbc.gridx = 1;
        gbc.gridy = 1;
        gbc.weightx = 1.0;
        gbc.anchor = GridBagConstraints.EAST;
        panel4.add(label1, gbc);
        final JPanel spacer3 = new JPanel();
        gbc = new GridBagConstraints();
        gbc.gridx = 0;
        gbc.gridy = 1;
        gbc.weightx = 7.0;
        gbc.fill = GridBagConstraints.HORIZONTAL;
        panel4.add(spacer3, gbc);
        final JPanel spacer4 = new JPanel();
        gbc = new GridBagConstraints();
        gbc.gridx = 4;
        gbc.gridy = 1;
        gbc.weightx = 2.0;
        gbc.fill = GridBagConstraints.HORIZONTAL;
        panel4.add(spacer4, gbc);
        final JLabel label2 = new JLabel();
        label2.setText("数量（本）");
        gbc = new GridBagConstraints();
        gbc.gridx = 1;
        gbc.gridy = 3;
        gbc.anchor = GridBagConstraints.EAST;
        panel4.add(label2, gbc);
        final JPanel spacer5 = new JPanel();
        gbc = new GridBagConstraints();
        gbc.gridx = 2;
        gbc.gridy = 2;
        gbc.fill = GridBagConstraints.VERTICAL;
        panel4.add(spacer5, gbc);
        numberField = new JSpinner();
        gbc = new GridBagConstraints();
        gbc.gridx = 3;
        gbc.gridy = 3;
        gbc.weightx = 3.0;
        gbc.anchor = GridBagConstraints.WEST;
        gbc.fill = GridBagConstraints.HORIZONTAL;
        panel4.add(numberField, gbc);
        buyButton = new JButton();
        buyButton.setText("购买");
        gbc = new GridBagConstraints();
        gbc.gridx = 1;
        gbc.gridy = 5;
        gbc.weightx = 3.0;
        gbc.fill = GridBagConstraints.HORIZONTAL;
        panel4.add(buyButton, gbc);
        concealButton = new JButton();
        concealButton.setText("取消");
        gbc = new GridBagConstraints();
        gbc.gridx = 3;
        gbc.gridy = 5;
        gbc.weightx = 3.0;
        gbc.fill = GridBagConstraints.HORIZONTAL;
        panel4.add(concealButton, gbc);
        final JPanel spacer6 = new JPanel();
        gbc = new GridBagConstraints();
        gbc.gridx = 2;
        gbc.gridy = 5;
        gbc.weightx = 1.0;
        gbc.fill = GridBagConstraints.HORIZONTAL;
        panel4.add(spacer6, gbc);
        final JPanel spacer7 = new JPanel();
        gbc = new GridBagConstraints();
        gbc.gridx = 2;
        gbc.gridy = 6;
        gbc.fill = GridBagConstraints.VERTICAL;
        gbc.insets = new Insets(15, 0, 0, 0);
        panel4.add(spacer7, gbc);
        final JPanel spacer8 = new JPanel();
        gbc = new GridBagConstraints();
        gbc.gridx = 3;
        gbc.gridy = 0;
        gbc.fill = GridBagConstraints.VERTICAL;
        gbc.insets = new Insets(15, 0, 0, 0);
        panel4.add(spacer8, gbc);

        add(panel1);
    }
}
