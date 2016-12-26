package homework4;

/**
 * Created by Connor on 2016/12/26.
 */

import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;

public class _14211383_张博康_4_Swing {
    public static void run (final JFrame f, final int width, final int height) {
        SwingUtilities.invokeLater(() -> {
            f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            f.setSize(width, height);
            f.setVisible(true);
        });
    }

    public static void main(String[] args) {
        run(new SimpleMenus(), 640, 480);
    }

    public static double getAverage() {
        double total = 0;
        if (employees.size() == 0)
            return 0;

        for (Object employee : employees) {
            total += ((_14211383_张博康_4_Employee)employee).earning();
        }

        return total / employees.size();
    }

    public static void addEmployee(_14211383_张博康_4_Employee employee) {
        employees.add(employee);
    }

    private static ArrayList employees = new ArrayList<_14211383_张博康_4_Employee>();
}

//EmployeeInfoInput（一级菜单）
//    --CommisionEmployee（二级菜单）
//    --BasePlusCommisionEmployee
//
//Search（一级菜单）
//    --AverageEarningSearch（查询全部员工的平均工资）
class SimpleMenus extends JFrame {
    public SimpleMenus() {
        // 设置EmployeeInfoInput菜单
        JMenu menuInput = new JMenu("EmployeeInfoInput");
        // 添加CommisionEmployee子对话框
        JMenuItem item1 = new JMenuItem("CommisionEmployee");
        item1.addActionListener((e) -> {
            new CommisionEmployeeInput().setVisible(true);
        });
        menuInput.add(item1);

        // 添加BasePlusCommisionEmployee子对话框
        JMenuItem item2 = new JMenuItem("BasePlusCommisionEmployee");
        item2.addActionListener((e) -> {
            new BasePlusCommisionEmployeeInput().setVisible(true);
        });
        menuInput.add(item2);

        // 设置Search菜单
        JMenu menuSearch = new JMenu("Search");
        JMenuItem item = new JMenuItem("AverageEarningSearch");
        item.addActionListener((e) -> {
            new AverageEarningSearch().setVisible(true);
        });
        menuSearch.add(item);

        // 添加菜单
        JMenuBar md = new JMenuBar();
        md.add(menuInput);
        md.add(menuSearch);
        setJMenuBar(md);
    }
}

class BasePlusCommisionEmployeeInput extends JDialog {
    public BasePlusCommisionEmployeeInput() {
        setSize(340, 270);
        setLayout(new FlowLayout());
        Box baseBox = Box.createVerticalBox();
        // 先加入一个不可见的 Strut，从而使顶部留出一定的空间
        baseBox.add(Box.createVerticalStrut(10));

        // 姓
        Box lastNameBox = Box.createHorizontalBox();
        lastNameBox.add(new JLabel("LastName"));
        lastNameBox.add(Box.createHorizontalStrut(20));
        JTextField lastNameField = new JTextField(10);
        lastNameBox.add(lastNameField);
        baseBox.add(lastNameBox);
        baseBox.add(Box.createVerticalStrut(5));

        // 名
        Box firstNameBox = Box.createHorizontalBox();
        firstNameBox.add(new JLabel("FirstName"));
        firstNameBox.add(Box.createHorizontalStrut(20));
        JTextField firstNameField = new JTextField(10);
        firstNameBox.add(firstNameField);
        baseBox.add(firstNameBox);
        baseBox.add(Box.createVerticalStrut(5));

        // 社保号
        Box socialSecurityNumberBox = Box.createHorizontalBox();
        socialSecurityNumberBox.add(new JLabel("SSNumber"));
        socialSecurityNumberBox.add(Box.createHorizontalStrut(20));
        JTextField socialSecurityNumberField = new JTextField(10);
        socialSecurityNumberBox.add(socialSecurityNumberField);
        baseBox.add(socialSecurityNumberBox);
        baseBox.add(Box.createVerticalStrut(5));

        // 销售额
        Box grossSalesBox = Box.createHorizontalBox();
        grossSalesBox.add(new JLabel("GrossSales"));
        grossSalesBox.add(Box.createHorizontalStrut(20));
        JTextField grossSalesField = new JTextField(10);
        grossSalesBox.add(grossSalesField);
        baseBox.add(grossSalesBox);
        baseBox.add(Box.createVerticalStrut(5));

        // 提成比率
        Box commissionRateBox = Box.createHorizontalBox();
        commissionRateBox.add(new JLabel("CommissionRate"));
        commissionRateBox.add(Box.createHorizontalStrut(20));
        JTextField commissionRateField = new JTextField(10);
        commissionRateBox.add(commissionRateField);
        baseBox.add(commissionRateBox);
        baseBox.add(Box.createVerticalStrut(5));

        // 基础工资
        Box baseSalaryBox = Box.createHorizontalBox();
        baseSalaryBox.add(new JLabel("BaseSalary"));
        baseSalaryBox.add(Box.createHorizontalStrut(20));
        JTextField baseSalaryField = new JTextField(10);
        baseSalaryBox.add(baseSalaryField);
        baseBox.add(baseSalaryBox);
        baseBox.add(Box.createVerticalStrut(18));

        // 添加和取消按钮
        Box buttonBox = Box.createHorizontalBox();
        JButton addEmployee = new JButton("Add");
        addEmployee.addActionListener((e) -> {
            _14211383_张博康_4_Swing.addEmployee(
                    new BasePlusCommisionEmployee(
                            firstNameField.getText(),
                            lastNameField.getText(),
                            socialSecurityNumberField.getText(),
                            Integer.parseInt(grossSalesField.getText()),
                            Integer.parseInt(commissionRateField.getText()),
                            Integer.parseInt(baseSalaryField.getText())
                    ));
            dispose();
        });
        JButton close = new JButton("Conceal");
        close.addActionListener((e) -> {
            this.dispose();
        });

        buttonBox.add(addEmployee);
        buttonBox.add(Box.createHorizontalStrut(40));
        buttonBox.add(close);
        baseBox.add(buttonBox);

        add(baseBox);
    }

}

class CommisionEmployeeInput extends JDialog {
    public CommisionEmployeeInput() {
        setSize(340, 250);
        setLayout(new FlowLayout());
        Box baseBox = Box.createVerticalBox();
        // 先加入一个不可见的 Strut，从而使顶部留出一定的空间
        baseBox.add(Box.createVerticalStrut(10));

        // 姓
        Box lastNameBox = Box.createHorizontalBox();
        lastNameBox.add(new JLabel("LastName"));
        lastNameBox.add(Box.createHorizontalStrut(20));
        JTextField lastNameField = new JTextField(10);
        lastNameBox.add(lastNameField);
        baseBox.add(lastNameBox);
        baseBox.add(Box.createVerticalStrut(5));

        // 名
        Box firstNameBox = Box.createHorizontalBox();
        firstNameBox.add(new JLabel("FirstName"));
        firstNameBox.add(Box.createHorizontalStrut(20));
        JTextField firstNameField = new JTextField(10);
        firstNameBox.add(firstNameField);
        baseBox.add(firstNameBox);
        baseBox.add(Box.createVerticalStrut(5));

        // 社保号
        Box socialSecurityNumberBox = Box.createHorizontalBox();
        socialSecurityNumberBox.add(new JLabel("SSNumber"));
        socialSecurityNumberBox.add(Box.createHorizontalStrut(20));
        JTextField socialSecurityNumberField = new JTextField(10);
        socialSecurityNumberBox.add(socialSecurityNumberField);
        baseBox.add(socialSecurityNumberBox);
        baseBox.add(Box.createVerticalStrut(5));

        // 销售额
        Box grossSalesBox = Box.createHorizontalBox();
        grossSalesBox.add(new JLabel("GrossSales"));
        grossSalesBox.add(Box.createHorizontalStrut(20));
        JTextField grossSalesField = new JTextField(10);
        grossSalesBox.add(grossSalesField);
        baseBox.add(grossSalesBox);
        baseBox.add(Box.createVerticalStrut(5));

        // 提成比率
        Box commissionRateBox = Box.createHorizontalBox();
        commissionRateBox.add(new JLabel("CommissionRate"));
        commissionRateBox.add(Box.createHorizontalStrut(20));
        JTextField commissionRateField = new JTextField(10);
        commissionRateBox.add(commissionRateField);
        baseBox.add(commissionRateBox);
        baseBox.add(Box.createVerticalStrut(18));

        // 添加和取消按钮
        Box buttonBox = Box.createHorizontalBox();
        JButton addEmployee = new JButton("Add");
        addEmployee.addActionListener((e) -> {
            _14211383_张博康_4_Swing.addEmployee(
                    new CommisionEmployee(
                            firstNameField.getText(),
                            lastNameField.getText(),
                            socialSecurityNumberField.getText(),
                            Integer.parseInt(grossSalesField.getText()),
                            Integer.parseInt(commissionRateField.getText())
                    ));
            dispose();
        });
        JButton close = new JButton("Conceal");
        close.addActionListener((e) -> {
            this.dispose();
        });

        buttonBox.add(addEmployee);
        buttonBox.add(Box.createHorizontalStrut(40));
        buttonBox.add(close);
        baseBox.add(buttonBox);

        add(baseBox);
    }
}

class AverageEarningSearch extends JDialog {
    public AverageEarningSearch() {
        setSize(200, 100);
        setLayout(new FlowLayout());
        add(new JLabel("Average Earning: " +
                String.valueOf(_14211383_张博康_4_Swing.getAverage())));
    }
}