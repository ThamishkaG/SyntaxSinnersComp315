#include "Perishable.h"

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
