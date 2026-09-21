#ifdef __cplusplus
extern "C"
{
#endif
    void autonomous(void);
    void initialize(void);
    void disabled(void);
    void competition_initialize(void);
    void opcontrol(void);
#ifdef __cplusplus
}
#endif

#include <chrono>
#include <thread>

int main(void)
{
    initialize();

    while (true)
    {
        opcontrol();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}