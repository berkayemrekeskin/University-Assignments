import java.util.Scanner;

public class Main {
    
    private static Directory currentDirectory;
    private static FileSystem fileSystem = new FileSystem();
    private static Scanner scanner = new Scanner(System.in);

    public static void main(String[] args)
    {
        currentDirectory = fileSystem.getRoot();
        while(true)
        {
            System.out.println();
            System.out.println("Current directory: " + fileSystem.getCurrentPath(currentDirectory));
            System.out.println();
            System.out.println("===== File System Management Menu =====");
            System.out.println("1. Change Directory");
            System.out.println("2. List Directory Contents");
            System.out.println("3. Create File / Directory");
            System.out.println("4. Delete File / Directory");
            System.out.println("5. Move File / Directory");
            System.out.println("6. Search File / Directory");
            System.out.println("7. Print Directory Tree");
            System.out.println("8. Sort Contents by Date");
            System.out.println("9. Exit");
            System.out.print("Please select an option: ");

            int choice = scanner.nextInt();
            scanner.nextLine();

            switch (choice)
            {
                case 1:
                    changeDirectory();
                    break;
                case 2:
                    listContents();
                    break;
                case 3:
                    create();
                    break;
                case 4:
                    delete();
                    break;
                case 5:
                    move();
                    break;
                case 6:
                    search();
                    break;
                case 7:
                    printDirectoryTree();
                    break;
                case 8:
                    sortDirectoryByDate();
                    break;
                case 9:
                    System.exit(0);
                    break;
                default:
                    System.out.println("Invalid choice. Please try again.");
            }
        }
    }
    
    private static void changeDirectory()
    {
        System.out.println("Current Directory: " + fileSystem.getCurrentPath(currentDirectory));
        System.out.print("Enter new directory path: ");
        String path = scanner.nextLine();
        Directory newDirectory = fileSystem.changeDirectory(path);
        if (newDirectory == null)
        {
            System.out.println("Invalid path.");
            return ;
        }
        else
        {
            currentDirectory = newDirectory;
            System.out.println("Directory changed to: " + fileSystem.getCurrentPath(currentDirectory));
        }
    }

    private static void listContents()
    {
        System.out.println("Listing contents of " + fileSystem.getCurrentPath(currentDirectory) + ":");
        fileSystem.listContents(currentDirectory);
    }

    private static void create()
    {
        System.out.println("Current Directory: " + fileSystem.getCurrentPath(currentDirectory));
        System.out.print("Create file or directory (f / d): ");
        String choice = scanner.nextLine();
        if (choice.equals("f"))
        {
            System.out.print("Enter name for the new file: ");
            String name = scanner.nextLine();
            if(currentDirectory.getChildren().contains(currentDirectory.searchElement(name)))
            {
                System.out.println("Element already exists in the current directory: " + name);
                return;
            }
            fileSystem.createFile(name, currentDirectory);
            System.out.println("File created: " + name);
        }
        else if (choice.equals("d"))
        {
            System.out.print("Enter name for the new directory: ");
            String name = scanner.nextLine();
            if(currentDirectory.getChildren().contains(currentDirectory.searchElement(name)))
            {
                System.out.println("Element already exists in the current directory: " + name);
                return;
            }
            fileSystem.createDirectory(name, currentDirectory);
            System.out.println("Directory created: " + name + "/");
        }
        else
            System.out.println("Invalid choice.");
    }

    private static void delete()
    {
        System.out.println("Current Directory: " + fileSystem.getCurrentPath(currentDirectory));
        System.out.print("Enter name of file/directory to delete: ");
        String name = scanner.nextLine();

        if(!currentDirectory.getChildren().contains(currentDirectory.searchElement(name)))
        {
            System.out.println("Element not found in the current directory: " + name);
            return;
        }

        int found = fileSystem.getType(name);
        if(found == 0)
        {
            fileSystem.deleteFile(name, currentDirectory);
            System.out.println("File deleted: " + name);
        }
        else if(found == 1)
        {
            fileSystem.deleteDirectory(name, currentDirectory);
            System.out.println("Directory deleted: " + name);
        }
        else
            System.out.println("Element not found: " + name);
    }

    private static void move()
    {
        System.out.println("Current Directory: " + fileSystem.getCurrentPath(currentDirectory));
        System.out.print("Enter name of file/directory to move: ");
        String name = scanner.nextLine();

        System.out.println("Enter new directory path: ");
        String path = scanner.nextLine();

        int found = fileSystem.getType(name);
        if(found == 0)
        {
            move(name,path);
            System.out.println("File moved: " + name + " to " + path);
        }
        else if(found == 1)
        {
            move(name,path);
            System.out.println("Directory moved: " + name + " to " + path);
        }
        else
            System.out.println("Element not found: " + name);
    }

    private static void move(String name, String path)
    {
        Directory newParent = fileSystem.changeDirectory(path);
        if (newParent == null)
            System.out.println("Invalid directory path.");
        else
            fileSystem.moveElement(name, newParent);
    }

    private static void search()
    {
        System.out.print("Search query: ");
        String name = scanner.nextLine();
        boolean found = fileSystem.search(name);
        System.out.println("Searching from root...");
        if (found)
        {
            System.out.println("Found: " + fileSystem.getPath(name));
        }
        else
        {
            System.out.println("Element not found!");
        }
    }

    private static void printDirectoryTree()
    {
        fileSystem.printDirectoryTree(currentDirectory);
    }

    private static void sortDirectoryByDate()
    {
        System.out.println("Sorted contents of " + fileSystem.getCurrentPath(currentDirectory) + " by date created: ");
        fileSystem.sortDirectoryByDate(currentDirectory);
    }
}
