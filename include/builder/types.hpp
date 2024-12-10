#include "function.hpp"
#include <cstdint>
#include <vector>

namespace VM {
    using jbyte   = int8_t;
    using jshort  = int16_t;
    using jint    = int32_t;
    using jlong   = int64_t;
    using jfloat  = float;
    using jdouble = double;

    using Bytecode = std::vector<Function>;
}