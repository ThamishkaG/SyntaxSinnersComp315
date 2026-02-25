#ifndef NONPERISHABLE_H
#define NONPERISHABLE_H

#include <Product.h>


class NonPerishable : public Product
{
    public:
        NonPerishable(int productID,string name, double price, int quantity,double taxRate,double discountRate);
        virtual ~NonPerishable();

        double calculateFinalPrice();


};

#endif // NONPERISHABLE_H
