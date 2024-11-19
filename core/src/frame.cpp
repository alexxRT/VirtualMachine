#include <memory>
#include <vector>
#include "bytecode.hpp"

template <typename T, class... Types> // return value
class Frame {
    Frame(std::shared_ptr<stack> program_stack, std::vector<int>& function_code) {
        stack = program_stack;
        body  = function_code;
    }

    T execute_bytecode() {
        for (auto& code : body) {
            switch (code) {
                #define _CMD_(name, op_code, type, args) \
                case type##name:                         \
                    name<type>(args);                    \
                break;
                #include "code.hpp"
                #undef _CMD_

                case BYTECODE::GOTO:
                    break;

                case BYTECODE::CALL:
                    break;
            }
        }
    }
    
    template <typename OP_T>
    void Frame::LOAD(int val_index) {
        local_vars[val_index] = stack->pop<OP_T>();
        return;
    }
    #define LOAD_I(I, type)                  \
    void Frame::LOAD_##I( ) {                \
        local_vars[I] = stack->pop<type>();  \
    };
    LOAD_I(0, int)
    LOAD_I(1, int)
    LOAD_I(2, int)
    LOAD_I(3, int)
    #undef LOAD_I


    template <typename OP_T>
    void Frame::STORE(int val_index) {
        stack->push<OP_T>(local_vars[val_index]);
        return;
    }
    #define STORE_I(I, type)                \
    void Frame::STORE_##I() {               \
        stack->push<type>(local_vars[I]);   \
        return;                             \
    };
    STORE_I(0, int)
    STORE_I(1, int)
    STORE_I(2, int)
    STORE_I(3, int)
    #undef STORE_I


    #define BIN_OP(name, op, type)        \
    void Frame::##name() {                \
        type var1 = stack->pop<type>();   \
        type var2 = stack->pop<type>();   \
        stack->push<type>(var1 op var2);  \
        return;                           \
    };
    BIN_OP(MUL, *, int)
    BIN_OP(DIV, /, int)
    BIN_OP(SUB, -, int)
    BIN_OP(OR, |, int)
    BIN_OP(XOR, ^, int)
    BIN_OP(AND, &, int)
    #undef BIN_OP


    #define BRANCH(name, cmp, type)     \
    bool Frame::##name() {              \
        type var1 = stack->pop<type>(); \
        type var2 = stack->pop<type>(); \
        return var1 cmp var2;           \
    };
    BRANCH(IF_CMPEQ, ==, int)
    BRANCH(IF_CMPGE, >=, int)
    BRANCH(IF_CMPGT, >, int)
    BRANCH(IF_CMPLE, <=, int)
    BRANCH(IF_CMPLT, <, int)
    BRANCH(IF_CMPNE, !=, int)
    #undef BRANCH


    template <typename OP_T>
    void POP() {
        stack->pop<OP_T>();
        return;
    }
    template <typename OP_T>
    void POP2() {
        stack->pop<OP_T>();
        stack->pop<OP_T>();
        return;
    }

    template <typename OP_T>
    void Frame::INC(const int c) {
        OP_T var1 = stack->pop<OP_T>();
        stack->push<OP_T>(var1 + c);
        return;
    }
    template <typename OP_T>
    void Frame::NEG() {
        OP_T var1 = stack->pop<OP_T>();
        stack->push<OP_T>(-var1);
        return;
    }

    std::shared_ptr<stack> stack;
    std::vector<int>& body;

    // describe all instructions here
    std::array<std::variant<Types>, 4> local_vars;
};