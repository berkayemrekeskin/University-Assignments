import java.util.LinkedList;

public class Directory extends FileSystemElement {

    private LinkedList<FileSystemElement> children;
    
    /**
     * Constructor for a directory.
     * @param name Name of the directory.
     * @param parent Parent directory of the directory.
     */
    public Directory(String name, FileSystemElement parent)
    {
        super(name, parent);
        children = new LinkedList<>();
    }

    /**
     * Add a file or directory to the directory.
     * @param element File or directory to add.
     */
    public void addElement(FileSystemElement element)
    {
        children.add(element);
        element.setParent(this);
    }

    /**
     * Remove a file or directory from the directory recursively.
     * @param element File or directory to remove.
     */
    public void removeElement(FileSystemElement element)
    {
        if(element instanceof Directory)
        {
            Directory directory = (Directory) element;
            for(FileSystemElement child : directory.children)
                removeElement(child);
        }
        element.setParent(null);
        children.remove(element);
    }

    /**
     * Search for a file or directory in the directory.
     * @param name Name of the file or directory to search for.
     * @return File or directory if found, null otherwise.
     */
    public FileSystemElement searchElement(String name)
    {
        return searchElementHelper(this, name);
    }

    /**
     * Helper function to search for a file or directory in the directory.
     * @param current Current directory to search in.
     * @param name Name of the file or directory to search for.
     * @return File or directory if found, null otherwise.
     */
    private FileSystemElement searchElementHelper(Directory current, String name)
    {
        for (FileSystemElement element : current.children)
        {
            if (element.getName().equals(name))
                return element;
            else if(element instanceof Directory)
            {
                FileSystemElement found = searchElementHelper((Directory) element, name);
                if (found != null)
                    return found;
            }
        }
        return null;
    }

    /**
     * Check if a file or directory is in the directory.
     * @param element File or directory to check.
     * @return True if the file or directory is in the directory, false otherwise.
     */
    public boolean isIn(FileSystemElement element)
    {
        return children.contains(element);
    }

    /**
     * Overloaded print function to print directory.
     * @param prefix Prefix to print before the directory.
     */
    @Override
    public void print(String prefix)
    {
        System.out.println(prefix + "* " + this.getName() + "/");
    }

    /**
     * Print the directory and its children.
     */
    public void printCurrentDirectory()
    {
        for(FileSystemElement element : children)
        {
            element.print("");
        }
    }
    
    /**
     * Sort the children of the directory by name.
     */
    public void sortByDate()
    {
        children.sort((FileSystemElement e1, FileSystemElement e2) -> e1.getDateCreated().compareTo(e2.getDateCreated())); // Lambda expression to sort by date
    }
    
    /**
     * Getter for the children of the directory.
     * @return Children of the directory.
     */
    public LinkedList<FileSystemElement> getChildren()
    {
        return children;
    }

}
