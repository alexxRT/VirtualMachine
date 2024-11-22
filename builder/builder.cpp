#include "builder.hpp"
#include "bytecode.hpp"

Builder::Builder(std::shared_ptr<std::vector<int>> bytecode) {
    bytecode_build = bytecode;
    bytecode_build->clear();
};

void Builder::_ILOAD_(int local_index) {
    if (VALID_LOCAL(local_index)) {
        bytecode_build->push_back(static_cast<int>(BYTECODE::ILOAD));
        bytecode_build->push_back(local_index)
        return;
    }

    std::cout << "Bad local variable index [" << local_index << "]. Aborting..." << std::endl;
    bytecode_build->clear();
    bytecode_build = nullptr;
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

void Builder::_STORE_(int local_index) {
    if (VALID_LOCAL(local_index)) {
        bytecode_build->push_back(static_cast<int>(BYTECODE::STORE));
        bytecode_build->push_back(local_index)
        return;
    }

    std::cout << "Bad local variable index [" << local_index << "]. Aborting..." << std::endl;
    bytecode_build->clear();
    bytecode_build = nullptr;
    return;
};

void Builder::_STORE_0() {
    bytecode_build->push_back(static_cast<int>(BYTECODE::STORE_0));
    return;
};

void Builder::_STORE_1() {
    bytecode_build->push_back(static_cast<int>(BYTECODE::STORE_1));
    return;
} 

void Builder::_STORE_2() {
    bytecode_build->push_back(static_cast<int>(BYTECODE::STORE_2));
    return;
};

void Builder::_STORE_3() {
    bytecode_build->push_back(static_cast<int>(BYTECODE::STORE_3));
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
void Builder::_IINC_() {
    bytecode_build->push_back(static_cast<int>(BYTECODE::IINC));
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
    bytecode_build->push_back(static_cast<int>(BYTECODE::IF_ICMPEQ));
    bytecode_build->push_back(branch_offset);
    return;
};

void Builder::_IF_ICMPGE_(const int branch_offset) {    
    bytecode_build->push_back(static_cast<int>(BYTECODE::IF_ICMPGE));
    bytecode_build->push_back(branch_offset);
    return;
};

void Builder::_IF_ICMPGT_(const int branch_offset) {
    bytecode_build->push_back(static_cast<int>(BYTECODE::IF_ICMPGT));
    bytecode_build->push_back(branch_offset);
    return;
};

void Builder::_IF_ICMPLE_(const int branch_offset) {
    bytecode_build->push_back(static_cast<int>(BYTECODE::IF_ICMPLE));
    bytecode_build->push_back(branch_offset);
    return;
};

void Builder::_IF_ICMPLT_(const int branch_offset) {
    bytecode_build->push_back(static_cast<int>(BYTECODE::IF_ICMPLT));
    bytecode_build->push_back(branch_offset);
    return;
};

void Builder::_IF_ICMPNE_(const int branch_offset) {
    bytecode_build->push_back(static_cast<int>(BYTECODE::IF_ICMPNE));
    bytecode_build->push_back(branch_offset);
    return;
};

void Builder::_GOTO_(const int branch_offset) {
    bytecode_build->push_back(static_cast<int>(BYTECODE::GOTO));
    bytecode_build->push_back(branch_offset);
    return;
};


void Builder::_POP_(const int branch_offset) {
    bytecode_build->push_back(static_cast<int>(BYTECODE::IPOP));
    return;
};


void Builder::_POP2_(const int branch_offset) {
    bytecode_build->push_back(static_cast<int>(BYTECODE::IPOP2));
    return;
};

void Builder::_CALL_(const int callee_indx) {
    bytecode_build->push_back(BYTECODE::CALL);
    bytecode_build->push_back(callee_indx);
    return;
}

void Builder::_RETURN_(const int branch_offset) {
    bytecode_build->push_back(static_cast<int>(BYTECODE::RETURN));
    return;
};
