package homework2;

import java.util.Scanner;

public class _14211383_张博康_2_Student {
    private String studentNumber;
    private String studentName;
    private int markForMaths;
    private int markForEnglish;
    private int markForScience;


    public _14211383_张博康_2_Student(String number, String name) {
        studentName = name;
        studentNumber = number;
        markForMaths = -1;
        markForEnglish = -1;
        markForScience = -1;
    }

    public _14211383_张博康_2_Student() {
        markForMaths = -1;
        markForEnglish = -1;
        markForScience = -1;
    }

    public String getName() {
        return studentName;
    }

    public String getNumber() {
        return studentNumber;
    }

    public void enterMarks(int markForMaths, int markForEnglish,
                           int markForScience)
            throws ScoreException {
        if (markForMaths < 0 || markForMaths > 100)
            throw new ScoreException();
        if (markForEnglish < 0 || markForEnglish > 100)
            throw new ScoreException();
        if (markForScience < 0 || markForScience > 100)
            throw new ScoreException();

        this.markForMaths = markForMaths;
        this.markForEnglish = markForEnglish;
        this.markForScience = markForScience;
    }

    public int getMathsMark() {
        return markForMaths;
    }

    public int getEnglishMark() {
        return markForEnglish;
    }

    public int getScienceMark() {
        return markForScience;
    }

    public double calculateAverage() {
        return (markForEnglish + markForMaths + markForScience) / 3.0;
    }

    public String toString() {
        return String.format("学号: %s\n" +
                        "姓名: %s\n" +
                        "数学成绩: %d\n" +
                        "英语成绩: %d\n" +
                        "科技成绩: %d\n" +
                        "平均成绩: %f\n",
                studentNumber, studentName, markForMaths,
                markForEnglish, markForScience, calculateAverage());
    }

}

class ScoreException extends Exception {
    public ScoreException() {
        super("成绩数据有误，请重新输入");
    }
}

class StudentNumberException extends Exception {
    public StudentNumberException() {
        super("学号格式不正确，请重新输入");
    }
}

class StudentTest {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        String studentNumber;
        while (true) {
            try {
                System.out.print("请输入学生学号：");
                studentNumber = input.nextLine();
                if (studentNumber.length() != 10 || !studentNumber.startsWith("20"))
                    throw new StudentNumberException();
            } catch (Exception e) {
                System.out.println(e.getMessage());
                continue;
            }
            break;
        }

        System.out.print("请输入学生姓名：");
        String studentName = input.nextLine();


        _14211383_张博康_2_Student student = null;
        while (true) {
            try {
                System.out.print("请输入学生三门课成绩: ");
                String[] str = input.nextLine().split(",");
                if (str.length != 3)
                    throw new ScoreException();
                int markForMaths = Integer.parseInt(str[0].trim());
                int markForEnglish = Integer.parseInt(str[1].trim());
                int markForScience = Integer.parseInt(str[2].trim());

                student = new _14211383_张博康_2_Student(studentNumber, studentName);
                student.enterMarks(markForMaths, markForEnglish, markForScience);
            } catch (ScoreException e) {
                System.out.println(e.getMessage());
                continue;
            }
            break;
        }
        System.out.println("学生信息如下: ");
        System.out.println(student);

    }
}