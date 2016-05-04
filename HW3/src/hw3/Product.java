package hw3;

import java.security.InvalidParameterException;

public class Product
{
    private int productId;
    private String name;
    private double price;
    private double quantity;
    public boolean isPartial;
    
    public Product(int id, String name, double price, double quantity, boolean partial)
    {
        this.productId = id;
        this.name = name;
        this.price = price;
        this.isPartial = partial;
        
        this.setQuantity(quantity);
    }

    public int getId()
    {
        return productId;
    }

    public String getName()
    {
        return name;
    }

    public void setName(String name)
    {
        this.name = name;
    }

    public double getPrice()
    {
        return price;
    }

    public void setPrice(double price)
    {
        if(price < 0.0) {
            System.out.println("Price can't be negative");
        }
        
        this.price = price;
    }

    public double getQuantity()
    {
        return quantity;
    }

    public final void setQuantity(double quantity)
    {
        if(this.isPartial) {
            quantity = Math.floor(quantity);
        }
        
        this.quantity = quantity;
    }
    
    public boolean reduceQuantity(double amount)
    {
        if(amount < 0.0) {
            System.out.println("Quantity can't be negative");
            return false;
        }
        
        if(amount > this.quantity) {
            System.out.println("Amount should be less then or equal to remaning quantity.");
            return false;
        }
        
        if(this.isPartial && amount % 1 != 0) {
            System.out.println("Whole number required!");
            return false;
        }
        
        this.quantity -= amount;
        
        return true;
    }
    
    public boolean increaseQuantity(double amount)
    {
        if(amount < 0.0) {
            System.out.println("Quantity can't be negative");
            return false;
        }
        
        if(this.isPartial && amount % 1 != 0) {
            System.out.println("Whole number required!");
            return false;
        }
        
        this.quantity += amount;
        
        return true;
    }
    
    @Override
    public String toString()
    {
        return this.getId() + "\t"
                + this.getName() + "\t"
                + this.getQuantity() + "\t"
                + this.getPrice();
    }
}
