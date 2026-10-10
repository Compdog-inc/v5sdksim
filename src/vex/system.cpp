#include "vex/v5.h"

#include <chrono>

extern "C"
{
    uint32_t vexSystemTimeGet(void)
    {
        // TODO: implement
        return static_cast<uint32_t>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count());
    }

    void vexGettime(struct time *pTime)
    {
        // TODO: implement
        std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
        std::time_t now_c = std::chrono::system_clock::to_time_t(now);
        std::tm *local_time = std::localtime(&now_c);
        pTime->ti_hour = local_time->tm_hour;
        pTime->ti_min = local_time->tm_min;
        pTime->ti_sec = local_time->tm_sec;
        pTime->ti_hund = static_cast<uint8_t>(std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count() % 1000 / 10);
    }

    void vexGetdate(struct date *pDate)
    {
        // TODO: implement
        std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
        std::time_t now_c = std::chrono::system_clock::to_time_t(now);
        std::tm *local_time = std::localtime(&now_c);
        pDate->da_year = static_cast<uint16_t>(local_time->tm_year + 1900);
        pDate->da_mon = static_cast<uint8_t>(local_time->tm_mon + 1);
        pDate->da_day = static_cast<uint8_t>(local_time->tm_mday);
    }

    uint64_t vexSystemHighResTimeGet(void)
    {
        // TODO: implement
        return static_cast<uint64_t>(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count());
    }

    uint64_t vexSystemPowerupTimeGet(void)
    {
        static auto start_time = std::chrono::steady_clock::now();
        // TODO: implement
        return static_cast<uint64_t>(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - start_time).count());
    }
};