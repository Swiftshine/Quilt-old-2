#include "game/mapdata.h"

void Mapdata::Mapbin::FileWrapper::Read(const std::vector<char>& data) {
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

        if (0 < numColbinTypes && 0 != colbinTypeOffset) {
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

        if (0 < numColbinTypes && 0 != colbinTypeOffset) {
            string32 name { 0 };
            offs = colbinTypeOffset + 4 + (sizeof(string32) * i);
            Quilt::GetFromVector(data, offs, name);
            wrapper.SetCollisionType(name);
        }
        
        if (0 < numLabeledWallLabels && 0 != labeledWallLabelOffset) {
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

        string32 bytes;
        offs = commonGimmickNameOffset + 4 + (sizeof(string32) * i);
        Quilt::GetFromVector(data, offs, bytes);
        wrapper.SetBytes(bytes);
        mCommonGimmicks.push_back(wrapper);
    }

    for (auto i = 0; i < numGimmicks; i++) {
        Gimmick gmk;
        GimmickWrapper wrapper;

        Quilt::GetFromVector(data, gimmickOffset, gmk);
        Vec3f v = gmk.mPosition;
        v.x = SwapF32(v.x);
        v.y = SwapF32(v.y);
        v.z = SwapF32(v.z);
        wrapper.SetUnk30(gmk.m_30);
        wrapper.SetName(gmk.mName);
        wrapper.SetPosition(v);
        MapdataParamsWrapper& params = wrapper.GetParams();
        
        for (auto j = 0; j < 3; j++) {
            params.SetIntParam(j, Swap32(gmk.mParams.mIntParams[j]));
            params.SetFloatParam(j, SwapF32(gmk.mParams.mFloatParams[j]));
            params.SetStringParam(j, gmk.mParams.mStringParams[j]);
        }

        mGimmicks.push_back(wrapper);
    }
    
    for (auto i = 0; i < numPaths; i++) {
        Path path;
        PathWrapper wrapper;
        Quilt::GetFromVector(data, pathOffset, path);
        wrapper.SetName(CharArrayToString(path.mName, sizeof(string32)));
        wrapper.SetType(CharArrayToString(path.mType, sizeof(string32)));

        MapdataParamsWrapper& params = wrapper.GetParams();

        for (auto j = 0; j < 3; j++) {
            params.SetIntParam(j, Swap32(path.mParams.mIntParams[j]));
            params.SetFloatParam(j, SwapF32(path.mParams.mFloatParams[j]));
            params.SetStringParam(j, CharArrayToString(path.mParams.mStringParams[j], sizeof(string64)));
        }

        u32 num = Swap32(path.mNumPoints);
        for (auto i = 0; i < num; i++) {
            Vec2f v;
            Quilt::ByteSwapFromVector(data, pathOffset, v.x);
            Quilt::ByteSwapFromVector(data, pathOffset, v.y);
            wrapper.AddPoint(v);
        }

        mPaths.push_back(wrapper);
    }

    for (auto i = 0; i < numZones; i++) {
        Zone zone;
        ZoneWrapper wrapper;
        Quilt::GetFromVector(data, zoneOffset, zone);

        wrapper.SetName(CharArrayToString(zone.mName, sizeof(string32)));
        wrapper.SetUnk20(CharArrayToString(zone.m_20, sizeof(string32)));
        
        MapdataParamsWrapper& params = wrapper.GetParams();

        for (auto j = 0; j < 3; j++) {
            params.SetIntParam(j, Swap32(zone.mParams.mIntParams[j]));
            params.SetFloatParam(j, SwapF32(zone.mParams.mFloatParams[j]));
            params.SetStringParam(j, CharArrayToString(zone.mParams.mStringParams[j], sizeof(string64)));
        }

        wrapper.SetBoundsMin( {SwapF32(zone.mBoundsMin.x), SwapF32(zone.mBoundsMin.y)} );
        wrapper.SetBoundsMax( {SwapF32(zone.mBoundsMax.x), SwapF32(zone.mBoundsMax.y)} );
    }

    for (auto i = 0; i < numCourseInfo; i++) {
        RaceCourseInfo info;
        RaceCourseInfoWrapper wrapper;
        Quilt::GetFromVector(data, courseInfoOffset, info);

        wrapper.SetName(CharArrayToString(info.mName, sizeof(string32)));
        wrapper.SetUnk20(CharArrayToString(info.m_20, sizeof(string32)));

        MapdataParamsWrapper& params = wrapper.GetParams();

        for (auto j = 0; j < 3; j++) {
            params.SetIntParam(j, Swap32(info.mParams.mIntParams[j]));
            params.SetFloatParam(j, SwapF32(info.mParams.mFloatParams[j]));
            params.SetStringParam(j, CharArrayToString(info.mParams.mStringParams[j], sizeof(string64)));
        }

        wrapper.SetPosition( {SwapF32(info.mPosition.x), SwapF32(info.mPosition.y), SwapF32(info.mPosition.z)} );
    }

    
}
