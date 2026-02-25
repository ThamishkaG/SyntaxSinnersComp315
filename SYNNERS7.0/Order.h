#ifndef ORDER_H
#define ORDER_H
#include "Product.h"
using namespace std;

class Order
{
    private:
        int orderID;
        int productID;
        int quantity;
        string status;
    public:
        Order(int orderID,int productID,int quantity);
        virtual ~Order();

        int getOrderID();

        int getProductID();

        int getQuantity();

        void setStatus(string status);


};

#endif // ORDER_H
