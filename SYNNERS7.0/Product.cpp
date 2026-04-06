#include "Product.h"

Product::Product(int pID, std::string pname,double prices,double dRate,double tRate , int quant)
       :productID(pID),name(pname),price(prices),quantity(quant),discountRate(dRate),
        taxRate(tRate){}
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
    return price ;
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

//retrieves taxRate
double Product::getTaxRate() const
{
    return taxRate;
}

//retrieves discountRate
double Product::getDiscountRate() const
{
    return discountRate;
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

