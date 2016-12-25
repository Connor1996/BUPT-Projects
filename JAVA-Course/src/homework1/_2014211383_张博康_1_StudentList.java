package homework1;

import java.lang.reflect.Method;
import java.util.Scanner;

/**
 * Created by Connor on 2016/10/12.
 */

public class _2014211383_张博康_1_StudentList {
    private _2014211383_张博康_1_Student[] list;
    private int total;

    public _2014211383_张博康_1_StudentList(int length) {
        total = 0;
        list = new _2014211383_张博康_1_Student[length];
    }

    public boolean add(_2014211383_张博康_1_Student stu) {
        if (total == list.length)
            return false;
        else {
            list[total] = stu;
            total += 1;
            return true;
        }
    }

    public boolean remove(int no) {
        _2014211383_张博康_1_Student[] _list = new _2014211383_张博康_1_Student[list.length];
        int _total = total;
        int j = 0;
        for(int i = 0; i < total; i++) {
            if (i != no - 1) {
                _list[j] = list[i];
                j += 1;
            }
            else {
                total -= 1;
            }
        }
        list = _list;
        if (total == _total)
            return false;
        else
            return true;
    }

    public boolean remove(String number) {
        _2014211383_张博康_1_Student[] _list = new _2014211383_张博康_1_Student[list.length];
        int _total = total;
        int j = 0;
        for(int i = 0; i < total; i++) {
            if (list[i].getNumber().equals(number) == false) {
                _list[j] = list[i];
                j += 1;
            }
            else {
                total -= 1;
            }
        }
        list = _list;
        if (total == _total)
            return false;
        else
            return true;
    }

    public boolean isEmpty() {
        return total == 0;
    }

    public _2014211383_张博康_1_Student getItem(int no) {
        if (no > total)
            return null;
        else
            return list[no - 1];
    }

    public _2014211383_张博康_1_Student getItem(String number) {
        for(int i = 0; i < total; i++) {
            if (list[i].getNumber().equals(number))
                return list[i];
        }
        return null;
    }

    public int getTotal() {
        return total;
    }

}


class StudentListTest {
    public static void main(String[] args) {
        System.out.println("菜单如下，请输入1~8代表您要执行的操作");
        System.out.println("1.增加1个学生");
        System.out.println("2.根据学号删除学生");
        System.out.println("3.根据位置删除学生");
        System.out.println("4.判断是否为空");
        System.out.println("5.根据位置返回学生");
        System.out.println("6.根据学号返回学生");
        System.out.println("7.输出全部学生信息");
        System.out.println("8.退出程序");

        _2014211383_张博康_1_StudentList studentList = new _2014211383_张博康_1_StudentList(10);

        Scanner scanner = new Scanner(System.in);
        while (true) {
            System.out.print("请输入您的操作: ");
            int choose = scanner.nextInt();
            switch (choose) {
                case 1: {
                    System.out.println("请输入学生信息：");
                    System.out.print("学号： ");
                    String studentNumber = scanner.next().trim();
                    System.out.print("姓名：");
                    String studentName = scanner.next();
                    System.out.print("数学成绩: ");
                    int markForMaths = scanner.nextInt();
                    System.out.print("英语成绩: ");
                    int markForEnglish = scanner.nextInt();
                    System.out.print("科学成绩: ");
                    int markForScience = scanner.nextInt();

                    _2014211383_张博康_1_Student student = new _2014211383_张博康_1_Student(studentNumber, studentName);
                    student.enterMarks(markForMaths, markForEnglish, markForScience);
                    studentList.add(student);

                    System.out.println(String.format("---目前有%d个学生，信息为---", studentList.getTotal()));
                    for (int i = 0; i < studentList.getTotal(); i++) {
                        System.out.println(studentList.getItem(i + 1));
                    }
                    break;
                }
                case 2: {
                    System.out.print("请输入学生学号：");
                    String studentNumber = scanner.next();
                    if (studentList.remove(studentNumber))
                        System.out.println("删除成功");
                    else
                        System.out.println("删除失败");

                    System.out.println(String.format(
                            "---目前有%d个学生，信息为---", studentList.getTotal()));
                    for (int i = 0; i < studentList.getTotal(); i++) {
                        System.out.println(String.format(
                                "-----------------第%d个学生信息------------------", i + 1));
                        System.out.println(studentList.getItem(i + 1) + "\n");
                    }
                    break;
                }
                case 3: {
                    System.out.print("请输入学生位置：");
                    int no = scanner.nextInt();
                    if (studentList.remove(no))
                        System.out.println("删除成功");
                    else
                        System.out.println("删除失败");

                    System.out.println(String.format(
                            "---目前有%d个学生，信息为---", studentList.getTotal()));
                    for (int i = 0; i < studentList.getTotal(); i++) {
                        System.out.println(String.format(
                                "---第%d个学生信息---", i + 1));
                        System.out.println(studentList.getItem(i + 1) + "\n");
                    }
                    break;
                }
                case 4: {
                    if (studentList.isEmpty())
                        System.out.println("列表为空");
                    else
                        System.out.println("列表不为空");
                    break;
                }
                case 5: {
                    System.out.print("请输入学生位置：");
                    int no = scanner.nextInt();
                    _2014211383_张博康_1_Student stu = studentList.getItem(no);
                    if (stu != null) {
                        System.out.println("学生信息如下：");
                        System.out.println(stu);
                    }
                    else
                        System.out.println("对不起，没有相应的学生");

                    break;
                }
                case 6: {
                    System.out.print("请输入学生学号：");
                    String studentNumber = scanner.next();
                    _2014211383_张博康_1_Student stu = studentList.getItem(studentNumber.trim());
                    if (stu != null) {
                        System.out.println("学生信息如下：");
                        System.out.println(stu);
                    }
                    else
                        System.out.println("对不起，没有相应的学生");
                    break;
                }
                case 7: {
                    System.out.println(String.format(
                            "---目前有%d个学生，信息为---", studentList.getTotal()));
                    for (int i = 0; i < studentList.getTotal(); i++) {
                        System.out.println(String.format(
                                "---第%d个学生信息---", i + 1));
                        System.out.println(studentList.getItem(i + 1) + "\n");
                    }
                    break;
                }
                case 8: {
                    System.exit(0);
                }
            }
        }
    }
}