package myPack;
import java.util.Iterator;

/**
 * This interface represents a generic container in Java.
 * It provides methods to add and remove elements, get the size of the container,
 * and obtain an iterator to iterate over the elements.
 *
 * @param <T> the type of elements stored in the container
 */
public interface JavaContainer<T> 
{
    /**
     * Adds the specified element to the container.
     *
     * @param value the element to be added
     */
    public void add(T value);

    /**
     * Removes the specified element from the container.
     *
     * @param value the element to be removed
     */
    public void remove(T value);

    /**
     * Returns the number of elements in the container.
     *
     * @return the number of elements in the container
     */
    public int size();

    /**
     * Returns an iterator over the elements in the container.
     *
     * @return an iterator over the elements in the container
     */
    public Iterator<T> getIterator(); 
}