package homework7;

/**
 * Created by Connor on 2016/12/26.
 */
import java.lang.String;

public class _14211383_张博康_7_BookSpecification {
    private double price;
    private String title;
    private int type;
    private String isbn;

    public _14211383_张博康_7_BookSpecification(double price, String title,
                                             int type, String isbn)
    {
        this.price = price;
        this.title = title;
        this.type = type;
        this.isbn = isbn;
    }

    public int getType() {
        return type;
    }

    public String getIsbn() {
        return isbn;
    }

    public String getTitle() {
        return title;
    }

    public double getPrice() {
        return price;
    }
}
