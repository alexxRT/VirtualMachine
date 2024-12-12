#ifndef DEF_INSTR
    #define DEF_INSTR(...)
#endif

#ifndef OP_FROM_MEMORY
    #define OP_FROM_MEMORY byte_code[++pc]
#endif

DEF_INSTR(ILOAD,    15,   OP_FROM_MEMORY)
DEF_INSTR(ILOAD_0,  0x1a, 0) 
DEF_INSTR(ILOAD_1,  0x1b, 1) 
DEF_INSTR(ILOAD_2,  0x1c, 2) 
DEF_INSTR(ILOAD_3,  0x1d, 3)
