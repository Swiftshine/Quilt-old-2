#pragma once

#include "types.h"

#define GFARCH_VERSION 0x0300 // 3.0
namespace gfl {
    namespace GfArch {

        static inline u32 checksum(std::string s) {
            u32 result = 0;
            for (char c : s) {
                if (0 == c) break;
                result = c + (result * 137);
            }
            return result;
        }

        struct Header {
            char mMagic[4]; // "GFAC" - GoodFeel ArChive
            u32 mVersion;
            bool mIsCompressed;
            u8 padding1[3];
            u32 mFileInfoOffset;
            u32 mFileInfoSize;
            u32 mCompressionHeaderOffset;
            u32 mCompressedBlockSize; // the size of all data starting with the compression header offset
            u8 padding[0x10];
            u32 mFileCount;
        };

        struct FileEntry {
            u32 mChecksum; // if this entry is the last one, a flag of 0x80000000 is applied.
            u32 mNameOffset;
            u32 mDecompressedSize;
            u32 mDecompressedDataOffset; // calculated as if the compression header isn't present.
        };

        struct CompressionHeader {
            char mMagic[4]; // "GFCP" - GoodFeel ComPression
            u32 m_4;
            s32 mCompressionType;
            u32 mDecompressedDataSize;
            u32 mCompressedDataSize;
        };
    }
}
