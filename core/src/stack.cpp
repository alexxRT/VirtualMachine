#include "stack.hpp"

using namespace VM;


Stack::Stack(size_t byte_size) {
    data.reserve(byte_size);
};

template <typename T>
void Stack::push(const T& elem) {
    size_t elem_sz = sizeof(T);
    size_t data_sz = data.size();
    data.resize(data.size() + elem_sz);
    memmove(static_cast<void*>(data.data() + data_sz), static_cast<const void*>(&elem), elem_sz);
};

void Stack::push(const value_t& elem) {
    size_t elem_size = elem.value_size;
    size_t data_sz = data.size();
    data.resize(data.size() + elem_sz);
    memmove(static_cast<void*>(data.data() + data.size()), elem.value, elem_sz);
}

template <typename T>
T Stack::pop() {
    size_t elem_sz = sizeof(T);
    size_t data_sz = data.size();
    if (data_sz < elem_sz) {
        std::cout << "Error! Data size: " << data_sz << " Elem size: " << elem_sz << std::endl;
        return T();
    }
    T elem;
    memmove(static_cast<void*>(&elem), data.data() + data_sz - elem_sz, elem_sz);
    data.resize(data_sz - elem_sz);

    return elem;
};

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