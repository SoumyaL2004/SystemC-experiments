#ifndef FIFO_H
#define FIFO_H

#include <systemc.h>
#include <deque>  // For the FIFO buffer

template <typename T, int SIZE = 4>
SC_MODULE(FIFO) {
    // Ports
    sc_in<bool> clk;
    sc_in<bool> rst_n;

    sc_in<bool> wr_en;
    sc_in<T> data_in;

    sc_in<bool> rd_en;
    sc_out<T> data_out;

    sc_out<bool> full;
    sc_out<bool> empty;

    // Internal buffer (FIFO)
    std::deque<T> buffer;

    // Process for FIFO operations
    void fifo_proc();

    // Constructor
    SC_CTOR(FIFO) {
        SC_METHOD(fifo_proc);
        sensitive << clk.pos();  // Trigger on positive clock edge
        dont_initialize();  // Don't execute the method on initialization
    }
};

#endif // FIFO_H
