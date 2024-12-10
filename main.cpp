#include "machine.hpp"
#include "builder.hpp"
#include "types.hpp"

VM::Bytecode fibanachi_cycled(int n) {
    Builder build;

    // public static int fib(int)
    build._BIPUSH_(0);          // 0
    build._ISTORE_1();          // 2
    build._BIPUSH_(1);          // 3
    build._ISTORE_2();          // 5
    build._BIPUSH_(0);          // 6
    build._ISTORE_3();          // 8
    build._ILOAD_3();           // 9
    build._ILOAD_0();           // 10
    build._IF_ICMPGE_(28);      // 11
    build._ILOAD_1();           // 13
    build._ILOAD_2();           // 14
    build._IADD_();             // 15
    build._ISTORE_(4);          // 16
    build._ILOAD_2();           // 18
    build._ISTORE_1();          // 19
    build._ILOAD_(4);           // 20
    build._ISTORE_2();          // 22
    build._IINC_(3, 1);         // 23
    build._GOTO_(9);            // 26
    build._ILOAD_2();           // 28
    build._RETURN_();           // 29

    auto fib = build.create_function<VM::jint>();

    // public static void main()
    build._BIPUSH_(n);          // 30
    build._CALL_(1);            // 32
    build._RETURN_();           // 34

    auto main = build.create_function();

    // main allways has entrance point in zero
    // 0 - main, 1 - fib
    return build.create_bytecode(std::move(main), std::move(fib));
}

int main() {
    auto bytecode = fibanachi_cycled(10);
    VM::Execute(bytecode);

    // VM::Machine jvm;
    // jvm.load_fibanachi_cycled(10);
    // jvm.print_bytecode();
    // jvm.execute();

    // std::cout << std::endl << "BENCHMARK 1 N=10:" << std::endl;
    // jvm.print_stack();

    // jvm.reset();

    // jvm.load_fibonachi_recursive(10);
    // jvm.print_bytecode();
    // jvm.execute();

    // std::cout << std::endl << "BENCHMARK 2 N=10:" << std::endl;
    // jvm.print_stack();

    return 0;
}