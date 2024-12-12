#pragma once
#include "common.hpp"
#include "types.hpp"
#include <concepts>
#include <utility>

class Builder {
    public:
        Builder() = default;
        Builder(std::shared_ptr<std::vector<int>> byte_code);

        void ILOAD(const size_t local_index);
        void ISTORE(const size_t local_index);

        void IINC(const size_t var_index, const int inc);
        void BIPUSH(const int value);
        
        void CALL(const size_t calle_indx);
        void GOTO(const int branch_offset);


        #define DEF_INSTR(INSTR_NAME, ...) \
            void INSTR_NAME(const int branch_offset);
        #include "instructions/condBr.inc"
        #undef DEF_INSTR


        #define DEF_INSTR(INSTR_NAME, ...) \
            void INSTR_NAME();
        #include "instructions/withoutOperands.inc"
        #undef DEF_INSTR


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