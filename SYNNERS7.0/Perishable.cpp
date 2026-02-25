#include "Perishable.h"

Perishable::Perishable(int productID,string name,double price,int quantity,double taxRate,double discountRate,string expiryDate)
    :Product(productID, name, price, discountRate, taxRate), expiryDate(expiryDate)
{
    //ctor
}

Perishable::~Perishable()
{
    //dtor
}
