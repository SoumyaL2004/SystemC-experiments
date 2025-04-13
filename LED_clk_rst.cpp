#include <systemc>
#include <iostream>

using namespace sc_core;
using namespace sc_dt;
using namespace std;

SC_MODULE(LED_Blinker) {
    sc_in<bool> clk;
    sc_in<bool> rst_n;       // Active LOW reset
    sc_out<bool> led;

    void blink_process() {
        led.write(0);   // Default LED state
        wait();         // wait for next clock after reset

        while (true) {
            led.write(!led.read());  // Toggle LED
            cout << "LED: " << (led.read() ? "ON" : "OFF") << " at " << sc_time_stamp() << endl;
            wait(2);     // Wait 2 clock cycles before next toggle
        }
    }

    SC_CTOR(LED_Blinker) {
        SC_CTHREAD(blink_process, clk.pos());        // Clocked thread
        reset_signal_is(rst_n, false);               // Active-low reset
    }
};

int sc_main(int argc, char* argv[]) {
    sc_signal<bool> clk_sig;
    sc_signal<bool> rst_sig;
    sc_signal<bool> led_sig;

    LED_Blinker blinker("blinker");
    blinker.clk(clk_sig);
    blinker.rst_n(rst_sig);
    blinker.led(led_sig);

    // Generate clock
    sc_time clk_period(1, SC_NS);
    for (int i = 0; i < 20; ++i) {
        rst_sig.write(i < 2 ? 0 : 1);  // Deassert reset after 2 ns
        clk_sig.write(0);
        sc_start(clk_period / 2);
        clk_sig.write(1);
        sc_start(clk_period / 2);
    }

    return 0;
}
