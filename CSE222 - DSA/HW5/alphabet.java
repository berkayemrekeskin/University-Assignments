import java.util.HashMap;
import java.util.Map;
import java.util.LinkedHashSet;
import java.util.Set;
import java.util.Iterator;

public class alphabet {
	private Set<Character> english_alphabet = new LinkedHashSet<Character>();
	private Map<Character, Map<Character, Character>> map = new HashMap<Character,  Map<Character, Character>>();
	
	/**
	 * This constructor fills the "english_alphabet" set with the English alphabet and fills the "map" map with the Vigenere cipher table.
	 */
	public alphabet() {
		// do not edit this method
		fill_english_alphabet();
		fill_map();
	}

	/**
	 * This method fills the "english_alphabet" set with the English alphabet.
	 */
	private void fill_english_alphabet() {
		// do not edit this method
		for(char c : "ABCDEFGHIJKLMNOPQRSTUVWXYZ".toCharArray()) {
		    english_alphabet.add(c);
		}
	}

	/**
	 * This method fills the "map" map with the Vigenere cipher table.
	 */
	private void fill_map() {
		// You must use the "english_alphabet" variable in this method, to fill the "map" variable.
		// You can define 1 or 2 iterators to iterate through the set items.

		/* I used 2 iterators, both are for the keys of the maps but I generated the table elements with those keys */

		// Creating 2 iterators
		Iterator<Character> it1 = english_alphabet.iterator();
		Iterator<Character> it2 = english_alphabet.iterator();
		
		while(it1.hasNext()) {
			char c1 = it1.next(); // Getting the key with first iterator
			Map<Character, Character> inner_map = new HashMap<Character, Character>(); // Creating a map for the internal map
			while(it2.hasNext()) {
				char c2 = it2.next(); // Getting the key with second iterator
				char val = (char) (((c1 + c2) % 26) + 'A'); // Calculating the value of the key (Circular shift by adding the ASCII values of the keys and mod 26)
				inner_map.put(c2, val); // Putting the key and value to the internal map
			}
			map.put(c1, inner_map);	// Putting the key and the internal map to the main map
			it2 = english_alphabet.iterator(); // Resetting the second iterator
		}

	}

	/**
	 * This method prints the Vigenere cipher table.
	 */
	public void print_map() {
		// do not edit this method
		System.out.println("*** Viegenere Cipher ***\n\n");
		System.out.println("    " + english_alphabet);
		System.out.print("    ------------------------------------------------------------------------------");
		for(Character k: map.keySet()) {
			System.out.print("\n" + k + " | ");
			System.out.print(map.get(k).values());
		}
		System.out.println("\n");

	}

	/**
	 * This method returns the map.
	 * @return the map
	 */
	public Map<Character, Map<Character,Character>> get_map() {
		return map;
	}
}