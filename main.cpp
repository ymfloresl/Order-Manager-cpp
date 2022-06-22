#include "inc/OrdersManager.h"
#include "src/OrdersManager.c"

int main()
{
    // // Using time point and system_clock
    chrono::time_point<chrono::system_clock> start, end;
  
    start = chrono::system_clock::now();
    OrderManager orders_manager;
    orders_manager.processOrders();
    end = chrono::system_clock::now();
  
    chrono::duration<double> elapsed_seconds = end - start;
    time_t end_time = chrono::system_clock::to_time_t(end);
  
    cout << "Computation finished at " << ctime(&end_time)
              << "elapsed time: " << elapsed_seconds.count() << "seconds\n";
}