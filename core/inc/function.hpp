
#include "common.hpp"
#include "stack.hpp"

namespace VM {
    class Function {
        //stores offset in bytecode and arguments
        public:
            template <typename... Types>
            Function::Function(size_t byte_offset, Types... args) : offset(byte_offset) {
                arguments = {{sizeof(Types)}...};
            };
        private:
            size_t offset;
            std::vector<size_t> arguments;
    };
};
