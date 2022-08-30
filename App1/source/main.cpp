/*main.cpp App1*/

#include "app1.h"

int main()
{
    app1 App1;

    std::thread Thread1(&app1::Thread1Function, std::ref(App1));
    std::thread Thread2(&app1::Thread2Function, std::ref(App1));
    Thread1.join();
    Thread2.join();

    return 0;
}
