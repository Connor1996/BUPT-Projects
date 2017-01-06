package homework7;

/**
 * Created by Connor on 2016/12/26.
 */
import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.util.Vector;

public class _14211383_张博康_7_ShoppingCarUI  extends JFrame implements _14211383_张博康_7_Observer{
    private JPanel panel1;
    private JTable table1;
    private JLabel totalLabel;

    public _14211383_张博康_7_ShoppingCarUI() {
        InitUI();
    }
    
    public void update(_14211383_张博康_7_Sale sale) {
        DefaultTableModel shoppingTableModel = new DefaultTableModel();
        table1.setModel(shoppingTableModel);
        shoppingTableModel.addColumn("书名");
        shoppingTableModel.addColumn("单价");
        shoppingTableModel.addColumn("数量");
        setVisible(true);
        // 设置购买条目的显示
        for (Vector<Object> row : sale.getTable()) {
            shoppingTableModel.addRow(row);
        }
        totalLabel.setText("总价： " + sale.getTotal() + " 元");
    }

    public void InitUI() {
        //setVisible(true);
        setTitle("购物车");
        setSize(400, 480);
        setLocation(200, 200);
        setDefaultCloseOperation(HIDE_ON_CLOSE);

        panel1 = new JPanel();
        panel1.setLayout(new BorderLayout(0, 0));
        final JPanel panel2 = new JPanel();
        panel2.setLayout(new GridBagLayout());
        panel1.add(panel2, BorderLayout.CENTER);
        totalLabel = new JLabel();
        totalLabel.setText("总价： 0 元");
        GridBagConstraints gbc;
        gbc = new GridBagConstraints();
        gbc.gridx = 3;
        gbc.gridy = 1;
        gbc.anchor = GridBagConstraints.WEST;
        panel2.add(totalLabel, gbc);
        final JPanel spacer1 = new JPanel();
        gbc = new GridBagConstraints();
        gbc.gridx = 4;
        gbc.gridy = 1;
        gbc.weightx = 2.0;
        gbc.fill = GridBagConstraints.HORIZONTAL;
        panel2.add(spacer1, gbc);
        final JPanel spacer2 = new JPanel();
        gbc = new GridBagConstraints();
        gbc.gridx = 2;
        gbc.gridy = 1;
        gbc.weightx = 5.0;
        gbc.fill = GridBagConstraints.HORIZONTAL;
        panel2.add(spacer2, gbc);
        final JPanel spacer3 = new JPanel();
        gbc = new GridBagConstraints();
        gbc.gridx = 3;
        gbc.gridy = 2;
        gbc.fill = GridBagConstraints.VERTICAL;
        panel2.add(spacer3, gbc);
        final JPanel spacer4 = new JPanel();
        gbc = new GridBagConstraints();
        gbc.gridx = 3;
        gbc.gridy = 0;
        gbc.fill = GridBagConstraints.VERTICAL;
        panel2.add(spacer4, gbc);
        final JScrollPane scrollPane1 = new JScrollPane();
        scrollPane1.setAlignmentX(0.0f);
        scrollPane1.setAlignmentY(0.0f);
        scrollPane1.setOpaque(true);
        scrollPane1.setPreferredSize(new Dimension(453, 350));
        panel1.add(scrollPane1, BorderLayout.NORTH);

        // 设置购买项目显示表格
        DefaultTableModel shoppingTableModel = new DefaultTableModel();
        table1 = new JTable(shoppingTableModel);
        shoppingTableModel.addColumn("书名");
        shoppingTableModel.addColumn("数量");

        scrollPane1.setViewportView(table1);

        add(panel1);
    }
}
