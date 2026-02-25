#ifndef PRODUCT_H
#define PRODUCT_H
#include <string>

using namespace std;
class Product
{
    private:
        int productID;
        string name;
        double price;
        int quantity;
        double discountRate;
        double taxRate;
        int amount;
    public:
        Product(int productID, string name,double price,double discountRate,double taxRate);
        virtual ~Product();


    double calculateFinalPrice();

    int getProductID();

    string getName();

    double getPrice();

    int getQuantity();

    void setTaxRate(double taxRate);

    void setDiscountRate(double discountRate);

    void reduceQuantity(int amount);

    void setQuantity(int amount);
};

#endif // PRODUCT_H
