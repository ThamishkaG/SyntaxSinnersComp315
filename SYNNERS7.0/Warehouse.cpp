#include "Warehouse.h"
#include "Inventory.h"
#include <iostream>
#include "Order.h"

Warehouse::Warehouse(int id,std::shared_ptr<Inventory> inventory)
    : warehouseID(id),inventory(inventory)
{
}
void Warehouse::processOrders(std::vector<Order>& orders)//Each thread gets created
{
    for (const Order& order :orders)
   {
    threads.emplace_back(&Warehouse::processOneOrder,this,order);
   }

}
void Warehouse::processOneOrder(Order order)//Each thread executes this function
{
    bool approved = inventory ->processOrder(order);
    if (approved)
    {
        std::cout<<"Warehouse: "<<warehouseID<< " order approved.Successfully processed\n"
    }
    else
    {
        std::cout<<"Warehouse: "<< warehouseID<<" order NOT approved. Unsuccesfull order\n "
    }
}
void Warehouse::waitForThreads()
{
     for (std::thread &t : threads)
     {
        if (t.joinable())
        {
            t.join();
        }
     }
}



