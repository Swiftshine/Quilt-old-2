#pragma once

#include <cstdio>

namespace bpe {
    void decode(FILE* in, FILE* out);
    void encode(FILE* in, FILE* out);
}
