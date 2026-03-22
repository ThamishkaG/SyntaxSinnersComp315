#include <iostream>
#include <memory>
#include <vector>
#include <thread>
#include <random>
#include <iomanip>
#include <string>

#include "Inventory.h"
#include "Warehouse.h"
#include "Product.h"
#include "Perishable.h"
#include "NonPerishable.h"
#include "Order.h"

void displayMainMenu();
void populateSampleProducts(Inventory& inventory);std::vector<Order> generateSampleOrders(int numOrders);
void processOrdersMultiThreaded(Inventory& inventory, std::vector<Order>& orders);
void waitForUserInput();
int main()
{
    cout << "Hello world!" << endl;
    return 0;
    //project compiles just fine but some called methods aren't defined therefore there's no output
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
    std::cout << "========================================" << std::endl;
}
