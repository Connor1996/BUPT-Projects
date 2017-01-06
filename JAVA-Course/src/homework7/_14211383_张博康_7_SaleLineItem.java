package homework7;

/**
 * Created by Connor on 2016/12/26.
 */
public class _14211383_张博康_7_SaleLineItem {
    private int copies;
    private _14211383_张博康_7_BookSpecification prodSpec;
    private _14211383_张博康_7_IPricingStrategy strategy;

    public _14211383_张博康_7_SaleLineItem(_14211383_张博康_7_BookSpecification prodSpec,
                                        int copies) {
        this.copies = copies;
        this.prodSpec = prodSpec;
        this.strategy = _14211383_张博康_7_PricingStrategyFactory.getInstance()
                .getPricingStrategy(prodSpec.getType());
    }

    public int getCopies() {
        return copies;
    }

    public double getPrice() {
        return prodSpec.getPrice();
    }

    public String getBookName() {
        return prodSpec.getTitle();
    }

    public double getSubTotal() {
        return strategy.getSubTotal(this);
    }

}
