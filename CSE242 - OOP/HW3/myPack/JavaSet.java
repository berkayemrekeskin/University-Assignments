package myPack;
import java.util.Iterator;

/**
 * JavaSet class that implements the JavaContainer interface 
 * and contains methods for a set data structure.
 */

public class JavaSet<T> implements JavaContainer<T> {

    // FIELDS FOR THE SET

    private T[] data; // Array to store the elements
    private int size; // Number of elements in the set
    private int capacity; // Capacity of the set

    // CONSTRUCTORS FOR THE SET
    
    /**
     * Default constructor for the set.
     * Sets the capacity to 10.
     */
    public JavaSet() {
        this(10); // Default capacity is 10
    }

    /**
     * Parametirized constructor for the set.
     * @param capacity The capacity of the set.
     */
    @SuppressWarnings("unchecked")
    public JavaSet(int capacity) throws ArithmeticException {
        if (capacity <= 0) 
        {
            throw new ArithmeticException("Capacity cannot be or lower than 0");
        }
        data = (T[]) new Object[capacity]; // Create an array of type T with the given capacity
        this.capacity = capacity;
    }

    /**
     * Copy constructor for the set.
     * @param other The set to copy from.
     */
    @SuppressWarnings("unchecked")
    public JavaSet(JavaSet<T> other) {
        data = (T[]) new Object[other.capacity]; // Create a new array with the same capacity as the other set
        for (int i = 0; i < other.size; i++) {
            data[i] = other.data[i]; // Copy the elements from the other set to the new set
        }
        size = other.size;
        capacity = other.capacity;
    }

    // OVERRIDDEN METHODS FROM JAVA OBJECT CLASS

    /**
     * Overridden toString method for the set.
     */
    public String toString() {
        var result = "";
        for (int i = 0; i < size; i++) {
            result += data[i] + " "; // Append each element to the result string
        }
        return result;
    }
    /**
     * Overridden equals method for the set.
     * @param other The object to compare to.
     * @return True if the sets are equal, false otherwise.
     */
    public boolean equals(Object other) {
        if (other == null) 
        {
            return false;
        }
        if (!(other instanceof JavaSet)) 
        {
            return false;
        }
        @SuppressWarnings("unchecked")
        var otherSet = (JavaSet<T>) other;
        if (size != otherSet.size) {
            return false;
        }
        for (int i = 0; i < size; i++) {
            if (data[i] != otherSet.data[i]) {
                return false;
            }
        }
        return true;
    }

    // OVERRIDDEN METHODS FROM JAVA CONTAINER INTERFACE

    /**
     * Adds an element to the set.
     * @param value The element to add.
     * @throws ArithmeticException if the element is null.
     * @throws ArithmeticException if the element is already in the set.
     */
    public void add(T value) throws ArithmeticException {
        // Check if value is already in the set
        if (isIn(value)) {
            throw new ArithmeticException("Element is already in the data");
        }
        if (value == null) {
            throw new ArithmeticException("Element cannot be null");
        }
        if (size == capacity) {
            this.capacity *= 2; // Double the capacity
            @SuppressWarnings("unchecked")
            var temp = (T[]) new Object[capacity]; // Create a temporary set with the new capacity
            for (int i = 0; i < size; i++) {
                temp[i] = data[i]; // Copy the elements to the temporary set
            }
            temp[size++] = value; // Add the new value to the temporary set
            this.data = temp; // Replace the data array with the temporary set's data array
        } else {
            data[size++] = value; // Add the value to the set
        }
    }

    /**
     * Removes an element from the set.
     * @param value The element to remove.
     * @throws ArithmeticException if the element is not in the set.
     * @throws ArithmeticException if the set is empty.
     */
    public void remove(T value) throws ArithmeticException {
        if (!isIn(value)) {
            throw new ArithmeticException("Element is not in the data");
        }
        if (size == 0) {
            throw new ArithmeticException("Data is empty");
        }
        for (int i = 0; i < size; i++) 
        {
            if (this.data[i] == value) 
            {
                for (int j = i; j < size - 1; j++) 
                {
                    data[j] = data[j + 1]; // Shift the elements to the left to remove the value
                }
            }
        }
        size--; // Decrease the size of the set
    }

    public int size() {
        return size; // Return the number of elements in the set
    }

    // HELPER METHODS FOR THE SET

    /**
     * Checks if the given element is in the set.
     * @param element The element to check for.
     * @return True if the element is in the set, false otherwise.
     */
    public boolean isIn(T element) {
        for (int i = 0; i < size; i++) 
        {
            if (this.data[i] == element)
            {
                return true; // Check if the element is in the set
            }
        }
        return false;
    }

    // ITERATOR CLASS & METHODS FOR THE SET

    /**
     * Iterator class for the set.
     */
    public class SetIterator implements Iterator<T> {
        private int index;

        public SetIterator() {
            index = 0;
        }
        public boolean hasNext() {
            return index < size; // Check if there are more elements to iterate over
        }
        public T next() {
            return data[index++]; // Return the next element and move the index forward
        }
    }

    /**
     * Returns a new iterator for the set.
     * @return A new iterator for the set.
     */
    public Iterator<T> getIterator() {
        return new SetIterator(); // Return a new iterator for the set
    }
}
