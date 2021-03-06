#include "../inc/OrdersManager.h"

string OrderManager::get_uuid() 
{
    static random_device dev;
    static mt19937 rng(dev());

    uniform_int_distribution<int> dist(0, 15);

    const char *v = "0123456789abcdef";
    const bool dash[] = { 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0 };

    string res;
    for (int i = 0; i < 16; i++) 
    {
        if (dash[i]) res += "-";
        res += v[dist(rng)];
        res += v[dist(rng)];
    }
    return res;
}

float OrderManager::getRandomNumber(float min, float max) 
{
    // Making rng static ensures that it stays the same
    // Between different invocations of the function
    static default_random_engine rng;

    uniform_real_distribution<float> dist(min, max); 
    return dist(rng); 
}

void OrderManager::generateFakeOrders(uint32_t quantity)
{
    log("Generating fake orders");
    memset(orders, 0, quantity);

    for (uint32_t order_idx = 0; order_idx < quantity; order_idx++)
    {
        orders[order_idx] = get_uuid();
    }

    char new_msg[100]; 
    snprintf(new_msg, 100, "%d generated...", quantity);
    log(new_msg);
}

void OrderManager::log(char* message)
{
    char *ctime_no_newline;
    m_sys = chrono::system_clock::now();
    time_t log_time = chrono::system_clock::to_time_t(m_sys);
    ctime_no_newline = strtok(ctime(&log_time), "\n");
    // last_printed_log = chrono::system_clock::to_time_t(m_sys);
    cout << ctime_no_newline << " > " << message << endl;
    // cout << message << endl;
}

void OrderManager::fakeSaveOnDb(uint32_t order_idx)
{
    string id = orders[order_idx];
    char message[100];
    snprintf(message, 100, "Order [%s] [%d] was successfully prosecuted.", id.c_str(), order_idx);
    log(message);
    float time_to_sleep_ms = getRandomNumber(0.0, 1.0) * 1000;
    _sleep(time_to_sleep_ms);
}

void OrderManager::processOrders()
{
    for (uint32_t order = 0; order < FAKE_ORDER_NUMBER; order++)
    {
        fakeSaveOnDb(order);
        orders_processed += 1;

        if(time(NULL) - last_printed_log > 5)
        {
            last_printed_log = time(NULL);    
            char message[100];
            snprintf(message, 100, "Total orders executed: {%d}/{%d}", orders_processed, FAKE_ORDER_NUMBER);
            log(message);
        }
    }
}