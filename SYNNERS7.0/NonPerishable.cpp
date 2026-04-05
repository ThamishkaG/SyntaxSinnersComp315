#include "NonPerishable.h"
//edited by Cebile Nxumalo
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
NonPerishable::~NonPerishable()
{
    //dtor
}
