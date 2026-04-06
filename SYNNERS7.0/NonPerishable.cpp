#include "NonPerishable.h"
#include <iostream>
#include <string>
//edited by Cebile Nxumalo
//NonPerishable::NonPerishable(int productID,std::string name,double price,int quantity,double taxRate,double discountRate)
 //     :Product(productID, name, price, taxRate, discountRate)


NonPerishable::NonPerishable(int id, const std::string& productName, double price,
        double discount, double tax, int qty)
      : Product(id, productName, price, discount, tax, qty)
      //,taxRate(tax)
      {}

//distructor of non perisharable
NonPerishable::~NonPerishable() {

}

double NonPerishable::calculateFinalPrice() const {
    double price = getPrice()+getPrice()*getTaxRate() ;
    const double discountRate=getDiscountRate();
    if (discountRate!=0) {
        price = getPrice()+getPrice()*getTaxRate() - discountRate ;
    }
    return price;
}


