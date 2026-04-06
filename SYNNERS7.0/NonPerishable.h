#ifndef NONPERISHABLE_H
#define NONPERISHABLE_H
#include <string>
#include "Product.h"


class NonPerishable : public Product {
private:



public:
   // Constructor: Initializes a perishable product with given values
    NonPerishable(int id, const std::string& productName, double price,
          double discount, double tax ,  int qty );
    ~NonPerishable();
    double calculateFinalPrice() const;
    //double getTaxRate() const;
    //void setTaxRate(double tax);
    //double getTaxRate() const override;
};

#endif // NONPERISHABLE_H
