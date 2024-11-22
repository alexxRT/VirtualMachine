
#include "common.hpp"
#include "stack.hpp"

namespace VM {
    class Function {
        //stores offset and arguments
        public:
            template <typename... Types>
            Function(size_t byte_offset, Types... args);

            //pop elements from stack on function exit
            exit(Stack* program_stack);
        private:
            size_t offset;
            std::vector<value_t> arguments;
    };
};
