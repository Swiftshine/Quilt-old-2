#pragma once

#include "game/colbin.h"

#pragma pack(push, 1)


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

    struct LabeledWall : public Colbin::Entry {
        u32 mLabelIndex;
    };

    struct MapdataParams {
        int mIntParams[3];
        f32 mFloatParams[3];
        char mStringParams[3][0x40];
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
        char mString1[0x20];
        u8 mTheRest[0x120];
    };

    struct CommonGimmick {
        u32 mNameIndex;
        Vec3f mPosition;
        CommonGimmickParams mParams;
    };

    // variable length structure
    struct Path {
        char mName[0x20];
        char mType[0x20];
        MapdataParams mParams;
        u32 mNumPoints;
        // Vec2f mPoints[mNumPoints];
    };

    struct Zone {
        char mName[0x20];
        char m_20[0x20];
        MapdataParams mParams;
        Vec2f mBoundsMin;
        Vec2f mBoundsMax;  
    };

    struct RaceCourseInfo {
        char mName[0x20];
        char m_20[0x20];
        MapdataParams mParams;
        Vec3f mPosition;
    };

    /* utility wrappers */

    class FileWrapper {
    public:
        FileWrapper();
        ~FileWrapper();


    private:

    };
}
}

#pragma pack(pop)
