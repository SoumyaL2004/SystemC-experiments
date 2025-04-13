#include <systemc.h>

SC_MODULE(Mymodule) {
    sc_signal<int> my_signal;
  
    void process_method() {
        while(true) {
            cout << "count " << my_signal.read() << " time " << sc_time_stamp() << endl;
            my_signal.write(my_signal.read() + 1);
            wait(2, SC_NS);
        }
    }
  
    SC_CTOR(Mymodule) {
        SC_THREAD(process_method);
        my_signal.write(0);
    }
};

int sc_main(int argc, char* argv[]) {
    Mymodule module("countermodule");
    sc_start(12, SC_NS);
    return 0;
}
