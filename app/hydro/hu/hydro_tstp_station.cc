#include <alarm.h>
#include <transducer.h>

using namespace EPOS;

int kick()
{
    OStream cout;
    cout << "Watchdog init" << endl;

    Watchdog::enable();
    Watchdog::kick();

    while(Periodic_Thread::wait_next())
        Watchdog::kick();    

    return 0;
}

int main()
{
    if(Traits<Hydro_Board>::P3_enabled)
        new Water_Level(0, 3000000, Water_Level::ADVERTISED);

    // P5 is used for turbidity infrared actuator

    if(Traits<Hydro_Board>::P6_enabled)
        new Water_Turbidity(3, 3700000, Water_Turbidity::ADVERTISED);

    if(Traits<Hydro_Board>::P7_enabled)
        //new Rain(0, 1000000, Rain::ADVERTISED);
        new Water_Flow(0, 1000000, static_cast<Water_Flow::Mode>(Water_Flow::ADVERTISED | Water_Flow::CUMULATIVE));

    Periodic_Thread * watchdog = new Periodic_Thread(500 * 1000, kick);

    watchdog->join();

    Thread::self()->suspend();

    return 0;
}
