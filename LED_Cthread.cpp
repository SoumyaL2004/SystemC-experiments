#include <systemc>
#include <iostream>

using namespace sc_core;
using namespace sc_dt;
using namespace std;

SC_MODULE(led_blinker){
  sc_in<bool> clk;
  sc_in<bool> rst_n;
  sc_out<sc_uint<4>> led;
  
  void led_process(){
    led.write(0b0001);
    wait();
    while(true){
      led.write(led.read()<<1 | led.read()>>3);
      cout << "LED is " << led.read().to_string(SC_BIN) << " Time " << sc_time_stamp() << endl;
      wait(2);
    }
  }
    SC_CTOR(led_blinker){
      SC_CTHREAD(led_process, clk.pos());
      reset_signal_is(rst_n, false); 
    }
};


int sc_main(int argc, char* argv[]){
  sc_signal<bool> clk_sig;
  sc_signal<bool> rst_n_sig;
  sc_signal<sc_uint<4>> led_sig;
  
  led_blinker module("blinker");
  module.clk(clk_sig);
  module.rst_n(rst_n_sig);
  module.led(led_sig);

    // Generate clock
    sc_time clk_period(1, SC_NS);
    for (int i = 0; i < 20; ++i) {
        rst_n_sig.write(i < 2 ? 0 : 1);  // Deassert reset after 2 ns
        clk_sig.write(0);
        sc_start(clk_period / 2);
        clk_sig.write(1);
        sc_start(clk_period / 2);
    }
    return 0;
}
