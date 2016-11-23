import java.util.Scanner;

public class _2014211383_张博康_1_Student {
    private String studentNumber;
    private String studentName;
    private int markForMaths;
    private int markForEnglish;
    private int markForScience;


    public _2014211383_张博康_1_Student(String number, String name) {
        studentName = name;
        studentNumber = number;
        markForMaths = -1;
        markForEnglish = -1;
        markForScience = -1;
    }

    public _2014211383_张博康_1_Student() {
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
                           int markForScience) {
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

class StudentTest {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        System.out.print("请输入学生学号：");
        String studentNumber = input.nextLine();
        System.out.print("请输入学生姓名：");
        String studentName = input.nextLine();
        System.out.print("请输入学生三门课成绩: ");


        String[] str = input.nextLine().split(",");
        int markForMaths = Integer.parseInt(str[0]);
        int markForEnglish = Integer.parseInt(str[1]);
        int markForScience = Integer.parseInt(str[2]);

        _2014211383_张博康_1_Student student = new _2014211383_张博康_1_Student(studentNumber, studentName);
        student.enterMarks(markForMaths, markForEnglish, markForScience);

        System.out.println("学生信息如下: ");
        System.out.println(student);
    }
}