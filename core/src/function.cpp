#include "function.hpp"

using namespace VM;
  
template <typename... Types>
Function::Function(size_t byte_offset, Types... args) : offset(byte_offset) {
    arguments = {{std::shared_ptr<void>(new Types(std::forward<Types>(args))), sizeof(Types)}...};
};

Function::exit(Stack* program_stack) {
    for (size_t i = arguments.size() - 1, i >= 0; i--) {
        arguments[i] = program_stack->pop(arguments[i].value_size);
    }
};