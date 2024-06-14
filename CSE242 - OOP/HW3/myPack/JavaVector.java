package myPack;
import java.util.Iterator;

/**
 * JavaVector class that implements the JavaContainer interface
 * and contains methods for a vector data structure.
 */

 public class JavaVector<T> implements JavaContainer<T> {

    // FIELDS FOR THE VECTOR
    
    private T[] data; // Array to store the elements
    private int size; // Number of elements in the vector
    private int capacity; // Maximum capacity of the vector

    // CONSTRUCTORS FOR THE VECTOR

    /**
     * Default constructor for the vector.
     * Sets the capacity to 10.
     */
    public JavaVector() {
        this(10); // Default capacity is 10
    }

    /**
     * Parametirized constructor for the vector.
     * @param capacity The capacity of the vector.
     */
    @SuppressWarnings("unchecked")
    public JavaVector(int capacity) throws ArithmeticException {
        if (capacity <= 0) {
            throw new ArithmeticException("Capacity cannot be 0 or lower");
        }
        data = (T[]) new Object[capacity]; // Create an array of type T with the given capacity
        this.capacity = capacity;
    }

    /**
     * Copy constructor for the vector.
     * @param other The vector to copy from.
     */
    @SuppressWarnings("unchecked")
    public JavaVector(JavaVector<T> other) {
        data = (T[]) new Object[other.capacity]; // Create a new array with the same capacity as the other vector
        this.capacity = other.capacity;
        this.size = other.size;
        for (int i = 0; i < size; i++) {
            this.data[i] = other.data[i]; // Copy the elements from the other vector to this vector
        }
    }

    /**
     * Overridden toString method for the vector.
     */
    @Override
    public String toString() {
        String temp = "";
        for (int i = 0; i < size; i++) {
            temp += this.data[i] + " "; // Concatenate the elements of the vector into a string
        }
        return temp;
    }

    /**
     * Overridden equals method for the vector.
     * @param other The vector to compare with.
     * @return True if the vectors are equal, false otherwise.
     */
    @Override
    public boolean equals(Object other) {
        if (other == null) {
            return false;
        }
        if (!(other instanceof JavaVector)) {
            return false;
        }
        @SuppressWarnings("unchecked")
        var otherVec = (JavaVector<T>) other;
        if (size != otherVec.size) {
            return false;
        }
        for (int i = 0; i < size; i++) {
            if (data[i] != otherVec.data[i]) {
                return false;
            }
        }
        return true;
    }

    // OVERRIDEN METHODS FROM THE JAVA CONTAINER INTERFACE

    /**
     * Adds an element to the vector.
     * @param value The element to add.
     * @throws ArithmeticException if the element is null.
     */
    @SuppressWarnings("unchecked")
    public void add(T value) throws ArithmeticException {
        if (value == null) {
            throw new ArithmeticException("Element cannot be null");
        }
        if (size == capacity) {
            this.capacity *= 2; // Double the capacity
            var temp = (T[]) new Object[capacity]; // Create a new array with the updated capacity
            for (int i = 0; i < size; i++) {
                temp[i] = this.data[i]; // Copy the elements to the new array
            }
            temp[size++] = value; // Add the new element to the end of the vector
            this.data = temp; // Update the reference to the new array
        } else {
            this.data[size++] = value; // Add the new element to the end of the vector
        }
    }

    /**
     * Removes an element from the vector.
     * @param value The element to remove.
     * @throws ArithmeticException if the element is not in the vector.
     * @throws ArithmeticException if the vector is empty.
     */
    public void remove(T value) throws ArithmeticException {
        if (!isIn(value)) {
            throw new ArithmeticException("Element is not in the vector");
        }
        if (size == 0) {
            throw new ArithmeticException("Vector is empty");
        }
        for (int i = 0; i < size; i++) 
        {
            if (data[i] == value) 
            {
                for (int j = i; j < size-1; j++)
                {
                    this.data[j] = this.data[j + 1]; // Shift the elements to the left to remove the element
                }
            }
        }
        size--; // Decrease the size of the vector
    }

    public int size() {
        return size; // Return the number of elements in the vector
    }

    // HELPER METHODS FOR THE VECTOR

    /**
     * Checks if the given element is in the vector.
     * @param element The element to check for.
     * @return True if the element is in the vector, false otherwise.
     */
    public boolean isIn(T element) {
        for (int i = 0; i < size; i++) 
        {
            if (this.data[i] == element) 
            {
                return true; // Check if the element is in the vector
            }
        }
        return false;
    }

    /**
     * Iterator class for the vector.
     */

    public class VectorIterator implements Iterator<T> {
        private int index;

        public VectorIterator() {
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
     * Returns an iterator for the vector.
     * @return An iterator for the vector.
     */
    public Iterator<T> getIterator() {
        return new VectorIterator(); // Return a new instance of the VectorIterator
    }
}
