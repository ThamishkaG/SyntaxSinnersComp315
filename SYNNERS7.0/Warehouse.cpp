#include "Warehouse.h"
#include "Inventory.h"
#include <iostream>
#include "Order.h"
static std::mutex coutMutex;

Warehouse::Warehouse(int id,std::shared_ptr<Inventory> inventory)
    : warehouseID(id),inventory(inventory)
{
}
void Warehouse::processOrders(std::vector<Order>& orders)//Each thread gets created
{
    for (Order& order :orders)
   {
    std::lock_guard<std::mutex> lock(threads_mutex);
    threads.emplace_back(&Warehouse::processOneOrder,this,std::ref(order));
   }

}
void Warehouse::processOneOrder(const Order& order)
{
    bool success = inventory->processOrder(order);

    std::lock_guard<std::mutex> lock(coutMutex);

    if (success)
        std::cout << "Order " << order.getOrderID() << " processed\n";
    else
        std::cout << "Order cannot be fulfilled: Product ID "
                  << order.getProductID() << " not found\n";
}
void Warehouse::waitForThreads()
{
    for (auto& t : threads)
    {
        if (t.joinable())
        {
            t.join();
        }
    }
    threads.clear();
}


