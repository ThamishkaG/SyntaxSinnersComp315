#include "Inventory.h"
#include <iostream>
#include <map>
#include <memory>
#include <vector>
#include <algorithm>
#include <mutex>

using namespace std;

//Zine Duma (224007195)
void Inventory::addProduct( std::shared_ptr<Product> product){
    // if we used the an object instead of a pointer:
    // Polymorphism would have been lost, derived class behavior broken and
    // Requirement of smart pointer would not have been adhered to.

    std::lock_guard<std::mutex> lock(inventoryMutex);

    int id = product-> getProductID();  //getting it from the product class btw

    // condition to check whether the product ID given exists in the system
    if( products.find(id) != products.end()){
        std::cout<< "Product with ID"<< id << " already exists. \n";
        return ;
    }


    products[id] = product;
    std::cout<<" Product has been added to the system successfully. \n";
}

void Inventory::displayAllProducts() const{
    std::lock_guard<std::mutex> lock(inventoryMutex);

    if ( products.empty()){
        std::cout<< " There are no products in inventory. \n";
        return ;
    }

    // for each iteration we have a key value pair.
    for(const std::pair<const int, std::shared_ptr<Product>> &pair: products){

        //This is needed so that we can access the actual product since it is a pointer.
        const std::shared_ptr<Product>& product = pair.second;
        std::cout<< "Product ID:" << product-> getProductID() <<  "Product Name:" <<product-> getName()
                 << "Product Price:"<< product-> getPrice() << "Quantity:" << product-> getQuantity()<< "\n";

    }

}


void Inventory::sortByPrice(){ // this method sorts from cheapest to most expensive
    std::lock_guard<std::mutex> lock(inventoryMutex);
    std::vector<std::shared_ptr<Product>> productList;// we had to use a vector because a map sorts by key only and not values

    for( const std::pair<const int, std::shared_ptr<Product>>& pair : products){
        productList.push_back(pair.second); // this copies each product pointer to the list
    }

    std::sort(productList.begin(),productList.end(),
         []( const std::shared_ptr<Product>& a,
             const std::shared_ptr<Product>& b){
              return a-> getPrice() < b-> getPrice();
         });

    for (const auto& product : productList) {
        std::cout << "ID: " << product->getProductID()
                  << " Name: " << product->getName()
                  << " Price: " << product->getPrice()
                  << " Quantity: " << product->getQuantity()
                  << "\n";
    }
}

void Inventory::sortByQuantity(){

     std::lock_guard<std::mutex> lock(inventoryMutex);
     std::vector<std::shared_ptr<Product>> productList;// we had to use a vector because a map sorts by key only and not values

    for( const std::pair<const int, std::shared_ptr<Product>>& pair : products){
        productList.push_back(pair.second); // this copies each product pointer to the list
    }

    std::sort(productList.begin(),productList.end(),
         []( const std::shared_ptr<Product>& a,
             const std::shared_ptr<Product>& b){
              return a-> getQuantity() < b-> getQuantity();
         });

    for (const auto& product : productList) {
         std::cout << "ID: " << product->getProductID()
                  << " Name: " << product->getName()
                  << " Price: " << product->getPrice()
                  << " Quantity: " << product->getQuantity()
                  << "\n";
    }
}

//Lindelihle Sibiya (224064327)
void Inventory::searchProduct(int productId) const {
    //search for product using its ID
    //shared data, so use lock guard to prevent data races while reading
    //function is constant bc it shouldn't modify the inventory contents

    // lock the mutex to ensure safe concurrent access.
    // lock_guard automatically unlocks when it goes out of scope.
    std::lock_guard<std::mutex> lock(inventoryMutex);

    //code was initially
    //auto temp = products.find(productId);
    //logically the same but I'm avoiding shortcuts
    std::map<int , std::shared_ptr<Product>>::const_iterator temp = products.find(productId);


    if (temp != products.end()) {

        const std::shared_ptr<Product> product = temp->second;
        // temp->first  = key (product ID)
        // temp->second = shared_ptr<Product>

        // access the actual product object through the smart pointer.
        // since shared_ptr overloads the -> operator,
        // directly call getter methods.
        std::cout<< "Product found";
        std::cout<< "Product ID: " << product->getProductID() <<"\n";
        std::cout<< "Name: " << product->getName() <<"\n";
        std::cout<< "Price: " << product->getPrice() <<"\n";
        std::cout<< "Quantity: " << product->getQuantity() <<"\n";

    } else {
        std::cout << "Product not found";
    }
}

void Inventory::searchProduct(const std::string& name) const {

    std::lock_guard<std::mutex> lock(inventoryMutex);

    //use a boolean because search id has an implicit boolean
    //ID has a single comparison, therefore it's a binary deceision
    //name search requires a full traversal, multiple comparisons and match tracking
    bool found = false;

    for(std::map<int, std::shared_ptr<Product>>::const_iterator temp = products.begin();
        temp != products.end(); temp++) {

        const std::shared_ptr<Product>& product=temp->second;

        if (product->getName()==name) {
            found = true;

            std::cout<< "Product ID: " << product->getProductID() <<"\n";
            std::cout<< "Name: " << product->getName() <<"\n";
            std::cout<< "Price: " << product->getPrice() <<"\n";
            std::cout<< "Quantity: " << product->getQuantity() <<"\n";
    }
}
        if (!found) {
            std::cout << "No products found with that name.\n";
        }

}

void Inventory::removeProduct(int productId) {
    //removes product from inventory using its ID
    //since erase() modifies the map, the mutex must be locked to prevent race conditions
    //locking mutex to protect shared resource (unordered_map)

    lock_guard<mutex> lock(inventoryMutex);

    //search using key
    std::map<int, std::shared_ptr<Product>>:: iterator temp = products.find(productId);

    if (temp != products.end()) { //if we dont reach the end its successsful
        products.erase(temp);

        std::cout << "Product successfully removed";
    } else {
        std::cout << "Product not found. Cannot be removed";

    }
}

//methoa will be implemented in phase 2 once Order class is implemented
bool Inventory::processOrder(const Order& order) {
    std::lock_guard<std::mutex> lock(inventoryMutex);

    std::cout << "Order processsing not implemented yet.\n";
    return false;
}


void Inventory::restockProduct(int productId, int amount) {

    //since changing the quantity of a product modifies, it must be locked to prevent race conditions
    std::lock_guard<std::mutex> lock(inventoryMutex);

    std::map<int, std::shared_ptr<Product>>::iterator temp = products.find(productId);

    if (temp != products.end()) {
        if (amount > 0) {
            temp->second->setQuantity(temp->second->getQuantity()+amount); //set the quantity to the new one by adding it to the old one

            std::cout<<"Product restocked successfully.\n";
        } else {
            std::cout<<"Invalid restock amount";
        }
    } else {
        std::cout<<"Product not Found.\n";
    }

}
