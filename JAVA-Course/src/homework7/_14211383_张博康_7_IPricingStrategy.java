package homework7;

/**
 * Created by Connor on 2016/12/26.
 */
public abstract class _14211383_张博康_7_IPricingStrategy {
    protected String id;
    protected String name;

    public abstract double getSubTotal(_14211383_张博康_7_SaleLineItem saleLineItem);

    public String getId() { return id; }
    public String getName() { return name; }
}
