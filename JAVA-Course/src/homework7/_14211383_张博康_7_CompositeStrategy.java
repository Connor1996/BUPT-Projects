package homework7;

import java.util.ArrayList;

/**
 * Created by Connor on 2016/12/26.
 */
public abstract class _14211383_张博康_7_CompositeStrategy extends  _14211383_张博康_7_IPricingStrategy {
    protected ArrayList<_14211383_张博康_7_IPricingStrategy> strategies;

    public String getDiscount() {
        StringBuilder stringBuilder = new StringBuilder();

        // 生成序列化信息
        for (_14211383_张博康_7_IPricingStrategy strategy : strategies) {
            stringBuilder.append(strategy.getName());
            stringBuilder.append("|");
        }
        // 删除末尾多余的符号
        stringBuilder.deleteCharAt(stringBuilder.length() - 1);
        return stringBuilder.toString();
    }

    public _14211383_张博康_7_CompositeStrategy(String id, String name) {
        this.id = id;
        this.name = name;
        strategies = new ArrayList();
    }

    public void add(_14211383_张博康_7_IPricingStrategy iPricingStrategy) {
        strategies.add(iPricingStrategy);
    }
}
