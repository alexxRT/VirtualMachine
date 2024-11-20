#include "common.hpp"

namespace VM {
    class Stack {
        public:
            Stack(size_t byte_size);

            template <typename T>
            void push(const T& elem);

            template <typename T>
            T pop();

            size_t get_size();

            void print_stat();
         
        private:
            std::vector<uint8_t> data;
    };
}