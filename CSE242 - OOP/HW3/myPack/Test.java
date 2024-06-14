package myPack;
import java.util.Scanner;
import java.io.FileWriter;

/**
 * This class represents a test program for JavaSet and JavaVector classes.
 * It allows the user to interactively add and remove elements from a set and a vector,
 * and then displays the elements using iterators. Also writes the elements of the set and vector to a text file.
 */
public class Test {
    /**
     * This is the main method which makes use of the JavaSet and JavaVector classes.
     * @param args Unused.
     * @return Nothing.
     * @exception Exception On input error.
     * @see Exception
     */
    public static void main(String[] args) {
        try
        {
            int cap1, cap2;
            Scanner scanner = new Scanner(System.in);
            // Getting the capacities of the set and vector from the user
            // I already check the capacities in the constructors of the set and vector but
            // I also check them here just in case for the pdf.
            System.out.printf("Enter Set Capacity: ");
            cap1 = scanner.nextInt();
            if(cap1 <= 0)
            {
                scanner.close();
                throw new ArithmeticException("Capacity cannot be or lower than 0");
            }
            System.out.printf("Enter Vector Capacity: ");
            cap2 = scanner.nextInt();
            if(cap2 <= 0)
            {
                scanner.close();
                throw new ArithmeticException("Capacity cannot be or lower than 0");
            }
            // Creating a set and a vector with the given capacities
            JavaContainer<Integer> set1 = new JavaSet<Integer>(cap1);
            JavaContainer<Integer> vector1 = new JavaVector<Integer>(cap2);
            
            // Adding elements to the set and vector
            System.out.printf("Add Set Elements (-1 to stop): ");
            int element;
            element = scanner.nextInt();
            while(element != -1)
            {
                set1.add(element);
                System.out.printf("Set size: %d\n", set1.size());
                System.out.printf("Add Set Elements (-1 to stop): ");
                element = scanner.nextInt();
            }
            System.out.printf("Add Vector Elements (-1 to stop): ");
            element = scanner.nextInt();
            while(element != -1)
            {
                vector1.add(element);
                System.out.printf("Vector size: %d\n", vector1.size());
                System.out.printf("Add Vector Elements (-1 to stop): ");
                element = scanner.nextInt();
            }

            // Removing elements from the set and vector
            System.out.printf("Remove Set Elements (-1 to stop): ");
            element = scanner.nextInt();
            while(element != -1)
            {
                set1.remove(element);
                System.out.printf("Set size: %d\n", set1.size());
                System.out.printf("Remove Set Elements (-1 to stop): ");
                element = scanner.nextInt();
            }
            System.out.printf("Remove Vector Elements (-1 to stop): ");
            element = scanner.nextInt();
            while(element != -1)
            {
                vector1.remove(element);
                System.out.printf("Vector size: %d\n", vector1.size());
                System.out.printf("Remove Vector Elements (-1 to stop): ");
                element = scanner.nextInt();
            }
            System.out.println();

            // Displaying the elements of the set and vector using iterators
            var iter = set1.getIterator();
            System.out.println("Set Elements using Iterator: ");
            while(iter.hasNext())
            {
                System.out.printf("%d ", iter.next());
            }
            System.out.println();
            iter = vector1.getIterator();
            System.out.println("Vector Elements using Iterator: ");
            while(iter.hasNext())
            {
                System.out.printf("%d ", iter.next());
            }
            System.out.println();

            // Using equals method to compare the set and vector (Cannot be equal because they are not same type)
            if(set1.equals(vector1))
            {
                System.out.println("Set and Vector are equal");
            }
            else
            {
                System.out.println("Set and Vector are not equal");
            }

            // In the pdf file, it says write some sets to text files, but I'm not sure what that means.
            // I'm assuming it means write the elements of the sets to text files. So i wrote the elements
            // of the sets & vectors to output.txt.

            // Using toString method to write the elements of the set and vector to a text file
            FileWriter writer = new FileWriter("output.txt");
            writer.write("Set Elements: ");
            writer.write(set1.toString());
            writer.write("\nVector Elements: ");
            writer.write(vector1.toString());
            writer.close();
            scanner.close();
        }
        catch(Exception e)
        {
            System.out.println(e.getMessage());
        }
        finally
        {
            System.out.println("Program Terminated");
        }
    }
}
