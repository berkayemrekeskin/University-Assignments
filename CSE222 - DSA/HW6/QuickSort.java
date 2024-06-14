public class QuickSort extends SortAlgorithm {

	public QuickSort(int input_array[]) {
		super(input_array);
	}
	
    private int partition(int first, int last){
        // fill this method
        int pivot = arr[last]; // Selecting the pivot as the last element
        int i = first - 1;  // Index of smaller element
            
        for(int j = first; j < last; j++) // From the first to the last - 1 element
        {
            comparison_counter++;
            if(arr[j] <= pivot) // If current is smaller or equal than pivot
            {
                i++;
                swap(i,j);  // Swapping the elements
            }
        }

        swap(i+1, last); // Swapping the pivot with the last incremented index.
        return i+1; // Returning the index of the pivot

    }

    private void sort(int first, int last){
        // fill this method
        if(first < last) // Base case for the recursive function. (While the first index is smaller than the last index)
        {
            int index_of_pivot = partition(first, last); // Getting the index of the pivot
            sort(first,index_of_pivot-1); // Calling this function from first to index of pivot
            sort(index_of_pivot+1, last); // Calling this function from index of pivot to last
        }

    }

    @Override
    public void sort() {

        if(arr == null || arr.length == 0) // Base condition for the array
            return;

        int size = arr.length;
    	sort(0, size-1); // Sending first and last index of the array
    }

    @Override
    public void print() {
    	System.out.print("Quick Sort\t=>\t");
    	super.print();
    }
}
