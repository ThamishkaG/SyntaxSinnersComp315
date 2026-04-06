#ifndef WAREHOUSE_H
#define WAREHOUSE_H
#include <mutex>
#include <vector>
#include <thread>
#include <memory>

class Inventory;   // Forward declaration
class Order;       // Forward declaration


class Warehouse
{

    public:
        Warehouse(int id,std::shared_ptr<Inventory> inventory);

        //explicit deletion of copy operations
        Warehouse(const Warehouse&)=delete;
        Warehouse& operator=(const Warehouse&)=delete;

        void processOrders(std::vector<Order>& orders);
        void processOneOrder(const Order& order);
        void waitForThreads();

    protected:

    private:
        int warehouseID;
        std:: shared_ptr<Inventory> inventory;
        std::vector<std::thread> threads;
        std::mutex threads_mutex;
};

#endif // WAREHOUSE_H
