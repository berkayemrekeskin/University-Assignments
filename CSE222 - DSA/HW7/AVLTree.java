public class AVLTree {
    
    private static class Node
    {
        private Stock data;
        private Node left;
        private Node right;
        private int height;

        public Node(Stock _data)
        {
            this.data = _data;
            this.height = 1;
        }
    }

    private Node root = null; 

    public AVLTree() {/* Intentionally empty */}
    
    /**
     * @param node Node to get height
     * @return height of the node
     */
    private int height(Node node)
    {
        if(node == null)
            return 0;
        else
            return node.height;
    }

    /**
     * @param node Node to update height
     * @return height of the node after updating
     */
    private int update_height(Node node)
    {
        return Math.max(height(node.left), height(node.right)) +1;
    }

    /**
     * @param node Node to get balance factor
     * @return balance factor of the node
     */
    private int get_balance(Node node)
    {
        if(node == null)
            return 0;
        else 
            return height(node.left) - height(node.right);
    }

    /**
     * @param y Node to be rotated right
     * @return right rotation of the node
     */
    private Node rotate_right(Node y)
    {
        Node x = y.left;
        Node temp = x.right;

        x.right = y;
        y.left = temp;

        y.height = update_height(y);
        x.height = update_height(x);

        return x;
    }

    /**
     * @param x Node to be rotated left
     * @return left rotation of the node
     */
    private Node rotate_left(Node x)
    {
        Node y = x.right;
        Node temp = y.left;

        y.left = x;
        x.right = temp;

        x.height = update_height(x);
        y.height = update_height(y);
        
        return y;
    }

    /**
     * @param root Node to find minimum stock
     * @return minimum stock in the tree
     */
    private Stock find_min(Node root)
    {
        Node cur = root;
        while(cur.left != null)
            cur = cur.left;
        return cur.data;
    }

    /**
     * @param root Node to find maximum stock
     * @return maximum stock in the tree
     */
    private Stock find_max(Node root)
    {
        Node cur = root;
        while(cur.right != null)
            cur = cur.right;
        return cur.data;
    }

    /**
     * Inorder traversal of the tree
     */
    public void inorder() {
        inorder(root);
        System.out.println();
    }

    private void inorder(Node root) {
        if (root != null) {
            inorder(root.left);
            System.out.println(root.data.getSymbol() + " " );
            inorder(root.right);
        }
    }

    /**
     * Preorder traversal of the tree
     */
    public void preorder()
    {
        preorder(root);
    }

    private void preorder(Node root)
    {
        if(root != null)
        {
            preorder(root.left);
            preorder(root.right);
            System.out.println(root.data.getSymbol() + " ");
        }
    }

    /**
     * Postorder traversal of the tree
     */
    public void postorder()
    {
        postorder(root);
    }

    private void postorder(Node root)
    {
        if(root != null)
        {
            System.out.println(root.data.getSymbol() + " ");
            postorder(root.left);
            postorder(root.right);
        }
    }

    /**
     * Insert a stock into the tree
     * Time Complexity: O(log n)
     * @param stock stock to be inserted
     */
    public void insert(Stock stock)
    {
        root = insert(root, stock);
    }

    /**
     * Inserting the stock recursively to the tree and balancing it if necessary 
     */
    private Node insert(Node localroot, Stock stock)
    {
        if(localroot == null)
            return new Node(stock);
        else if(localroot.data.getSymbol().compareTo(stock.getSymbol()) == 0)
            return localroot;
        else if(localroot.data.getSymbol().compareTo(stock.getSymbol()) < 0)
            localroot.right = insert(localroot.right, stock);
        else 
            localroot.left = insert(localroot.left, stock);

        localroot.height = 1 + Math.max(height(localroot.left), height(localroot.right));

        int balance = get_balance(localroot);

        if (balance > 1) {
            if (get_balance(localroot.left) >= 0) 
            {
                return rotate_right(localroot);
            }
            else {
                localroot.left = rotate_left(localroot.left);
                return rotate_right(localroot);
            }
        }

        if (balance < -1) {
            if (get_balance(localroot.right) <= 0) 
            {
                return rotate_left(localroot);
            } 
            else {
                localroot.right = rotate_right(localroot.right);
                return rotate_left(localroot);
            }
        }
        return localroot;

    }
    
    /**
     * Delete a stock from the tree
     * Time Complexity: O(log n)
     * @param symbol symbol of the stock to be deleted
     */
    public void delete(String symbol)
    {
        root = delete(root, symbol);
    }

    /**
     * Deleting the stock recursively from the tree and balancing it if necessary
     */
    private Node delete(Node localroot, String symbol)
    {
        if(localroot == null)
            return null;
        
        String localSymbol = localroot.data.getSymbol();

        if(symbol.compareTo(localSymbol) < 0)
            localroot.left = delete(localroot.left, symbol);
        else if (symbol.compareTo(localSymbol) > 0)
            localroot.right = delete(localroot.right, symbol);
        else 
        {
            if(localroot.left == null && localroot.right == null)
                return null;
            if(localroot.right != null)
            {
                localroot.data = find_min(localroot.right);
                localroot.right = delete(localroot.right, find_min(localroot.right).getSymbol());
                return localroot;
            }
            else 
            {
                localroot.data = find_max(localroot.left);
                localroot.left = delete(localroot.left, find_max(localroot.left).getSymbol());
                return localroot;
            }
        }

        localroot.height = Math.max(height(localroot.left),height(localroot.right)) + 1;

        int balance = get_balance(localroot);

        if (balance > 1) {
            if (get_balance(localroot.left) >= 0) 
            {
                return rotate_right(localroot);
            }
            else 
            {
                localroot.left = rotate_left(localroot.left);
                return rotate_right(localroot);
            }
        }

        if (balance < -1) {
            if (get_balance(localroot.right) <= 0) 
            {
                return rotate_left(localroot);
            } 
            else 
            {
                localroot.right = rotate_right(localroot.right);
                return rotate_left(localroot);
            }
        }
        return localroot;

    }

    /**
     * Search for a stock in the tree with the given symbol
     * Time Complexity: O(log n)
     * @param symbol symbol of the stock to be searched
     * @return stock if found, null otherwise
     */

    public Stock search(String symbol)
    {
        Node result = search(root, symbol);
        return (result != null) ? result.data : null;
    }

    private Node search(Node localroot, String symbol)
    {
        if(localroot == null)
            return null;
        else if(localroot.data.getSymbol().compareTo(symbol) == 0)
            return localroot;
        else if(localroot.data.getSymbol().compareTo(symbol) < 0)
            return search(localroot.right, symbol);
        else 
            return search(localroot.left, symbol);
    }
}
