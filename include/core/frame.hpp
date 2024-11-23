#pragma once
#include "common.hpp"
#include "bytecode.hpp"
#include "stack.hpp"
#include "function.hpp"

namespace VM {
    class Frame {
        public:
            Frame(Stack* program_stack, const Function& f_callee, Frame* prev_frame, size_t pc) : callee(f_callee) {
                stack   = program_stack;
                prev    = prev_frame;
                context = pc;

                for (size_t i = callee.arguments.size() - 1; i >= 0; i --) {
                    value_t val = program_stack->pop(callee.arguments[i]);
                    local_variables.push_front(val);
                }
            };

            void run_context(std::vector<int>& byte_code, std::vector<Function>& f_table);
               
        private:
            void LOAD(const size_t val_index);

            template <int I> 
            void LOAD_I();

            template <typename T>
            void STORE(const size_t val_index);

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
            void INC(const size_t var_indx, const T c);

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