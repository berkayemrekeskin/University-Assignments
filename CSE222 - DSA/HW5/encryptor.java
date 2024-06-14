import java.util.Map;

public class encryptor {
	private Map<Character, Map<Character, Character>> map;
	private String key;
	private String keystream = "";
	private String plain_text;
	private String cipher_text = "";
	
	/**
	 * This constructor initializes the "map", "key" and "plain_text" variables.
	 * @param _map map
	 * @param _key key
	 * @param text plain text
	 */
	public encryptor(Map<Character, Map<Character, Character>> _map, String _key, String text) {
		this.key = _key;
		this.map = _map;
		this.plain_text = text;
	}
	
	/**
	 * This method generates the keystream & cipher text.
	 */
	public void encrypt() {
		// do not edit this method
		generate_keystream();
		generate_cipher_text();
	}
	
	/**
	 * This method generates the keystream.
	 */
	private void generate_keystream() {

		int len_of_plain_text = plain_text.length(); // Length of the plain text
		int len_of_key = key.length(); // Length of the key
		StringBuilder str = new StringBuilder(); // StringBuilder to store the keystream

		/*Cases given in the pdf */

		if(len_of_plain_text < len_of_key) // Adding the key chars to the keystream until the length of the plain text
		{
			for(int i = 0; i < len_of_plain_text; i++)
			{
				str.append(key.charAt(i));
			}
		}
		else if(len_of_plain_text > len_of_key) // Circularly adding the key chars to the keystream
		{
			int j = 0;
			for(int i = 0; i < len_of_plain_text; i++)
			{
				if(j == len_of_key)	// If the key is finished, start from the beginning
					j = 0;
				str.append(key.charAt(j));
				j++;
			}
		}
		else // If the lengths are equal, just add the whole key to the keystream
		{
			str.append(key);
		}

		this.keystream = str.toString();
	}

	/**
	 * This method generates the cipher text.
	 */
	private void generate_cipher_text() {

		int len_of_plain_text = plain_text.length(); // Length of the plain text
		int len_of_keystream = keystream.length(); // Length of the keystream
		StringBuilder str = new StringBuilder(); // StringBuilder to store the cipher text

		/*Step by Step Algorithm: 
		 * 1. Get the inner map of the character in the plain text (Select the row)
		 * 2. Get the character in the inner map with the character in the keystream (Select the column)
		 * 3. Append the character to the cipher text (Get the element and append it)
		 * 4. Repeat until the end of the plain text or the keystream (Repeat)
		 */

		for(int i = 0, j = 0; i < len_of_plain_text && j < len_of_keystream; i++, j++)
		{
			Map<Character, Character> innerMap = map.get(this.plain_text.charAt(i));
			Character ch = innerMap.get(keystream.charAt(j));
			str.append(ch);
		}

		this.cipher_text = str.toString();
		
	}
	
	/**
	 * This method returns the keystream.
	 * @return keystream
	 */
	public String get_keystream() {
		return keystream;
	}
	
	/**
	 * This method returns the cipher text.
	 * @return cipher text
	 */
	public String get_cipher_text() {
		return cipher_text;
	}
}
