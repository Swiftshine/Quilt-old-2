#pragma once

#include "common.h"

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