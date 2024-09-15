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
        u32 mZoneIffset;
        u32 mNumCourseInfo;
        u32 mCourseInfoOffset;
        u32 mCommonGimmickNameOffset;
        u32 mColbinTypeOffset;
        u32 mLabeledWallLabels;
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

        std::string GetName() const {
            return mName;
        }

        void SetName(const std::string& value) {
            mName = value;
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
        std::string mName;
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

    };
}
}

#pragma pack(pop)
