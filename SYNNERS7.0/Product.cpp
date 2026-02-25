#include "Product.h"

Product::Product(int productID, string name,double price,double discountRate,double taxRate)
     :productID(productID),name(name), price(price), discountRate(discountRate), taxRate(taxRate), amount(0)
{
    //ctor
}

Product::~Product()
{
    //dtor
}
