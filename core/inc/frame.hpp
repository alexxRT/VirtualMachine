#include "common.hpp"
#include "bytecode.hpp"
#include "stack.hpp"
#include "function.hpp"

namespace VM {
    class Frame {
        public:
            Frame(Stack* program_stack, const Function& callee, Frame* prev_frame, size_t pc) : stack(program_stack), context(pc), callee(callee), prev(prev_frame) {};

            void run_context(std::vector<int>& byte_code, std::vector<Function>& f_table);
               
        private:
            template <typename T>
            void LOAD(int val_index);

            template <typename T, int I> 
            void LOAD_I();

            template <typename T>
            void STORE(int val_index);

            template <typename T, int I>
            void STORE_I();

            template <typename T, std::regular_invocable<T, T> F>
            void BIN(F op);

            template <typename T, std::regular_invocable<T, T> CMP>
            bool BRANCH(CMP cmp_op);

            template <typename T>
            void POP();

            template <typename T>
            void POP2();

            template <typename T>
            void INC(const int c);

            template <typename T>
            void NEG();

        private:
            Stack* stack = nullptr;
            Frame* prev  = nullptr;
            Function callee;
            size_t context;
            
            // std::array<std::variant<Types>, 4> local_vars;
    };
};