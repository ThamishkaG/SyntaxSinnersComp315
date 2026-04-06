#include "Inventory.h"
#include <iostream>
#include <map>
#include <memory>
#include <vector>
#include <algorithm>
#include <mutex>

//using namespace std;

//Zine Duma (224007195)
void Inventory::addProduct( std::shared_ptr<Product> product){
    // if we used an object instead of a pointer:
    // Polymorphism would have been lost, derived class behavior broken and
    // Requirement of smart pointer would not have been adhered to.

    // exception: Check for null pointer to prevent undefined behavior
    if (!product) {
        throw std::invalid_argument("Cannot add null product to inventory");
    }

    std::lock_guard<std::mutex> lock(inventoryMutex);

    int id = product-> getProductID(); // getting it from the product class btw

    // condition to check whether the product ID given exists in the system
    if( products.find(id) != products.end()){
        // exception: Use exception instead of cout for error handling
        throw std::runtime_error("Product with ID " + std::to_string(id) + " already exists");
    }


    products[id] = product;
    std::cout<<" Product has been added to the system successfully. \n";
}

void Inventory::displayAllProducts() const{
    std::lock_guard<std::mutex> lock(inventoryMutex);

    if ( products.empty()){
        // exception: Use exception instead of cout for empty inventory
        throw std::runtime_error("Cannot display: There are no products in inventory");
    }

    // for each iteration we have a key value pair.
    for(const std::pair<const int, std::shared_ptr<Product>> &pair: products){

        // exception: Validate each product pointer before accessing
        if (!pair.second) {
            throw std::runtime_error("Corrupted inventory: Null product found with ID " +
                                    std::to_string(pair.first));
        }

        //This is needed so that we can access the actual product since it is a pointer.
        const std::shared_ptr<Product>& product = pair.second;
        std::cout<< "Product ID: " << product-> getProductID() <<  " | Product Name: " <<product-> getName()
                 << " | Product Price: "<< product-> getPrice() << " | Quantity: " << product-> getQuantity()<< "\n";

    }

}


void Inventory::sortByPrice(){ // this method sorts from cheapest to most expensive
    std::lock_guard<std::mutex> lock(inventoryMutex);

    // exception: Check if we have enough products to sort meaningfully
    if (products.size() < 2) {
        throw std::runtime_error("Cannot sort: Need at least 2 products to sort by price");
    }

    std::vector<std::shared_ptr<Product>> productList;// we had to use a vector because a map sorts by key only and not values

    for( const std::pair<const int, std::shared_ptr<Product>>& pair : products){
        // exception: Validate each product before adding to vector
        if (!pair.second) {
            throw std::runtime_error("Cannot sort by price: Null product found with ID " +
                                    std::to_string(pair.first));
        }
        productList.push_back(pair.second); // this copies each product pointer to the list
    }

    std::sort(productList.begin(),productList.end(),
         []( const std::shared_ptr<Product>& a,
             const std::shared_ptr<Product>& b){
              // exception: Validate during comparison to prevent crashes
              if (!a || !b) {
                  throw std::runtime_error("Null product encountered during price sort comparison");
              }
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

     // exception: Check if we have enough products to sort meaningfully
     if (products.size() < 2) {
         throw std::runtime_error("Cannot sort: Need at least 2 products to sort by quantity");
     }

     std::vector<std::shared_ptr<Product>> productList;// we had to use a vector because a map sorts by key only and not values

    for( const std::pair<const int, std::shared_ptr<Product>>& pair : products){
        // exception: Validate each product before adding to vector
        if (!pair.second) {
            throw std::runtime_error("Cannot sort by quantity: Null product found with ID " +
                                    std::to_string(pair.first));
        }
        productList.push_back(pair.second); // this copies each product pointer to the list
    }

    std::sort(productList.begin(),productList.end(),
         []( const std::shared_ptr<Product>& a,
             const std::shared_ptr<Product>& b){
              // exception: Validate during comparison to prevent crashes
              if (!a || !b) {
                  throw std::runtime_error("Null product encountered during quantity sort comparison");
              }
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

    if (productId < 0) {
       throw std::invalid_argument("Product ID cannot be negative");
    }
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

    if (name.empty()) {
        throw std::invalid_argument("Product name cannot be empty");
    }
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

    std::lock_guard<std::mutex> lock(inventoryMutex);
    if (productId < 0) {
        throw std::invalid_argument("Product ID cannot be negative");
    }
    //search using key
    std::map<int, std::shared_ptr<Product>>:: iterator temp = products.find(productId);

    if (temp != products.end()) { //if we dont reach the end its successsful
        products.erase(temp);

        std::cout << "Product successfully removed";
    } else {
        std::cout << "Product not found. Cannot be removed";

    }
}


bool Inventory::processOrder(const Order& order) {
    std::lock_guard<std::mutex> lock(inventoryMutex);

    //validation
    if (order.getProductID() < 0) {
        throw std::invalid_argument("Product ID cannot be negative");
    }

    std::map<int, std::shared_ptr<Product>>:: iterator temp = products.find(order.getProductID());

    if (temp == products.end()) {
        std::cout << "Order cannot be fulfiled: Product ID " << order.getProductID() << "not found.\n";
        return false;
    }

    if (temp->second-> getQuantity() < order.getQuantity()) {
        std::cout << "Order cannot be fulfilled: Insufficient quantity for Product ID " << order.getProductID() << ".\n";
        std::cout << "Requested: " << order.getQuantity()
                  << " | Available: " << temp->second->getQuantity() << ".\n";
        return false; // insufficient quantity, order cannot be fulfiled
    }

    temp->second->reduceQuantity(order.getQuantity());

    std::cout << "Order fulfiled successfully.\n";
    return true;

}


void Inventory::restockProduct(int productId, int amount) {

    //since changing the quantity of a product modifies, it must be locked to prevent race conditions
    std::lock_guard<std::mutex> lock(inventoryMutex);
    if (amount <= 0) {
        throw std::invalid_argument("Restock amount must be positive");
    }

    std::map<int, std::shared_ptr<Product>>::iterator temp = products.find(productId);

    if (temp != products.end()) {
        if (amount > 0) {
            temp->second->increaseQuantity(amount); // update the quantity using the superclass method directly innstead of using setQuantity

            std::cout<<"Product restocked successfully.\n";
        } else {
            std::cout<<"Invalid restock amount";
        }
    } else {
        std::cout<<"Product not Found.\n";
    }

}
