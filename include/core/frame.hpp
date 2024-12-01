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

                std::vector<size_t>::reverse_iterator it = callee.arguments.rbegin();
                for (; it < callee.arguments.rend(); it++) {
                    value_t local = {calloc(*it, sizeof(uint8_t)), *it};
                    program_stack->pop(local);
                    local_variables.push_front(local);
                }
            };

            ~Frame() {
                for (auto& val : local_variables) {
                    if (val.value)
                        free(val.value);
                }
            }
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