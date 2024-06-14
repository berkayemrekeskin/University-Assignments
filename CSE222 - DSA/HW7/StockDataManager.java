public class StockDataManager {
    private AVLTree avlTree;

    public StockDataManager() {
        avlTree = new AVLTree();
    }

    // Add or update a stock
    public void addOrUpdateStock(String symbol, double price, long volume, long marketCap) {
        Stock existingStock = avlTree.search(symbol);
        if (existingStock != null)  // If stock already exists, update the details
        {
            existingStock.setPrice(price);
            existingStock.setVolume(volume);
            existingStock.setMarketCap(marketCap);
        } 
        else // If stock does not exist, add a new stock
        { 
            Stock newStock = new Stock(symbol, price, volume, marketCap);
            avlTree.insert(newStock);
        }
    }

    // Remove a stock
    public void removeStock(String symbol) 
    {
        avlTree.delete(symbol);
    }

    // Search for a stock
    public Stock searchStock(String symbol) 
    {
        return avlTree.search(symbol);

    }

    // Update stock details
    public void updateStock(String symbol, double newPrice, long newVolume, long newMarketCap) 
    {
        Stock stock = avlTree.search(symbol);
        if (stock != null) {
            stock.setPrice(newPrice);
            stock.setVolume(newVolume);
            stock.setMarketCap(newMarketCap);
        }
    }
}
