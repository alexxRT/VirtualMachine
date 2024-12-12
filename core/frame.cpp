#include "frame.hpp"
#include "types.hpp"
#include <cassert>

using namespace VM;

void Frame::run_context(Stack& stack, std::vector<int>& byte_code, std::vector<Function>& f_table) {

    while (pc < byte_code.size()) {
        switch (byte_code[pc]) {

            // case ILOAD, ILOAD_1, ILOAD_2, ...
            #define DEF_INSTR(INSTR_NAME, OPCODE, OPERAND_INDEX)                \
                case BYTECODE::INSTR_NAME: {                                    \
                    auto op_index = static_cast<size_t>(OPERAND_INDEX);         \
                    assert(op_index < local_variables.size());                  \
                    stack.push(local_variables[op_index]);                      \
                    pc++;                                                       \
                    break;                                                      \
                }
            #include "instructions/memory/load.inc"
            #undef DEF_INSTR

            // case ISTORE, ISTORE_1, ISTORE_2
            #define DEF_INSTR(INSTR_NAME, OPCODE, OPERAND_TYPE, OPERAND_INDEX)  \
                case BYTECODE::INSTR_NAME: {                                    \
                    auto op_index = static_cast<size_t>(OPERAND_INDEX);         \
                    if (op_index >= local_variables.size())                     \
                        create_local_variable<OPERAND_TYPE>();                  \
                    stack.pop(local_variables[op_index]);                       \
                    pc++;                                                       \
                    break;                                                      \
                }
            #include "instructions/memory/store.inc"
            #undef DEF_INSTR

            // case IADD, IMUL, IDIV, ... 
            #define DEF_INSTR(INSTR_NAME, OPCODE, OPERAND_TYPE, OPERATION)      \
                case BYTECODE::INSTR_NAME: {                                    \
                    auto var1 = stack.pop<OPERAND_TYPE>();                      \
                    auto var2 = stack.pop<OPERAND_TYPE>();                      \
                    stack.push(OPERATION(var2, var1));                          \
                    pc++;                                                       \
                    break;                                                      \
                }
            #include "instructions/binOp.inc"
            #undef DEF_INSTR

            // case IF_ICMPEQ, IF_ICMPGE, IF_ICMPGT, ...
            #define DEF_INSTR(INSTR_NAME, OPCODE, OPERAND_TYPE, OPERATION)      \
                case BYTECODE::INSTR_NAME: {                                    \
                    auto jump_offset = byte_code[++pc];                         \
                    auto var1 = stack.pop<OPERAND_TYPE>();                      \
                    auto var2 = stack.pop<OPERAND_TYPE>();                      \
                    pc++;                                                       \
                    if (OPERATION(var2, var1))                                  \
                        pc = jump_offset;                                       \
                    break;                                                      \
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
