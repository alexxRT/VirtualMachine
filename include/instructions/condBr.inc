#ifndef DEF_INSTR
    #define DEF_INSTR(...)
#endif

DEF_INSTR(IF_ICMPEQ, 0x9f, jint, std::equal_to{})
DEF_INSTR(IF_ICMPGE, 0xa2, jint, std::greater_equal{})
DEF_INSTR(IF_ICMPGT, 0xa3, jint, std::greater{})
DEF_INSTR(IF_ICMPLE, 0xa4, jint, std::less_equal{})
DEF_INSTR(IF_ICMPLT, 0xa1, jint, std::less{})
DEF_INSTR(IF_ICMPNE, 0xa0, jint, std::not_equal_to{})