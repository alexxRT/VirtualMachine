#ifndef DEF_INSTR
    #define DEF_INSTR(...)
#endif

#ifndef OP_FROM_MEMORY
    #define OP_FROM_MEMORY byte_code[++pc]
#endif

DEF_INSTR(ISTORE,   36,   jint, OP_FROM_MEMORY) 
DEF_INSTR(ISTORE_0, 0x3b, jint, 0) 
DEF_INSTR(ISTORE_1, 0x3c, jint, 1) 
DEF_INSTR(ISTORE_2, 0x3d, jint, 2) 
DEF_INSTR(ISTORE_3, 0x3e, jint, 3) 