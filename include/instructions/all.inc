#ifndef DEF_INSTR
    #define DEF_INSTR(...)
#endif

#include "instructions/binOp.inc"
#include "instructions/condBr.inc"
#include "instructions/memory/store.inc"
#include "instructions/memory/load.inc"
DEF_INSTR(IINC,   0x84)
DEF_INSTR(INEG,   74)
DEF_INSTR(GOTO,   0xa7)
DEF_INSTR(IPOP,   0x57)
DEF_INSTR(IPOP2,  0x58)
DEF_INSTR(BIPUSH, 0x10)
DEF_INSTR(RETURN, 0xb1)
DEF_INSTR(CALL,   77)