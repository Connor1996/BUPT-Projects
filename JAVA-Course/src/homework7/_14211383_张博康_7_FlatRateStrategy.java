package homework7;

/**
 * Created by Connor on 2016/12/26.
 */
public class _14211383_张博康_7_FlatRateStrategy extends _14211383_张博康_7_IPricingStrategy {
    private double discountPerBook;

    public String getDiscount() { return String.valueOf(discountPerBook); }

    public _14211383_张博康_7_FlatRateStrategy(String id, String name, double discountPerBook) {
        this.id = id;
        this.name = name;
        this.discountPerBook = discountPerBook;
    }

    @Override
    public double getSubTotal(_14211383_张博康_7_SaleLineItem saleLineItem) {
        return saleLineItem.getCopies() * ( saleLineItem.getPrice() - discountPerBook);
    }
}
