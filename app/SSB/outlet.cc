#include <transducer.h>
#include <watchdog.h>

using namespace EPOS;

int kick()
{
    Watchdog::enable();
    Watchdog::kick();

    while(Periodic_Thread::wait_next())
        Watchdog::kick();    

    return 0;
}

int main()
{
    Periodic_Thread * watchdog = new Periodic_Thread(500 * 1000, kick);

    Current c0(0, 1000000, Current::COMMANDED);

    watchdog->join();

    return 0;
}
