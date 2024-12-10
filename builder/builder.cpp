#include "builder.hpp"
#include "bytecode.hpp"


void Builder::_ILOAD_(const size_t local_index) {
    bytecode.push_back(BYTECODE::ILOAD);
    bytecode.push_back(local_index);
    return;
};

void Builder::_ILOAD_0() {
    bytecode.push_back(BYTECODE::ILOAD_0);
    return;
};

void Builder::_ILOAD_1() {
    bytecode.push_back(BYTECODE::ILOAD_1);
    return;
};

void Builder::_ILOAD_2() {
    bytecode.push_back(BYTECODE::ILOAD_2);
    return;
};

void Builder::_ILOAD_3() {
    bytecode.push_back(BYTECODE::ILOAD_3);
    return;
};

void Builder::_ISTORE_(const size_t local_index) {
    bytecode.push_back(BYTECODE::ISTORE);
    bytecode.push_back(local_index);
    return;
};

void Builder::_ISTORE_0() {
    bytecode.push_back(BYTECODE::ISTORE_0);
    return;
};

void Builder::_ISTORE_1() {
    bytecode.push_back(BYTECODE::ISTORE_1);
    return;
} 

void Builder::_ISTORE_2() {
    bytecode.push_back(BYTECODE::ISTORE_2);
    return;
};

void Builder::_ISTORE_3() {
    bytecode.push_back(BYTECODE::ISTORE_3);
    return;
};

void Builder::_IADD_() {
    bytecode.push_back(BYTECODE::IADD);
    return;
};

void Builder::_IMUL_() {
    bytecode.push_back(BYTECODE::IMUL);
    return;
};
void Builder::_IINC_(const size_t var_index, const int inc) {
    bytecode.push_back(BYTECODE::IINC);
    bytecode.push_back(var_index);
    bytecode.push_back(inc);
    return;
};

void Builder::_IDIV_() {
    bytecode.push_back(BYTECODE::IDIV);
    return;
};

void Builder::_ISUB_() {
    bytecode.push_back(BYTECODE::ISUB);
    return;
};

void Builder::_IOR_() {
    bytecode.push_back(BYTECODE::IOR);
    return;
};

void Builder::_IXOR_() {
    bytecode.push_back(BYTECODE::IXOR);
    return;
};

void Builder::_IAND_() {
    bytecode.push_back(BYTECODE::IAND);
    return;
};

void Builder::_INEG_() {
    bytecode.push_back(BYTECODE::INEG);
    return;
};

void Builder::_IF_ICMPEQ_(const int branch_offset) {
    bytecode.push_back(BYTECODE::IIF_CMPEQ);
    bytecode.push_back(branch_offset);
    return;
};

void Builder::_IF_ICMPGE_(const int branch_offset) {    
    bytecode.push_back(BYTECODE::IIF_CMPGE);
    bytecode.push_back(branch_offset);
    return;
};

void Builder::_IF_ICMPGT_(const int branch_offset) {
    bytecode.push_back(BYTECODE::IIF_CMPGT);
    bytecode.push_back(branch_offset);
    return;
};

void Builder::_IF_ICMPLE_(const int branch_offset) {
    bytecode.push_back(BYTECODE::IIF_CMPLE);
    bytecode.push_back(branch_offset);
    return;
};

void Builder::_IF_ICMPLT_(const int branch_offset) {
    bytecode.push_back(BYTECODE::IIF_CMPLT);
    bytecode.push_back(branch_offset);
    return;
};

void Builder::_IF_ICMPNE_(const int branch_offset) {
    bytecode.push_back(BYTECODE::IIF_CMPNE);
    bytecode.push_back(branch_offset);
    return;
};

void Builder::_GOTO_(const int branch_offset) {
    bytecode.push_back(BYTECODE::GOTO);
    bytecode.push_back(branch_offset);
}

void Builder::_POP_() {
    bytecode.push_back(BYTECODE::IPOP);
    return;
};


void Builder::_POP2_() {
    bytecode.push_back(BYTECODE::IPOP2);
    return;
};

void Builder::_BIPUSH_(const int value) {
    bytecode.push_back(BYTECODE::BIPUSH);
    bytecode.push_back(value);
    return;
}

void Builder::_CALL_(const size_t callee_indx) {
    bytecode.push_back(BYTECODE::CALL);
    bytecode.push_back(callee_indx);
    return;
}

void Builder::_RETURN_() {
    bytecode.push_back(BYTECODE::RETURN);
    return;
};
