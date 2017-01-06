package homework7;

import java.util.ArrayList;
import java.util.Observer;
import java.util.Vector;

/**
 * Created by Connor on 2016/12/26.
 */
public class _14211383_张博康_7_Sale implements _14211383_张博康_7_Subject {
    private ArrayList<_14211383_张博康_7_Observer> observers;
    private ArrayList<_14211383_张博康_7_SaleLineItem> saleLineItems;

    public _14211383_张博康_7_Sale() {
        observers = new ArrayList();
        saleLineItems = new ArrayList();
    }

    public double getTotal() {
        double sum = 0;
        for (_14211383_张博康_7_SaleLineItem item : saleLineItems) {
            sum += item.getSubTotal();
        }
        return sum;
    }

    public Vector<Vector<Object>> getTable() {
        Vector<Vector<Object>> table = new Vector();

        // 构建二维数组，用于显示表格信息
        for (_14211383_张博康_7_SaleLineItem item : saleLineItems) {
            Vector<Object> row = new Vector();

            row.add(item.getBookName());
            row.add(item.getCopies());
            row.add(item.getPrice());

            table.add(row);
        }

        return table;
    }

    @Override
    public void removeObserver(_14211383_张博康_7_Observer observer) {
        observers.remove(observer);
    }

    @Override
    public void registerObserver(_14211383_张博康_7_Observer observer) {
        observers.add(observer);
    }

    @Override
    public void notifyObservers() {
        for (_14211383_张博康_7_Observer item : observers) {
            item.update(this);
        }
    }

    public void addItem(_14211383_张博康_7_SaleLineItem item) {
        saleLineItems.add(item);
        notifyObservers();
    }

}
