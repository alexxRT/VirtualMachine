#ifndef DEF_INSTR
    #define DEF_INSTR(...)
#endif

#ifndef OP_FROM_MEMORY
    #define OP_FROM_MEMORY byte_code[++pc]
#endif

#include "instructions/memory/load_n.inc"
DEF_INSTR(ILOAD, 15, OP_FROM_MEMORY)
