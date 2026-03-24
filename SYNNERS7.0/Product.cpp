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


//consructor 
Perishable::Perishable(int id, const std::string& productName, double price,
                       const std::string& expiry, double discount, int qty)
    : Product(id, productName, price, qty),

      expiryDate(expiry),
      discountPrice(discount) {}
}

//distructor
Perishable::~Perishable() {}

//return final price icluding tax and discount
double Perishable::calculateFinalPrice() const {
    double price = getPrice()+getPrice()*taxRate() ;


    if (discountPrice!=0) {
        price = getPrice()+getPrice()*taxRate() - discountPrice ;
    }
}
// return expiry date
std::string Perishable::getExpiryDate() const {
    return expiryDate;
}

//update expiry date
void Perishable::setExpiryDate(const std::string& expiry) {
    expiryDate = expiry;
}


//contructor of non perisharable
NonPerishable::NonPerishable(int id, const std::string& productName, double price,
                             double tax, int qty)
    : Product(id, productName, price, qty),
      taxRate(tax),{}

//distructor of non perisharable
NonPerishable::~NonPerishable() {

}

double NonPerishable::calculateFinalPrice() const {
    double price = getPrice()+getPrice()*taxRate() ;


    if (discountPrice!=0) {
        price = getPrice()+getPrice()*taxRate() - discountPrice ;
    }
}

//return tax rate
double NonPerishable::getTaxRate() const {
    return taxRate;
}

//update tax rate
void NonPerishable::setTaxRate(double tax) {

   taxRate = tax;

}
