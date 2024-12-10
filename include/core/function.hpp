#pragma once
#include "common.hpp"
#include "stack.hpp"

namespace VM {
    class Function {
        public:
            Function(std::vector<int>&& Bytecode,
                     std::initializer_list<size_t> Arguments) : 
                bytecode(std::move(Bytecode)),
                arguments(Arguments)
                {}
        public:
            std::vector<int> bytecode;
            std::vector<size_t> arguments;
    };
};
