#ifndef CODE_HPP
#define CODE_HPP

#ifndef _CMD_
#define _CMD_(...)
#endif

_CMD_(LOAD, 15, int, (int val_index))
_CMD_(LOAD_0, 0x1a, int, ())
_CMD_(LOAD_1, 0x1b, int, ())
_CMD_(LOAD_2, 0x1c, int, ())
_CMD_(LOAD_3, 0x1d, int, ())
_CMD_(STORE, 36, int, (int val_index))
_CMD_(STORE_0, 0x3b, int, ())
_CMD_(STORE_1, 0x3c, int, ())
_CMD_(STORE_2, 0x3d, int, ())
_CMD_(STORE_3, 0x3e, int, ())
_CMD_(ADD, 0x60, int, ())
_CMD_(MUL, 0x68, int, ())
_CMD_(INC, 0x84, int, (const int c))
_CMD_(DIV, 0x6c, int, ())
_CMD_(SUB, 0x64, int, ())
_CMD_(OR,  0x80, int, ())
_CMD_(XOR, 0x82, int, ())
_CMD_(AND, 0x7e, int, ())
_CMD_(NEG, 74, int, ())
_CMD_(IF_CMPEQ, 0x9f, int, ())
_CMD_(IF_CMPGE, 0xa2, int, ())
_CMD_(IF_CMPGT, 0xa3, int, ())
_CMD_(IF_CMPLE, 0xa4, int, ())
_CMD_(IF_CMPLT, 0xa1, int, ())
_CMD_(IF_CMPNE, 0xa0, int, ())
_CMD_(POP, 0x57, int, ())
_CMD_(POP2, 0x58, int, ())
_CMD_(RETURN, 0xb1, void, ())
_CMD_(RETURN, 0xac, int, ())

#endif //CODE_HPP
