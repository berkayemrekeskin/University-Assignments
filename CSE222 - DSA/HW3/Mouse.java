/**
 * Mouse class that extends DeviceObject
 */
public class Mouse extends DeviceObject {

    /**
     * Mouse constructor
     * Complexity = O(1)
     * @param category
     * @param name
     * @param price
     * @param quantity
     */
    public Mouse(String category, String name, double price, int quantity)
    {
        super(category,name,price,quantity);
    }
}