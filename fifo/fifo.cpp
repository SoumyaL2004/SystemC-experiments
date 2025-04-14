#include "fifo.h"

// FIFO process for read/write operations
template <typename T, int SIZE>
void FIFO<T, SIZE>::fifo_proc() {
    if (!rst_n.read()) {
        // Reset FIFO
        buffer.clear();
        full.write(false);
        empty.write(true);
        data_out.write(0);
    }
    else {
        // Write to FIFO
        if (wr_en.read() && buffer.size() < SIZE) {
            buffer.push_back(data_in.read());
        }

        // Read from FIFO
        if (rd_en.read() && !buffer.empty()) {
            data_out.write(buffer.front());
            buffer.pop_front();
        }

        // Update full and empty flags
        full.write(buffer.size() == SIZE);
        empty.write(buffer.empty());
    }
}

// Explicit template instantiations (so that the code knows about the specific types you are using)
template class FIFO<int, 4>;  // For FIFO of size 4
template class FIFO<int, 8>;  // For FIFO of size 8
