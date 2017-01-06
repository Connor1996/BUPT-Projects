package homework7;

/**
 * Created by Connor on 2016/12/26.
 */
public class _14211383_张博康_7_NoDiscountStrategy extends  _14211383_张博康_7_IPricingStrategy {

    @Override
    public double getSubTotal(_14211383_张博康_7_SaleLineItem saleLineItem) {
        return saleLineItem.getCopies() * saleLineItem.getPrice();
    }

    @Override
    public String getDiscount() {
        return "";
    }
}
