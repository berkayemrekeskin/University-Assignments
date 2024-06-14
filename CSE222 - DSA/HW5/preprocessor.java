public class preprocessor {
	private String initial_string;
	private String preprocessed_string;
	
	/**
	 * This constructor initializes the "initial_string" variable with the given string.
	 * @param str initial string
	 */
	public preprocessor(String str) {
		initial_string = str;
	}

	/**
	 * This method preprocesses the string.
	 */
	public void preprocess() {
		// do not edit this method
		capitalize();
		clean();
	}

	/**
	 * This method capitalizes the string.
	 */
	private void capitalize() {
		initial_string = initial_string.toUpperCase(); // Capitalizing the string
	}

	/**
	 * This method cleans the string.
	 */
	private void clean() {
		StringBuilder str = new StringBuilder(); // StringBuilder to store the cleaned string
		
		for(int i = 0; i < initial_string.length(); i++) {
			char c = initial_string.charAt(i);
			if(c >= 'A' && c <= 'Z') // If the char is a letter, append it to the cleaned string
				str.append(c);
		}
		preprocessed_string = str.toString(); // Setting the preprocessed string
	} 
	
	/**
	 * This method returns the preprocessed string.
	 * @return preprocessed string
	 */
	public String get_preprocessed_string() {
		return preprocessed_string;
	}
}