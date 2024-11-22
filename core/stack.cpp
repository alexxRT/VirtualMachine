#include "stack.hpp"
#include <cstring>

using namespace VM;


Stack::Stack(size_t byte_size) {
    data.reserve(byte_size);
};

void Stack::push(const value_t& elem) {
    size_t elem_sz = elem.value_size;
    size_t data_sz = data.size();
    data.resize(data.size() + elem_sz);

    memmove(static_cast<void*>(data.data() + data_sz), elem.value.get(), elem_sz);
}

value_t Stack::pop(size_t size) {
    size_t elem_sz = size;
    size_t data_sz = data.size();
    if (data_sz < elem_sz) {
        std::cout << "Error! Data size: " << data_sz << " Elem size: " << elem_sz << std::endl;
        return {nullptr, 0};
    }
    
    value_t elem = {};
    memmove(static_cast<void*>(elem.value.get()), data.data() + data_sz - elem_sz, elem_sz);

    data.resize(data_sz - elem_sz);

    return elem;
}

size_t Stack::get_size() {
    return data.size();
};

void Stack::print_stat() {
    std::cout << "Stack capacity: " << data.capacity() << std::endl;
    std::cout << "Stack size: " << data.size() << std::endl;
};