#ifndef DEF_INSTR
    #define DEF_INSTR(...)
#endif

DEF_INSTR(IADD, 0x60, jint, std::plus{}) 
DEF_INSTR(IMUL, 0x68, jint, std::multiplies{}) 
DEF_INSTR(IDIV, 0x6c, jint, std::divides{})
DEF_INSTR(ISUB, 0x64, jint, std::minus{}) 
DEF_INSTR(IOR,  0x80, jint, std::bit_or{}) 
DEF_INSTR(IAND, 0x7e, jint, std::bit_and{}) 
DEF_INSTR(IXOR, 0x82, jint, std::bit_xor{}) 
