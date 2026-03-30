#include "Order.h"

Order::Order(int oId ,int pId ,int qty)
    :orderID(oId),
    productID(pId),
    quantity(qty),
    status("Pending") {}

    Order::~Order(){}


// Returns the unique order Id(const - doesn't modify object)
int Order::getOrderID()const {
    return orderID;
}
// Returns the product ID being odered (const)
int Order::getProductID() const {
    return productID;
}
// Returns the quantity ordered (const)
int Order::getQuantity() const {
    return quantity;
}

// Updates the order status (non-const - modifies object)
// Takes const reference to avoid string copying
void Order::setStatus(const std::string& stat){
    status = stat;
}

// Returns current order status (const)
// Returns by value copy for safety
std::string Order::getStatus()const {
    return status;
}
