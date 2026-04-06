#include "Perishable.h"
#include <string>
//edited by Cebile Nxumalo
//Perishable::Perishable(int productID,string name,double price,int quantity,double taxRate,double discountRate,string expiryDate)
    //:Product(productID, name, price, discountRate, taxRate), expiryDate(expiryDate)



Perishable::Perishable(int productID, const std::string& productName, double price,
                      const std::string& expiry, double dRate, double tRate, int qty)
    : Product(productID, productName, price, dRate, tRate, qty),expiryDate(expiry),
      discountPercentage(dRate) {}


//distructor
Perishable::~Perishable() {}

//return final price icluding tax and discount
double Perishable::calculateFinalPrice() const {
    double price = getPrice()+getPrice()*getTaxRate() ;
    if (discountPercentage!=0) {
        price = getPrice()+getPrice()*getTaxRate() - discountPercentage ;
    }
    return price;
}
// return expiry date
std::string Perishable::getExpiryDate() const {
    return expiryDate;
}

//update expiry date
void Perishable::setExpiryDate(const std::string& expiry) {
    expiryDate = expiry;
}
