#include "builder.hpp"
#include "bytecode.hpp"


void Builder::ILOAD(const size_t local_index) {
    bytecode.push_back(BYTECODE::ILOAD);
    bytecode.push_back(local_index);
    return;
}

void Builder::ISTORE(const size_t local_index) {
    bytecode.push_back(BYTECODE::ISTORE);
    bytecode.push_back(local_index);
    return;
}

void Builder::IINC(const size_t var_index, const int inc) {
    bytecode.push_back(BYTECODE::IINC);
    bytecode.push_back(var_index);
    bytecode.push_back(inc);
    return;
}

void Builder::GOTO(const int branch_offset) {
    bytecode.push_back(BYTECODE::GOTO);
    bytecode.push_back(branch_offset);
}

void Builder::BIPUSH(const int value) {
    bytecode.push_back(BYTECODE::BIPUSH);
    bytecode.push_back(value);
    return;
}

void Builder::CALL(const size_t callee_indx) {
    bytecode.push_back(BYTECODE::CALL);
    bytecode.push_back(callee_indx);
    return;
}


#define DEF_INSTR(INSTR_NAME, ...)                          \
    void Builder::INSTR_NAME() {                            \
        bytecode.push_back(BYTECODE::INSTR_NAME);           \
        return;                                             \
    }
#include "instructions/withoutOperands.inc"
#undef DEF_INSTR


#define DEF_INSTR(INSTR_NAME, ...)                          \
    void Builder::INSTR_NAME(const int branch_offset) {     \
        bytecode.push_back(BYTECODE::INSTR_NAME);           \
        bytecode.push_back(branch_offset);                  \
        return;                                             \
    }
#include "instructions/condBr.inc"
#undef DEF_INSTR
