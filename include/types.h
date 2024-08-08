#pragma once

#include <cstdint>
#include <cstring>

using f32 = float;

using u64 = uint64_t;
using s64 = int64_t;
using u32 = uint32_t;
using s32 = int32_t;
using u16 = uint16_t;
using s16 = int16_t;
using u8  = uint8_t;
using s8  = int8_t;

using Offset = u32;

static f32 SwapF32(f32);

struct Vec2f {
    Vec2f() { x = 0; y = 0; }
    Vec2f(f32 nx, f32 ny) { x = nx; y = ny; }
    Vec2f(const Vec2f& other) { x = other.x; y = other.y; }
    
    void Swap() { x = SwapF32(x); y = SwapF32(y); }
    f32 x, y;
};

#define ASSERT_SIZE(c, s) static_assert(sizeof(c) == s);

static u16 Swap16(u16 value) {
    return (value << 8) | (value >> 8);
}

static u32 Swap32(u32 value) {
    return ((value >> 24) & 0x000000FF) |
        ((value >> 8) & 0x0000FF00) |
        ((value << 8) & 0x00FF0000) |
        ((value << 24) & 0xFF000000);
}

static u64 Swap64(u64 value) {
    return ((value << 56) & 0xFF00000000000000ULL) |
        ((value << 40) & 0x00FF000000000000ULL) |
        ((value << 24) & 0x0000FF0000000000ULL) |
        ((value << 8) & 0x000000FF00000000ULL) |
        ((value >> 8) & 0x00000000FF000000ULL) |
        ((value >> 24) & 0x0000000000FF0000ULL) |
        ((value >> 40) & 0x000000000000FF00ULL) |
        ((value >> 56) & 0x00000000000000FFULL);
}

static f32 SwapF32(float value) {
    u32 intval;
    std::memcpy(&intval, &value, sizeof(float));
    intval = Swap32(intval);
    float result;
    std::memcpy(&result, &intval, sizeof(float));
    return result;
}