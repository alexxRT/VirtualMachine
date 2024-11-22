#include "function.hpp"
#include "stack.hpp"
#include "frame.hpp"
#include "builder.hpp"
#include "common.hpp"

namespace VM {
    class Machine {
        void load_fibanachi_cycled() {
            Builder build(std::make_shared(bytecode));
            //fib(n)
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
            build._ISTORE(4);           // 16
            build._ILOAD_2();           // 18
            build._ISTORE_1();          // 19
            build._ILOAD_(4);           // 20
            build._ISTORE_2();          // 22
            build._IINC_(3, 1);         // 23
            build._GOTO_(9);            // 26
            build._ILOAD_2();           // 28
            build._RETURN_();           // 29

            size_t main_offset = bytecode.size();

            // main()
            build._BIPUSH_(10);         // 30
            build._CALL_(1);            // 31
            build._RETURN_();           // 32

            // add main(): // main allways has entrance point in zero
            // 0 - main, 1 - fibanachi
            Function MAIN(main_offset);
            functions.push_back(MAIN);

            // add fib(int):
            Function FIB(0, static_cast<int>(0));
            functions.push_back(FIB);

        };

        void load_fibonachi_recursive() {
            Builder build(std::make_shared(bytecode));
            // fib(n)
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

            size_t main_offset = bytecode.size();

            // main()
            build._BIPUSH_(10);         // 21
            build._CALL_(1);            // 23
            build._RETURN_();           // 25

            // add main(): // main allways has entrance point in zero
            // 0 - main, 1 - fibanachi
            Function MAIN(main_offset);
            functions.push_back(MAIN);

            // add fib(int):
            Function FIB(0, static_cast<int>(0));
            functions.push_back(FIB);
        };

        void print_bytecode() {
            std::vector<int>::iterator code = bytecode.begin();
            while (code != bytecode.end()) {
                if (*code == BYTECODE::CALL or *code == BYTECODE::ILOAD or *code == BYTECODE::ISTORE or *code == BYTECODE::IINC) {
                    std::cout << std::format("{:#x}", *code) << " " << std::format("{:#x}", *(code + 1)) << " " << string_code[*code] << " " << std::format("{:#x}", *(code + 1)) << std::endl;
                    code ++
                }
                std::cout << std::foramt("{:#x}", *code) << " " << string_code[*code] << std::endl; 
                code ++;
            }
        }

        void execute() {
            if (bytecode.size() == 0) {
                std::cout << "Nothing to execute! Please use load functions to load your programm!" << std::endl;
                return;
            }

            if (functions.size() == 0 or entry_point >= functions.size()) {
                std::cout << "No entry point exists!" << std::endl;
                return;
            }

            size_t main_offset = functions[0].offset;

            Frame* main_frame = new Frame(&stack, functions, nullptr, main_offset);
            main_frame->run_context(bytecode);
        };

        void reset() {
            entry_point = 0;
            bytecode.clear();
            stack.clear();
            functions.clear();
        }

        private:
            Stack stack;
            int entry_point;
            std::vector<int> bytecode;
            std::vector<Function> functions;
    };
};