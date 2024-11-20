#ifndef BYTECODE_HPP
#define BYTECODE_HPP

enum class BYTECODE : int32_t {
    ILOAD = 15, 
    ILOAD_0 = 0x1a, 
    ILOAD_1 = 0x1b, 
    ILOAD_2 = 0x1c, 
    ILOAD_3 = 0x1d, 
    ISTORE = 36, 
    ISTORE_0 = 0x3b, 
    ISTORE_1 = 0x3c, 
    ISTORE_2 = 0x3d, 
    ISTORE_3 = 0x3e, 
    IADD = 0x60, 
    IMUL = 0x68, 
    IINC = 0x84,
    IDIV = 0x6c,
    ISUB =0x64, 
    IOR = 0x80, 
    IXOR = 0x82, 
    IAND = 0x7e,
    INEG = 74,
    IIF_CMPEQ = 0x9f,
    IIF_CMPGE = 0xa2,
    IIF_CMPGT = 0xa3,
    IIF_CMPLE = 0xa4,
    IIF_CMPLT = 0xa1,
    IIF_CMPNE = 0xa0,
    IPOP = 0x57,
    IPOP2 = 0x58,
    RETURN = 0xb1,
    GOTO = 0xa7,
    CALL = 77
};

#endif // BYTECODE_HPP