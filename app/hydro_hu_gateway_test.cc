#include <http.h>
#include <tstp.h>
#include <gpio.h>
#include <machine.h>
#include <smart_data.h>
#include <transducer.h>
#include <persistent_storage.h>
#include <utility/ostream.h>
#include <watchdog.h>

using namespace EPOS;

// Test time
const RTC::Microsecond INTEREST_EXPIRY = 1ull * 60 * 1000000;
const RTC::Microsecond HTTP_SEND_PERIOD = 1ull * 60 * 1000000;
const RTC::Microsecond INTEREST_PERIOD = INTEREST_EXPIRY / 2;
const unsigned int HTTP_SEND_PERIOD_MULTIPLY = 1;//2 * 12;

// Production time
// const RTC::Microsecond INTEREST_EXPIRY = 5ull * 60 * 1000000;
// const RTC::Microsecond HTTP_SEND_PERIOD = 30ull * 60 * 1000000;
// const RTC::Microsecond INTEREST_PERIOD = INTEREST_EXPIRY / 2;
// const unsigned int HTTP_SEND_PERIOD_MULTIPLY = 4;//2 * 12;

typedef Smart_Data_Common::DB_Record DB_Record;
typedef Smart_Data_Common::DB_Series DB_Series;
typedef Persistent_Ring_FIFO<DB_Record> Storage;

const char DOMAIN[]   = "hydro";
const char USERNAME[] = "hydro";
const char PASSWORD[] = "3ab0fd";

struct Credentials
{
    Credentials() {
        _size_domain = sizeof(DOMAIN) - 1;
        memcpy(_domain,DOMAIN,_size_domain);
        _size_username = sizeof(USERNAME) - 1;
        memcpy(_username,USERNAME,_size_username);
        _size_password = sizeof(PASSWORD) - 1;
        memcpy(_password,PASSWORD,_size_password);
    }
    char _size_domain;
    char _domain[sizeof(DOMAIN) - 1];
    char _size_username;
    char _username[sizeof(USERNAME) - 1];
    char _size_password;
    char _password[sizeof(PASSWORD) - 1];
}__attribute__((packed));

struct Attach_Payload
{
    void credentials(Credentials credentials){ _credentials = credentials; }
    void payload(DB_Series series){ _series = series; }
public:    
    Credentials _credentials;
    DB_Series _series;
}__attribute__((packed));

struct Put_Payload
{
    void credentials(Credentials credentials){ _credentials = credentials; }
    void payload(DB_Record smartdata){ _smartdata = smartdata; }
public:    
    Credentials _credentials;
    DB_Record _smartdata;
}__attribute__((packed));

Put_Payload put_payload;
Attach_Payload attach_payload;

Water_Flow_M170 * flow0;
Water_Flow_WSTAR * flow1;
Water_Flow_M170 * flow2;

int http_send()
{
    OStream cout;
    DB_Record e;

    M95 * m95 = M95::get(0);
    m95->on();
    int ret = 0;

    attach_payload.payload(flow0->db_series());
    while(ret <= 0)
    {
        cout << "sizeof payload: " << sizeof(Attach_Payload) << endl;
        ret = Quectel_HTTP::post("https://150.162.62.3/api/attach.php", &attach_payload, sizeof(Attach_Payload));
        cout << "post flow0 db_series: " << ret << endl;
    }
    ret = 0;

    attach_payload.payload(flow1->db_series());
    while(ret <= 0)
    {
        ret = Quectel_HTTP::post("https://150.162.62.3/api/attach.php", &attach_payload, sizeof(Attach_Payload));    
        cout << "post flow1 db_series: " << ret << endl;
    }
    ret = 0;

    attach_payload.payload(flow2->db_series());
    while(ret <= 0)
    {
        ret = Quectel_HTTP::post("https://150.162.62.3/api/attach.php", &attach_payload, sizeof(Attach_Payload));    
        cout << "post flow2 db_series: " << ret << endl;
    }
    ret = 0;

    m95->off();

    while(true) {
        for(unsigned int i = 0; i < HTTP_SEND_PERIOD_MULTIPLY; i++)
            Periodic_Thread::wait_next();

        cout << "http_send()" << endl;
        CPU::int_disable();
        if(Storage::pop(&e)) {
            CPU::int_enable();
            cout << "Turning GPRS on" << endl;
            m95->on();
            bool popped = true;
            while(popped) {
                cout << "Popped" << endl;
                put_payload.payload(e);
                cout << "sizeof db_record: " << sizeof(Put_Payload) << endl;
                ret = Quectel_HTTP::post("https://150.162.62.3/api/put.php", &put_payload, sizeof(Put_Payload));
                cout << "post = " << ret << endl;
                if(ret <= 0) {
                    CPU::int_disable();
                    Storage::push(e);
                    CPU::int_enable();
                    break;
                }
                Thread::self()->yield();
                CPU::int_disable();
                popped = Storage::pop(&e);
                CPU::int_enable();
            }
            if(ret > 0) {
                RTC::Microsecond t = m95->now();
                if(t)
                    TSTP::epoch(t);
            }
            cout << "Turning GPRS off" << endl;
            m95->off();
        } else
            CPU::int_enable();
        cout << "Going to sleep..." << endl;
    }
}

int tstp_work()
{
    OStream cout;
    cout << "tstp_work() init" << endl;

    cout << "epoch now = " << TSTP::absolute(TSTP::now()) / 1000000 << endl;

    cout << "Going to sleep..." << endl;
    while(Periodic_Thread::wait_next()) {

        cout << "tstp_work()" << endl;
        cout << "sleeping 10 seconds..." << endl;
        Alarm::delay(10000000);
        cout << "...woke up" << endl;

        Smart_Data_Common::DB_Record r0 = flow0->db_record();
        cout << "r0 = " << r0 << endl;
        Smart_Data_Common::DB_Record r1 = flow1->db_record();
        cout << "r1 = " << r1 << endl;
        Smart_Data_Common::DB_Record r2 = flow2->db_record();
        cout << "r2 = " << r2 << endl;

        CPU::int_disable();
        if(!flow0->expired()) {
            Storage::push(r0);
            cout << "push r0 OK" << endl;
        }
        if(!flow1->expired()) {
            Storage::push(r1);
            cout << "push r1 OK" << endl;
        }
        if(!flow2->expired()) {
            Storage::push(r2);
            cout << "push r2 OK" << endl;
        }
        CPU::int_enable();
        cout << "Going to sleep..." << endl;
    }

    return 0;
}

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
    OStream cout;

    cout << "main()" << endl;

    // Storage::clear(); cout << "storage cleared" << endl; while(true);

    Alarm::delay(5000000);

    M95 * m95 = M95::get(0);

    TSTP::Time t = m95->now();
    TSTP::epoch(t);

    m95->off();

    //TSTP config
    TSTP::Coordinates center_station1(50,0,0);
    TSTP::Coordinates center_station2(-6000,4500,0);

    TSTP::Region region_station1(center_station1, 0, 0, -1);
    TSTP::Region region_station2(center_station2, 0, 0, -1);

    flow0 = new Water_Flow_M170(0, INTEREST_EXPIRY, static_cast<Water_Flow_M170::Mode>(Water_Flow_M170::PRIVATE | Water_Flow_M170::CUMULATIVE));
    flow1 = new Water_Flow_WSTAR(region_station1, INTEREST_EXPIRY, INTEREST_PERIOD, Water_Flow_WSTAR::CUMULATIVE);
    flow2 = new Water_Flow_M170(region_station2, INTEREST_EXPIRY, INTEREST_PERIOD, Water_Flow_M170::CUMULATIVE);

    //Threads config
    Periodic_Thread * tstp_worker = new Periodic_Thread(INTEREST_EXPIRY, tstp_work);
    Periodic_Thread * http_sender = new Periodic_Thread(HTTP_SEND_PERIOD, http_send);

    Periodic_Thread * watchdog = new Periodic_Thread(500 * 1000, kick);

    cout << "threads created. Joining." << endl;

    watchdog->join();
    tstp_worker->join();
    http_sender->join();

    return 0;
}
