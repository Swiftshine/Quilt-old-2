#pragma once

#include "common.h"
#include "gfl/gfarch.h"
#include "bpe.h"

class GfArchUtility {
public:
    // returns decompressed files
    static std::vector<Quilt::File> Extract(std::string archivePath);
    static void Archive(std::vector<Quilt::File> files, std::string archivePath);
private:
    GfArchUtility() = default;
    ~GfArchUtility() = default;
};
