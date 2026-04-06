#ifndef INVENTORY_H
#define INVENTORY_H

#include <map>          //for std::map
#include <memory>       //for std::shared_ptr
#include <mutex>        //for std::mutex

#include "Product.h"    //for superclass's
#include "Order.h"


class Inventory {
private:
    //used a Map, UnorderedMap is more efficient but Map maintains a sorted order (by ID)
    //and provides balanced tree operations, which are sufficiant for a system of this size.

    //key   -> productID (int)
    //value -> shared pointer to Product object
    std::map<int, std::shared_ptr<Product>> products; //declaration

    //mutex to protect the Map in multithreaded access
    mutable std::mutex inventoryMutex;

public:
    //constructor
    //default is sufficiant because we're not initializing anything
    //some methods should not allow for modifications so they've  been declared as constant
    Inventory() = default;

    //explicite deltion of copy operations
    Inventory(const Inventory&)=delete;//prevents copying
    Inventory& operator=(Inventory&)=delete;//prevents assignment
    Inventory(Inventory&&)=default;//allows moving
    Inventory& operator=(Inventory&&)=default;

    void addProduct(std::shared_ptr<Product> product);
    void addProduct(int productId, int value);
    void displayAllProducts() const;

    //overloading search funtions
    void searchProduct(int productId)const;
    void searchProduct(const std::string& name)const;


    void setQuantity(int value);
    void sortByQuantity();
    void sortByQuantity(int quantity);
    void sortByPrice();
    void sortByPrice(double price);
    void removeProduct(int productId);

    //will be implemented at a later stage
    //Plan
    bool processOrder(const Order& order);
    void restockProduct(int productId, int amount);

};

#endif // INVENTORY_H
