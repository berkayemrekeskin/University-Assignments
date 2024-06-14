/**
 * Device interface for the DeviceObject class
 */
public interface Device {
    /**
     * Getters and Setters for the DeviceObject class
     */
    public String getCategory();
    public String getName();
    public double getPrice();
    public int getQuantity();

    public void setCategory(String category);
    public void setName(String name);
    public void setPrice(double price);
    public void setQuantity(int quantity);

}