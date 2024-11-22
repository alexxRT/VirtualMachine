#pragma once
#include "common.hpp"
#include "bytecode.hpp"
#include "stack.hpp"
#include "function.hpp"

namespace VM {
    class Frame {
        public:
            Frame(Stack* program_stack, const Function& callee, Frame* prev_frame, size_t pc) : stack(program_stack), context(pc), callee(callee), prev(prev_frame) {
                for (size_t i = callee.arguments.size() - 1; i >= 0; i --) {
                    value_t val = program_stack->pop(callee.arguments[i]);
                    local_variables.push_front(val);
                }
            };

            void run_context(std::vector<int>& byte_code, std::vector<Function>& f_table);
               
        private:
            void LOAD(int val_index);

            template <int I> 
            void LOAD_I();

            template <typename T>
            void STORE(int val_index);

            template <typename T, int I>
            void STORE_I();

            template <typename T, std::regular_invocable<T, T> F>
            void BIN(F op);

            template <typename T, std::regular_invocable<T, T> CMP>
            void BRANCH(CMP cmp_op, int branch);

            template <typename T>
            void POP();

            template <typename T>
            void POP2();

            template <typename T>
            void INC(const int var_indx, const T c);

            template <typename T>
            void NEG();

            void BIPUSH(const int value);

        private:
            Stack* stack = nullptr;
            Frame* prev  = nullptr;
            std::deque<value_t> local_variables;
            Function callee;
            size_t context;
    };
};