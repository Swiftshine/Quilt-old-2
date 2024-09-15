#pragma once

#include "common.h"
#include "game/mapdata.h"

// the same thing can be done with std::pair,
// but this is easier to read
struct EnbinMapbinIndices {
    int mEnbinIndex;
    int mMapbinIndex;
};

class LevelEditor {
public:
    static LevelEditor* Instance() {
        static LevelEditor inst;
        return &inst;
    }

    bool IsActive() {
        return mIsActive;
    }

    void SetActive(bool active) {
        mIsActive = active;
    }

    void Run();
    void Render();
private:
    LevelEditor();
    ~LevelEditor();

    void Menu();
    void OpenByName();
    void OpenByArchive();
    void ProcessLevelContents();
    void ShowFiles();
private:
    bool mIsActive;
    bool mTryOpenByName;
    bool mLevelOpen;
    std::vector<std::pair<std::string, int>> mLevelList;
    SDL_Texture* mTexture;
    std::string mCurrentLevelPath;
    std::vector<Quilt::File> mCurrentLevelContents;
    EnbinMapbinIndices mCurrentFileIndex;
};
