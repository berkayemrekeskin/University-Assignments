/**
 * DeviceObject class implements the Device interface and provides the basic structure for the device objects
 * Subclasses of DeviceObject are Headphone, Laptop, Mouse, Smartphone, and Television
 */
public abstract class DeviceObject implements Device {

    private String category;
    private String name;
    private double price;
    private int quantity;
    
    /**
     * Constructor for DeviceObject
     * Complexity: O(1)
     * @param category 
     * @param name
     * @param price
     * @param quantity
     */
    public DeviceObject(String category, String name, double price, int quantity)
    {
        this.category = category;
        this.name = name;
        this.price = price;
        this.quantity = quantity;
    }
    /**
     * Returns the price of the device
     * Complexity: O(1)
     * @return price
     */
    @Override
    public double getPrice() {
        return price;
    }
    /**
     * Returns the quantity of the device
     * Complexity: O(1)
     * @return quantity
     */
    @Override
    public int getQuantity() {
        return quantity;
    }
    /**
     * Returns the name of the device
     * Complexity: O(1)
     * @return name
     */
    @Override
    public String getName() {
        return name;
    }

    /**
     * Returns the category of the device
     * Complexity: O(1)
     * @return category
     */
    @Override
    public String getCategory() {
        return category;
    }

    /**
     * Sets the category of the device
     * Complexity: O(1)
     * @param category
     */
    @Override
    public void setCategory(String category) {
        this.category = category;
    }

    /**
     * Sets the name of the device
     * Complexity: O(1)
     * @param name
     */
    @Override
    public void setName(String name) {
        this.name = name;
    }

    /**
     * Sets the price of the device
     * Complexity: O(1)
     * @param price
     */
    @Override
    public void setPrice(double price) {
        this.price = price;
    }

    /**
     * Sets the quantity of the device
     * Complexity: O(1)
     * @param quantity
     */
    @Override
    public void setQuantity(int quantity) {
        this.quantity = quantity;
    }

}
