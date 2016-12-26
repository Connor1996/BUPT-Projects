package homework5;

public abstract class _14211383_张博康_5_Employee {
    private String firstName;
    private String lastName;
    private String socialSecurityNumber;

    public _14211383_张博康_5_Employee(String firstName, String lastName,
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

class SalaridEmployee extends _14211383_张博康_5_Employee {
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

class  HourlyEmployee extends _14211383_张博康_5_Employee {
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

class  CommisionEmployee extends _14211383_张博康_5_Employee {
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
