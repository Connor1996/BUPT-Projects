package homework7;

/**
 * Created by Connor on 2016/12/26.
 */
public class _14211383_张博康_7_PricingStrategyFactory {
    private static _14211383_张博康_7_PricingStrategyFactory instance;
    private _14211383_张博康_7_StrategyCatalog strategyCatalog;

    private _14211383_张博康_7_PricingStrategyFactory() {  }

    public static _14211383_张博康_7_PricingStrategyFactory getInstance() {
        if (instance == null)
            return instance = new _14211383_张博康_7_PricingStrategyFactory();
        else
            return instance;
    }

    public _14211383_张博康_7_IPricingStrategy getPricingStrategy(int bookType) {
        return strategyCatalog.getStrategy(bookType);
    }

    public void setCatalog(_14211383_张博康_7_StrategyCatalog strategyCatalog) {
        this.strategyCatalog = strategyCatalog;
    }

}
