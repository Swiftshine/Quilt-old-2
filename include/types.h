#pragma once

#include <cstdint>
#include <cstring>
#include <string>

using f32 = float;
// using u64 = uint64_t;
// using s64 = int64_t;
using u32 = uint32_t;
using s32 = int32_t;
using u16 = uint16_t;
using s16 = int16_t;
using u8  = uint8_t;
using s8  = int8_t;

using uint = unsigned int;
using Offset = u32;

struct RGBA {
    RGBA() {
        color = 0;
    }
    
    RGBA(const RGBA& other) {
        color = other.color;
    }

    RGBA(const u32 val) {
        color = val;
    }

    RGBA(const u8 red, const u8 green, const u8 blue, const u8 alpha) {
        r = red;
        g = green;
        b = blue;
        a = alpha;
    }

    union {
        u32 color;

        struct {
            u8 r;
            u8 g;
            u8 b;
            u8 a;
        };
    };
};

struct Vec3f {
    f32 x, y, z;
};

struct Vec2f {
    Vec2f() {
        x = 0;
        y = 0;
    }

    Vec2f(const float val) {
        x = val;
        y = val;
    }

    Vec2f(const Vec2f& other) {
        x = other.x;
        y = other.y;
    }

    Vec2f(const Vec3f& other) {
        x = other.x;
        y = other.y;
    }

    Vec2f(float nx, float ny)
        : x(nx)
        , y(ny)
    { }

    Vec2f operator+(const Vec2f& other) const {
        return Vec2f(x + other.x, y + other.y);
    }

    Vec2f operator-(const Vec2f& other) const {
        return Vec2f(x - other.x, y - other.y);
    }

    Vec2f operator*(const Vec2f& other) const {
        return Vec2f(x * other.x, y * other.y);
    }

    Vec2f operator/(const Vec2f& other) const {
        return Vec2f(x / other.x, y / other.y);
    }

    Vec2f operator/(const float val) const {
        return Vec2f(x / val, y / val);
    }

    Vec2f operator*(const float val) const {
        return Vec2f(x * val, y * val);
    }

    inline void operator=(const float val) {
        x = val;
        y = val;
    }

    inline ImVec2 ToImVec2() {
        return ImVec2(x, y);
    }
    

    f32 x, y;
};

inline Vec2f ToVec2f(const ImVec2 vec) {
    return Vec2f(vec.x, vec.y);
}


static f32 SwapF32(f32);

static u16 Swap16(u16 value) {
    return (value << 8) | (value >> 8);
}

static u32 Swap32(u32 value) {
    return ((value >> 24) & 0x000000FF) |
        ((value >> 8) & 0x0000FF00) |
        ((value << 8) & 0x00FF0000) |
        ((value << 24) & 0xFF000000);
}

// static u64 Swap64(u64 value) {
//     return ((value << 56) & 0xFF00000000000000ULL) |
//         ((value << 40) & 0x00FF000000000000ULL) |
//         ((value << 24) & 0x0000FF0000000000ULL) |
//         ((value << 8) & 0x000000FF00000000ULL) |
//         ((value >> 8) & 0x00000000FF000000ULL) |
//         ((value >> 24) & 0x0000000000FF0000ULL) |
//         ((value >> 40) & 0x000000000000FF00ULL) |
//         ((value >> 56) & 0x00000000000000FFULL);
// }

static f32 SwapF32(float value) {
    u32 intval;
    std::memcpy(&intval, &value, sizeof(float));
    intval = Swap32(intval);
    float result;
    std::memcpy(&result, &intval, sizeof(float));
    return result;
}

#define ARRAY_LENGTH(x) (sizeof((x)) / sizeof((x)[0]))
