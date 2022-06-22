#ifndef _ORDERS_MANAGER_H_
#define _ORDERS_MANAGER_H_
#include <iostream>
#include <ctime>
#include <chrono>
#include <cstring>

#include <random>
#include <string>
#include <thread>

#define FAKE_ORDER_NUMBER 1000

using namespace std;

class OrderManager
{
public:
    OrderManager()
    {        
        m_sys = chrono::system_clock::now();
        last_printed_log = chrono::system_clock::to_time_t(m_sys);
        generateFakeOrders(FAKE_ORDER_NUMBER);
    }

    void generateFakeOrders(uint32_t quantity);
    void fakeSaveOnDb(uint32_t order_idx);
    void log(char* message);
    void processOrders();

private:
    string get_uuid();
    float getRandomNumber(float min, float max);

    string orders[FAKE_ORDER_NUMBER];
    uint32_t orders_processed = 0;
    chrono::time_point<chrono::system_clock> m_sys;
    time_t last_printed_log;

};

#endif//_ORDERS_MANAGER_H_

