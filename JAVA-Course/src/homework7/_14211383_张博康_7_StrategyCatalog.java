package homework7;

import java.util.HashMap;

/**
 * Created by Connor on 2016/12/26.
 */
public class _14211383_张博康_7_StrategyCatalog {
    private HashMap<Integer, _14211383_张博康_7_IPricingStrategy> strategies;

    public _14211383_张博康_7_StrategyCatalog() {
        strategies = new HashMap();
    }

    public Object[][] getStrategies( ) {
        for (HashMap.Entry<Integer, _14211383_张博康_7_IPricingStrategy> entry : strategies.entrySet()) {
            //entry.
        }
        return null;
    }

    public _14211383_张博康_7_IPricingStrategy getStrategy(String strategyId) {
        for (HashMap.Entry<Integer, _14211383_张博康_7_IPricingStrategy> entry : strategies.entrySet()) {
            if (entry.getValue().getId().equals(strategyId))
                return entry.getValue();
        }
        return null;
    }

    public _14211383_张博康_7_IPricingStrategy getStrategy(int bookType) {
        return strategies.get(bookType);
    }

    public boolean addStrategy(int bookType, _14211383_张博康_7_IPricingStrategy strategy) {
        if (strategies.containsKey(bookType))
            return false;
        for (HashMap.Entry<Integer, _14211383_张博康_7_IPricingStrategy> entry : strategies.entrySet()) {
            if (entry.getValue().getId().equals(strategy.getId())) {
                System.out.print("what ");
                return false;
            }
        }
        strategies.put(bookType, strategy);
        return true;
    }

    public boolean updateStrategy(int bookType, _14211383_张博康_7_IPricingStrategy strategy) {
        for (HashMap.Entry<Integer, _14211383_张博康_7_IPricingStrategy> entry : strategies.entrySet()) {
            if (entry.getValue().getId() == strategy.getId()) {
                if (entry.getKey() == bookType)
                    entry.setValue(strategy);
                else {
                    strategies.remove(entry.getKey());
                    if (strategies.containsKey(bookType))
                        return false;
                    else {
                        strategies.put(bookType, strategy);
                        return true;
                    }
                }
            }
        }
        return false;
    }

    public void deleteStrategy(String id) {
        for (HashMap.Entry<Integer, _14211383_张博康_7_IPricingStrategy> entry : strategies.entrySet()) {
            if (entry.getValue().getId().equals(id)) {
                strategies.remove(entry.getKey());
            }
        }
    }
}
