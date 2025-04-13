#include <systemc.h>

SC_MODULE(EventCounter) {
    sc_event count_event;   // Declare an event
    int counter = 0;

    // Method that runs when the event is triggered
    void process_method() {
        cout << "Counter: " << counter << " at time " << sc_time_stamp() << endl;
        counter++;
    }

    // Thread to trigger the event multiple times at different simulation times
    void trigger_thread() {
        wait(2, SC_NS);  // Wait for 2 ns
        count_event.notify();

        wait(3, SC_NS);  // Wait for 3 ns (now time is 5 ns)
        count_event.notify();

        wait(3, SC_NS);  // Wait for 3 ns more (now time is 8 ns)
        count_event.notify();
    }

    // Constructor
    SC_CTOR(EventCounter) {
        SC_METHOD(process_method);
        sensitive << count_event;  // Method is triggered when count_event is notified
        dont_initialize();  // Don't run the method at time 0

        SC_THREAD(trigger_thread);  // Start the thread to schedule events
    }
};

int sc_main(int argc, char* argv[]) {
    EventCounter module("CounterModule");

    // Start the simulation
    sc_start(10, SC_NS);  // Run the simulation for 10 ns
    return 0;
}
