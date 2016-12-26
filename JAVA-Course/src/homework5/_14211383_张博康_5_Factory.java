package homework5;

import java.lang.String;
import java.lang.reflect.Method;
import java.util.InputMismatchException;
import java.util.Scanner;
import java.util.HashMap;

public class _14211383_张博康_5_Factory {
    public _14211383_张博康_5_Factory() {
        employees = new HashMap();
        initEmployees();
    }

    public void initEmployees() {
        Scanner input = new Scanner(System.in);
        final String[] type = {"SalaridEmployee", "HourlyEmployee",
                "CommisionEmployee", "BasePlusCommisionEmployee"};

        String firstName;
        String lastName;
        String socialSecurityNumber;
        for (int i = 1; i <= 10; i++) {
            System.out.println("第" + i + "个员工: ");
            System.out.print("请输入姓：");
            lastName = input.nextLine();
            System.out.print("请输入名：");
            firstName = input.nextLine();
            System.out.print("请输入社保号：");
            socialSecurityNumber = input.nextLine();
            System.out.println();

            if (socialSecurityNumber == "0000")
                break;

            try
            {
                // 使用反射实例化类对象
                Class cls  = Class.forName("homework5." + type[(int)(Math.random() * 4)]);
                _14211383_张博康_5_Employee employee = (_14211383_张博康_5_Employee)cls
                        .getConstructor(String.class, String.class, String.class)
                        .newInstance(firstName, lastName, socialSecurityNumber);

                // 使用反射设置类的各个属性
                Method[] methods = cls.getMethods();
                for (Method method : methods) {
                    String methodName = method.getName();
                    if (methodName.startsWith("set") && !methodName.contains("Name"))
                        method.invoke(employee, (int)(100 + Math.random() * 100));
                }

                // 插入新员工
                if (addEmployee(employee) == null) {
                    System.out.println("已经有该员工，请重新输入");
                    i--;
                }
            }
            catch (Exception e)
            {
                e.printStackTrace();
            }
        }
    }

    public _14211383_张博康_5_Employee getEmployee(String empSecNum) {
        return employees.get(empSecNum);
    }

    public _14211383_张博康_5_Employee deleteEmployee(String empSecNum) {
        return employees.remove(empSecNum);
    }

    public _14211383_张博康_5_Employee addEmployee(_14211383_张博康_5_Employee stu) {
        if (employees.containsKey(stu.getSocialSecurityNumber()))
            return null;
        else {
            employees.put(stu.getSocialSecurityNumber(), stu);
            return stu;
        }
    }

    public _14211383_张博康_5_Employee updateEmployee(String empSecNUm, _14211383_张博康_5_Employee emp) {
        if (employees.put(empSecNUm, emp) == null)
            return null;
        else
            return emp;
    }

    public void printEmployees() {
        for (HashMap.Entry<String, _14211383_张博康_5_Employee> emp : employees.entrySet())
            System.out.println(emp.getValue());
    }

    private HashMap<String, _14211383_张博康_5_Employee> employees;

    public static void main(String[] argv) {
        _14211383_张博康_5_Factory factory = new _14211383_张博康_5_Factory();

        // 输出菜单
        Scanner input = new Scanner(System.in);
        System.out.println("请输入要执行的命令\n" +
        "0. 退出程序\n" +
        "1. 查询员工信息\n" +
        "2. 更新员工信息\n" +
        "3. 删除员工信息\n" +
        "4. 打印全部员工信息\n");

        // 根据输入选择命令
        int choose;
        boolean quit = false;
        while(true) {
            try{
                choose = input.nextInt();
            } catch (InputMismatchException e) {
                System.out.println("无效命令");
                input.next();
                continue;
            }

            try {
                switch (choose) {
                    case 0:
                        quit = true;
                        break;
                    case 1: {
                        System.out.print("请输入要查询的员工社会保险号: ");
                        String empSecNum = input.next();
                        _14211383_张博康_5_Employee emp = factory.getEmployee(empSecNum);
                        if (emp == null)
                            throw new Exception("无该员工信息");
                        else
                            System.out.println(emp);
                        break;
                    }
                    case 2: {
                        System.out.print("请输入要更新的员工社会保险号： ");
                        String empSecNUm = input.next();
                        _14211383_张博康_5_Employee emp = factory.getEmployee(empSecNUm);
                        if (factory.getEmployee(empSecNUm) == null)
                            throw new Exception("无该员工信息");

                        System.out.print("将该员工的姓改为： ");
                        String lastName = input.next();
                        emp.setLastName(lastName);
                        System.out.print("将该员工的名改为： ");
                        String firstName = input.next();
                        emp.setFirstName(firstName);

                        break;
                    }
                    case 3: {
                        System.out.print("请输入要删除的员工社会保险号： ");
                        String empSecNum = input.next();
                        if (factory.deleteEmployee(empSecNum) == null)
                            throw new Exception("无该员工信息");
                        break;
                    }
                    case 4: {
                        factory.printEmployees();
                        break;
                    }
                    default:
                        System.out.println("无效命令");
                }
            } catch (Exception e) {
                System.out.println(e.getMessage());
            }

            if (quit)
                break;
        }

    }
}