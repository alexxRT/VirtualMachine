#ifndef DEF_INSTR
    #define DEF_INSTR(...)
#endif

#ifndef OP_FROM_MEMORY
    #define OP_FROM_MEMORY byte_code[++pc]
#endif

#include "instructions/memory/store_n.inc"
DEF_INSTR(ISTORE, 36, jint, OP_FROM_MEMORY) 