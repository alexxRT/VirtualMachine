#include "common.hpp"
#include <type_traits>

struct value_t {
    std::shared_ptr<void> value;
    size_t value_size;
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
            value_t pop(size_t size);

            size_t get_size();

            void print_stat();

            void clear() { data.clear(); };
         
        private:
            std::vector<uint8_t> data;
    };
};