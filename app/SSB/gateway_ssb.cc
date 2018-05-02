#include <transducer.h>
#include <smart_data.h>
#include <utility/ostream.h>
#include <gpio.h>

using namespace EPOS;

IF<Traits<USB>::enabled, USB, UART>::Result io;

typedef Smart_Data_Common::DB_Series DB_Series;
typedef Smart_Data_Common::DB_Record DB_Record;
typedef TSTP::Coordinates Coordinates;
typedef TSTP::Region Region;

const unsigned int INTEREST_PERIOD = 30 * 1000000;
const unsigned int INTEREST_EXPIRY = INTEREST_PERIOD;

template<typename T>
void print(const T & d)
{
    bool was_locked = CPU::int_disabled();
    if(!was_locked)
        CPU::int_disable();
    for(unsigned int i = 0; i < sizeof(T); i++)
        io.put(reinterpret_cast<const char *>(&d)[i]);
    for(unsigned int i = 0; i < 3; i++)
        io.put('X');
    if(!was_locked)
        CPU::int_enable();
}

template<typename T>
class Printer: public Smart_Data_Common::Observer
{
public:
    Printer(T * t) : _data(t) {
        _data->attach(this);
        print(_data->db_series());
    }
    ~Printer() { _data->detach(this); }

    void update(Smart_Data_Common::Observed * obs) {
        print(_data->db_record());
    }

private:
    T * _data;
};

void setup() 
{
    // Get epoch time from serial
    TSTP::Time epoch = 0;
    while(!io.ready_to_get());
    char c = io.get();
    if(c != 'X') {
        epoch += c - '0';
        while(!io.ready_to_get());
        c = io.get();
        while(c != 'X') {
            epoch *= 10;
            epoch += c - '0';
            while(!io.ready_to_get());
            c = io.get();
        }
        TSTP::epoch(epoch);
    }

    Alarm::delay(5000000);
}

int main()
{
    //OStream cout;
    setup();
    /*
    Alarm::delay(5000000);
    cout << "Press any key to start..." << endl;
    while(!USB::ready_to_get());
    USB::get();
    cout << "Starting!" << endl;
    */

    // Interest center points
    //Coordinates center_room(150, 300, 125);
    Coordinates center_lights1(150, 50, 250);
    Coordinates center_lights2(-140, 50, 250);
    Coordinates center_lights3(430, 300, 250);
    Coordinates center_lights4(150, 300, 250);
    Coordinates center_lights5(-140, 300, 250);
    Coordinates center_lights7(150, 500, 250);
    Coordinates center_lights8(-140, 500, 250);
    Coordinates center_lux0(15, 0, 0);
    Coordinates center_temperature0(10, 0, 0);

    // Regions of interest
    //Region region_room(center_room, 1500, 0, -1);
    Region region_lights1(center_lights1, 0, 0, -1);
    Region region_lights2(center_lights2, 0, 0, -1);
    Region region_lights3(center_lights3, 0, 0, -1);
    Region region_lights4(center_lights4, 0, 0, -1);
    Region region_lights5(center_lights5, 0, 0, -1);
    Region region_lights7(center_lights7, 0, 0, -1);
    Region region_lights8(center_lights8, 0, 0, -1);
    Region region_lux0(center_lux0, 0, 0, -1);
    Region region_temperature0(center_temperature0, 0, 0, -1);

    // Data of interest
    //Current current(region_room, INTEREST_EXPIRY, INTEREST_PERIOD);
    Current current_lights1(region_lights1, INTEREST_EXPIRY, INTEREST_PERIOD);
    Current current_lights2(region_lights2, INTEREST_EXPIRY, INTEREST_PERIOD);
    Current current_lights3(region_lights3, INTEREST_EXPIRY, INTEREST_PERIOD);
    Current current_lights4(region_lights4, INTEREST_EXPIRY, INTEREST_PERIOD);
    Current current_lights5(region_lights5, INTEREST_EXPIRY, INTEREST_PERIOD);
    Current current_lights7(region_lights7, INTEREST_EXPIRY, INTEREST_PERIOD);
    Current current_lights8(region_lights8, INTEREST_EXPIRY, INTEREST_PERIOD);

    Luminous_Intensity lux(region_lux0, INTEREST_EXPIRY, INTEREST_PERIOD);
    Temperature temperature(region_temperature0, INTEREST_EXPIRY, INTEREST_PERIOD);

    // Data transforms and aggregators
    Percent_Transform<Luminous_Intensity> lux_transform(0, 1833);

    // Printers to output received messages to serial
    Printer<Current> p1(&current_lights1);
    Printer<Current> p2(&current_lights2);
    Printer<Current> p3(&current_lights3);
    Printer<Current> p4(&current_lights4);
    Printer<Current> p5(&current_lights5);
    Printer<Current> p7(&current_lights7);
    Printer<Current> p8(&current_lights8);
    Printer<Luminous_Intensity> p9(&lux);
    Printer<Temperature> p10(&temperature);

    /*
    while(true) {
        char a, b;
        cout << "Enter dimmer value to set: " << endl;
        while(!USB::ready_to_get());
        a = USB::get();
        cout << a;
        while(!USB::ready_to_get());
        b = USB::get();
        cout << b << endl;
        if(!(a < '0' || a > '9' || b < '0' || b > '9')) {
            int dim = (a - '0') * 10 + (b - '0');
            cout << "Setting dimmer value to " << dim << endl;
            current_lights1 = dim;
            current_lights2 = dim;
            current_lights3 = dim;
            current_lights4 = dim;
            current_lights5 = dim;
            current_lights7 = dim;
            current_lights8 = dim;
        }
    }
    */

    // Time-triggered actuators
    TSTP::Time last_actuation = 0;
    while(true) {
        Alarm::delay(INTEREST_PERIOD / 2);
        TSTP::Time t = lux.time();
        if(t > last_actuation) {
            Luminous_Intensity::Value result;
            lux_transform.apply(&result, &lux);
            current_lights1 = result;
            current_lights2 = result;
            current_lights3 = result;
            current_lights4 = result;
            current_lights5 = result;
            current_lights7 = result;
            current_lights8 = result;
        }
        last_actuation = t;
    }

    Thread::self()->suspend();

    return 0;
}
