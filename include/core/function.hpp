#pragma once
#include "common.hpp"
#include "stack.hpp"
#include <numeric>

namespace VM {
    class Function {
        public:
            Function(std::vector<int>&& Bytecode,
                     std::initializer_list<size_t> Arguments) : 
                bytecode(std::move(Bytecode)),
                arguments(Arguments),
                arguments_size(std::accumulate(Arguments.begin(), Arguments.end(), 0))
                {}
        public:
            std::vector<int> bytecode;
            std::vector<size_t> arguments;
            size_t arguments_size {};
    };
};
