#include <iostream>
#include <memory>
#include <vector>
#include <thread>
#include <random>
#include <iomanip>
#include <string>
//our headers
#include "Inventory.h"
#include "Warehouse.h"
#include "Product.h"
#include "Perishable.h"
#include "NonPerishable.h"
#include "Order.h"

//methods to implement,prototypes
void displayMainMenu();//done
void populateSampleProducts(Inventory& inventory);std::vector<Order> generateSampleOrders(int numOrders);//done
std::vector<Order> generateSampleOrders(int numOrders);//done
void processOrdersMultiThreaded(Inventory& inventory, std::vector<Order>& orders);//done
void waitForUserInput();//done

int main()
{
    

}

void displayMainMenu() {

    std::cout << "\n========================================" << std::endl;
    std::cout << "              MAIN MENU" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "1. Add Product" << std::endl;
    std::cout << "2. Remove Product" << std::endl;
    std::cout << "3. Display All Products" << std::endl;
    std::cout << "4. Search Product by ID" << std::endl;
    std::cout << "5. Search Product by Name" << std::endl;
    std::cout << "6. Sort Products by Price" << std::endl;
    std::cout << "7. Sort Products by Quantity" << std::endl;
    std::cout << "8. Process Orders (Multi-threaded)" << std::endl;
    std::cout << "9. Restock Product" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "=======================================" << std::endl;
}

void populateSampleProducts(Inventory &inventory){

    //vector is easier to work with when handeling products when it comes to adding and removing
    std::vector<std::shared_ptr<Product>> sampleProducts;

    //a few nonperishable products(not food)
    sampleProducts.push_back(std::make_shared<NonPerishable>(101, "Laptop", 999.99, 10, 0.15, 0.10));
    sampleProducts.push_back(std::make_shared<NonPerishable>(102, "Mouse", 29.99, 50, 0.15, 0.00));
    sampleProducts.push_back(std::make_shared<NonPerishable>(103, "Keyboard", 79.99, 30, 0.15, 0.05));
    sampleProducts.push_back(std::make_shared<NonPerishable>(104, "Monitor", 299.99, 15, 0.15, 0.10));
    sampleProducts.push_back(std::make_shared<NonPerishable>(105, "USB Cable", 9.99, 100, 0.15, 0.00));
    //a fedw perishable products
    sampleProducts.push_back(std::make_shared<Perishable>(201, "Milk", 3.99, 20, 0.00, 0.00, "2024-12-15"));
    sampleProducts.push_back(std::make_shared<Perishable>(202, "Bread", 2.49, 25, 0.00, 0.00, "2024-12-10"));
    sampleProducts.push_back(std::make_shared<Perishable>(203, "Eggs", 4.99, 15, 0.00, 0.00, "2024-12-20"));
    sampleProducts.push_back(std::make_shared<Perishable>(204, "Cheese", 5.99, 12, 0.00, 0.05, "2025-01-01"));
    sampleProducts.push_back(std::make_shared<Perishable>(205, "Yogurt", 3.49, 18, 0.00, 0.00, "2024-12-25"));
    //a few non perishable food products
    sampleProducts.push_back(std::make_shared<NonPerishable>(301, "Rice", 12.99, 40, 0.00, 0.00));
    sampleProducts.push_back(std::make_shared<NonPerishable>(302, "Pasta", 1.99, 60, 0.00, 0.00));
    sampleProducts.push_back(std::make_shared<NonPerishable>(303, "Canned Soup", 2.49, 35, 0.00, 0.00));
    sampleProducts.push_back(std::make_shared<NonPerishable>(304, "Coffee", 8.99, 25, 0.00, 0.10));
    sampleProducts.push_back(std::make_shared<NonPerishable>(305, "Tea", 4.99, 30, 0.00, 0.00));
 
    //all all created products toinventory
    for (const auto& product : sampleProducts){
        try{
            inventory.addProduct(product);
        }catch (const std::exception& e){
            std::cout << "Warning: " << e.what() << std::endl;
        }
    }
    
     std::cout << "Added " << sampleProducts.size() << " sample products to inventory." << std::endl;//confirmation

}

std::vector<Order> generateSampleOrders(int numOrders){
    
    std::vector<Order> orders;
    
    // Available product IDs from what we created
    int productIDs[] = {101, 102, 103, 104, 105, 201, 202, 203, 204, 205, 301, 302, 303, 304, 305};
    int numProducts = 15;
    
    // Simple random number generation without complex distributions
    srand(static_cast<unsigned int>(time(NULL)));
    
    for (int i = 1; i <= numOrders; i++){
        int randomIndex = rand() % numProducts;
        int productID = productIDs[randomIndex];
    
        // Random quantity between 1 and 5
        int quantity = (rand() % 5) + 1;
        
        // Create order
        Order order(i, productID, quantity);
        orders.push_back(order);
    }
    
    return orders;
}
void processOrdersMultiThreaded(Inventory &inventory, std::vector<Order> &orders)
{
    std::cout << "\n--- Processing Orders with Multiple Threads ---" << std::endl;
    std::cout << "Thread ID | Order ID | Product ID | Quantity | Status" << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl;
    
    // Create warehouse objs
    std::vector<Warehouse> warehouses;
    std::vector<std::thread> threads;
    
    // Create 3
    std::shared_ptr<Inventory> inventoryPtr = std::make_shared<Inventory>(inventory);
    
    for (int i = 0; i < 3; i++){
        Warehouse warehouse(i + 1, inventoryPtr);
        warehouses.push_back(warehouse);
    }
    
    // Distribute orders to warehouses(round robin from comp313)
    std::vector<std::vector<Order>> orderBatches(3);
    for (size_t i = 0; i < orders.size(); i++){
        int warehouseIndex = i % 3;
        orderBatches[warehouseIndex].push_back(orders[i]);
    }
    
    // Create and start threads for each warehouse
    for (int i = 0; i < 3; i++){
        threads.push_back(std::thread([&warehouses, i, &orderBatches]() {
            warehouses[i].processOrders(orderBatches[i]);
        }));
    }
    
    // Wait for all threads to finish
    for (auto& thread : threads){
        if (thread.joinable()){
            thread.join();
        }
    }
    
    std::cout << "--------------------------------------------------------" << std::endl;
    std::cout << "All orders have been processed!" << std::endl;
}

void waitForUserInput()
{
    std::cout << "Press Enter to continue...";
    std::cin.ignore();
    std::cin.get();
}
