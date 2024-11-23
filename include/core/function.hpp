#pragma once
#include "common.hpp"
#include "stack.hpp"

namespace VM {
    class Function {
        //stores offset in bytecode and arguments
        public:
            template <typename... Types>
            Function(size_t byte_offset, Types... args) : offset(byte_offset) {
                arguments = {{sizeof(args)}...};
            };
        public:
            size_t offset;
            std::vector<size_t> arguments;
    };
};
