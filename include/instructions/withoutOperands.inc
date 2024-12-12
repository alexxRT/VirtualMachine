#ifndef DEF_INSTR
    #define DEF_INSTR(...)
#endif

#include "instructions/memory/load_n.inc"
#include "instructions/memory/store_n.inc"
#include "instructions/binOp.inc"
DEF_INSTR(INEG)
DEF_INSTR(IPOP)
DEF_INSTR(IPOP2)
DEF_INSTR(RETURN)