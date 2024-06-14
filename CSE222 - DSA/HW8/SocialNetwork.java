import java.util.*;

public class SocialNetwork {
    
    private Map<String, Person> people;
    private Map<Person, List<Person>> friendships;

    public SocialNetwork() {
        people = new HashMap<>();
        friendships = new HashMap<>();
    }

    /**
     * Add a person to the network
     * @param name 
     * @param age
     * @param hobbies
     */
    public void addPerson(String name, int age, List<String> hobbies)
    {
        if(people.containsKey(name)) // Check if the person is already in the network
        {
            System.out.println("This name is already in the list!");
            return;
        }
        // Create a new person object and add it to the people map and friendships graph
        Person person = new Person(name, age, hobbies);
        people.put(name, person);
        friendships.put(person, new ArrayList<>());
        System.out.println("Person added: " + person);
    }
    /**
     * Remove a person from the network
     * @param name
     * @param age
     * @param timestamp
     * @return
     */
    public Person removePerson(String name, int age, String timestamp)
    {
        Person person = people.get(name);
        // Check if the person exists in the network and the details match
        if(person == null)
        {
            System.out.println("Person not found.");
            return null;
        }
        if(person.getAge() != age)
        {
            System.out.println("Age does not match.");
            return null;
        }
        if(!person.gettimestamp().toString().equals(timestamp))
        {
            System.out.println("Timestamp does not match.");
            return null;
        }
        people.remove(name); // Remove the person from the people map and friendships graph
        for(List<Person> friends : friendships.values()) // We use adjacency list representation for the graph so we need to remove the person from all the adjacency lists
        {
            friends.remove(person);
        }
        System.out.println("Person removed: " + person.getName());
        return person;
    }
    /**
     * Add a friendship between two people
     * @param first_name
     * @param first_timestamp
     * @param second_name
     * @param second_timestamp
     */
    public void addFriendship(String first_name, String first_timestamp, String second_name, String second_timestamp)
    {
        Person first = people.get(first_name);
        Person second = people.get(second_name);
        // Check if the people exist in the network 
        if(first == null || second == null)
        {
            System.out.println("Person not found.");
            return;
        }
        // Check if the friendship already exists
        if(friendships.get(first).contains(second))
        {
            System.out.println("Friendship already exists.");
            return;
        }
        // Add the friendship to the adjacency lists of both people
        friendships.get(first).add(second);
        friendships.get(second).add(first);
        System.out.println("Friendship added between " + first_name + " and " + second_name);
    }
    /**
     * Remove a friendship between two people
     * @param first_name
     * @param first_timestamp
     * @param second_name
     * @param second_timestamp
     */
    public void removeFriendship(String first_name, String first_timestamp, String second_name, String second_timestamp)
    {
        Person first = people.get(first_name);
        Person second = people.get(second_name);
        // Check if the people exist in the network
        if(first == null || second == null)
        {
            System.out.println("Person not found.");
            return;
        }
        // Check if the friendship exists
        if(!friendships.get(first).contains(second))
        {
            System.out.println("Friendship not found.");
            return;
        }
        // Remove the friendship from the adjacency lists of both people
        friendships.get(first).remove(second);
        friendships.get(second).remove(first);
        System.out.println("Friendship removed between " + first_name + " and " + second_name);
    }

    /**
     * Find the shortest path between two people using BFS
     * @param first_name
     * @param first_timestamp
     * @param second_name
     * @param second_timestamp
     */
    public void findShortestPath(String first_name, String first_timestamp, String second_name, String second_timestamp)
    {
        Person first = people.get(first_name);
        Person second = people.get(second_name);
        // Check if the people exist in the network
        if(first == null || second == null)
        {
            System.out.println("Person not found.");
            return;
        }
        List<Person> path = shortestPath(first, second); // Find the shortest path
        if(path == null) // If no path is found, print a message and return
        {
            System.out.println("No path found between " + first_name + " and " + second_name);
            return;
        }
        // Print the shortest path
        System.out.println("Shortest path:");
        for(Person person : path)
        {
            System.out.print(person.getName());
            if(person != path.get(path.size() - 1))
            {
                System.out.print(" -> ");
            }
        }
        System.out.println();   
    }
    /**
     * BFS for finding the shortest path 
     * @param start
     * @param end
     * @return
     */
    private List<Person> shortestPath(Person start, Person end) {
        // Using BFS to find the shortest path
        Map<Person, Person> parent = new HashMap<>();
        Queue<Person> queue = new LinkedList<>();
        queue.add(start);
        parent.put(start, null);

        while (!queue.isEmpty()) {
            Person current = queue.poll();

            if (current == end) {   // If the end is reached, create the path and return
                return createPath(parent, start, end);
            }
            for (Person neighbor : friendships.get(current)) {  // Add all the neighbors of the current person to the queue
                if (!parent.containsKey(neighbor)) {
                    queue.add(neighbor); // Add the neighbor to the queue
                    parent.put(neighbor, current); // Add the current person as the parent of the neighbor (visited node)
                }
            }
        }
        return null;
    }

    /**
     * Create the path from start to end using the parent map
     * @param parent
     * @param start
     * @param end
     * @return
     */
    private List<Person> createPath(Map<Person, Person> parent, Person start, Person end) {
        // Create the path from start to end using the parent map
        List<Person> path = new ArrayList<>();
        Person current = end;

        while (current != null) {
            path.add(current);
            current = parent.get(current);
        }

        Collections.reverse(path);
        return path;
    }

    /**
     * Suggest friends for a person based on mutual friends and hobbies
     * Score = mutual friends + (0.5 * common hobbies)
     * @param name
     * @param timestamp
     * @param maxFriends
     */
    public void suggestFriends(String name, String timestamp, int maxFriends)
    {
        // I used a straightforward approach to suggest friends based on mutual friends and hobbies
        Map<Person,Double> suggestions = new HashMap<>(); // Map to store the suggestions with their scores
        Person person = people.get(name); // Get the person from the people map

        if(person == null)
        {
            System.out.println("Person not found.");
            return;
        }
        Set<Person> friends_of_person = new HashSet<>(friendships.get(person)); // Get the friends of the person
        for(Person random : people.values()) // Iterate over all the people in the network
        {
            if(random == person || friends_of_person.contains(random)) // Skip the person and the friends of the person
            {
                continue;
            }
            // Find the mutual friends and common hobbies and calculate the score
            List<Person> mutuals = new ArrayList<>(friendships.get(random));
            mutuals.retainAll(friends_of_person);
            int mutualFriends = mutuals.size();

            List<String> mutualHobbies = new ArrayList<>(random.getHobbies());
            mutualHobbies.retainAll(person.getHobbies());
            int mutualHobbiesCount = mutualHobbies.size();

            double totalScore = mutualFriends + (mutualHobbiesCount * 0.5);
            suggestions.put(random, totalScore); // Add the person to the suggestions map with the score
        }
        // Sort the suggestions based on the score
        List<Map.Entry<Person,Double>> sortedSuggestions = new ArrayList<>(suggestions.entrySet());
        sortedSuggestions.sort((a,b) -> Double.compare(b.getValue(), a.getValue()));

        // Print the suggestions
        System.out.println("Friend suggestions for " + name + ":");
        for(int i = 0; i < maxFriends && i < sortedSuggestions.size(); i++)
        {
            System.out.println(sortedSuggestions.get(i).getKey() + " (Score: " + sortedSuggestions.get(i).getValue() + ", " + getMutualFriendCount(person, sortedSuggestions.get(i).getKey()) + " mutual friends, " + getCommonHobbiesCount(person, sortedSuggestions.get(i).getKey()) + " common hobbies)");
        }
        
    }

    /**
     * Get the count of mutual friends between two people
     * @param person1
     * @param person2
     * @return
     */
    private int getMutualFriendCount(Person person1, Person person2)
    {
        List<Person> mutuals = new ArrayList<>(friendships.get(person1));
        mutuals.retainAll(friendships.get(person2));
        return mutuals.size();
    }

    /**
     * Get the count of common hobbies between two people
     * @param person1
     * @param person2
     * @return
     */
    private int getCommonHobbiesCount(Person person1, Person person2)
    {
        List<String> mutualHobbies = new ArrayList<>(person1.getHobbies());
        mutualHobbies.retainAll(person2.getHobbies());
        return mutualHobbies.size();
    }

    /**
     * Count the number of clusters in the social network using BFS
     * @param clusters
     * @return
     */
    public int countClusters(List<List<Person>> clusters) /* I added the people with no friends in the cluster also */
    {
        Set<Person> visited = new HashSet<>(); // Set to store the visited people
        int count = 0; // Count of clusters
        for(Person person : people.values()) // Iterate over all the people in the network
        {
            if(!visited.contains(person)) // If the person is not visited, start BFS from that person
            {
                List<Person> cluster = new ArrayList<>(); // List to store the people in the cluster
                bfs(person, visited, cluster); // BFS to find all the people in the cluster
                count++; // Increment the count of clusters
                clusters.add(cluster); // Add the cluster to the list of clusters
            }
        }
        return count; // Return the count of clusters
    }

    /**
     * BFS to find all the people in a cluster
     * @param start
     * @param visited
     * @param cluster
     */
    private void bfs(Person start, Set<Person> visited, List<Person> cluster) {
        // BFS to find all the people in a cluster
        Queue<Person> queue = new LinkedList<>();
        queue.add(start); // Add the start person to the queue
        visited.add(start); // Mark the start person as visited

        while (!queue.isEmpty()) {
            Person current = queue.poll(); // Get the current person
            cluster.add(current); // Add the current person to the cluster

            for (Person neighbor : friendships.get(current)) {

                if (!visited.contains(neighbor)) { // If the neighbor is not visited, add it to the queue and mark it as visited
                    queue.add(neighbor); 
                    visited.add(neighbor);
                }
            }
        }
    }
    
    
}
