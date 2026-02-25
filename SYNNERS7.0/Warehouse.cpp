#include "Warehouse.h"
#include "Inventory.h"
#include <iostream>
#include "Order.h"

Warehouse::Warehouse(int id,std::shared_ptr<Inventory> inventory)
    : warehouseID(id),inventory(inventory)
{
    //The constructor will be implemented in Phase 2
}
void Warehouse::processOrders(std::vector<Order>& orders)
{
     //The method will be implemented in Phase 2

}
void Warehouse::waitForThreads()
{
     //The logic for thread joining will be implemented in Phase 2
}

