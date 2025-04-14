#include "fifo.h"  // Include the FIFO header file

int sc_main(int argc, char* argv[]) {
    // Declare signals to connect to the FIFO module
    sc_clock clk("clk", 10, SC_NS);  // Create a 10ns clock signal
    sc_signal<bool> rst_n;
    sc_signal<bool> wr_en;
    sc_signal<int> data_in;
    sc_signal<bool> rd_en;
    sc_signal<int> data_out;
    sc_signal<bool> full;
    sc_signal<bool> empty;

    // Instantiate the FIFO module with data type `int` and size `4`
    FIFO<int, 4> fifo("FIFO");

    // Bind the signals to the FIFO ports
    fifo.clk(clk);
    fifo.rst_n(rst_n);
    fifo.wr_en(wr_en);
    fifo.data_in(data_in);
    fifo.rd_en(rd_en);
    fifo.data_out(data_out);
    fifo.full(full);
    fifo.empty(empty);

    // Set initial reset state (active low)
    rst_n.write(false);
    sc_start(10, SC_NS);  // Start the simulation for 10ns
    rst_n.write(true);
    sc_start(10, SC_NS);  // Run simulation for another 10ns to complete reset

    // Write data into FIFO
    wr_en.write(true);
    data_in.write(1); sc_start(10, SC_NS);  // Write 1 to FIFO
    data_in.write(2); sc_start(10, SC_NS);  // Write 2 to FIFO
    data_in.write(3); sc_start(10, SC_NS);  // Write 3 to FIFO
    data_in.write(4); sc_start(10, SC_NS);  // Write 4 to FIFO
    wr_en.write(false);  // Stop writing

    // Read data from FIFO
    rd_en.write(true);
    sc_start(10, SC_NS);  // Run simulation for 10ns
    cout << "Data Out: " << data_out.read() << endl;  // Output: 1

    rd_en.write(true);
    sc_start(10, SC_NS);
    cout << "Data Out: " << data_out.read() << endl;  // Output: 2

    rd_en.write(true);
    sc_start(10, SC_NS);
    cout << "Data Out: " << data_out.read() << endl;  // Output: 3

    rd_en.write(true);
    sc_start(10, SC_NS);
    cout << "Data Out: " << data_out.read() << endl;  // Output: 4

    // End the simulation
    sc_stop();
    return 0;
}
