#pragma once
#include "common.hpp"

#define VALID_LOCAL(indx) indx >= 0 and indx <= 3

class Builder {
    public:
        Builder(std::shared_ptr<std::vector<int>> bytecode);

        void _ILOAD_(const int local_index);
        void _ILOAD_0();
        void _ILOAD_1();
        void _ILOAD_2();
        void _ILOAD_3();
        void _ISTORE_(const int local_index);
        void _ISTORE_0();
        void _ISTORE_1();
        void _ISTORE_2();
        void _ISTORE_3();

        void _IADD_();
        void _IMUL_();
        void _IINC_(const int var_index, const int inc);
        void _IDIV_();
        void _ISUB_();
        void _IOR_();
        void _IXOR_();
        void _IAND_();
        void _INEG_();

        void _IF_ICMPEQ_(const int branch_offset);
        void _IF_ICMPGE_(const int branch_offset);
        void _IF_ICMPGT_(const int branch_offset);
        void _IF_ICMPLE_(const int branch_offset);
        void _IF_ICMPLT_(const int branch_offset);
        void _IF_ICMPNE_(const int branch_offset);
        void _GOTO_(const int branch_offset);

        void _POP_();
        void _POP2_();
        void _BIPUSH_(const int value);

        void _CALL_(const int calle_indx);
        void _RETURN_();

    private:
        std::shared_ptr<std::vector<int>> bytecode_build;
};