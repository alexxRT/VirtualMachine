#include "machine.hpp"

int main() {
    VM::Machine jvm;
    jvm.load_fibanachi_cycled(10);
    jvm.print_bytecode();
    jvm.execute();

    std::cout << std::endl << "BENCHMARK 1 N=10:" << std::endl;
    jvm.print_stack();

    jvm.reset();

    jvm.load_fibonachi_recursive(10);
    jvm.print_bytecode();
    jvm.execute();

    std::cout << std::endl << "BENCHMARK 2 N=10:" << std::endl;
    jvm.print_stack();

    return 0;
}