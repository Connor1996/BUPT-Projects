package homework7;

/**
 * Created by Connor on 2016/12/26.
 */
public class _14211383_张博康_7_Controller {
    private _14211383_张博康_7_BookCatalog bookCatalog;
    private _14211383_张博康_7_StrategyCatalog strategyCatalog;

    public _14211383_张博康_7_Controller() {
        bookCatalog = new _14211383_张博康_7_BookCatalog();
        strategyCatalog = new _14211383_张博康_7_StrategyCatalog();
    }

    public void addBook(double price, String title, int type, String isbn) {
        bookCatalog.addBook(
            new _14211383_张博康_7_BookSpecification(
                    price,
                    title,
                    type,
                    isbn
            )
        );
    }

    public void addCompositeStrategy() {

    }

    public void addSimpleStrategy() {

    }

    public void deleteStrategy() {

    }

    public void updateStrategy() {

    }

    public void buyBook() {

    }

    public _14211383_张博康_7_Sale getSale() {
        return null;
    }

}
