#ifndef ORDER_H
#define ORDER_H
#include "Product.h"
#include <string>
//using namespace std;

class Order
{
    private:
        int orderID;
        int productID;
        int quantity;
        std::string status;
    public:
        Order(int orderID,int productID,int quantity);
        virtual ~Order();

        int getOrderID() const;

        int getProductID() const;

        int getQuantity() const;

        void setStatus(const std::string& status);

        std::string getStatus() const;


};

#endif // ORDER_H
