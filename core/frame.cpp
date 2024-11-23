#include "frame.hpp"
#include <cassert>

using namespace VM;

void Frame::run_context(std::vector<int>& byte_code, std::vector<Function>& f_table) {
    while (context < byte_code.size()) {
        switch (byte_code[context]) {
            case BYTECODE::ILOAD: {
                int index = byte_code[++context];
                LOAD(index);
            }
            break;
            case BYTECODE::ISTORE: {
                int index = byte_code[++context];
                STORE<int>(index);
            }
            break;
            case BYTECODE::IINC: {
                int var_indx = byte_code[++context];
                int inc = byte_code[++context];
                INC<int>(var_indx, inc);
            }
            break;
            case BYTECODE::CALL: {
                context ++;
                size_t callee_indx = byte_code[context];
                Frame* next_frame  = new Frame(stack, f_table[callee_indx], this, f_table[callee_indx].offset);
                next_frame->run_context(byte_code, f_table);
            }
            break;
            case BYTECODE::ILOAD_0:
                LOAD_I<0>();
            break;
            case BYTECODE::ILOAD_1:
                LOAD_I<1>();
            break;
            case BYTECODE::ILOAD_2:
                LOAD_I<2>();
            break;
            case BYTECODE::ILOAD_3:
                LOAD_I<3>();
            break;
            case BYTECODE::ISTORE_0:
                STORE_I<int, 0>();
            break;
            case BYTECODE::ISTORE_1:
                STORE_I<int, 1>();
            break;
            case BYTECODE::ISTORE_2:
                STORE_I<int, 2>();
            break;
            case BYTECODE::ISTORE_3:
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
            case BYTECODE::IIF_CMPEQ: {
                int jump_offset = byte_code[++context];
                BRANCH<int>(std::equal_to{}, jump_offset);
            }
            break;
            case BYTECODE::IIF_CMPGE: {
                int jump_offset = byte_code[++context];
                BRANCH<int>(std::greater_equal{}, jump_offset);
            }
            break;
            case BYTECODE::IIF_CMPGT: {
                int jump_offset = byte_code[++context];
                BRANCH<int>(std::greater{}, jump_offset); 
            }
            break;
            case BYTECODE::IIF_CMPLE: {
                int jump_offset = byte_code[++context];
                BRANCH<int>(std::less_equal{}, jump_offset);
            }
            break;
            case BYTECODE::IIF_CMPLT: {
                int jump_offset = byte_code[++context];
                BRANCH<int>(std::less{}, jump_offset);
            }
            break;
            case BYTECODE::IIF_CMPNE: {
                int jump_offset = byte_code[++context];
                BRANCH<int>(std::not_equal_to{}, jump_offset);
            }
            break;
            case BYTECODE::GOTO: {
                int jump_offset = byte_code[++context];
                context = jump_offset;
            }
            break;
            case BYTECODE::IPOP:
                POP<int>();
            break;
            case BYTECODE::IPOP2:
                POP2<int>();
            break;
            case BYTECODE::RETURN:
                return;
        }
    }
    std::cout << "Error! Frame bytecode has no return statement" << std::endl;
};

template <typename T>
void Frame::STORE(const size_t val_index) {
    if (val_index >= local_variables.size())
        local_variables.resize(val_index);
    local_variables[val_index] = stack->pop(sizeof(T));
    context ++;
    return;
};

template <typename T, int I> 
void Frame::STORE_I() {
    if (I >= local_variables.size())
        local_variables.resize(I);
    local_variables[I] = stack->pop(sizeof(T));
    context ++;
    return;
};

void Frame::LOAD(const size_t val_index) {
    assert(val_index < local_variables.size());
    stack->push(local_variables[val_index]);
    context ++;
    return;
};

template <int I>
void Frame::LOAD_I() {
    assert(I < local_variables.size());
    stack->push(local_variables[I]);
    context ++;
};

template <typename T, std::regular_invocable<T, T> F>
void Frame::BIN(F op) {
    T var1 = stack->pop<T>();
    T var2 = stack->pop<T>();
    stack->push<T>(op(var2, var1));
    context ++;
};

template <typename T, std::regular_invocable<T, T> CMP>
void Frame::BRANCH(CMP cmp_op, int branch) {
    T var1 = stack->pop<T>();
    T var2 = stack->pop<T>();
    context ++;
    if (cmp_op(var1, var2))
        context = branch;
}

void Frame::BIPUSH(const int value) {
    stack->push<int>(value);
    context ++;
    return;
}

template <typename T>
void Frame::POP() {
    stack->pop<T>();
    context ++;
    return;
}
template <typename T>
void Frame::POP2() {
    stack->pop<T>();
    stack->pop<T>();
    context ++;
    return;
}

template <typename T>
void Frame::INC(const size_t var_indx, const T c) {
    assert(var_indx < local_variables.size());
    static_cast<T*>(local_variables[var_indx].value.get())[0] += c;
    context ++;
    return;
}

template <typename T>
void Frame::NEG() {
    T var1 = stack->pop<T>();
    stack->push<T>(-var1);
    context ++;
    return;
}
