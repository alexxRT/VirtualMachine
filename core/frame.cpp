#include "frame.hpp"
#include "types.hpp"
#include <cassert>

using namespace VM;

void Frame::run_context(Stack& stack, std::vector<int>& byte_code, std::vector<Function>& f_table) {

    while (pc < byte_code.size()) {
        switch (byte_code[pc]) {

            #define DEF_INSTR(INSTR_NAME, OPCODE, OPERAND_INDEX)                         \
                case BYTECODE::INSTR_NAME: {                                             \
                    assert(static_cast<size_t>(OPERAND_INDEX) < local_variables.size()); \
                    stack.push(local_variables[OPERAND_INDEX]);                          \
                    pc++;                                                                \
                    break;                                                               \
                }
            #include "instructions/load.inc"
            #undef DEF_INSTR


            #define DEF_INSTR(INSTR_NAME, OPCODE, OPERAND_TYPE, OPERAND_INDEX)        \
                case BYTECODE::INSTR_NAME: {                                          \
                    if (static_cast<size_t>(OPERAND_INDEX) >= local_variables.size()) \
                        create_local_variable<OPERAND_TYPE>();                        \
                    stack.pop(local_variables[OPERAND_INDEX]);                        \
                    pc ++;                                                            \
                    break;                                                            \
                }
            #include "instructions/store.inc"
            #undef DEF_INSTR


            #define DEF_INSTR(INSTR_NAME, OPCODE, OPERAND_TYPE, OPERATION) \
                case BYTECODE::INSTR_NAME: {                               \
                    auto var1 = stack.pop<OPERAND_TYPE>();                 \
                    auto var2 = stack.pop<OPERAND_TYPE>();                 \
                    stack.push(OPERATION(var2, var1));                     \
                    pc++;                                                  \
                    break;                                                 \
                }
            #include "instructions/binOp.inc"
            #undef DEF_INSTR


            #define DEF_INSTR(INSTR_NAME, OPCODE, OPERAND_TYPE, OPERATION) \
                case BYTECODE::INSTR_NAME: {                               \
                    auto jump_offset = byte_code[++pc];                    \
                    auto var1 = stack.pop<OPERAND_TYPE>();                 \
                    auto var2 = stack.pop<OPERAND_TYPE>();                 \
                    pc++;                                                  \
                    if (OPERATION(var2, var1))                             \
                        pc = jump_offset;                                  \
                    break;                                                 \
                }  
            #include "instructions/condBr.inc"
            #undef DEF_INSTR

            case BYTECODE::CALL: {
                size_t callee_indx = byte_code[++pc];
                Frame next_frame   = Frame(stack, f_table[callee_indx], this);
                next_frame.run_context(stack, f_table[callee_indx].bytecode, f_table);
                pc ++;
                break;
            }
            case BYTECODE::GOTO: {
                auto next_pc = byte_code[++pc];
                pc = next_pc;
                break;
            }
            case BYTECODE::IINC: {
                auto var_indx = byte_code[++pc];
                auto inc = byte_code[++pc];
                auto var = get_local_variable<jint>(var_indx);
                set_local_variable<jint>(var_indx, var + inc);
                pc++;
                break;
            }
            case BYTECODE::INEG: {
                auto var = stack.pop<jint>();
                stack.push<jint>(-var);
                pc++;
                break;
            }
            case BYTECODE::BIPUSH: {
                auto value = byte_code[++pc];
                stack.push<jint>(value);
                pc++;
                break;
            }
            case BYTECODE::IPOP:
                stack.pop<jint>();
                pc++;           
                break;
            case BYTECODE::IPOP2:
                stack.pop<jint>();
                stack.pop<jint>();
                pc++;
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

// template <typename T>
// void ISA::STORE(const size_t val_index) {
//     if (val_index >= local_variables.size())
//         local_variables.resize(val_index + 1, {nullptr, 0});

//     if (local_variables[val_index].value)
//         free(local_variables[val_index].value);

//     local_variables[val_index].value = calloc(sizeof(T), sizeof(uint8_t));
//     local_variables[val_index].value_size = sizeof(T);
    
//     stack->pop(local_variables[val_index]);
//     pc ++;
//     return;
// };

// template <typename T, int I> 
// void ISA::STORE() {
//     if (I >= local_variables.size())
//         local_variables.resize(I + 1, {nullptr, 0});

//     if (local_variables[I].value)
//         free(local_variables[I].value);

//     local_variables[I].value = calloc(sizeof(T), sizeof(uint8_t));
//     local_variables[I].value_size = sizeof(T);
    
//     stack->pop(local_variables[I]);
//     pc++;
//     return;
// };

// void ISA::LOAD(const size_t val_index) {
//     assert(val_index < local_variables.size());
//     stack->push(local_variables[val_index]);
//     pc++;
//     return;
// };

// template <int I>
// void ISA::LOAD() {
//     assert(I < local_variables.size());
//     stack->push(local_variables[I]);
//     pc++;
// };

// template <typename T, std::regular_invocable<T, T> F>
// void ISA::BIN(F op, Stack& stack, Frame* frame) {
//     T var1 = stack.pop<T>();
//     T var2 = stack.pop<T>();
//     stack.push<T>(op(var2, var1));
//     frame->pc++;
// };

// template <typename T, std::regular_invocable<T, T> CMP>
// void ISA::BRANCH(CMP cmp_op, int branch) {
//     T var1 = stack->pop<T>();
//     T var2 = stack->pop<T>();
//     pc ++;
//     if (cmp_op(var2, var1))
//         pc = branch;
// }

// void ISA::BIPUSH(const int value) {
//     stack->push<int>(value);
//     pc++;
//     return;
// }

// template <typename T>
// void ISA::POP() {
//     stack->pop<T>();
//     pc ++;
//     return;
// }
// template <typename T>
// void ISA::POP2() {
//     stack->pop<T>();
//     stack->pop<T>();
//     pc++;
//     return;
// }

// template <typename T>
// void ISA::INC(const size_t var_indx, const T c) {
//     assert(var_indx < local_variables.size());
//     static_cast<T*>(local_variables[var_indx].value)[0] += c;
//     pc++;
//     return;
// }

// template <typename T>
// void ISA::NEG() {
//     T var1 = stack->pop<T>();
//     stack->push<T>(-var1);
//     pc++;
//     return;
// }
