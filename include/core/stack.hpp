#pragma once
#include "common.hpp"
#include <type_traits>
#include <cstring>
#include <span>

struct value_t {
    uint8_t*  value_p;
    size_t    value_size;
};

namespace VM {
    class Stack {
        public:
            Stack(size_t byte_size);

            template <typename T>
            void push(const T& elem);

            template <typename T>
            T pop();

            void push(const value_t& elem);
            void pop(value_t& elem);

            size_t get_size();

            void print_stat();

            void clear() { data.clear(); };
         
            void print() {
                for (auto& elem : data) {
                    std::cout << std::format("{:#x}", elem) << " ";
                }
            }

            std::span<uint8_t> back(size_t size) {
                return std::span<uint8_t>(data).subspan(data.size() - size, size);
            }

            void pop(size_t size) {
                data.resize(data.size() - size);
            }

        private:
            std::vector<uint8_t> data;
    };

    template <typename T>
    void Stack::push(const T& elem) {
        size_t elem_sz   = sizeof(T);
        size_t data_sz   = data.size();
        data.resize(data.size() + elem_sz);

        memmove(static_cast<void*>(data.data() + data_sz), static_cast<const void*>(&elem), elem_sz);
    };

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

};