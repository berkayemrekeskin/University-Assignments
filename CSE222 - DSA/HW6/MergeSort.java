public class MergeSort extends SortAlgorithm {
	
	public MergeSort(int input_array[]) {
		super(input_array);
	}
	
	private void merge(int[] left, int[] right, int[] array){
        // fill this method
        int len_of_left = left.length; // Getting the length of the left array
        int len_of_right = right.length; // Getting the length of the right array

        int i = 0, j = 0, k = 0;

        while(i < len_of_left && j < len_of_right) // Iterating through the arrays at the same time
        {
            comparison_counter++;

            if(left[i] < right[j]) // Comparing the arrays according to the indexes
                array[k++] = left[i++];
            else 
                array[k++] = right[j++];
        }
        
        // Adding the remaining elements in the splitted arrays.

        while(i < len_of_left) 
            array[k++] = left[i++];
        
        while(j < len_of_right)
            array[k++] = right[j++];

    }

    private void sort(int[] array){
        // fill this method
        if(array == null)
            return;

        int size = array.length; // Getting the length of the array

        if(size > 1)
        {
            int mid = size / 2; // Getting the middle index of array

            int[] left = new int[mid];  // Creating left array
            int[] right = new int[size - mid]; // Creating right array
    
            for(int i = 0; i < mid; i++)    // Inserting the elements from start to mid
                left[i] = array[i];
            for(int i = mid; i < size; i++) // Inserting the elements from mid to end
                right[i-mid] = array[i];
    
            sort(left); // Recalling the sort function for the left array
            sort(right); // Recalling the sort function for the right array
    
            merge(left, right, array); // Merging from the smallest array to the biggest array
        }
        
    }
    
    @Override
    public void sort() {
        
        if(arr == null || arr.length == 0) // Base condition for the array
            return;

        sort(arr); // Sending the arr to the private sort function
    }
    
    @Override
    public void print() {
    	System.out.print("Merge Sort\t=>\t");
    	super.print();
    }
}
