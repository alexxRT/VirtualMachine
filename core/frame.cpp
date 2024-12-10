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
                size_t callee_indx = byte_code[++context];
                Frame next_frame   = Frame(stack, f_table[callee_indx], this);
                next_frame.run_context(f_table[callee_indx].bytecode, f_table);
                context ++;
            }
            break;
            case BYTECODE::BIPUSH: {
                int push_val = byte_code[++context];
                BIPUSH(push_val);
            }
            break;

            #define DEF_INSTR(INSTR_NAME, OPCODE, VAL) \
                case BYTECODE::INSTR_NAME: {           \
                    LOAD<VAL>();                       \
                    break;                             \
                }
            #include "instructions/load.inc"
            #undef DEF_INSTR

            #define DEF_INSTR(INSTR_NAME, OPCODE, VAL) \
                case BYTECODE::INSTR_NAME: {           \
                    STORE<int, VAL>();                 \
                    break;                             \
                }
            #include "instructions/store.inc"
            #undef DEF_INSTR


            #define DEF_INSTR(INSTR_NAME, OPCODE, OPERATION) \
                case BYTECODE::INSTR_NAME: {                 \
                    BIN<int>(OPERATION);                     \
                    break;                                   \
                }
            #include "instructions/binOp.inc"
            #undef DEF_INSTR


            #define DEF_INSTR(INSTR_NAME, OPCODE, OPERATION)    \
                case BYTECODE::INSTR_NAME: {                    \
                    int jump_offset = byte_code[++context];     \
                    BRANCH<int>(OPERATION, jump_offset);        \
                    break;                                      \
                }  
            #include "instructions/condBr.inc"
            #undef DEF_INSTR

            case BYTECODE::INEG:
                NEG<int>();
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
            default:
                std::cout << "Unknow bytecode when executing! Abort..." << std::endl;
                return;
        }
    }
    std::cout << "Error! Frame bytecode has no return statement" << std::endl;
};

template <typename T>
void Frame::STORE(const size_t val_index) {
    if (val_index >= local_variables.size())
        local_variables.resize(val_index + 1, {nullptr, 0});

    if (local_variables[val_index].value)
        free(local_variables[val_index].value);

    local_variables[val_index].value = calloc(sizeof(T), sizeof(uint8_t));
    local_variables[val_index].value_size = sizeof(T);
    
    stack->pop(local_variables[val_index]);
    context ++;
    return;
};

template <typename T, int I> 
void Frame::STORE() {
    if (I >= local_variables.size())
        local_variables.resize(I + 1, {nullptr, 0});

    if (local_variables[I].value)
        free(local_variables[I].value);

    local_variables[I].value = calloc(sizeof(T), sizeof(uint8_t));
    local_variables[I].value_size = sizeof(T);
    
    stack->pop(local_variables[I]);
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
void Frame::LOAD() {
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
    if (cmp_op(var2, var1))
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
    static_cast<T*>(local_variables[var_indx].value)[0] += c;
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
