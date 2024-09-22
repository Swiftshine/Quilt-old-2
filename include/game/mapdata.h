#pragma once

#include "game/colbin.h"

#pragma pack(push, 1)

using string32 = char[0x20];
using string64 = char[0x40];

namespace Mapdata {
namespace Mapbin {
    /* actual mapbin data */

    struct Header {
        f32 m_0;
        Vec2f mBoundsMin;
        Vec2f mBoundsMax;
        u32 mNumWalls;
        u32 mWallOffset;
        u32 mNumLabeledWalls;
        u32 mLabeledWallOffset;
        u32 mNumCommonGimmicks;
        u32 mCommonGimmickOffset;
        u32 mNumGimmicks;
        u32 mGimmickOffset;
        u32 mNumPaths;
        u32 mPathOffset;
        u32 mNumZones;
        u32 mZoneOffset;
        u32 mNumCourseInfo;
        u32 mCourseInfoOffset;
        u32 mCommonGimmickNameOffset;
        u32 mColbinTypeOffset;
        u32 mLabeledWallLabelOffset;
    };

    using Wall = Colbin::Entry;

    struct LabeledWall : public Colbin::Entry {
        u32 mLabelIndex;
    };

    struct MapdataParams {
        int mIntParams[3];
        f32 mFloatParams[3];
        string64 mStringParams[3];
    };

    struct Gimmick {
        char mName[0x30];
        u8 m_30[0x10];
        Vec3f mPosition;
        MapdataParams mParams;
    };
    
    struct CommonGimmickParams {
        int mIntParams1[3];
        f32 mFloatParams1[3];
        int mIntParams2[4];
        float mFloatParams2[3];
        float mFloatParams3[3];
        string32 mStringParam1;
        u8 mTheRest[0x120];
    };

    struct CommonGimmick {
        u32 mNameIndex;
        Vec3f mPosition;
        CommonGimmickParams mParams;
    };

    // variable length structure
    struct Path {
        string32 mName;
        string32 mType;
        MapdataParams mParams;
        u32 mNumPoints;
        // Vec2f mPoints[mNumPoints];
    };

    struct Zone {
        string32 mName;
        string32 m_20;
        MapdataParams mParams;
        Vec2f mBoundsMin;
        Vec2f mBoundsMax;  
    };

    struct RaceCourseInfo {
        string32 mName;
        string32 m_20;
        MapdataParams mParams;
        Vec3f mPosition;
    };

    /* utility wrappers */

    using WallWrapper = Colbin::EntryWrapper;

    class LabeledWallWrapper : public Colbin::EntryWrapper {
    public:
        LabeledWallWrapper() = default;
        ~LabeledWallWrapper() = default;

        void SetLabel(std::string label) {
            mLabel = label;
        }

        std::string GetLabel() const {
            return mLabel;
        }

    private:
        std::string mLabel;
    };

    class MapdataParamsWrapper {
    public:
        MapdataParamsWrapper() = default;
        ~MapdataParamsWrapper() = default;

        int GetIntParam(u32 index) const {
            return mIntParams[index];
        }

        void SetIntParam(u32 index, int value) {
            mIntParams[index] = value;
        }

        f32 GetFloatParam(u32 index) const {
            return mFloatParams[index];
        }

        void SetFloatParam(u32 index, float value) {
            mFloatParams[index] = value;
        }

        std::string GetStringParam(u32 index) const {
            return mStringParams[index];
        }

        void SetStringParam(u32 index, std::string value) {
            mStringParams[index] = value;
        }

    private:
        int mIntParams[3];
        f32 mFloatParams[3];
        std::string mStringParams[3];
    };

    class GimmickWrapper {
    public:
        GimmickWrapper() = default;
        ~GimmickWrapper() = default;

        std::string GetName() const {
            return mName;
        }

        void SetName(std::string value) {
            mName = value;
        }

        std::array<u8, 0x10> GetUnk30() const {
            return m_30;
        }

        void SetUnk30(std::array<u8, 0x10> value) {
            m_30 = value;
        }

        Vec3f GetPosition() const {
            return mPosition;
        }

        void SetPosition(Vec3f value) {
            mPosition = value;
        }

        MapdataParamsWrapper& GetParams() {
            return mParams;
        }
        

    private:
        std::string mName;
        std::array<u8, 0x10> m_30;
        Vec3f mPosition;
        MapdataParamsWrapper mParams;    
    };

    class CommonGimmickParamsWrapper {
    public:
        CommonGimmickParamsWrapper() = default;
        ~CommonGimmickParamsWrapper() = default;

        int GetIntParam1(u32 index) const {
            return mIntParams1[index];
        }

        void SetIntParam1(u32 index, int value) {
            mIntParams1[index] = value;
        }

        f32 GetFloatParam1(u32 index) const {
            return mFloatParams1[index];
        }

        void SetFloatParam1(u32 index, f32 value) {
            mFloatParams1[index] = value;
        }

        int GetIntParam2(u32 index) const {
            return mIntParams2[index];
        }

        void SetIntParam2(u32 index, int value) {
            mIntParams2[index] = value;
        }

        f32 GetFloatParam2(u32 index) const {
            return mFloatParams2[index];
        }

        void SetFloatParam2(u32 index, f32 value) {
            mFloatParams2[index] = value;
        }

        f32 GetFloatParam3(u32 index) const {
            return mFloatParams3[index];
        }

        void SetFloatParam3(u32 index, f32 value) {
            mFloatParams3[index] = value;
        }

        std::string GetStringParam1() const {
            return mStringParam1;
        }

        void SetStringParam1(const std::string& value) {
            mStringParam1 = value;
        }

        std::array<u8, 0x120> GetTheRest() const {
            return mTheRest;
        }

        void SetTheRest(const std::array<u8, 0x120>& value) {
            mTheRest = value;
        }

        void SetTheRest(char arr[0x120]) {
            std::memcpy(arr, mTheRest.data(), 0x120);
        }

    private:
        int mIntParams1[3];
        f32 mFloatParams1[3];
        int mIntParams2[4];
        f32 mFloatParams2[3];
        f32 mFloatParams3[3];
        std::string mStringParam1;
        std::array<u8, 0x120> mTheRest;
    };


    class CommonGimmickWrapper {
    public:
        CommonGimmickWrapper() = default;
        ~CommonGimmickWrapper() = default;

        std::array<char, 0x20> GetBytes() const {
            return mBytes;
        }

        void SetBytes(const std::array<char, 0x20> bytes) {
            mBytes = bytes;
        }

        void SetBytes(const char bytes[0x20]) {
            std::memcpy(mBytes.data(), bytes, 0x20);
        }

        Vec3f GetPosition() const {
            return mPosition;
        }

        void SetPosition(Vec3f value) {
            mPosition = value;
        }

        CommonGimmickParamsWrapper& GetParams() {
            return mParams;
        }

    private:
        std::array<char, 0x20> mBytes; // the name of the common gimmick; it's usually in ShiftJIS
        Vec3f mPosition;
        CommonGimmickParamsWrapper mParams;
    };

    class PathWrapper {
    public:
        PathWrapper() = default;
        ~PathWrapper() = default;

        std::string GetName() const {
            return mName;
        }

        void SetName(const std::string& value) {
            mName = value;
        }

        std::string GetType() const {
            return mType;
        }

        void SetType(const std::string& value) {
            mType = value;
        }

        MapdataParamsWrapper& GetParams() {
            return mParams;
        }

        u32 GetNumPoints() const {
            return mNumPoints;
        }

        void SetNumPoints(u32 value) {
            mNumPoints = value;
        }

    private:
        std::string mName;
        std::string mType;
        MapdataParamsWrapper mParams;
        u32 mNumPoints;
    };


    class ZoneWrapper {
    public:
        ZoneWrapper() = default;
        ~ZoneWrapper() = default;

        std::string GetName() const {
            return mName;
        }

        void SetName(const std::string& value) {
            mName = value;
        }

        std::string GetUnk20() const {
            return m_20;
        }

        void SetUnk20(const std::string& value) {
            m_20 = value;
        }

        MapdataParamsWrapper& GetParams() {
            return mParams;
        }

        Vec2f GetBoundsMin() const {
            return mBoundsMin;
        }

        void SetBoundsMin(Vec2f value) {
            mBoundsMin = value;
        }

        Vec2f GetBoundsMax() const {
            return mBoundsMax;
        }

        void SetBoundsMax(Vec2f value) {
            mBoundsMax = value;
        }

    private:
        std::string mName;
        std::string m_20;
        MapdataParamsWrapper mParams;
        Vec2f mBoundsMin;
        Vec2f mBoundsMax;
    };

    class RaceCourseInfoWrapper {
    public:
        RaceCourseInfoWrapper() = default;
        ~RaceCourseInfoWrapper() = default;

        std::string GetName() const {
            return mName;
        }

        void SetName(const std::string& value) {
            mName = value;
        }

        std::string GetUnk20() const {
            return m_20;
        }

        void SetUnk20(const std::string& value) {
            m_20 = value;
        }

        MapdataParamsWrapper& GetParams() {
            return mParams;
        }

        Vec3f GetPosition() const {
            return mPosition;
        }

        void SetPosition(Vec3f value) {
            mPosition = value;
        }

    private:
        std::string mName;
        std::string m_20;
        MapdataParamsWrapper mParams;
        Vec3f mPosition;
    };

    class FileWrapper {
    public:
        FileWrapper() = default;
        ~FileWrapper() = default;

        f32 GetUnk0() const {
            return m_0;
        }

        void SetUnk0(f32 value) {
            m_0 = value;
        }

        Vec2f GetBoundsMin() const {
            return mBoundsMin;
        }

        void SetBoundsMin(Vec2f value) {
            mBoundsMin = value;
        }


        Vec2f GetBoundsMax() const {
            return mBoundsMax;
        }

        void SetBoundsMax(Vec2f value) {
            mBoundsMax = value;
        }

        WallWrapper& GetWall(u32 index) {
            return mWalls[index];
        }

        void AddWall(WallWrapper wrapper) {
            mWalls.push_back(wrapper);
        }

        void RemoveWall(u32 index) {
            mWalls.erase(mWalls.begin() + index);
        }

        u32 GetNumWalls() {
            return mWalls.size();
        }

        LabeledWallWrapper& GetLabeledWall(u32 index) {
            return mLabeledWalls[index];
        }

        void AddLabeledWall(LabeledWallWrapper wrapper) {
            mLabeledWalls.push_back(wrapper);
        }

        void RemoveLabeledWall(u32 index) {
            mLabeledWalls.erase(mLabeledWalls.begin() + index);
        }

        CommonGimmickWrapper& GetCommonGimmick(u32 index) {
            return mCommonGimmicks[index];
        }

        u32 GetNumCommonGimmicks() {
            return mCommonGimmicks.size();
        }

        void AddCommonGimmick(CommonGimmickWrapper wrapper) {
            mCommonGimmicks.push_back(wrapper);
        }

        void RemoveCommonGimmick(u32 index) {
            mCommonGimmicks.erase(mCommonGimmicks.begin() + index);
        }

        GimmickWrapper& GetGimmick(u32 index) {
            return mGimmicks[index];
        }

        u32 GetNumGimmicks() {
            return mGimmicks.size();
        }

        void AddGimmick(GimmickWrapper wrapper) {
            mGimmicks.push_back(wrapper);
        }

        void RemoveGimmick(u32 index) {
            mGimmicks.erase(mGimmicks.begin() + index);
        }

        PathWrapper& GetPath(u32 index) {
            return mPaths[index];
        }

        void AddPath(PathWrapper wrapper) {
            mPaths.push_back(wrapper);
        }

        void RemovePath(u32 index) {
            mPaths.erase(mPaths.begin() + index);
        }

        ZoneWrapper& GetZone(u32 index) {
            return mZones[index];
        }

        void AddZone(ZoneWrapper wrapper) {
            mZones.push_back(wrapper);
        }

        void RemoveZone(u32 index) {
            mZones.erase(mZones.begin() + index);
        }


        RaceCourseInfoWrapper& GetRaceCourseInfo(u32 index) {
            return mRaceCourseInfo[index];
        }

        void AddRaceCourseInfo(RaceCourseInfoWrapper wrapper) {
            mRaceCourseInfo.push_back(wrapper);
        }

        void RemoveRaceCourseInfo(u32 index) {
            mRaceCourseInfo.erase(mRaceCourseInfo.begin() + index);
        }

        void Read(const std::vector<char>& data) {
            ClearAll();

            u32 offs = 0;
            
            u32 numWalls;
            u32 wallOffset;
            u32 numLabeledWalls;
            u32 labeledWallOffset;
            u32 numCommonGimmicks;
            u32 commonGimmickOffset;
            u32 numGimmicks;
            u32 gimmickOffset;
            u32 numPaths;
            u32 pathOffset;
            u32 numZones;
            u32 zoneOffset;
            u32 numCourseInfo;
            u32 courseInfoOffset;
            u32 commonGimmickNameOffset;
            u32 numCommonGimmickNames;
            u32 colbinTypeOffset;
            u32 numColbinTypes;
            u32 labeledWallLabelOffset;
            u32 numLabeledWallLabels;

            Quilt::ByteSwapFromVector(data, offs, m_0);
            Quilt::ByteSwapFromVector(data, offs, mBoundsMin.x);
            Quilt::ByteSwapFromVector(data, offs, mBoundsMin.y);
            Quilt::ByteSwapFromVector(data, offs, mBoundsMax.x);
            Quilt::ByteSwapFromVector(data, offs, mBoundsMax.y);
            Quilt::ByteSwapFromVector(data, offs, numWalls);
            Quilt::ByteSwapFromVector(data, offs, wallOffset);
            Quilt::ByteSwapFromVector(data, offs, numLabeledWalls);
            Quilt::ByteSwapFromVector(data, offs, labeledWallOffset);
            Quilt::ByteSwapFromVector(data, offs, numCommonGimmicks);
            Quilt::ByteSwapFromVector(data, offs, commonGimmickOffset);
            Quilt::ByteSwapFromVector(data, offs, numGimmicks);
            Quilt::ByteSwapFromVector(data, offs, gimmickOffset);
            Quilt::ByteSwapFromVector(data, offs, numPaths);
            Quilt::ByteSwapFromVector(data, offs, pathOffset);
            Quilt::ByteSwapFromVector(data, offs, numZones);
            Quilt::ByteSwapFromVector(data, offs, zoneOffset);
            Quilt::ByteSwapFromVector(data, offs, numCourseInfo);
            Quilt::ByteSwapFromVector(data, offs, courseInfoOffset);
            Quilt::ByteSwapFromVector(data, offs, commonGimmickNameOffset);
            Quilt::ByteSwapFromVector(data, offs, colbinTypeOffset);
            Quilt::ByteSwapFromVector(data, offs, labeledWallLabelOffset);

            Quilt::ByteSwapFromVector(data, commonGimmickNameOffset, numCommonGimmickNames, false);
            Quilt::ByteSwapFromVector(data, colbinTypeOffset, numColbinTypes, false);
            Quilt::ByteSwapFromVector(data, labeledWallLabelOffset, numLabeledWallLabels, false);

            // at this point, "offs" can be used for whatever

            for (auto i = 0; i < numWalls; i++) {
                Wall wall;
                WallWrapper wrapper;

                Quilt::GetFromVector(data, wallOffset, wall);
                wrapper.SetStart(SwapF32(wall.mStart.x), SwapF32(wall.mStart.y));
                wrapper.SetEnd(SwapF32(wall.mEnd.x), SwapF32(wall.mEnd.y));
                wrapper.SetUnk10({SwapF32(wall.m_10.x), SwapF32(wall.m_10.y)});

                if (0 < numColbinTypes) {
                    string32 name { 0 };
                    
                    offs = colbinTypeOffset + 4 + (sizeof(string32) * i);
                    Quilt::GetFromVector(data, offs, name);
                    wrapper.SetCollisionType(name);
                }

                mWalls.push_back(wrapper);
            }

            for (auto i = 0; i < numLabeledWalls; i++) {
                LabeledWall wall;
                LabeledWallWrapper wrapper;

                Quilt::GetFromVector(data, labeledWallOffset, wall);
                wrapper.SetStart(SwapF32(wall.mStart.x), SwapF32(wall.mStart.y));
                wrapper.SetEnd(SwapF32(wall.mEnd.x), SwapF32(wall.mEnd.y));
                wrapper.SetUnk10({SwapF32(wall.m_10.x), SwapF32(wall.m_10.y)});

                if (0 < numColbinTypes) {
                    string32 name { 0 };
                    offs = colbinTypeOffset + 4 + (sizeof(string32) * i);
                    Quilt::GetFromVector(data, offs, name);
                    wrapper.SetCollisionType(name);
                }
                
                if (0 < numLabeledWallLabels) {
                    string32 name { 0 };
                    offs = labeledWallLabelOffset + 4 + (sizeof(string32) * i);
                    Quilt::GetFromVector(data, offs, name);
                    wrapper.SetLabel(name);
                }

                mLabeledWalls.push_back(wrapper);
            }


            for (auto i = 0; i < numCommonGimmicks; i++) {
                CommonGimmick cgmk;
                CommonGimmickWrapper wrapper;

                Quilt::GetFromVector(data, commonGimmickOffset, cgmk);

                for (auto j = 0; j < 3; j++) {
                    wrapper.GetParams().SetIntParam1(j, Swap32(cgmk.mParams.mIntParams1[j]));
                    wrapper.GetParams().SetIntParam2(j, Swap32(cgmk.mParams.mIntParams2[j]));
                    wrapper.GetParams().SetFloatParam1(j, SwapF32(cgmk.mParams.mFloatParams1[j]));
                    wrapper.GetParams().SetFloatParam2(j, SwapF32(cgmk.mParams.mFloatParams2[j]));
                    wrapper.GetParams().SetFloatParam3(j, SwapF32(cgmk.mParams.mFloatParams3[j]));
                }
                wrapper.GetParams().SetIntParam2(3, Swap32(cgmk.mParams.mIntParams1[3]));
            }

            for (auto i = 0; i < numGimmicks; i++) {
                
            }
            
            // todo: the rest later
        }
        
        void Save() const;

        void ClearAll() {
            mWalls.clear();
            mLabeledWalls.clear();
            mCommonGimmicks.clear();
            mGimmicks.clear();
            mPaths.clear();
            mZones.clear();
            mRaceCourseInfo.clear();
        }
    private:
        f32 m_0;
        Vec2f mBoundsMin;
        Vec2f mBoundsMax;
        std::vector<WallWrapper> mWalls;
        std::vector<LabeledWallWrapper> mLabeledWalls;
        std::vector<CommonGimmickWrapper> mCommonGimmicks;
        std::vector<GimmickWrapper> mGimmicks;
        std::vector<PathWrapper> mPaths;
        std::vector<ZoneWrapper> mZones;
        std::vector<RaceCourseInfoWrapper> mRaceCourseInfo;
    };

}
}

#pragma pack(pop)
