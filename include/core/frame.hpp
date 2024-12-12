#pragma once
#include "common.hpp"
#include "bytecode.hpp"
#include "stack.hpp"
#include "function.hpp"
#include <cassert>

namespace VM {
    class Frame {
        public:
            Frame(Stack& programm_stack, const Function& callee_, Frame* prev_frame_) : callee(callee_), local_variables_storage(), local_variables(), prev_frame(prev_frame_) {
                if (callee.arguments.size() == 0)
                    return;
                
                // Move function arguments from programm stack to frame
                auto arguments = programm_stack.back(callee.arguments_size);
                std::move(arguments.begin(), arguments.end(), std::back_inserter(local_variables_storage));
                programm_stack.pop(arguments.size());

                // Match each local variable with its address inside the frame
                local_variables.emplace_back(&local_variables_storage.front(), callee.arguments.front());
                for (auto it = callee.arguments.begin() + 1, ite = callee.arguments.end(); it != ite; ++it) {
                    auto previous_variable = local_variables.back();
                    local_variables.emplace_back(previous_variable.value_p + previous_variable.value_size, *it);
                }
            };

            void run_context(Stack& stack, std::vector<int>& byte_code, std::vector<Function>& f_table);

        private:
            template <typename T> 
            T get_local_variable(unsigned n) {
                assert(local_variables[n].value_size == sizeof(T));
                auto var_ptr = reinterpret_cast<T*>(local_variables[n].value_p);
                return *var_ptr;
            }

            template <typename T> 
            void set_local_variable(unsigned n, T&& value) {
                assert(local_variables[n].value_size == sizeof(T));
                auto var_ptr = reinterpret_cast<T*>(local_variables[n].value_p);
                *var_ptr = value;
            }

            template <typename T>
            void create_local_variable() {
                local_variables_storage.resize(local_variables_storage.size() + sizeof(T));
                auto last_variable = local_variables.back();
                local_variables.emplace_back(last_variable.value_p + last_variable.value_size, sizeof(T));
            }

        private:
            Function callee;
            std::deque<uint8_t>  local_variables_storage;
            std::vector<value_t> local_variables;

            Frame* prev_frame  = nullptr;
            size_t pc          = 0;
    };
};