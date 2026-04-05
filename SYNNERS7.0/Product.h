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


#endif // PRODUCT_H
