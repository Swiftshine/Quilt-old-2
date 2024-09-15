#pragma once

#include "types.h"
#include <fstream>

namespace Quilt {
    static const char zero = 0;

    static void AlignOutstream(std::ofstream& file, u32 alignment) {
        if (file.tellp() % alignment != 0) {
            for (auto i = 0; i < (file.tellp() % alignment); i++) {
                file.write(&Quilt::zero, 1);
            }
        }
    }

    static bool ValidateRoot(std::string root) {
        if (root.empty()) {
            return false;
        }

        if (!fs::exists(root)) {
            return false;
        }

        // there are more folders but at the moment
        // these are the only folders that matter
        static const std::vector<std::string> queries = {
            "mapdata"
        };

        for (const std::string& query : queries) {
            if (!fs::is_directory(root + "/" + query)) {
                return false;
            }
        }

        return true;
    };
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
