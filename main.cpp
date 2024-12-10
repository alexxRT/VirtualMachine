#include "machine.hpp"
#include "builder.hpp"
#include "types.hpp"

VM::Bytecode fibonachi_cycled(int n) {
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

VM::Bytecode fibonachi_recursive(int n) {
    Builder build;
    
    // public static int fib(int)
    build._ILOAD_0();           // 0
    build._BIPUSH_(1);          // 1
    build._IF_ICMPGT_(7);       // 3
    build._ILOAD_0();           // 5
    build._RETURN_();           // 6
    build._ILOAD_0();           // 7
    build._BIPUSH_(1);          // 8
    build._ISUB_();             // 10
    build._CALL_(1);            // 11
    build._ILOAD_0();           // 13
    build._BIPUSH_(2);          // 14
    build._ISUB_();             // 16
    build._CALL_(1);            // 17
    build._IADD_();             // 19
    build._RETURN_();           // 20

    auto fib = build.create_function<VM::jint>();

    // main()
    build._BIPUSH_(n);          // 21
    build._CALL_(1);            // 23
    build._RETURN_();           // 25

    auto main = build.create_function();

    // main allways has entrance point in zero
    // 0 - main, 1 - fibanachi
    return build.create_bytecode(std::move(main), std::move(fib));
}

int main() {
    auto bytecode = fibonachi_cycled(10);
    VM::Execute(bytecode);

    bytecode = fibonachi_recursive(10);
    VM::Execute(bytecode);
    return 0;
}