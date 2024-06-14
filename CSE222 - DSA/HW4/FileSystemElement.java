import java.sql.Timestamp;

/**
 * Abstract class representing a file system element.
 */
public abstract class FileSystemElement
{
    private String name;
    private Timestamp dateCreated;
    private FileSystemElement parent;

    /**
     * Constructor for a file system element.
     * @param name Name of the element .
     * @param parent Parent directory of the element.
     */
    public FileSystemElement(String name, FileSystemElement parent)
    {
        this.name = name;
        this.parent = parent;
        this.dateCreated = new Timestamp(System.currentTimeMillis());
    }

    /**
     * Getter for the name of the element.
     * @return Name of the element.
     */
    public String getName()
    {
        return name;
    }

    /**
     * Getter for the date the element was created.
     * @return Date the element was created.
     */
    public Timestamp getDateCreated()
    {
        return dateCreated;
    }

    /**
     * Getter for the parent directory of the element.
     * @return Parent directory of the element.
     */
    public FileSystemElement getParent()
    {
        return parent;
    }

    /**
     * Setter for the parent directory of the element.
     * @param parent Parent directory of the element.
     */
    public void setParent(Directory parent)
    {
        this.parent = parent;
    }

    /**
     * Abstract method to print the element.
     * @param prefix Prefix to print before the element.
     */
    public abstract void print(String prefix);
}