package hw3;

public class Store
{
    public String name;
    public Product[] products;
    
    public Store(String name, Product[] products)
    {
        this.name = name;
        this.products = products;
    }
    
    public String getName()
    {
        return this.name;
    }
    
    public void productList()
    {
        System.out.println("ID\tName\tQty\tPrice");
        
        for(Product p : this.products) {
            System.out.println(p);
        }
    }
    
    public double sellProduct(int id, double amount)
    {
        Product p = getProductById(id);
        if(null == p) {
            System.out.println("Product not found!");
            return -1;
        }
        
        if(!p.reduceQuantity(amount)) {
            return -1;
        }
        
        System.out.println(p.getName() + ": " + amount +
                " sold at " + p.getPrice()
        );
        
        return p.getPrice() * amount;
    }
    
    public boolean addQuantity(int id, double amount)
    {
        Product p = getProductById(id);
        if(null == p) {
            System.out.println("Product not found!");
            return false;
        }
        
        if(!p.increaseQuantity(amount)) {
            return false;
        }
        
        System.out.println(p.getName() + ": " + amount +
                " added"
        );
        
        return true;
    }
    
    public void discount(int id, double percentage)
    {
        Product p = getProductById(id);
        if(null == p) {
            System.out.println("Product not found!");
            return;
        }
        
        p.setPrice(p.getPrice() * (1 - percentage));
    }

    private Product getProductById(int id)
    {
        for(Product p : this.products) {
            if(p.getId() == id) {
                return p;
            }
        }
        
        return null;
    }
}
