#pragma once
#include "common.hpp"
#include "types.hpp"
#include <concepts>
#include <utility>

class Builder {
    public:
        Builder() = default;
        Builder(std::shared_ptr<std::vector<int>> byte_code);

        void _ILOAD_(const size_t local_index);
        void _ILOAD_0();
        void _ILOAD_1();
        void _ILOAD_2();
        void _ILOAD_3();
        void _ISTORE_(const size_t local_index);
        void _ISTORE_0();
        void _ISTORE_1();
        void _ISTORE_2();
        void _ISTORE_3();

        void _IADD_();
        void _IMUL_();
        void _IINC_(const size_t var_index, const int inc);
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

        void _CALL_(const size_t calle_indx);
        void _RETURN_();

        template <typename... Types>
        VM::Function create_function() {
            return VM::Function(std::move(bytecode),
                                {sizeof(Types)...});
        }

        template <std::convertible_to<VM::Function>... Functions>
        VM::Bytecode create_bytecode(Functions&&... functions) {
            return {std::forward<Functions>(functions)...};
        }

    private:
        std::vector<int> bytecode;
};