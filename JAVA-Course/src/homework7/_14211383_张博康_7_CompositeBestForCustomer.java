package homework7;

/**
 * Created by Connor on 2016/12/26.
 */
public class _14211383_张博康_7_CompositeBestForCustomer extends _14211383_张博康_7_CompositeStrategy {

    public _14211383_张博康_7_CompositeBestForCustomer(String id, String name) {
        super(id, name);
    }

    @Override
    public double getSubTotal(_14211383_张博康_7_SaleLineItem saleLineItem) {
        double min = 1000000000;

        // 寻找最小的总价
        for (_14211383_张博康_7_IPricingStrategy strategy : strategies) {
            min = Math.min(strategy.getSubTotal(saleLineItem), min);
        }

        return min;
    }
}
