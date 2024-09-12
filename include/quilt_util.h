#pragma once

#include "types.h"
#include <fstream>

namespace quilt {
    static const char zero = 0;

    static void AlignOutstream(std::ofstream& file, u32 alignment) {
        if (file.tellp() % alignment != 0) {
            for (auto i = 0; i < (file.tellp() % alignment); i++) {
                file.write(&quilt::zero, 1);
            }
        }
    }
}

// macros

#define ASSERT_SIZE(structure, size) \
    static_assert(size == sizeof(structure));

#define SET_FLAG(val, flag) \
    val |= flag;

#define CLEAR_FLAG(val, flag) \
    val &= ~flag;

#define PTR_INVALID(ptr) \
    (nullptr == ptr)

#define PTR_VALID(ptr) \
    (nullptr != ptr)
