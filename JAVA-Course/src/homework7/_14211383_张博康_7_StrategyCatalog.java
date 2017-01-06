package homework7;

import java.lang.reflect.Array;
import java.util.Vector;
import java.util.HashMap;

/**
 * Created by Connor on 2016/12/26.
 */
public class _14211383_张博康_7_StrategyCatalog {
    private HashMap<Integer, _14211383_张博康_7_IPricingStrategy> strategies;

    public _14211383_张博康_7_StrategyCatalog() {
        strategies = new HashMap();
    }

    public Vector<Vector<Object>> getStrategies( ) {
        Vector<Vector<Object>> table = new Vector();

        for (HashMap.Entry<Integer, _14211383_张博康_7_IPricingStrategy> entry : strategies.entrySet()) {
            Vector<Object> row = new Vector();
            
            row.add(entry.getValue().getId());
            row.add(entry.getValue().getName());

            switch(entry.getValue().getClass().getName()) {
                case "homework7._14211383_张博康_7_FlatRateStrategy":
                    row.add("绝对值优惠策略");
                    break;
                case "homework7._14211383_张博康_7_PercentageStrategy":
                    row.add("百分比折扣策略");
                    break;
                case "homework7._14211383_张博康_7_CompositeBestForCustomer":
                    row.add("组合策略");
                    break;
                default:
                    System.out.println("[Error] classname:" + entry.getValue().getClass().getName());
            }

            switch(entry.getKey() + 1) {
                case 1:
                    row.add("非教材类计算机图书");
                    break;
                case 2:
                    row.add("教材类图书");
                    break;
                case 3:
                    row.add("连环画类图书");
                    break;
                case 4:
                    row.add("养生类图书");
                    break;
                case 5:
                    row.add("其他");
                    break;
                default:
                    System.out.println("[Error] bookType:" + entry.getKey());
            }

            row.add(entry.getValue().getDiscount());
            
            table.add(row);
        }
        return table;
    }

    public _14211383_张博康_7_IPricingStrategy getStrategy(String strategyId) {
        for (HashMap.Entry<Integer, _14211383_张博康_7_IPricingStrategy> entry : strategies.entrySet()) {
            if (entry.getValue().getId().equals(strategyId))
                return entry.getValue();
        }
        return null;
    }

    public _14211383_张博康_7_IPricingStrategy getStrategy(int bookType) {
        if (!strategies.containsKey(bookType))
            return new _14211383_张博康_7_NoDiscountStrategy();
        else
            return strategies.get(bookType);
    }

    public boolean addStrategy(int bookType, _14211383_张博康_7_IPricingStrategy strategy) {
        // 如果该类型书已经有相应策略返回false
        if (strategies.containsKey(bookType))
            return false;
        // 在没有重复策略名时添加
        for (HashMap.Entry<Integer, _14211383_张博康_7_IPricingStrategy> entry : strategies.entrySet()) {
            if (entry.getValue().getId().equals(strategy.getId())) {
                return false;
            }
        }
        strategies.put(bookType, strategy);
        return true;
    }

    public boolean updateStrategy(int bookType, _14211383_张博康_7_IPricingStrategy strategy) {
        for (HashMap.Entry<Integer, _14211383_张博康_7_IPricingStrategy> entry : strategies.entrySet()) {
            // 找到原来的策略
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
