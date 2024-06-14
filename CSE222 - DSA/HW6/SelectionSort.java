public class SelectionSort extends SortAlgorithm {

	public SelectionSort(int input_array[]) {
		super(input_array);
	}

    @Override
    public void sort() {
        // fill this method
        if(arr == null || arr.length == 0) // Base condition for the array
            return;
            
        int size = arr.length;

        for(int i = 0; i < size-1; i++) // Iterating through the array 
        {
            int index_of_min = i;   // Getting the index of an element as a min element

            for(int j = i+1; j < size; j++) // Iterating from index of min + 1 to the last element
            {
                comparison_counter++;
                
                if(arr[j] < arr[index_of_min]) // Checking if the iterated element is smaller than the min element
                {
                    index_of_min = j; // Changing the index of the min element
                }
            }
            
            swap(i, index_of_min);  // After iterating all the elements after the min indexed element, we swap the min element with i (outer iteration)
        }
    }

    @Override
    public void print() {
    	System.out.print("Selection Sort\t=>\t");
    	super.print();
    }
}
