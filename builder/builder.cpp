#include "builder.hpp"
#include "bytecode.hpp"

Builder::Builder(std::shared_ptr<std::vector<int>> bytecode) {
    bytecode_build = bytecode;
    bytecode_build->clear();
};

void Builder::_ILOAD_(const size_t local_index) {
    bytecode_build->push_back(static_cast<int>(BYTECODE::ILOAD));
    bytecode_build->push_back(local_index);
    return;
};

void Builder::_ILOAD_0() {
    bytecode_build->push_back(static_cast<int>(BYTECODE::ILOAD_0));
    return;
};

void Builder::_ILOAD_1() {
    bytecode_build->push_back(static_cast<int>(BYTECODE::ILOAD_1));
    return;
};

void Builder::_ILOAD_2() {
    bytecode_build->push_back(static_cast<int>(BYTECODE::ILOAD_2));
    return;
};

void Builder::_ILOAD_3() {
    bytecode_build->push_back(static_cast<int>(BYTECODE::ILOAD_3));
    return;
};

void Builder::_ISTORE_(const size_t local_index) {
    bytecode_build->push_back(static_cast<int>(BYTECODE::ISTORE));
    bytecode_build->push_back(local_index);
    return;
};

void Builder::_ISTORE_0() {
    bytecode_build->push_back(static_cast<int>(BYTECODE::ISTORE_0));
    return;
};

void Builder::_ISTORE_1() {
    bytecode_build->push_back(static_cast<int>(BYTECODE::ISTORE_1));
    return;
} 

void Builder::_ISTORE_2() {
    bytecode_build->push_back(static_cast<int>(BYTECODE::ISTORE_2));
    return;
};

void Builder::_ISTORE_3() {
    bytecode_build->push_back(static_cast<int>(BYTECODE::ISTORE_3));
    return;
};

void Builder::_IADD_() {
    bytecode_build->push_back(static_cast<int>(BYTECODE::IADD));
    return;
};

void Builder::_IMUL_() {
    bytecode_build->push_back(static_cast<int>(BYTECODE::IMUL));
    return;
};
void Builder::_IINC_(const size_t var_index, const int inc) {
    bytecode_build->push_back(static_cast<int>(BYTECODE::IINC));
    bytecode_build->push_back(var_index);
    bytecode_build->push_back(inc);
    return;
};

void Builder::_IDIV_() {
    bytecode_build->push_back(static_cast<int>(BYTECODE::IDIV));
    return;
};

void Builder::_ISUB_() {
    bytecode_build->push_back(static_cast<int>(BYTECODE::ISUB));
    return;
};

void Builder::_IOR_() {
    bytecode_build->push_back(static_cast<int>(BYTECODE::IOR));
    return;
};

void Builder::_IXOR_() {
    bytecode_build->push_back(static_cast<int>(BYTECODE::IXOR));
    return;
};

void Builder::_IAND_() {
    bytecode_build->push_back(static_cast<int>(BYTECODE::IAND));
    return;
};

void Builder::_INEG_() {
    bytecode_build->push_back(static_cast<int>(BYTECODE::INEG));
    return;
};

void Builder::_IF_ICMPEQ_(const int branch_offset) {
    bytecode_build->push_back(static_cast<int>(BYTECODE::IIF_CMPEQ));
    bytecode_build->push_back(branch_offset);
    return;
};

void Builder::_IF_ICMPGE_(const int branch_offset) {    
    bytecode_build->push_back(static_cast<int>(BYTECODE::IIF_CMPGE));
    bytecode_build->push_back(branch_offset);
    return;
};

void Builder::_IF_ICMPGT_(const int branch_offset) {
    bytecode_build->push_back(static_cast<int>(BYTECODE::IIF_CMPGT));
    bytecode_build->push_back(branch_offset);
    return;
};

void Builder::_IF_ICMPLE_(const int branch_offset) {
    bytecode_build->push_back(static_cast<int>(BYTECODE::IIF_CMPLE));
    bytecode_build->push_back(branch_offset);
    return;
};

void Builder::_IF_ICMPLT_(const int branch_offset) {
    bytecode_build->push_back(static_cast<int>(BYTECODE::IIF_CMPLT));
    bytecode_build->push_back(branch_offset);
    return;
};

void Builder::_IF_ICMPNE_(const int branch_offset) {
    bytecode_build->push_back(static_cast<int>(BYTECODE::IIF_CMPNE));
    bytecode_build->push_back(branch_offset);
    return;
};

void Builder::_GOTO_(const int branch_offset) {
    bytecode_build->push_back(static_cast<int>(BYTECODE::GOTO));
    bytecode_build->push_back(branch_offset);
}

void Builder::_POP_() {
    bytecode_build->push_back(static_cast<int>(BYTECODE::IPOP));
    return;
};


void Builder::_POP2_() {
    bytecode_build->push_back(static_cast<int>(BYTECODE::IPOP2));
    return;
};

void Builder::_BIPUSH_(const int value) {
    bytecode_build->push_back(static_cast<int>(BYTECODE::BIPUSH));
    bytecode_build->push_back(value);
    return;
}

void Builder::_CALL_(const size_t callee_indx) {
    bytecode_build->push_back(static_cast<int>(BYTECODE::CALL));
    bytecode_build->push_back(callee_indx);
    return;
}

void Builder::_RETURN_() {
    bytecode_build->push_back(static_cast<int>(BYTECODE::RETURN));
    return;
};
