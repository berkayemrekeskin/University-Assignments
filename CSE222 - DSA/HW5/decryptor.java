import java.util.Map;
import java.util.Iterator;

public class decryptor {
	private Map<Character, Map<Character, Character>> map;
	private String key;
	private String keystream = "";
	private String plain_text = "";
	private String cipher_text;
	
	/**
	 * This constructor initializes the "map", "key" and "cipher_text" variables.
	 * @param _map map
	 * @param _key key
	 * @param text cipher text
	 */
	public decryptor(Map<Character, Map<Character, Character>> _map, String _key, String text) {
		this.map = _map;
		this.key = _key;
		this.cipher_text = text;
	}

	/**
	 * This method generates the keystream & plain text.
	 */
	public void decrypt() {
		// do not edit this method
		generate_keystream();
		generate_plain_text();
	}
	
	/**
	 * This method generates the keystream.
	 */
	private void generate_keystream() {

		int len_of_cipher_text = cipher_text.length(); // Length of the cipher text
		int len_of_key = key.length(); // Length of the key
		StringBuilder str = new StringBuilder(); // StringBuilder to store the keystream

		/* Cases given in the pdf */
		
		if(len_of_cipher_text < len_of_key) // Adding the key chars to the keystream until the length of the cipher text
		{
			for(int i = 0; i < len_of_cipher_text; i++)
			{
				str.append(key.charAt(i));
			}
		}
		else if(len_of_cipher_text > len_of_key) // Circularly adding the key chars to the keystream
		{
			int j = 0;
			for(int i = 0; i < len_of_cipher_text; i++)
			{
				if(j == len_of_key)	// If the key is finished, start from the beginning
					j = 0;
				str.append(key.charAt(j));
				j++;
			}
		}
		else // Appending the whole key to keystream
		{
			str.append(key);
		}

		this.keystream = str.toString();
	}
	
	/**
	 * This method generates the plain text.
	 */
	private void generate_plain_text() {
		// You must use map.get(x).keySet() with an iterator in this method
		
		int len_of_cipher_text = cipher_text.length(); // Length of the cipher text
		int len_of_keystream = keystream.length(); // Length of the keystream
		StringBuilder str = new StringBuilder(); // StringBuilder to store the plain text

		/*	Step by Step Algorithm:
		 * 1. Find the right column for the value.
		 * 2. Iterate through the rows and find the element in the table.
		 * 3. If the element is equal to the cipher text char, append the row to the plain text.
		 * 4. Repeat the steps for all the cipher text chars.
		 */

		for(int i = 0, j = 0; i < len_of_cipher_text && j < len_of_keystream; i++, j++)
		{
			Iterator<Character> colIterator = map.get(keystream.charAt(i)).keySet().iterator();	// Iterator for the columns
			Iterator<Character> rowIterator = map.keySet().iterator(); // Iterator for the rows
			
			while(colIterator.hasNext()) // Iterating through the columns
			{
				char column = colIterator.next(); // Getting the column
				if(column == keystream.charAt(i)) // Finding the column
				{
					while(rowIterator.hasNext()) // Iterating through the rows
					{
						char row = rowIterator.next(); // Getting the row
						char element = map.get(row).get(column); // Getting the element in the table
						if(element == cipher_text.charAt(j)) // If the element is equal to the cipher text char, append the row to the plain text
						{
							str.append(row);
						}
					}
				}
			}
		}

		this.plain_text = str.toString();

	}

	/*
	 * This method returns the keystream.
	 */
	public String get_keystream() {
		return keystream;
	}
	
	/*
	 * This method returns the plain text.
	 */
	public String get_plain_text() {
		return plain_text;
	}
}
