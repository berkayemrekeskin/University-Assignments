public class BubbleSort extends SortAlgorithm {

	public BubbleSort(int input_array[]) {
		super(input_array);
	}
	
    @Override
    public void sort() {
    	// fill this method
        if(arr == null || arr.length == 0) // Base condition for the array
            return;
            
        int size = arr.length;  // Getting the size of the array

        for(int i = 0; i < size-1; i++) // Iterating until the end of the array
        {
            for(int j = 0; j < size-i-1; j++) // Iterating according to the first iteration
            {
                comparison_counter++;
                if(arr[j] > arr[j+1]) // Comparing duos in the inner iteration
                {
                    swap(j, j+1); // Swapping if the lower-indexed element is bigger than larger-indexed element
                }
            }
        }
    }
    
    @Override
    public void print() {
    	System.out.print("Bubble Sort\t=>\t");
    	super.print();
    }
}
