#include "gfarch_utility.h"
#include "common.h"

// menu functions



// GfArch functions

std::string getstring(std::vector<char>& archive, u32 offset) {
    offset = offset & 0x00FFFFFF;

    std::string result = "";

    while (0 != archive[offset]) {
        result += archive[offset++];
    }

    return result;
}

inline u32 align16(u32 value) {
    return ((value + 0xF) & ~(0xF));
}

inline u32 align32(u32 value) {
    return ((value + 0x1F) & ~(0x1F));
}

std::vector<Quilt::File> GfArchUtility::Extract(std::string archivePath) {
    std::ifstream in(archivePath, std::ios::binary);
    if (!fs::is_regular_file(archivePath)) {
        AppLog::Error("File " + archivePath + " does not exist.");
    }

    std::vector<char> archive((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    in.close();

    u32 currentOffset = 0;

    gfl::GfArch::Header header;
    std::memcpy(&header, archive.data(), sizeof(gfl::GfArch::Header));
    currentOffset += sizeof(gfl::GfArch::Header);

    if (0 != std::memcmp(header.mMagic, "GFAC", 4)) {
        AppLog::Error("File " + archivePath + " has an invalid archive header.");
    }

    std::vector<gfl::GfArch::FileEntry> entries;
    std::vector<std::string> filenames;

    for (auto i = 0; i < header.mFileCount; i++) {
        gfl::GfArch::FileEntry entry;
        std::memcpy(&entry, &archive[currentOffset], sizeof(gfl::GfArch::FileEntry));
        currentOffset += sizeof(gfl::GfArch::FileEntry);
        entries.push_back(entry);
        filenames.push_back(getstring(archive, entry.mNameOffset));
    }

    currentOffset = header.mCompressionHeaderOffset;

    gfl::GfArch::CompressionHeader cHeader;
    std::memcpy(&cHeader, &archive[currentOffset], sizeof(gfl::GfArch::CompressionHeader));
    currentOffset += sizeof(gfl::GfArch::CompressionHeader);

    if (0 != std::memcmp(cHeader.mMagic, "GFCP", 4)) {
        AppLog::Error("File " + archivePath + " has an invalid compression header.");
    }

    std::vector<char> compressed;
    std::vector<char> decompressed;
    compressed.insert(compressed.end(), archive.begin() + currentOffset, archive.end());
    {
        if (!fs::exists("quilt_temp")) {
            fs::create_directory("quilt_temp");
        }

        std::ofstream temp("quilt_temp/temp1.bin", std::ios::binary);
        temp.write(compressed.data(), compressed.size());
        temp.close();
    }
    {
        FILE* t1 = fopen("quilt_temp/temp1.bin", "rb");
        FILE* t2 = fopen("quilt_temp/temp2.bin", "wb");

        bpe::decode(t1, t2);
        fclose(t1);
        fclose(t2);

        std::ifstream in("quilt_temp/temp2.bin", std::ios::binary);
        decompressed = std::vector<char>((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
        in.close();

        if (fs::exists("quilt_temp")) {
            fs::remove_all("quilt_temp");
        }
    }

    std::vector<Quilt::File> files;

    for (auto i = 0; i < entries.size(); i++) {
        gfl::GfArch::FileEntry& entry = entries[i];
        std::string filename = filenames[i];

        std::vector<char> data;

        auto start = decompressed.begin() + entry.mDecompressedDataOffset - header.mCompressionHeaderOffset;
        data.insert(data.end(), start, start + entry.mDecompressedSize);
        files.emplace_back(filename, data);
    }

    return files;
}
