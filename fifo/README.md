# FIFO Implementation in SystemC

This project contains a basic FIFO (First In, First Out) buffer implementation in SystemC, using `fifo.cpp`, `fifo.h`, and `main.cpp`. The FIFO is used to buffer data in hardware design and has the following features:
- Configurable depth (default: 4)
- Write and read operations
- Full and empty flags to manage buffer status

### Files:
1. **fifo.h**: Header file for FIFO class with method declarations and member variables.
2. **fifo.cpp**: Implementation file for the FIFO class methods.
3. **fifomain.cpp**: The simulation file to demonstrate how to use the FIFO buffer.

### How to Use:
1. Clone the repository.
2. Compile the code using the following commands:
g++ -o fifo_simulation fifomain.cpp fifo.cpp -I$SYSTEMC_HOME/include -L$SYSTEMC_HOME/lib-linux64 -lsystemc
3. Run the simulation:
./fifo_simulation
4. View the output on the console.

This is a simple demonstration of how FIFO buffers are implemented using SystemC.

