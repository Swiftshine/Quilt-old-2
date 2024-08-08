#include "key/colbin.h"
#include "applog.h"

using namespace key::colbin;

/* Colbin Entry */

wrapper::Entry::Entry(std::ifstream& file) {
    Read(file);
}

wrapper::Entry::Entry() { }

wrapper::Entry::~Entry() { }

void wrapper::Entry::SetPoint1(const Vec2f& p) { mPoint1 = p; }
void wrapper::Entry::SetPoint2(const Vec2f& p) { mPoint2 = p; }
void wrapper::Entry::SetUnk10(const Vec2f& p) { mUnk10 = p; }

Vec2f& wrapper::Entry::GetPoint1() { return mPoint1; }
Vec2f& wrapper::Entry::GetPoint2() { return mPoint2; }
Vec2f& wrapper::Entry::GetUnk10() { return mUnk10; }

u32 wrapper::Entry::GetIndex() { return mIndex; }
u32 wrapper::Entry::GetCollisionTypeIndex() { return mCollisionTypeIndex; }

void wrapper::Entry::Read(std::ifstream& file) {
    Vec2f v;
    file.read((char*)&v, 8);
    v.Swap();
    mPoint1 = v;
    file.read((char*)&v, 8);
    v.Swap();
    mPoint2 = v;
    file.read((char*)&v, 8);
    v.Swap();
    mUnk10 = v;
    u32 i;
    file.read((char*)&i, 4);
    mIndex = Swap32(i);
    file.read((char*)&i, 4);
    mCollisionTypeIndex = Swap32(i);
}

void wrapper::Entry::Write(std::ofstream& file) {
    Vec2f v = mPoint1;
    v.Swap();
    file.write((char*)&v, 8);
    v = mPoint2;
    v.Swap();
    file.write((char*)&v, 8);
    v = mUnk10;
    v.Swap();
    file.write((char*)&v, 8);
    u32 i = Swap32(mIndex);
    file.write((char*)&i, 4);
    i = Swap32(mCollisionTypeIndex);
    file.write((char*)&i, 4);
}

/* Colbin File */


wrapper::Colbin::Colbin() { }

wrapper::Colbin::Colbin(std::ifstream& file) {
    Read(file);
}

wrapper::Colbin::~Colbin() {
    mEntries.clear();
    mCollisionTypes.clear();
}

void wrapper::Colbin::Add() {

}

void wrapper::Colbin::Read(std::ifstream& file) {
    file.read((char*)&mUnk0, 4);
    mUnk0 = SwapF32(mUnk0);
    u32 numEntries;
    file.read((char*)&numEntries, 4);
    Offset toEntries;
    file.read((char*)&toEntries, 4);
    Offset toFooter;
    file.read((char*)&toFooter, 4);

    numEntries = Swap32(numEntries);
    toEntries = Swap32(toEntries);
    toFooter = Swap32(toFooter);

    file.seekg(toEntries);

    for (auto i = 0; i < numEntries; i++) {
        mEntries.push_back(wrapper::Entry(file));
    }

    file.seekg(toFooter);
    u32 numCollisionTypes;
    file.read((char*)&numCollisionTypes, 4);
    numCollisionTypes = Swap32(numCollisionTypes);

    for (auto i = 0; i < numCollisionTypes; i++) {
        char type[0x20];
        file.read(type, 0x20);
        mCollisionTypes.push_back(std::string(type));
    }
}

void wrapper::Colbin::Write(std::ofstream& file) {
    f32 f = SwapF32(mUnk0);
    file.write((char*)&f, 4);
    u32 numEntries = Swap32(mEntries.size());
    file.write((char*)&numEntries, 4);
    Offset toEntries = Swap32(sizeof(data::Header));
    file.write((char*)&toEntries, 4);
    Offset toFooter = sizeof(data::Header);
    toFooter += mEntries.size() * sizeof(data::Entry);
    toFooter = Swap32(toFooter);
    file.write((char*)&toFooter, 4);

    for (auto i = 0; i < mEntries.size(); i++) {
        mEntries[i].Write(file);
    }

    u32 numCollisionTypes = Swap32(mCollisionTypes.size());
    file.write((char*)&numCollisionTypes, 4);

    for (auto i = 0; i < mCollisionTypes.size(); i++) {
        // put chars into buffer first to ensure safe writing

        char type[0x20];
        std::memcpy(type, mCollisionTypes[i].c_str(), 0x20);
        file.write(type, 0x20);
    }
}