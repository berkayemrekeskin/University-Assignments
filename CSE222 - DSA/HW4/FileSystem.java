public class FileSystem {
    
    private Directory root;

    /**
     * Constructor for the file system.
     */
    public FileSystem()
    {
        root = new Directory("root", null);
    }   

    /**
     * Change the current directory to the specified path.
     * @param path Path to change the directory to.
     * @return Directory if the path is valid, null otherwise.
     */
    public Directory changeDirectory(String path)
    {
        if(path.equals("/root"))
            return root;
        String[] pathArray = pathToArray(path);
        if(pathArray.length <= 1)
            return null;
        return changeDirectoryHelper(root, pathArray, 1);
    }

    /**
     * Helper function to change the current directory to the specified path.
     * @param current Current directory.
     * @param path Path to change the directory to.
     * @param index Index of the path array.
     * @return Directory if the path is valid, null otherwise.
     */
    private Directory changeDirectoryHelper(Directory current, String path[], int index)
    {
        if(index == path.length)
            return current;
        Directory next = (Directory) getElement(path[index]);
        if(next != null)
            return changeDirectoryHelper(next, path, index + 1);
        else
            return null;
    }
    /**
     * List the contents of the current directory.
     * @param directory Current directory.
     */
    public void listContents(Directory directory)
    {
        directory.printCurrentDirectory();
    }

    /**
     * Create a file in the current directory.
     * @param name Name of the file.
     * @param parent Parent directory of the file.
     */
    public void createFile(String name, Directory parent)
    {
        parent.addElement(new File(name, parent));
    }

    /**
     * Create a directory in the current directory.
     * @param name Name of the directory.
     * @param parent Parent directory of the directory.
     */
    public void createDirectory(String name , Directory parent)
    {
        parent.addElement(new Directory(name, parent));
    }

    /**
     * Delete a file in the current directory.
     * @param name Name of the file.
     * @param parent Parent directory of the file.
     */
    public void deleteFile(String name, Directory parent)
    {
        parent.removeElement(getElement(name));
    }

    /**
     * Delete a directory in the current directory.
     * @param name Name of the directory.
     * @param parent Parent directory of the directory.
     */
    public void deleteDirectory(String name, Directory parent)
    {
        parent.removeElement(getElement(name));
    }

    /**
     * Move a file or directory to a new parent directory.
     * @param name Name of the file or directory.
     * @param newParent New parent directory.
     */
    public void moveElement(String name, Directory newParent)
    {
        FileSystemElement element = getElement(name); // Returning the reference of the object
        if(element != null) // Checking if the given name matches with an object in the file system
        {
            // Changing the parent of the object. Removing it from the past parent. Adding it to the new parent.
            Directory parent = (Directory) element.getParent();
            parent.getChildren().remove(element);
            newParent.getChildren().add(element);
            element.setParent(newParent);
        }
    }

    /**
     * Search for a file or directory in the file system.
     * @param name Name of the file or directory to search for.
     * @return True if the file or directory is found, false otherwise.
     */
    public boolean search(String name)
    {
        if(name.equals("/root") || name.equals("/"))
            return true;
        return getElement(name) != null;
    }

    /**
     * Print the directory tree of the file system.
     * @param currentDirectory Current directory.
     */
    public void printDirectoryTree(Directory currentDirectory)
    {
        System.out.println("* root/");
        printDirectoryTreeHelper(root, currentDirectory,  "  ");
    }

    /**
     * Helper function to print the directory tree of the file system.
     * @param current Current directory.
     * @param lastDirectory Last directory in the path.
     * @param prefix Prefix to print before the directory.
     */
    private void printDirectoryTreeHelper(Directory current, Directory lastDirectory, String prefix)
    {
        for(FileSystemElement element : current.getChildren())
        {
            if(element instanceof Directory)
            {
                if(element == lastDirectory)
                {
                    System.out.println(prefix + "* " + element.getName() + "/" + "(Current Directory)");
                    for(FileSystemElement child : ((Directory) element).getChildren())
                        child.print(prefix + "  ");
                    return;
                }
                else
                {
                    element.print(prefix);
                    printDirectoryTreeHelper((Directory) element, lastDirectory, prefix + "  ");
                }
            }
        }
    }

    /**
     * Sort the current directory by name.
     * @param directory Current directory.
     */
    public void sortDirectoryByDate(Directory directory)
    {
        directory.sortByDate();
        for(FileSystemElement element : directory.getChildren())
        {
            if(element instanceof Directory)
                System.out.println("* " + element.getName() + "/ " + "(" + element.getDateCreated() + ")");
            else
                System.out.println(element.getName() + " "  + "(" + element.getDateCreated() + ")");
        }
    }

    /**
     * Get the current path of the file system.
     * @param directory Current directory.
     * @return Current path of the file system.
     */
    public String getCurrentPath(Directory directory)
    {
        StringBuilder path = new StringBuilder();
        getCurrentPathHelper(directory, path);
        return path.toString();
    }

    /**
     * Helper function to get the current path of the file system.
     * @param current Current directory.
     * @param path Path of the file system.
     */
    private void getCurrentPathHelper(Directory current, StringBuilder path)
    {
        if(current.getParent() == null)
        {
            path.insert(0, "/" + current.getName());
            return;
        }
        path.insert(0,"/" + current.getName());
        getCurrentPathHelper((Directory) current.getParent(), path); 
    }

    /**
     * Find a file or directory in the file system.
     * @param name Name of the file or directory to find.
     * @return 0 if the element is a file, 1 if the element is a directory, -1 if the element is not found.
     */
    public int getType(String name)
    {
        return getTypeHelper(root, name);
    }

    /**
     * Helper function to find a file or directory in the file system.
     * @param current Current directory.
     * @param name Name of the file or directory to find.
     * @return 0 if the element is a file, 1 if the element is a directory, -1 if the element is not found.
     */
    private int getTypeHelper(Directory current, String name)
    {
        FileSystemElement element = getElement(name);
        if(element != null && element instanceof File)
            return 0;
        else if(element != null && element instanceof Directory)
            return 1;
        else
            return -1;
    }

    /**
     * Get the path of a file or directory.
     * @param name Name of the file or directory.
     * @return Path of the file or directory.
     */
    public String getPath(String name)
    {
        if(name.equals("/root") || name.equals("/"))
            return "/";
        StringBuilder path = new StringBuilder();
        getPathHelper(name, path);
        return path.toString();
    }

    /**
     * Helper function to get the path of a file or directory.
     * @param name Name of the file or directory.
     * @param path Path of the file or directory.
     */
    private void getPathHelper(String name, StringBuilder path)
    {
        FileSystemElement element = getElement(name);
        if(element == null)
        {
            path.insert(0, "/root");
            return;
        }
        path.insert(0, "/" + element.getName());
        getPathHelper(element.getParent().getName(), path);
    }

    /**
     * Get the root directory of the file system.
     * @return Root directory of the file system.
     */
    public Directory getRoot()
    {
        return root;
    }

    /**
     * Get the file system element with the specified name.
     * @param name Name of the file system element.
     * @return File system element if found, null otherwise.
     */
    private FileSystemElement getElement(String name)
    {
        return root.searchElement(name);
    }

    /**
     * Convert a path to an array.
     * @param prefix Path to convert to an array.
     * @return Array of the path.
     */
    private String[] pathToArray(String prefix)
    {
        prefix = prefix.substring(1);
        return prefix.split("/");
    }
}
