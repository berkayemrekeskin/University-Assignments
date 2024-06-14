import java.util.Scanner;

/**
 * Main class is the main function of the program
 * It holds the inventory and temporary inputs
 * Functions are used to check the inputs of the user in this class
 */
public class Main {

    private static String category;
    private static String name;
    private static String selection;
    private static double price;
    private static int quantity;
    private static Inventory inventory;
    private static boolean bprice = true;
    private static boolean bquantity = true;

    /**
     * Main function of the program
     * Complexity depends on the user because i have an infinite loop until user gives input 0, O(1) per iteration
     * @param args 
     */
    public static void main(String[] args)
    {
        inventory = new Inventory();    
        Scanner scanner = new Scanner(System.in); 
        int choice;

        System.out.println("Welcome to the Electronics Inventory Management System!");

        while(true)
        {
            try
            {
                menu();
                choice = scanner.nextInt(); 
                switch (choice)
                {
                    case 1:
                        if(checkAdd(scanner))
                            inventory.add(category,name,price,quantity);
                        break;
                    case 2:
                        if (checkRemove(scanner)) 
                            inventory.remove(name);
                        break;
                    case 3:
                        if(checkUpdate(scanner))
                            inventory.update(name,price,quantity,bprice,bquantity);
                        break;
                    case 4:
                        inventory.list();
                        break;
                    case 5:
                        inventory.findCheapest();
                        break;
                    case 6:
                        inventory.sortByPrice();
                        break;
                    case 7:
                        inventory.totalValue();
                        break;
                    case 8:
                        if(checkRestock(scanner))
                            inventory.restock(name,quantity,selection);
                        break;
                    case 9:
                        inventory.export();
                        break;
                    case 0:
                        scanner.close();
                        return;
                }
            }
            catch(Exception e)
            { 
                System.out.println("Input is not valid.");
                return;
            }
        }
    }

    /**
     * Just prints the menu of program
     * Complexity = O(1)
     */
    public static void menu()
    {
        System.out.println();
        System.out.println("Please select an option: ");
        System.out.println("1. Add a new device");
        System.out.println("2. Remove a device");
        System.out.println("3. Update device details");
        System.out.println("4. List all devices");
        System.out.println("5. Find cheapest device");
        System.out.println("6. Sort devices by price");
        System.out.println("7. Calculate total inventory value");
        System.out.println("8. Restock a device");
        System.out.println("9. Export inventory report");
        System.out.println("0. Exit");
    }

    /**
     * Checks if the add function's inputs are correct
     * Complexity = O(1)
     * @param input sending the scanner inside the function to get input
     * @return true if the conversions are flawless, false otherwise
     */
    public static boolean checkAdd(Scanner input)
    {
        try
        {
            input.nextLine();
            System.out.println("Enter the category of the device: ");
            category = input.nextLine();
            System.out.println("Enter the name of the device: ");
            name = input.nextLine();
            System.out.println("Enter the price of the device: ");
            price = input.nextDouble();
            System.out.println("Enter the quantity of the device: ");
            quantity = input.nextInt();

        }
        catch(Exception e)
        {
            return false;
        }
        return true;
    }

    /**
     * Checks if the remove function's inputs are correct
     * Complexity = O(1)
     * @param input sending the scanner inside the function to get input
     * @return true if the conversions are flawless, false otherwise
     */
    public static boolean checkRemove(Scanner input)
    {
        try
        {
            input.nextLine();
            System.out.println("Enter the name of the device you want to remove: ");
            name = input.nextLine();
        }
        catch(Exception e)
        {
            return false;
        }
        return true;
    }

    /**
     * Checks if the update function's inputs are correct
     * Complexity = O(1)
     * @param input sending the scanner inside the function to get input
     * @return true if the conversions are flawless, false otherwise
     */
    public static boolean checkUpdate(Scanner input)
    {
        String sprice;
        String squantity;
        
        try
        {
            input.nextLine();
            System.out.println("Enter the name of the device to update: ");
            name = input.nextLine();
            System.out.println("Enter new price (leave blank to keep current price): ");
            sprice = input.nextLine();
            System.out.println("Enter new quantity (leave blank to keep current price): ");
            squantity = input.nextLine();
            
            if(!sprice.isEmpty())
            {
                if(!checkPrice(sprice))
                    bprice = false;
            }
            else
            {
                price = -1;
                bprice = true;
            }
            if(!squantity.isEmpty())
            {
                if(!checkQuantity(squantity))
                    bquantity = false;
            }
            else
            {
                quantity = -1;  
                bquantity = true;
            }

        }
        catch(Exception e)
        {
            return false;
        }
        return true;
    }
    /**
     * Checks if the price is a valid double
     * @param sprice the string that will be converted to double
     * @return true if the conversion is flawless, false otherwise
     */
    private static boolean checkPrice(String sprice) {
        try
        {
            price = Double.parseDouble(sprice);
        }
        catch(Exception e)
        {
            return false;
        }
        return true;
    }

    /**
     * Checks if the quantity is a valid integer
     * @param squantity the string that will be converted to integer
     * @return true if the conversion is flawless, false otherwise
     */
    private static boolean checkQuantity(String squantity) {
        try
        {
            quantity = Integer.parseInt(squantity);
        }
        catch(Exception e)
        {
            return false;
        }
        return true;
    }
    /**
     * Checks if the restock function's inputs are correct
     * Complexity = O(1)
     * @param input sending the scanner inside the function to get input
     * @return true if the conversions are flawless, false otherwise
     */
    public static boolean checkRestock(Scanner input)
    {
        try
        {
            input.nextLine();
            System.out.println("Enter the name of the device to restock:");
                name = input.nextLine();
            System.out.println("Do you want to add or remove stock? (Add / Remove)");
                selection = input.nextLine();
            System.out.println("Enter the quantity: ");
                quantity = input.nextInt();
            

        }
        catch(Exception e)
        {
            return false;
        }
        return true;
    }
}
