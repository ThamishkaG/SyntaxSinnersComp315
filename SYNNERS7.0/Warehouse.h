#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <vector>
#include <thread>
#include <memory>

class Inventory;   // Forward declaration
class Order;       // Forward declaration


class Warehouse
{

    public:
        Warehouse(int id,std::shared_ptr<Inventory> inventory);
        void processOrders(std::vector<Order>& orders);
        void waitForThreads();

    protected:

    private:
        int warehouseID;
        std:: shared_ptr<Inventory> inventory;
        std::vector<std::thread> threads;
};

#endif // WAREHOUSE_H
