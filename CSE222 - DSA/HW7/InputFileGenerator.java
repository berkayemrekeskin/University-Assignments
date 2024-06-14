import java.io.FileWriter;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class InputFileGenerator {

    private static List<String> inputs = new ArrayList<>(); // ArrayList to store the commands
    private static String[] commands = {"ADD", "REMOVE", "SEARCH", "UPDATE"}; // Commands
    private static String filename; // Filename

    /**
     * Generate a command based on the index of the command and the size
     * In this function we generate a random symbol and random values for price, volume and market cap
     * @param index_of_command index of the command
     * @param size size of the commands
     */
    public static void generate_command(int index_of_command, int size) 
    {
        int i = 0;
        while(i <= size)
        {   
            // Create Symbol
            StringBuilder symbol_builder = new StringBuilder();
            Random rand = new Random();
            symbol_builder.append((char)('A' + rand.nextInt(25)));
            symbol_builder.append((char)('A' + rand.nextInt(25)));
            symbol_builder.append((char)('A' + rand.nextInt(25)));
            String symbol = symbol_builder.toString();

            // Create Command
            StringBuilder command_builder = new StringBuilder();
            double temp_price = rand.nextDouble();
            long temp_volume = rand.nextLong();
            long temp_market_cap = rand.nextLong();

            switch (index_of_command) {
                case 0: command_builder.append(commands[index_of_command] + " " + symbol + " " + temp_price + " " + temp_volume + " " + temp_market_cap); break;
                case 1: command_builder.append(commands[index_of_command] + " " + symbol); break;
                case 2: command_builder.append(commands[index_of_command] + " " + symbol); break;
                case 3: command_builder.append(commands[index_of_command] + " " + symbol + " empty " + temp_price + " " + temp_volume + " " + temp_market_cap); break;
                default:
                    break;
            }
            
            String command = command_builder.toString();
            
            // Append the command to ArrayList
            if(!inputs.contains(command))
                inputs.add(command);
            i++;
        }
    }

    /**
     * Print the commands to the file
     * We shuffle the commands before writing to the file
     */
    public static void print_to_file()
    {
        try(FileWriter writer = new FileWriter(filename)) 
        {
            while(inputs.size() > 0)
            {
                int index = new Random().nextInt(inputs.size()); // Randomly select a command
                String command = inputs.get(index); // Get the command
                writer.write(command + "\n"); // Write the command to the file
                inputs.remove(index); // Remove the command from the ArrayList
            }
            writer.close();
        }
        catch(Exception e)
        {
            System.out.println(e.getMessage());
        }        

    }

    public static void main(String[] args)
    {
        // Check if the arguments are correct
        if(args.length < 2)
        {
            System.out.println("Usage: java InputFileGenerator <filename> <opeartion1> <size1> <operation2> <size2> ... <operationN> <sizeN>");
            return;
        }
        
        // Get the filename 
        filename = args[0];

        // Generate the commands based on the arguments
        for(int i = 1; i < args.length; i += 2)
        {
            String operation = args[i];
            int size = Integer.parseInt(args[i + 1]);
            switch(operation) {
            case "ADD":
                generate_command(0, size);
                break;
            case "REMOVE":
                generate_command(1, size);
                break;
            case "SEARCH":
                generate_command(2, size);
                break;
            case "UPDATE":
                generate_command(3, size);
                break;
            default:
                break;
            }
        }
        
        // Print the commands to the file
        print_to_file();        
    }
}
