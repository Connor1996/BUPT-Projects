package homework7;

import java.util.ArrayList;

/**
 * Created by Connor on 2016/12/26.
 */
public class _14211383_张博康_7_CompositeStrategy extends  _14211383_张博康_7_IPricingStrategy {
    private ArrayList<_14211383_张博康_7_IPricingStrategy> strategies;

    public _14211383_张博康_7_CompositeStrategy(String id, String name) {
        this.id = id;
        this.name = name;
        strategies = new ArrayList();
    }

    public void add(_14211383_张博康_7_IPricingStrategy iPricingStrategy) {
        strategies.add(iPricingStrategy);
    }


    @Override
    public double getSubTotal(_14211383_张博康_7_SaleLineItem saleLineItem) {
        return 0;
    }
}
