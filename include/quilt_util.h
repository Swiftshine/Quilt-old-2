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

    static bool InRect(SDL_Rect& rect, int x, int y) {
        return (x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h);
    }

    static bool InRect(Vec2f pos, SDL_Rect& rect) {
        return (pos.x >= rect.x && pos.x <= rect.x + rect.w && pos.y >= rect.y && pos.y <= rect.y + rect.h);
    }

    static bool InRect(Vec2f pos, Vec2f min, Vec2f max) {
        return (pos.x >= min.x && pos.x <= max.x &&
            pos.y >= min.y && pos.y <= max.y);
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
