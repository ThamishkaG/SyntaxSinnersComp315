#include "Product.h"

Product::Product(int pID, std::string pname,double price,double dRate,double tRate , int quant)
       :int productID(pID),
        std::string name(pname),
        double basePrice(prices),
        int quantity(quant),
        double discountRate(dRate),
        double taxRate(tRate),{}
Product::~Product() {}

// getter functions
int Product::getProductID()const
{
    return productID;
}

std::string Product::getName()const
{
    return name ;
}

double Product::getPrice()const
{
    return basePrice ;
}

int Product::getQuantity()const
{
    return quantity ;
}

//setter functions
void Product::setTaxRate(double tRate)
{
    taxRate = tRate;
}

void Product::setDiscountRate(double dRate)
{
    discountRate = dRate ;
}


//reduce quantity by amount 
void Product::reduceQuantity(int amount)
{
    quantity -= amount;
}

//increase quantity by amount
void Product::increaseQuantity(int amount)
{
    quantity += amount;
}





