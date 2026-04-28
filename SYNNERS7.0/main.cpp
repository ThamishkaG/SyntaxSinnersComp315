#include <iostream>
#include <memory>
#include <vector>
#include <thread>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <string>

// Headers
#include "Inventory.h"
#include "Warehouse.h"
#include "Product.h"
#include "Perishable.h"
#include "NonPerishable.h"
#include "Order.h"

// Constants (NO MAGIC NUMBERS)
const int NUM_WAREHOUSES = 3;
const int MAX_ORDER_QTY = 5;

// Function prototypes
void displayMainMenu();
void populateSampleProducts(std::shared_ptr<Inventory> inventory);
std::vector<Order> generateSampleOrders(int numOrders);
void processOrdersMultiThreaded(std::shared_ptr<Inventory> inventory, std::vector<Order>& osrders);
void waitForUserInput();
void clearInputStream();

int main()
{
    // Seed random number generator ONCE at program start
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    
    // Create shared Inventory across entire system
    std::shared_ptr<Inventory> inventory = std::make_shared<Inventory>();
    
    int choice = 0;
    
    do {
        displayMainMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cout << std::endl;
        
        try {
            switch (choice) {
                case 1: { // Add Sample Products
                    populateSampleProducts(inventory);
                    std::cout << "Sample products added successfully!" << std::endl;
                    break;
                }
                
                case 2: { // Remove Product
                    std::cout << "--- Remove Product ---" << std::endl;
                    int id;
                    std::cout << "Enter product ID to remove: ";
                    std::cin >> id;
                    inventory->removeProduct(id);
                    break;
                }
                
                case 3: { // Display All Products
                    std::cout << "\n--- All Products in Inventory ---" << std::endl;
                    std::cout << "========================================" << std::endl;
                    try {
                        inventory->displayAllProducts();
                    } catch (const std::exception& e) {
                        std::cout << "Error: " << e.what() << std::endl;
                    }
                    std::cout << "========================================" << std::endl;
                    break;
                }
                
                case 4: { // Search by ID
                    std::cout << "--- Search Product by ID ---" << std::endl;
                    int id;
                    std::cout << "Enter product ID: ";
                    std::cin >> id;
                    inventory->searchProduct(id);
                    break;
                }
                
                case 5: { // Search by Name
                    std::cout << "--- Search Product by Name ---" << std::endl;
                    std::string name;
                    std::cout << "Enter product name: ";
                    clearInputStream();
                    std::getline(std::cin, name);
                    inventory->searchProduct(name);
                    break;
                }
                
                case 6: { // Sort by Price
                    std::cout << "\n--- Products Sorted by Price (Cheapest to Expensive) ---" << std::endl;
                    std::cout << "========================================" << std::endl;
                    inventory->sortByPrice();
                    std::cout << "========================================" << std::endl;
                    break;
                }
                
                case 7: { // Sort by Quantity
                    std::cout << "\n--- Products Sorted by Quantity (Lowest to Highest) ---" << std::endl;
                    std::cout << "========================================" << std::endl;
                    inventory->sortByQuantity();
                    std::cout << "========================================" << std::endl;
                    break;
                }
                
                case 8: { // Process Orders (Multi-threaded)
                    std::cout << "--- Process Customer Orders (Multi-threaded) ---" << std::endl;
                    int numOrders;
                    std::cout << "How many orders to process? (5-20 recommended): ";
                    std::cin >> numOrders;
                    
                    if (numOrders <= 0) {
                        std::cout << "Number of orders must be positive!" << std::endl;
                        break;
                    }
                    
                    // Generate random orders
                    std::vector<Order> orders = generateSampleOrders(numOrders);
                    std::cout << "Generated " << orders.size() << " orders." << std::endl;
                    
                    // Process orders with multiple threads
                    processOrdersMultiThreaded(inventory, orders);
                    
                    // Show updated inventory after processing
                    std::cout << "\n--- Updated Inventory After Order Processing ---" << std::endl;
                    try {
                        inventory->displayAllProducts();
                    } catch (const std::exception& e) {
                        std::cout << "Error: " << e.what() << std::endl;
                    }
                    break;
                }
                
                case 9: { // Restock Product
                    std::cout << "--- Restock Product ---" << std::endl;
                    int id, amount;
                    std::cout << "Enter product ID to restock: ";
                    std::cin >> id;
                    std::cout << "Enter quantity to add: ";
                    std::cin >> amount;
                    
                    if (amount <= 0) {
                        std::cout << "Restock amount must be positive!" << std::endl;
                        break;
                    }
                    
                    inventory->restockProduct(id, amount);
                    break;
                }
                
                case 0: { // Exit
                    std::cout << "Thank you for using the Inventory Management System!" << std::endl;
                    std::cout << "Exiting program..." << std::endl;
                    break;
                }
                
                default:
                    std::cout << "Invalid choice. Please enter a number between 0 and 9." << std::endl;
            }
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
            std::cout << "Please try again." << std::endl;
        }
        
        if (choice != 0) {
            std::cout << std::endl;
            waitForUserInput();
        }
        
        // Clear input buffer error flags
        std::cin.clear();
        
    } while (choice != 0);
    
    return 0;
}

void displayMainMenu()
{
    std::cout << "\n========================================" << std::endl;
    std::cout << "         INVENTORY MANAGEMENT SYSTEM" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "1. Add Sample Products" << std::endl;
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

void populateSampleProducts(std::shared_ptr<Inventory> inventory)
{
    std::cout << "Adding sample products to inventory..." << std::endl;
    
    // Vector to hold all products
    std::vector<std::shared_ptr<Product>> products;
    
    // ============================================
    // NON-PERISHABLE PRODUCTS (Electronics)
    // Constructor: NonPerishable(ID, name, price, discount, tax, quantity)
    // ============================================
    
    // Electronics with various discounts and tax rates
    products.emplace_back(std::make_shared<NonPerishable>(101, "Laptop", 999.99, 0.10, 0.15, 10));
    products.emplace_back(std::make_shared<NonPerishable>(102, "Mouse", 29.99, 0.00, 0.15, 50));
    products.emplace_back(std::make_shared<NonPerishable>(103, "Keyboard", 79.99, 0.05, 0.15, 30));
    products.emplace_back(std::make_shared<NonPerishable>(104, "Monitor", 299.99, 0.10, 0.15, 15));
    products.emplace_back(std::make_shared<NonPerishable>(105, "USB Cable", 9.99, 0.00, 0.15, 100));
    
    // ============================================
    // PERISHABLE PRODUCTS (Food items)
    // Constructor: Perishable(ID, name, price, expiry, discount, tax, quantity)
    // ============================================
    
    // Dairy products (tax-free, no discount)
    products.emplace_back(std::make_shared<Perishable>(201, "Milk", 3.99, "2024-12-15", 0.00, 0.00, 20));
    products.emplace_back(std::make_shared<Perishable>(202, "Bread", 2.49, "2024-12-10", 0.00, 0.00, 25));
    products.emplace_back(std::make_shared<Perishable>(203, "Eggs", 4.99, "2024-12-20", 0.00, 0.00, 15));
    products.emplace_back(std::make_shared<Perishable>(204, "Cheese", 5.99, "2025-01-01", 0.05, 0.00, 12));
    products.emplace_back(std::make_shared<Perishable>(205, "Yogurt", 3.49, "2024-12-25", 0.00, 0.00, 18));
    
    // ============================================
    // NON-PERISHABLE PRODUCTS (Groceries)
    // Constructor: NonPerishable(ID, name, price, discount, tax, quantity)
    // ============================================
    
    // Grocery items (mostly tax-free)
    products.emplace_back(std::make_shared<NonPerishable>(301, "Rice", 12.99, 0.00, 0.00, 40));
    products.emplace_back(std::make_shared<NonPerishable>(302, "Pasta", 1.99, 0.00, 0.00, 60));
    products.emplace_back(std::make_shared<NonPerishable>(303, "Canned Soup", 2.49, 0.00, 0.00, 35));
    products.emplace_back(std::make_shared<NonPerishable>(304, "Coffee", 8.99, 0.10, 0.00, 25));
    products.emplace_back(std::make_shared<NonPerishable>(305, "Tea", 4.99, 0.00, 0.00, 30));
    
    // Add all products with error handling
    int successfulAdds = 0;
    for (auto& p : products)
    {
        try {
            inventory->addProduct(p);
            successfulAdds++;
        } catch (const std::exception& e) {
            std::cout << "Warning: " << e.what() << std::endl;
        }
    }
    
    std::cout << "Successfully added " << successfulAdds << " out of " 
              << products.size() << " sample products to inventory." << std::endl;
}

std::vector<Order> generateSampleOrders(int numOrders)
{
    std::vector<Order> orders;
    
    // Available product IDs (15 products total)
    int productIDs[] = {
        101, 102, 103, 104, 105,  // Electronics
        201, 202, 203, 204, 205,  // Perishable foods
        301, 302, 303, 304, 305   // Groceries
    };
    int numProducts = 15;
    
    for (int i = 1; i <= numOrders; i++)
    {
        // Random product ID selection
        int randomIndex = std::rand() % numProducts;
        int productID = productIDs[randomIndex];
        
        // Random quantity between 1 and MAX_ORDER_QTY
        int quantity = (std::rand() % MAX_ORDER_QTY) + 1;
        
        // Create order with status "Pending"
        Order order(i, productID, quantity);
        orders.push_back(order);
    }
    
    return orders;
}

void processOrdersMultiThreaded(std::shared_ptr<Inventory> inventory, std::vector<Order>& orders)
{
    std::cout << "\n========================================" << std::endl;
    std::cout << "      PROCESSING ORDERS (MULTI-THREADED)" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "Using " << NUM_WAREHOUSES << " warehouses to process " 
              << orders.size() << " orders..." << std::endl;
    std::cout << std::endl;
    
    // Create warehouse objects
    std::vector<std::shared_ptr<Warehouse>> warehouses;
    std::vector<std::thread> threads;
    
    // Create warehouses - each gets the SAME shared inventory
    for (int i = 0; i < NUM_WAREHOUSES; i++)
    {
        warehouses.emplace_back(std::make_shared<Warehouse>(i + 1, inventory));
        std::cout << "Warehouse " << (i + 1) << " created." << std::endl;
    }
    
    std::cout << std::endl;
    
    // Distribute orders to warehouses using round-robin
    std::vector<std::vector<Order>> batches(NUM_WAREHOUSES);
    
    for (size_t i = 0; i < orders.size(); i++)
    {
        int warehouseIndex = i % NUM_WAREHOUSES;
        batches[warehouseIndex].push_back(orders[i]);
    }
    
    // Display how many orders each warehouse gets
    for (int i = 0; i < NUM_WAREHOUSES; i++)
    {
        std::cout << "Warehouse " << (i + 1) << " received " 
                  << batches[i].size() << " orders." << std::endl;
    }
    
    std::cout << std::endl;
    std::cout << "--- Processing Results ---" << std::endl;
    
    // Launch threads for each warehouse
    for (int i = 0; i < NUM_WAREHOUSES; i++)
    {
        threads.emplace_back([&warehouses, &batches, i]()
        {
            warehouses[i]->processOrders(batches[i]);
            warehouses[i]->waitForThreads();
        });
    }
    
    // Wait for all threads to finish
    for (auto& t : threads)
    {
        if (t.joinable())
        {
            t.join();
        }
    }
    
    std::cout << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "All " << orders.size() << " orders have been processed!" << std::endl;
    std::cout << "========================================" << std::endl;
}

void waitForUserInput()
{
    std::cout << "Press Enter to continue...";
    clearInputStream();
    std::cin.get();
}

void clearInputStream()
{
    // Clears any leftover characters in the input buffer
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}