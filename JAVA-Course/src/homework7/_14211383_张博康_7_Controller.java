package homework7;

import java.util.Vector;
import java.util.HashMap;

/**
 * Created by Connor on 2016/12/26.
 */
public class _14211383_张博康_7_Controller {
    private _14211383_张博康_7_BookCatalog bookCatalog;
    private _14211383_张博康_7_StrategyCatalog strategyCatalog;
    private _14211383_张博康_7_Sale sale;

    public _14211383_张博康_7_Controller() {
        bookCatalog = new _14211383_张博康_7_BookCatalog();
        strategyCatalog = new _14211383_张博康_7_StrategyCatalog();
        sale = new _14211383_张博康_7_Sale();
        _14211383_张博康_7_PricingStrategyFactory.getInstance().setCatalog(strategyCatalog);
    }

    public Vector<Vector<Object>> getStrategies() {
        return strategyCatalog.getStrategies();
    }

    public Vector<Vector<Object>> getBooks() {
        return bookCatalog.getBooks();
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

    public boolean addCompositeStrategy(String id, String name, int bookType, String components) {
        _14211383_张博康_7_CompositeStrategy compositeStrategy
                = new _14211383_张博康_7_CompositeBestForCustomer(id, name);

        // 按“|”分割策略名
        for (String strategyId : components.split("\\|")) {
            _14211383_张博康_7_IPricingStrategy strategy = strategyCatalog.getStrategy(strategyId.trim());
            if (strategy != null)
                compositeStrategy.add(strategy);
            else
                return false;
        }

        strategyCatalog.addStrategy(bookType, compositeStrategy);
        return true;
    }

    public boolean addSimpleStrategy(String id, String name, int strategyType,
                                  int bookType, double discount) {

        _14211383_张博康_7_IPricingStrategy strategy;
        switch (strategyType + 1) {
            case 1:
                strategy = new _14211383_张博康_7_PercentageStrategy(id, name, discount);
                break;
            case 2:
                strategy = new _14211383_张博康_7_FlatRateStrategy(id, name, discount);
                break;
            default:
                strategy = new _14211383_张博康_7_NoDiscountStrategy();
        }
        return strategyCatalog.addStrategy(bookType, strategy);
    }

    public void deleteStrategy(String id) {
        strategyCatalog.deleteStrategy(id);
    }

    public void updateStrategy(String id, String name, int strategyType,
                               int bookType, double discount) {
        _14211383_张博康_7_IPricingStrategy strategy;
        switch (strategyType) {
            case 1:
                strategy = new _14211383_张博康_7_PercentageStrategy(id, name, discount);
                break;
            case 2:
                strategy = new _14211383_张博康_7_FlatRateStrategy(id, name, discount);
                break;
            default:
                strategy = new _14211383_张博康_7_NoDiscountStrategy();
        }

        strategyCatalog.updateStrategy(bookType, strategy);
    }

    public void buyBook(String isbn, int number) throws Exception {
        sale.addItem(new _14211383_张博康_7_SaleLineItem(
                bookCatalog.getBookSpecification(isbn),
                number
        ));
    }

    public _14211383_张博康_7_Sale getSale() {
        return sale;
    }

}
