#ifndef NONPERISHABLE_H
#define NONPERISHABLE_H

#include <Product.h>


class NonPerishable : public Product {
private:
    
  
    
public:
   // Constructor: Initializes a perishable product with given values 
    NonPerishable(int id, const std::string& productName, double price, 
                  double tax ,  int qty );
    
    
    ~NonPerishable();
    
    
    double calculateFinalPrice() const override;
    
    
   
    
    
    double getTaxRate() const;
    void setTaxRate(double tax);
   
    
    
};
#endif // NONPERISHABLE_H
