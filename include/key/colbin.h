#pragma once

#include "types.h"

#include <fstream>
#include <vector>

#pragma pack(push, 1)

namespace key::colbin::data {
    struct Header {
        f32 _0;
        u32 numEntries;
        Offset toEntries;
        Offset toFooter;
    };

    ASSERT_SIZE(Header, 0x10)

    struct Entry {
        Vec2f point1;
        Vec2f point2;
        Vec2f _14;
        u32 index;
        u32 collisionTypeIndex;
    };

    ASSERT_SIZE(Entry, 0x20)
}
#pragma pack(pop)

// File handling will utilise wrappers for ease of use.
namespace key::colbin::wrapper {

    // A wrapper for colbin entries.
    // To be used by a colbin wrapper.
    class Entry {
    public:
        Entry(std::ifstream& file);
        Entry();
        ~Entry();


        void SetPoint1(const Vec2f& p);
        void SetPoint2(const Vec2f& p);
        void SetUnk10(const Vec2f& p);
        void SetCollisionTypeIndex(const u32 n);

        Vec2f& GetPoint1();
        Vec2f& GetPoint2();
        Vec2f& GetUnk10();
        u32 GetIndex();
        u32 GetCollisionTypeIndex();

        void Read(std::ifstream& file);
        void Write(std::ofstream& file);
    private:
        Vec2f mPoint1;
        Vec2f mPoint2;
        Vec2f mUnk10;
        u32 mIndex;
        u32 mCollisionTypeIndex;
    };

    // A wrapper for colbin files.
    class Colbin {
    public:
        Colbin(std::ifstream& file);
        Colbin();
        ~Colbin();

        void Add();

        void Remove(u32 index);

        Entry* At(u32 index);

        u32 GetEntryCount();
        u32 GetCollisionTypeCount();
        
        void Read(std::ifstream& file);
        void Write(std::ofstream& file);
    private:
        f32 mUnk0;
        std::vector<Entry> mEntries;
        std::vector<std::string> mCollisionTypes;
    };
}