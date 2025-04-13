#include <systemc>
#include <iostream>
using namespace sc_core;
using namespace std;
SC_MODULE(light){
  sc_event blink_event;
  sc_signal <bool> led_state;
  void light_process(){
    cout << "LED is " << (led_state.read() ? "ON" : "OFF") << " time " << sc_time_stamp() << endl;
  }  
  void blink_trigger_thread(){
  wait (2, SC_NS);
    blink_event.notify();
  wait (2, SC_NS);
    blink_event.notify();
  }
  SC_CTOR(light){
  SC_METHOD(light_process);
    sensitive << led_state;
    dont_initialize();
  SC_THREAD(blink_trigger_thread);       
  }
};
int sc_main(int argc, char* argv[]){
  light module("mymod");  
  sc_start(2, SC_NS);
  module.led_state.write(1);
  sc_start(2, SC_NS);
  module.led_state.write(0);  
  sc_start(2, SC_NS);
  module.led_state.write(1);
  sc_start(2, SC_NS);
  module.led_state.write(0);
  sc_start(2, SC_NS);
  module.led_state.write(1);
  sc_start(2, SC_NS);
  module.led_state.write(0);
  sc_start(2, SC_NS);
  module.led_state.write(1);
  sc_start(2, SC_NS);
  module.led_state.write(0);
   sc_start(20, SC_NS);
  return 0;
}
