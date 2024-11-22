#include "frame.hpp"

using namespace VM;

void Frame::run_context(std::vector<int>& byte_code, std::vector<Function>& f_table) {
    while (context < byte_code.size()) {
        switch (byte_code[context]) {
            case BYTECODE::ILOAD:
                context ++;
                int index = code[context];
                LOAD<int>(index);
            break;
            case BYTECODE::ISTORE:
                context ++;
                int index = code[context];
                STORE<int>()
            break;
            case BYTECODE::IINC:
                context ++;
                int inc = code[context];
                INC<int>(inc);
            break;
            case BYTECODE::CALL:
                context ++;
                size_t callee_indx = code[context];
                Frame* next_frame  = new Frame(stack, f_table[callee_indx], this, f_table[callee_indx].offset);
                next_frame->run_context(byte_code, f_table);
            break;
            case BYTECODE::GOTO:
                context ++;
                context = code[context];
            break;
            case BYTECODE::ILOAD_0:
                LOAD_I<int, 0>();
            break;
            case BYTECODE::ILOAD_1:
                LOAD_I<int, 1>();
            break;
            case BYTECODE::ILOAD_2:
                LOAD_I<int, 2>();
            break;
            case BYTECODE::ILOAD_3:
                LOAD_I<int, 3>();
            break;
            case BYTECODE::STORE_0:
                STORE_I<int, 0>();
            break;
            case BYTECODE::STORE_1:
                STORE_I<int, 1>();
            break;
            case BYTECODE::STORE_2:
                STORE_I<int, 2>();
            break;
            case BYTECODE::STORE_3:
                STORE_I<int, 3>();
            break;
            case BYTECODE::IADD:
                BIN<int>(std::plus{});
            break;
            case BYTECODE::IDIV:
                BIN<int>(std::divides{});
            break;
            case BYTECODE::ISUB:
                BIN<int>(std::minus{});
            break;
            case BYTECODE::IMUL:
                BIN<int>(std::multiplies{});
            break;
            case BYTECODE::IOR:
                BIN<int>(std::bit_or{});
            break;
            case BYTECODE::IAND:
                BIN<int>(std::bit_and{});
            break;
            case BYTECODE::IXOR:
                BIN<int>(std::bit_xor{});
            break;
            case BYTECODE::INEG:
                NEG<int>();
            break;
            case BYTECODE::IIF_CMPEQ:
                BRANCH<int>(std::equal_to{});
            break;
            case BYTECODE::IIF_CMPGE:
                BRANCH<int>(std::greater_equal{});
            break;
            case BYTECODE::IIF_CMPGT:
                BRANCH<int>(std::greater{});
            break;
            case BYTECODE::IIF_CMPLE:
                BRANCH<int>(std::less_equal{});
            break;
            case BYTECODE::IIF_CMPLT:
                BRANCH<int>(std::less{});
            break;
            case BYTECODE::IIF_CMPNE:
                BRANCH<int>(std::not_equal_to{});
            break;
            case BYTECODE::IPOP:
                POP<int>();
            break;
            case BYTECODE::IPOP2:
                POP2<int>();
            break;
            case BYTECODE::RETURN:
                callee.exit();
                context ++;
                return;
        }
        context ++;
    }
    std::cout << "Error! Frame bytecode has no return statement" << std::endl;
    return RT();
};


template <typename T>
void Frame::LOAD(int val_index) {
    local_vars[val_index] = stack->pop<T>();
    return;
};

template <typename T, int I> 
void Frame::LOAD_I( ) {
    local_vars[I] = stack->pop<T>();
};

template <typename T>
void Frame::STORE(int val_index) {
    stack->push<T>(local_vars[val_index]);
    return;
};

template <typename T, int I>
void Frame::STORE_I() {
    stack->push<T>(local_vars[I]);
};

template <typename T, std::regular_invocable<T, T> F>
void Frame::BIN(F op) {
    T var1 = stack->pop<T>();
    T var2 = stack->pop<T>();
    stack->push<T>(op(var2, var1))
};

template <typename T, std::regular_invocable<T, T> CMP>
bool Frame::BRANCH(CMP cmp_op) {
    T var1 = stack->pop<T>();
    T var2 = stack->pop<T>();
    return cmp_op(var1, var2);
}

template <typename T>
void Frame::POP() {
    stack->pop<T>();
    return;
}
template <typename T>
void Frame::POP2() {
    stack->pop<T>();
    stack->pop<T>();
    return;
}

template <typename T>
void Frame::INC(const int c) {
    T var1 = stack->pop<T>();
    stack->push<T>(var1 + c);
    return;
}
template <typename T>
void Frame::NEG() {
    T var1 = stack->pop<T>();
    stack->push<T>(-var1);
    return;
}
