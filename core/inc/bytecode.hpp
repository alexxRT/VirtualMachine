#ifndef BYTECODE_HPP
#define BYTECODE_HPP


enum class BYTECODE : int32_t {
    #define _CMD_(name, op_code, type, args) type##name = op_code,
    #include "code.hpp"
    #undef _CMD_
    GOTO      = 0xa7,
    CALL      = 77,
};

#endif // BYTECODE_HPP