#ifndef PRODUCT_H
#define PRODUCT_H
#include <string>

class Product
{
    private:
        int productID;
        std::string name;
        double price;
        int quantity;
        double discountRate;
        double taxRate;

    public:
         // Constructor: Initializes a new product with given values
        Product(int productID, std::string name,double price,double discountRate,double taxRate ,int quantity );
        virtual ~Product();

    // Calculates final price after applying tax and discount
    // Pure virtual makes Product an abstract class
    virtual double calculateFinalPrice() const = 0;

    // Returns product ID (read-only)
    int getProductID()const;

    // Returns product Name (read-only)
    std::string getName()const;

    // Returns base price (read-only)
    double getPrice()const;

    // Returns current stock quantity (read-only)
    int getQuantity()const;

    // Updates the tax rate
    void setTaxRate(double taxRate);

    // Updates the discount rate
    void setDiscountRate(double discountRate);

    // Decreases stock by specified amount
    void reduceQuantity(int amount);

    // Increase stock by specified amount
    void increaseQuantity(int amount);


};
class Perishable : public Product {
private:
    std::string expiryDate; 
    double discountPercentage; 
    
public:
   // Constructor: Initializes Perishable with given values
    Perishable(int id, const std::string& productName, double price, 
               const std::string& expiry, double discount, int qty );
    
    // distructor
    ~Perishable();
    
    
    double calculateFinalPrice() const override;
    
    
    
    // return the expiry date of a perishable product
    std::string getExpiryDate() const;
    
    //update the expirery date 
    void setExpiryDate(const std::string& expiry);
    
    //set a discount of a product 
    void setDiscount(double discount);
    
  
};


class NonPerishable : public Product {
private:
    
  
    
public:
   // Constructor: Initializes a perishable product with given values 
    NonPerishable(int id, const std::string& productName, double price, 
                  double tax ,  int qty );
    
    
    ~NonPerishable();
    
    
    double calculateFinalPrice() const override;
    
    
   
    
    
    double getTaxRate() const;
    void setTaxRate(double tax);
   
    
    
};

#endif // PRODUCT_H
