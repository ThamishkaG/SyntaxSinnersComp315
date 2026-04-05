#ifndef PERISHABLE_H
#define PERISHABLE_H
#include <string>
#include <Product.h>
using namespace std;

class Perishable : public Product {
private:
    std::string expiryDate; 
    double discountPercentage; 
    
public:
   // Constructor: Initializes Perishable with given values
    Perishable(int id, const std::string& productName, double price, 
               const std::string& expiry, double discount, int qty );
    
    // distructor
    ~Perishable();
    
    
    double calculateFinalPrice() const override;
    
    
    
    // return the expiry date of a perishable product
    std::string getExpiryDate() const;
    
    //update the expirery date 
    void setExpiryDate(const std::string& expiry);
    
    //set a discount of a product 
    void setDiscount(double discount);
    
  
};
#endif // PERISHABLE_H
