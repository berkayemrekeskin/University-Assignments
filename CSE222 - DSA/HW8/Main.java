import java.util.*;

public class Main {
    
    private static SocialNetwork network;
    public static void main(String[] args)
    {
        network = new SocialNetwork();
        int choice;
        while(true)
        {
            try 
            {
                System.out.println("===== Social Network Analysis Menu =====");
                System.out.println("1. Add a person");
                System.out.println("2. Remove a person");
                System.out.println("3. Add a friendship");
                System.out.println("4. Remove a friendship");
                System.out.println("5. Find shortest path");
                System.out.println("6. Suggest friends");
                System.out.println("7. Count clusters");
                System.out.println("8. Exit");
                System.out.print("Please select an option:");
                choice = Integer.parseInt(System.console().readLine());
    
                switch(choice)
                {
                    case 1:
                        System.out.print("Enter name: ");
                        String name = System.console().readLine();
                        System.out.print("Enter age: ");
                        int age = Integer.parseInt(System.console().readLine());
                        System.out.print("Enter hobbies (comma separated): ");
                        String[] hobbyArray = System.console().readLine().split(",");
                        List<String> hobbies = Arrays.asList(hobbyArray);
                        network.addPerson(name, age, hobbies);
                        break;
                    case 2:
                        System.out.print("Enter name: ");
                        name = System.console().readLine();
                        System.out.print("Enter age: ");
                        age = Integer.parseInt(System.console().readLine());
                        System.out.print("Enter timestamp: ");
                        String timestampString = System.console().readLine();
                        network.removePerson(name, age, timestampString);
                        break;
                    case 3:
                        System.out.print("Enter first name: ");
                        String first_name = System.console().readLine();
                        System.out.print("Enter first person's timestamp: ");
                        String first_timestamp = System.console().readLine();
                        System.out.print("Enter second name: ");
                        String second_name = System.console().readLine();
                        System.out.print("Enter second person's timestamp: ");
                        String second_timestamp = System.console().readLine();
                        network.addFriendship(first_name, first_timestamp, second_name, second_timestamp);
                        break;
                    case 4:
                        System.out.print("Enter first name: ");
                        first_name = System.console().readLine();
                        System.out.print("Enter first person's timestamp: ");
                        first_timestamp = System.console().readLine();
                        System.out.print("Enter second name: ");
                        second_name = System.console().readLine();
                        System.out.print("Enter second person's timestamp: ");
                        second_timestamp = System.console().readLine();
                        network.removeFriendship(first_name, first_timestamp, second_name, second_timestamp);
                        break;
                    case 5:
                        System.out.print("Enter first name: ");     
                        first_name = System.console().readLine();
                        System.out.print("Enter first person's timestamp: ");
                        first_timestamp = System.console().readLine();
                        System.out.print("Enter second name: ");
                        second_name = System.console().readLine();
                        System.out.print("Enter second person's timestamp: ");
                        second_timestamp = System.console().readLine();
                        network.findShortestPath(first_name, first_timestamp, second_name, second_timestamp);
                        break;
                    case 6:
                        System.out.print("Enter person's name: ");     
                        first_name = System.console().readLine();
                        System.out.print("Enter person's timestamp: ");
                        first_timestamp = System.console().readLine();
                        System.out.print("Enter maximum number of friends to suggest: ");
                        int maxFriends = Integer.parseInt(System.console().readLine());
                        network.suggestFriends( first_name, first_timestamp, maxFriends);
                        break;
                    case 7:
                        System.out.println("Counting clusters in the social network...");
                        List<List<Person>> clusters = new ArrayList<>();
                        int count = network.countClusters(clusters);
                        System.out.println("Number of clusters found: " + count);
                        for (int i = 0; i < clusters.size(); i++) {
                            System.out.println("Cluster " + (i + 1) + ": ");
                            for (Person p : clusters.get(i)) {
                                System.out.println(p.getName());
                            }
                        }
                        break;
                    case 8:
                        System.out.println("Goodbye!");
                        System.exit(0);
                        break;
                    default:
                        System.out.println("Invalid choice. Please try again.");
                        break;
                }
            }
            catch (Exception e)
            {
                System.out.println("Invalid input. Please try again.");
            }
        }
    }
}
