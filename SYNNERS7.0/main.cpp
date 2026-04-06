#include <iostream>
#include <memory>
#include <vector>
#include <thread>
#include <cstdlib>
#include <ctime>
#include <limits>

// Headers
#include "Inventory.h"
#include "Warehouse.h"
#include "Product.h"
#include "Perishable.h"
#include "NonPerishable.h"
#include "Order.h"

// Constants (NO MAGIC NUMBERS)
const int NUM_WAREHOUSES = 3;
const int NUM_PRODUCTS = 15;
const int MAX_ORDER_QTY = 5;

// Function prototypes
void displayMainMenu();
void populateSampleProducts(std::shared_ptr<Inventory> inventory);
std::vector<Order> generateSampleOrders(int numOrders);
void processOrdersMultiThreaded(std::shared_ptr<Inventory> inventory, std::vector<Order>& orders);
void waitForUserInput();

int main()
{
    srand(static_cast<unsigned int>(time(nullptr))); // Seed ONCE

    // ✅ Shared Inventory across entire system
    std::shared_ptr<Inventory> inventory = std::make_shared<Inventory>();

    bool running = true;

    while (running)
    {
        displayMainMenu();

        int choice;
        std::cout << "Enter choice: ";
        std::cin >> choice;

        switch (choice)
        {
            case 1:
            {
                populateSampleProducts(inventory);
                std::cout << "Sample products added.\n";
                waitForUserInput();
                break;
            }

            case 2:
            {
                int id;
                std::cout << "Enter product ID to remove: ";
                std::cin >> id;

                inventory->removeProduct(id);
                std::cout << "Product removed.\n";
                waitForUserInput();
                break;
            }

            case 3:
            {
                inventory->displayAllProducts();
                waitForUserInput();
                break;
            }

            case 4:
            {
                int id;
                std::cout << "Enter product ID: ";
                std::cin >> id;

                inventory->searchProduct(id);
                waitForUserInput();
                break;
            }

            case 5:
            {
                std::string name;
                std::cout << "Enter product name: ";

                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, name);

                inventory->searchProduct(name);
                waitForUserInput();
                break;
            }

            case 6:
            {
                inventory->sortByPrice();
                std::cout << "Products sorted by price.\n";
                waitForUserInput();
                break;
            }

            case 7:
            {
                inventory->sortByQuantity();
                std::cout << "Products sorted by quantity.\n";
                waitForUserInput();
                break;
            }

            case 8:
            {
                int numOrders;
                std::cout << "Enter number of orders: ";
                std::cin >> numOrders;

                auto orders = generateSampleOrders(numOrders);

                processOrdersMultiThreaded(inventory, orders);
                waitForUserInput();
                break;
            }

            case 9:
            {
                int id, qty;
                std::cout << "Enter product ID to restock: ";
                std::cin >> id;

                std::cout << "Enter quantity: ";
                std::cin >> qty;

                inventory->restockProduct(id, qty);
                std::cout << "Product restocked.\n";
                waitForUserInput();
                break;
            }

            case 0:
            {
                std::cout << "Exiting program...\n";
                running = false;
                break;
            }

            default:
            {
                std::cout << "Invalid choice.\n";
                waitForUserInput();
            }
        }
    }

    return 0;
}

void displayMainMenu()
{
    std::cout << "\n========== MAIN MENU ==========\n";
    std::cout << "1. Add Sample Products\n";
    std::cout << "2. Remove Product\n";
    std::cout << "3. Display All Products\n";
    std::cout << "4. Search by ID\n";
    std::cout << "5. Search by Name\n";
    std::cout << "6. Sort by Price\n";
    std::cout << "7. Sort by Quantity\n";
    std::cout << "8. Process Orders (Multi-threaded)\n";
    std::cout << "9. Restock Product\n";
    std::cout << "0. Exit\n";
    std::cout << "===============================\n";
}

void populateSampleProducts(std::shared_ptr<Inventory> inventory)
{
    std::vector<std::shared_ptr<Product>> products;

    products.emplace_back(std::make_shared<NonPerishable>(101, "Laptop", 999.99, 0.15, 0.10, 10));
    products.emplace_back(std::make_shared<NonPerishable>(102, "Mouse", 29.99, 0.15, 0.00, 50));

    products.emplace_back(std::make_shared<Perishable>(201, "Milk", 3.99, "2024-12-15", 0.00, 0.00, 20));
    products.emplace_back(std::make_shared<Perishable>(202, "Bread", 2.49, "2024-12-10", 0.00, 0.00, 25));

    for (auto& p : products)
    {
        inventory->addProduct(p);
    }

    std::cout << products.size() << " products added.\n";
}

std::vector<Order> generateSampleOrders(int numOrders)
{
    std::vector<Order> orders;

    for (int i = 1; i <= numOrders; i++)
    {
        int productIDs[] = {
            101,102,103,104,105,
            201,202,203,204,205,
            301,302,303,304,305
        };

        int randomIndex = rand() % 15;
        int productID = productIDs[randomIndex];
        int quantity = (rand() % MAX_ORDER_QTY) + 1;

        orders.emplace_back(i,productID, quantity);
    }

    return orders;
}
void processOrdersMultiThreaded(std::shared_ptr<Inventory> inventory, std::vector<Order>& orders)
{
    std::cout << "\n--- Processing Orders ---\n";

    std::vector<std::shared_ptr<Warehouse>> warehouses;
    std::vector<std::thread> threads;

    // ✅ SAME shared inventory passed here
    for (int i = 0; i < NUM_WAREHOUSES; i++)
    {
        warehouses.emplace_back(std::make_shared<Warehouse>(i + 1, inventory));
    }

    // Distribute orders (round-robin)
    std::vector<std::vector<Order>> batches(NUM_WAREHOUSES);

    for (size_t i = 0; i < orders.size(); i++)
    {
        batches[i % NUM_WAREHOUSES].push_back(orders[i]);
    }

    // Launch threads
    for (int i = 0; i < NUM_WAREHOUSES; i++)
    {
        threads.emplace_back([&warehouses, &batches, i]()
        {
            warehouses[i]->processOrders(batches[i]);
        });
    }

    // Join threads
    for (auto& t : threads)
    {
        if (t.joinable())
            t.join();
    }

    std::cout << "All orders processed.\n";
}

void waitForUserInput()
{
    std::cout << "Press Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}
