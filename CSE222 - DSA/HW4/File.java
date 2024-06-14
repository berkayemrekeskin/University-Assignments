public class File extends FileSystemElement {
    /**
     * Constructor for a file.
     * @param name Name of the file.
     * @param parent Parent directory of the file.
     */
    public File(String name, FileSystemElement parent)
    {
        super(name, parent);
    }

    /**
     * Overloaded print function to print file.
     * @param prefix Prefix to print before the file.
     */
    @Override
    public void print(String prefix)
    {
        System.out.println(prefix + getName());
    }
}
