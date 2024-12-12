#ifndef BYTECODE_HPP
#define BYTECODE_HPP
#include <unordered_map>


namespace BYTECODE {

    enum OpCode {
        #define DEF_INSTR(INSTR_NAME, OPCODE, ...) \
            INSTR_NAME = OPCODE,
        #include "instructions/all.inc"
        #undef DEF_INSTR
    };


}

static const std::unordered_map<int, std::string> string_code {
    #define DEF_INSTR(CMD_NAME, ...) \
        {BYTECODE::CMD_NAME, #CMD_NAME},
    #include "instructions/all.inc"
    #undef DEF_INSTR
};

#endif // BYTECODE_HPP