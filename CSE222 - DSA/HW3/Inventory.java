import java.io.File;
import java.io.FileWriter;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.util.LinkedList;
import java.util.ArrayList;

/**
 * This class is used to create an inventory for an electronics shop
 * It has methods to add, remove, update, restock, list, find cheapest, sort by price, calculate total value & export the inventory
 * It also has helper methods to add, remove, update, restock, find & get the device
 */
public class Inventory {

    private LinkedList<ArrayList<DeviceObject>> deviceList;
    /**
     * Constructor for objects of class Inventory,
     * Complexity: O(1)
     */
    public Inventory()
    {
        deviceList = new LinkedList<ArrayList<DeviceObject>>();
    }
    
    /**
     * This method is used to add a device to the inventory,
     * Complexity: O(n) because it calls the addHelper method which is O(n) & the find method which is O(n)
     * @param category
     * @param name
     * @param price
     * @param quantity
     */
    public void add(String category, String name, double price, int quantity)
    {
        if(category.isEmpty() || name.isEmpty() || price <= 0 || quantity <= 0)
        {
            System.out.println("Invalid input!");
            return;
        }
        if(find(name) != null)
        {
            System.out.println("Device with the name " + name + " already exists in the store!");
            return;
        }
        DeviceObject device = get(category, name, price, quantity);
        if(addHelper(device))
            System.out.println(category + ", " + name + ", " + price + "$, " + quantity + " amount added...");
        else
            System.out.println("Device could not be added!");
    }

    /**
     * This method is a helper method for the add method,
     * Complexity = O(n) because it iterates through the deviceList which has 5 categories
     * @param newDevice getting the new device to be added
     * @return true if the device is added, false otherwise
     */
    private boolean addHelper(DeviceObject newDevice)
    {
        
        if(newDevice == null)
            return false;
        else if(newDevice.getQuantity() <= 0 || newDevice.getPrice() <= 0)
            return false;
        else
        {
            for(ArrayList<DeviceObject> list : deviceList) // 5 categories
            {
                if(list.get(0).getCategory().equals(newDevice.getCategory()))
                {
                    list.add(newDevice);
                    return true;
                }
            }
            ArrayList<DeviceObject> newList = new ArrayList<DeviceObject>();
            newList.add(newDevice);
            deviceList.add(newList);
            return true;
        }
    }

    /**
     * This method is used to remove a device from the inventory,
     * Complexity: O(n) because it calls the removeHelper method which is O(n) & the find method which is O(n)
     * @param name getting the name for the device to be removed
     */
    public void remove(String name)
    {
        if(name.isEmpty())
        {
            System.out.println("Invalid input!");
            return;
        }
        DeviceObject device = find(name);
        if(removeHelper(device))
            System.out.println(device.getCategory() + ", " + device.getName() + ", " + device.getPrice() + "$, " + device.getQuantity() + " removed...");
        else
            System.out.println("Device could not be removed!");
    }

    /**
     * This method is a helper method for the remove method,
     * Complexity: O(n) because it iterates through the deviceList which has 5 categories & then through the devices in the category which is O(n)
     * @param removedDevice getting the device to be removed
     * @return true if the device is removed, false otherwise
     */
    private boolean removeHelper(DeviceObject removedDevice) 
    {
        if(removedDevice == null)
            return false;
        else
        {
            for(ArrayList<DeviceObject> list : deviceList) 
            {
                if(list.get(0).getCategory().equals(removedDevice.getCategory()))
                {
                    for(DeviceObject device : list)
                    {
                        if(device.equals(removedDevice))
                        {
                            list.remove(device);
                            return true;
                        }
                    }
                }
            }
            return false;
        }
    }

    /**
     * This method is used to update the details of a device,
     * Complexity: O(n) because it calls the updateHelper method which is O(1) & the find method which is O(n)
     * @param name getting the name of the device to be updated
     * @param price getting the new price for the device
     * @param quantity getting the new quantity for the device
     */
    public void update(String name, double price, int quantity, boolean bprice, boolean bquantity)
    {
        if(name.isEmpty())
        {
            System.out.println("Invalid input!");
            return;
        }
        DeviceObject device = find(name);
        if(updateHelper(device, price, quantity, bprice, bquantity))
        {
            if(price > 0 && quantity > 0)
                System.out.println(device.getName() + " details updated: Price - " + price + ", " + "Quantity - " + quantity);
            else if(quantity < 0 && price > 0)
                System.out.println(device.getName() + " price updated: " + price + "$");
            else if(price < 0 && quantity > 0)
                System.out.println(device.getName() + " quantity updated: " + quantity);
            else 
                System.out.println("No changes made!"); 
        }
        else
            System.out.println("Device could not be updated!");
    }

    /**
     * This method is a helper method for the update method,
     * Complexity: O(1) because it is a constant time operation
     * @param updatedDevice getting the device to be updated
     * @param price getting the new price for the device 
     * @param quantity getting the new quantity for the device
     * @return true if the device is updated, false otherwise
     */
    private boolean updateHelper(DeviceObject updatedDevice, double price, int quantity, boolean bprice, boolean bquantity)
    {
        if(updatedDevice == null)
            return false;
        else 
        {
            if(bprice && bquantity)
            {
                if(price > 0)
                    updatedDevice.setPrice(price);
                if(quantity > 0)
                    updatedDevice.setQuantity(quantity);
                return true;
            }
            return false;
        }
    }

    /**
     * This method is used to restock a device,
     * Complexity: O(n) because it calls the restockHelper method which is O(1) & the find method which is O(n)
     * @param name getting the name of the device to be restocked
     * @param quantity getting the quantity to be restocked
     * @param choice getting the choice of restocking (Add/Remove)
     */
    public void restock(String name, int quantity, String choice)
    {
        if(name.isEmpty() || quantity <= 0)
        {
            System.out.println("Invalid input!");
            return;
        }
        DeviceObject device = find(name);
        if(restockHelper(device,quantity,choice))
            System.out.println(device.getName() + " restocked. New quantity: " + device.getQuantity());
        else
            System.out.println("Restock failed!");
    }

    /**
     * This method is a helper method for the restock method,
     * Complexity: O(1) because it is a constant time operation
     * @param device getting the device to be restocked
     * @param quantity getting the quantity to be restocked
     * @param selection getting the choice of restocking (Add/Remove)
     * @return true if the device is restocked, false otherwise
     */
    private boolean restockHelper(DeviceObject device, int quantity, String selection)
    {
        if(quantity < 0)
            return false;
        if(device == null)
            return false;
        if(selection.equals("Add"))
        {
            device.setQuantity(device.getQuantity() + quantity);
            return true;
        }
        else if(selection.equals("Remove"))
        {
            device.setQuantity(device.getQuantity() - quantity);
            return true;
        }
        else
            return false;
    }

    /**
     * This method is used to list all the devices in the inventory,
     * Complexity: O(n) because it iterates through the deviceList which has 5 categories & then through the devices in the category which is O(n),
     * O(5n) = O(n)
     */
    public void list()
    {
        System.out.println("Device List:");
        int number = 1;
        for(ArrayList<DeviceObject> list : deviceList) // 5 categories  
        {
            for(DeviceObject device : list) // n devices
            {
                System.out.println(number + ". Category: " + device.getCategory() + ", " + "Name: " + device.getName() + ", " + "Price: " + device.getPrice() + "$, " + "Quantity: " + device.getQuantity());
                number++;
            }
        }
    }
    
    /**
     * This method is used to find the cheapest device in the inventory,
     * Complexity: O(n) because it iterates through the deviceList which has 5 categories & then through the devices in the category which is O(n),
     * O(5n) = O(n)
     */
    public void findCheapest()
    {
        if(deviceList.isEmpty())
        {
            System.out.println("No devices found!");
            return;
        }
        else 
        {
            DeviceObject cheapest = null;

            for(ArrayList<DeviceObject> list : deviceList) // 5 categories
            {
                for(DeviceObject device : list) // n devices
                {
                    if(cheapest == null)
                        cheapest = device;
                    else if(device.getPrice() < cheapest.getPrice())
                        cheapest = device;
                }
            }
            System.out.println("The cheapest device is: ");
            System.out.println("Category: " + cheapest.getCategory() + ", Name: " + cheapest.getName() + ", Price: " + cheapest.getPrice() + "$, Quantity: " + cheapest.getQuantity());
        }
    }

    /**
     * This method is used to sort the devices by price,
     * Complexity: O(n^2) because it iterates all the devices in the inventory which is O(n) & then compares the prices of the devices which is O(n^2)
     */
    public void sortByPrice()
    {
        if(deviceList.isEmpty())
        {
            System.out.println("No devices found!");
            return;
        }
        else 
        {
            // O(5n) = O(n)
            ArrayList<DeviceObject> sortedList = new ArrayList<DeviceObject>();
            for(ArrayList<DeviceObject> list : deviceList) // 5 categories
            {
                for(DeviceObject device : list) // n devices
                {
                    sortedList.add(device); 
                }
            }

            // O(n * (n-1) / 2) = O(n^2)
            for(int i = 0; i < sortedList.size(); i++)
            {
                for(int j = 0; j < i; j++)
                {
                    if(sortedList.get(i).getPrice() < sortedList.get(j).getPrice())
                    {
                        DeviceObject temp = sortedList.get(i);
                        sortedList.set(i, sortedList.get(j));
                        sortedList.set(j, temp);
                    }
                }
            }
            // O(n)
            System.out.println("Devices sorted by price: ");
            for(int i = 0; i < sortedList.size(); i++)
            {
                System.out.println(i+1 + ". Category: " + sortedList.get(i).getCategory() + ", " + "Name: " + sortedList.get(i).getName() + ", " + "Price: " + sortedList.get(i).getPrice() + ", " + "Quantity: " + sortedList.get(i).getQuantity());
            }
        }
    }

    /**
     * This method is used to calculate the total value of the inventory,
     * Complexity: O(n) because it iterates through the deviceList which has 5 categories and then through the devices in the category which is O(n),
     * O(5n) = O(n)
     * @return the total value of the inventory
     */
    public double totalValue()
    {
        double total = 0.0;

        if(!deviceList.isEmpty())
        {
            for(ArrayList<DeviceObject> list : deviceList)
            {
                for(DeviceObject device : list)
                {
                    total += (device.getPrice() * device.getQuantity());
                }
            }
        }

        System.out.println("Total inventory value: " + total);
        return total;
    }

    /**
     * This method is used to export the inventory to a file,
     * Complexity: O(n) because it iterates through the deviceList which has 5 categories and then through the devices in the category which is O(n),
     * O(5n) = O(n)
     */
    public void export()
    {
        try
        {
            File file = new File("report.txt");
            FileWriter writer = new FileWriter(file);
            LocalDate date = LocalDate.now();
            DateTimeFormatter formatter = DateTimeFormatter.ofPattern("dd/MM/yyyy");
            String currentDate = date.format(formatter);
            
            writer.append("Electronics Shop Inventory Report\n");
            writer.append("Generated on: " + currentDate + "\n");
            writer.append("\n");

            writer.append("---------------------------------------\n");
            writer.append("| No. | Category | Name | Price | Quantity |\n");
            writer.append("---------------------------------------\n");

            int size = 0;
            for(int i = 0; i < deviceList.size(); i++) // 5 categories
            {
                for(int j = 0; j < deviceList.get(i).size(); j++) // n devices
                {
                    writer.append("| " + (i+1) + " | " + deviceList.get(i).get(j).getCategory() + " | " + deviceList.get(i).get(j).getName() + " | $" + deviceList.get(i).get(j).getPrice() + " | " + deviceList.get(i).get(j).getQuantity() + " |\n");
                    size++;
                }
            }
            writer.append("---------------------------------------\n\n");

            writer.append("Summary:\n");
            writer.append("- Total number of devices: " + size + "\n");
            writer.append("- Total Inventory value: " + totalValue() + "\n\n");
            writer.append("End of Report\n");
            writer.close();

            System.out.println("Report exported to report.txt");

        }
        catch(Exception e)
        {
            System.out.println("Error while writing to file!");
            return;
        }
    }

    /**
     * This method is used to create a new device object according to the category,
     * Complexity: O(1)
     * @param category getting the category of the device
     * @param name getting the name of the device
     * @param price getting the price of the device 
     * @param quantity getting the quantity of the device
     * @return the new device object according to the category & other details
     */
    private DeviceObject get(String category, String name, double price, int quantity)
    {
        switch (category) {
            case "Mouse":
                return new Mouse(category, name, price, quantity);
            case "Headphone":
                return new Headphone(category, name, price, quantity);
            case "Laptop":
                return new Laptop(category, name, price, quantity);
            case "Smartphone":
                return new Smartphone(category, name, price, quantity);
            case "Television":
                return new Television(category, name, price, quantity);
            default:
                return null;
        }
    }

    /**
     * This method is used to find a device in the inventory,
     * Complexity: O(n) because it iterates through the deviceList which has 5 categories and then through the devices in the category which is O(n),
     * O(5n) = O(n)
     * @param name getting the name of the device to be found
     * @return the device if found, null otherwise
     */
    private DeviceObject find(String name)
    {
        for(ArrayList<DeviceObject> list : deviceList)
        {
            for(DeviceObject device : list)
            {
                if(device.getName().equals(name))
                {
                    return device;
                }
            }
        }
        return null;
    }
}
