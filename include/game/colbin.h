#pragma once

#include "common.h"

#pragma pack(push, 1)
namespace Colbin {
    /* actual colbin data */

    struct Header {
        f32 m_0;
        u32 mNumEntries;
        Offset mEntryOffset;
        Offset mFooterOffset;
    };

    struct Entry {
        Vec2f mStart;
        Vec2f mEnd;
        Vec2f m_10;
        u32 mEntryIndex;
        u32 mCollisionTypeIndex;
    };


    /* utility wrappers */

    class EntryWrapper {
    public:
        EntryWrapper();
        ~EntryWrapper();
    
        void SetStart(Vec2f start) {
            mStart = start;
        }
        void SetEnd(Vec2f end) {
            mEnd = end;
        }
        void SetUnk10(Vec2f unk) {
            m_10 = unk;
        }
        void SetCollisionType(std::string type) {
            mCollisionType = type;
        }

        Vec2f& GetStart() {
            return mStart;
        }
        Vec2f& GetEnd() {
            return mEnd;
        }
        Vec2f& GetUnk10() {
            return m_10;
        }
        std::string& GetCollisionType() {
            return mCollisionType;
        }
    private:
        Vec2f mStart;
        Vec2f mEnd;
        Vec2f m_10;
        std::string mCollisionType;
    };

    class FileWrapper {
    public:
        FileWrapper();
        ~FileWrapper();

        f32 GetUnk0() const {
            return m_0;
        }

        void SetUnk0(f32 value) {
            m_0 = value;
        }
        
        void AddEntry(EntryWrapper entry) {
            mEntries.push_back(entry);
        }

        void RemoveEntry(u32 index) {
            if (index >= mEntries.size()) {
                AppLog::Error("Colbin::FileWrapper::RemoveEntry() - index out of bounds");
            }
            mEntries.erase(mEntries.begin() + index);
        }

        EntryWrapper& GetEntry(u32 index) {
            if (index >= mEntries.size()) {
                AppLog::Error("Colbin::FileWrapper::GetEntry() - index out of bounds");
            }
            return mEntries[index];
        }

        u32 GetNumEntries() const {
            return mEntries.size();
        }

        void AddCollisionType(std::string type);
        void RemoveCollisionType(std::string query);



        u32 GetNumCollisionTypes() const {
            return mCollisionTypes.size();
        }

        void Read(const std::vector<char>& data) {
            u32 offs = 0;
            f32 m_0 = SwapF32(*(f32*)&data[offs]);
            offs += sizeof(f32);

            u32 numEntries = Swap32(*(u32*)&data[offs]);
            offs += sizeof(u32);

            u32 entryOffs = Swap32(*(u32*)&data[offs]);
            offs += sizeof(u32);
            
            u32 footerOffs = Swap32(*(u32*)&data[offs]);
            offs = entryOffs;

            u32 numColl = Swap32(*(u32*)&data[footerOffs]);

            for (auto i = 0; i < numEntries; i++) {
                Entry entry;
                std::memcpy(&entry, &data[offs], sizeof(Entry));
                offs += sizeof(Entry);

                EntryWrapper wrapper;
                Vec2f v;
                v = entry.mStart;
                v.x = SwapF32(v.x);
                v.y = SwapF32(v.y);

                wrapper.SetStart(v);
                v = entry.mEnd;
                v.x = SwapF32(v.x);
                v.y = SwapF32(v.y);
                wrapper.SetEnd(v);

                v = entry.m_10;
                v.x = SwapF32(v.x);
                v.y = SwapF32(v.y);
                wrapper.SetUnk10(v);
            }

            offs = footerOffs;

            for (auto i = 0; i < numColl; i++) {
                char type[0x20] { 0 };
                std::memcpy(type, &data[offs], 0x20);
                mCollisionTypes.push_back(type);
                offs += 0x20;
            }
        }

        void Save(std::vector<char>& data) const;

    private:
        f32 m_0;
        std::vector<EntryWrapper> mEntries;
        std::vector<std::string> mCollisionTypes;
    };
}
#pragma pack(pop)
