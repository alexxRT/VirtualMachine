#ifndef BYTECODE_HPP
#define BYTECODE_HPP
#include <unordered_map>


namespace BYTECODE {
    enum {
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
        GOTO = 0xa7,
        IPOP = 0x57,
        IPOP2 = 0x58,
        BIPUSH = 0x10,
        RETURN = 0xb1,
        CALL = 77
    };
}

static const std::unordered_map<int, std::string> string_code {
    {BYTECODE::ILOAD, "ILOAD"},
    {BYTECODE::ILOAD_0, "ILOAD0"},
    {BYTECODE::ILOAD_1, "ILOAD1"},
    {BYTECODE::ILOAD_2, "ILOAD2"},
    {BYTECODE::ILOAD_3, "ILOAD3"},
    {BYTECODE::ISTORE, "ISTORE"},
    {BYTECODE::ISTORE_0, "ISTORE0"},
    {BYTECODE::ISTORE_1, "ISTORE1"},
    {BYTECODE::ISTORE_2, "ISTORE2"},
    {BYTECODE::ISTORE_3, "ISTORE3"},
    {BYTECODE::IADD, "IADD"},
    {BYTECODE::IMUL, "IMULL"},
    {BYTECODE::IDIV, "IDIV"},
    {BYTECODE::ISUB, "ISUB"},
    {BYTECODE::IINC, "IINC"},
    {BYTECODE::IAND, "IAND"},
    {BYTECODE::IXOR, "IXOR"},
    {BYTECODE::IOR, "IOR"},
    {BYTECODE::INEG, "INEG"},
    {BYTECODE::IIF_CMPEQ, "IIF_CMPEQ"},
    {BYTECODE::IIF_CMPGE, "IIF_CMPGE"},
    {BYTECODE::IIF_CMPGT, "IIF_CMPGT"},
    {BYTECODE::IIF_CMPLE, "IIF_CMPLE"},
    {BYTECODE::IIF_CMPLT, "IIF_CMPLT"},
    {BYTECODE::IIF_CMPNE, "IIF_CMPNE"},
    {BYTECODE::GOTO, "GOTO"},
    {BYTECODE::IPOP, "IPOP"},
    {BYTECODE::IPOP2, "IPOP2"},
    {BYTECODE::BIPUSH, "BIPUSH"},
    {BYTECODE::RETURN, "RETURN"},
    {BYTECODE::CALL, "CALL"}
};

#endif // BYTECODE_HPP