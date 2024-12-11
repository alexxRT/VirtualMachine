#include "stack.hpp"
#include <memory>
#include <cstring>
#include <cstdlib>

using namespace VM;


Stack::Stack(size_t byte_size) {
    data.reserve(byte_size);
};

void Stack::push(const value_t& elem) {
    size_t elem_sz = elem.value_size;
    size_t data_sz = data.size();
    data.resize(data.size() + elem_sz);

    memmove(static_cast<void*>(&data[data_sz]), elem.value_p, elem_sz);
}

void Stack::pop(value_t& elem) {
    size_t elem_sz = elem.value_size;
    size_t data_sz = data.size();

    if (data_sz < elem_sz) {
        std::cout << "Error! Data size: " << data_sz << " Elem size: " << elem_sz << std::endl;
        return;
    }
    
    memmove(elem.value_p, static_cast<void*>(&data[data_sz - elem_sz]), elem_sz);
    data.resize(data_sz - elem_sz);
}

size_t Stack::get_size() {
    return data.size();
};

void Stack::print_stat() {
    std::cout << "Stack capacity: " << data.capacity() << std::endl;
    std::cout << "Stack size: " << data.size() << std::endl;
};