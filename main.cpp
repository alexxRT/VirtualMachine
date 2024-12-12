#include "machine.hpp"
#include "builder.hpp"
#include "types.hpp"

VM::Bytecode fibonachi_cycled(int n) {
    Builder build;

    // public static int fib(int)
    build.BIPUSH(0);          // 0
    build.ISTORE_1();         // 2
    build.BIPUSH(1);          // 3
    build.ISTORE_2();         // 5
    build.BIPUSH(0);          // 6
    build.ISTORE_3();         // 8
    build.ILOAD_3();          // 9
    build.ILOAD_0();          // 10
    build.IF_ICMPGE(28);      // 11
    build.ILOAD_1();          // 13
    build.ILOAD_2();          // 14
    build.IADD();             // 15
    build.ISTORE(4);          // 16
    build.ILOAD_2();          // 18
    build.ISTORE_1();         // 19
    build.ILOAD(4);           // 20
    build.ISTORE_2();         // 22
    build.IINC(3, 1);         // 23
    build.GOTO(9);            // 26
    build.ILOAD_2();          // 28
    build.RETURN();           // 29

    auto fib = build.create_function<VM::jint>();

    // public static void main()
    build.BIPUSH(n);          // 30
    build.CALL(1);            // 32
    build.RETURN();           // 34

    auto main = build.create_function();

    // main allways has entrance point in zero
    // 0 - main, 1 - fib
    return build.create_bytecode(std::move(main), std::move(fib));
}

VM::Bytecode fibonachi_recursive(int n) {
    Builder build;
    
    // public static int fib(int)
    build.ILOAD_0();          // 0
    build.BIPUSH(1);          // 1
    build.IF_ICMPGT(7);       // 3
    build.ILOAD_0();          // 5
    build.RETURN();           // 6
    build.ILOAD_0();          // 7
    build.BIPUSH(1);          // 8
    build.ISUB();             // 10
    build.CALL(1);            // 11
    build.ILOAD_0();          // 13
    build.BIPUSH(2);          // 14
    build.ISUB();             // 16
    build.CALL(1);            // 17
    build.IADD();             // 19
    build.RETURN();           // 20

    auto fib = build.create_function<VM::jint>();

    // main()
    build.BIPUSH(n);          // 21
    build.CALL(1);            // 23
    build.RETURN();           // 25

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