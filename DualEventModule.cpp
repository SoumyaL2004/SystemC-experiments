#include <systemc>
#include <iostream>
using namespace sc_core;
using namespace std;

SC_MODULE(DualEventModule) {
    sc_event event_A, event_B;   // Declare the events

    // Method that runs when event_A is triggered
    void process_A() {
        cout << "Event A triggered at time: " << sc_time_stamp() << endl;
    }

    // Method that runs when event_B is triggered
    void process_B() {
        cout << "Event B triggered at time: " << sc_time_stamp() << endl;
    }

    // Thread to trigger the events at different times
    void trigger_thread() {
        wait(2, SC_NS);  // Wait for 2 ns
        event_A.notify();

        wait(2, SC_NS);  // Wait for 2 ns (total 4 ns now)
        event_B.notify();

        wait(2, SC_NS);  // Wait for 2 ns (total 6 ns now)
        event_A.notify();
    }

    // Constructor
    SC_CTOR(DualEventModule) {
        SC_METHOD(process_A);   // Process for event A
        sensitive << event_A;   // Trigger when event_A is notified
        dont_initialize();      // Do not initialize at time 0

        SC_METHOD(process_B);   // Process for event B
        sensitive << event_B;   // Trigger when event_B is notified
        dont_initialize();      // Do not initialize at time 0

        SC_THREAD(trigger_thread);  // Thread to schedule the events
    }
};

int sc_main(int argc, char* argv[]) {
    DualEventModule module("DualEventModule");

    // Start the simulation for 10 ns
    sc_start(10, SC_NS);  
    return 0;
}
