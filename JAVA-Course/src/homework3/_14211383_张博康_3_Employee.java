package homework3;

import java.lang.String;
import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.Scanner;
import java.lang.Math;

public abstract class _14211383_张博康_3_Employee {
    private String firstName;
    private String lastName;
    private String socialSecurityNumber;

    public _14211383_张博康_3_Employee(String firstName, String lastName,
                                    String socialSecurityNumber) {
        this.firstName = firstName;
        this.lastName = lastName;
        this.socialSecurityNumber = socialSecurityNumber;
    }

    public abstract int earning();
    
    public String getFirstName() {
        return firstName;
    }
    
    public String getLastName() {
        return lastName;
    }
    
    public String getSocialSecurityNumber() {
        return socialSecurityNumber;
    }

    public void setFirstName(String firstName) {
        this.firstName = firstName;
    }
    
    public void setLastName(String lastName) {
        this.lastName = lastName;
    }
    
    public String toString() {
        return "姓名: " + lastName + firstName + "\n"
                + "社保号: " + socialSecurityNumber;
    }
}

class SalaridEmployee extends _14211383_张博康_3_Employee {
    private int weeklySalary;

    public SalaridEmployee(String firstName, String lastName,
                          String socialSecurityNumber) {
        super(firstName, lastName, socialSecurityNumber);
    }

    public SalaridEmployee(String firstName, String lastName,
                           String socialSecurityNumber, int weeklySalary) {
        super(firstName, lastName, socialSecurityNumber);
        this.weeklySalary = weeklySalary;
    }

    public int earning() {
        return 4 * weeklySalary;
    }

    public int getWeeklySalary() {
        return weeklySalary;
    }

    public void setWeeklySalary(int weeklySalary) {
        this.weeklySalary = weeklySalary;
    }
}

class  HourlyEmployee extends _14211383_张博康_3_Employee {
    private int wage;
    private int hours;


    public HourlyEmployee(String firstName, String lastName,
                                     String socialSecurityNumber) {
        super(firstName, lastName, socialSecurityNumber);
    }

    public HourlyEmployee(String firstName, String lastName,
                          String socialSecurityNumber, int wage, int hours) {
        super(firstName, lastName, socialSecurityNumber);
        this.wage = wage;
        this.hours = hours;
    }

    public int earning() {
        return wage * hours;
    }

    public int getWage() {
        return wage;
    }

    public int getHours() {
        return hours;
    }

    public void setWage(int wage) {
        this.wage = wage;
    }

    public void setHours(int hours) {
        this.hours = hours;
    }
}

class  CommisionEmployee extends _14211383_张博康_3_Employee {
    protected int grossSales;
    protected int commissionRate;

    public CommisionEmployee(String firstName, String lastName,
                                     String socialSecurityNumber) {
        super(firstName, lastName, socialSecurityNumber);
    }

    public CommisionEmployee(String firstName, String lastName,
                             String socialSecurityNumber, int grossSales,
                             int commissionRate) {
        super(firstName, lastName, socialSecurityNumber);
        this.grossSales = grossSales;
        this.commissionRate = commissionRate;
    }

    public int earning() {
        return grossSales * commissionRate;
    }

    public int getGrossSales() {
        return grossSales;
    }

    public int getCommissionRate() {
        return commissionRate;
    }

    public void setGrossSales(int grossSales) {
        this.grossSales = grossSales;
    }

    public void setCommissionRate(int commissionRate) {
        this.commissionRate = commissionRate;
    }
}

class BasePlusCommisionEmployee extends CommisionEmployee {
    protected int baseSalary;


    public BasePlusCommisionEmployee(String firstName, String lastName,
                                     String socialSecurityNumber) {
        super(firstName, lastName, socialSecurityNumber);
    }

    public BasePlusCommisionEmployee(String firstName, String lastName,
                                     String socialSecurityNumber, int grossSales,
                                     int commissionRate, int baseSalary) {
        super(firstName, lastName, socialSecurityNumber, grossSales, commissionRate);
        this.baseSalary = baseSalary;
    }

    public int earning() {
        return grossSales * commissionRate + baseSalary;
    }

    public int getBaseSalary() {
        return baseSalary;
    }

    public void setBaseSalary(int baseSalary) {
        this.baseSalary = baseSalary;
    }
}

class EmployTest {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);

        ArrayList employees = new ArrayList<_14211383_张博康_3_Employee>();
        final String[] type = {"SalaridEmployee", "HourlyEmployee",
                "CommisionEmployee", "BasePlusCommisionEmployee"};

        String firstName;
        String lastName;
        String socialSecurityNumber;
        for (int i = 0; i < 10; i++) {
            System.out.println("第" + i + "个员工: ");
            System.out.print("请输入姓：");
            lastName = input.nextLine();
            System.out.print("请输入名：");
            firstName = input.nextLine();
            System.out.print("请输入社保号：");
            socialSecurityNumber = input.nextLine();
            System.out.println();

            try
            {
                Class cls  = Class.forName("homework3." + type[(int)(Math.random() * 4)]);
                _14211383_张博康_3_Employee employee = (_14211383_张博康_3_Employee)cls
                        .getConstructor(String.class, String.class, String.class)
                        .newInstance(firstName, lastName, socialSecurityNumber);

                Method[] methods = cls.getMethods();
                for (Method method : methods) {
                    String methodName = method.getName();
                    if (methodName.startsWith("set") && !methodName.contains("Name"))
                        method.invoke(employee, (int)(100 + Math.random() * 100));

                }
                employees.add(employee);
            }
            catch (Exception e)
            {
                e.printStackTrace();
            }
        }
        System.out.println();
        for (Object employee : employees) {
            System.out.println(employee);
            //System.out.println(employee.getClass().getName());
            System.out.println("月工资为: " + ((_14211383_张博康_3_Employee)employee).earning() + "\n");
        }
    }
}