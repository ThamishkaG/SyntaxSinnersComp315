#ifndef PERISHABLE_H
#define PERISHABLE_H
#include <string>
#include <Product.h>
using namespace std;

class Perishable : public Product
{
    private:
    string expiryDate;
    public:
        Perishable(int productID,string name,double price,int quantity,double taxRate,double discountRate,string expiryDate);
        virtual ~Perishable();


    double calculateFinalPrice();
    string getExpiryDate();
};

#endif // PERISHABLE_H
