#pragma once

#include "common.h"
#include "game/mapdata.h"
#include "camera.h"

#include "level_editor/le_selectable.h"

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
    void UpdateCamera(SDL_Event& event);
private:
    LevelEditor();
    ~LevelEditor();

    void Menu();
    void OpenByName();
    void OpenByArchive();
    void UpdateLevel();
    void ProcessLevelContents();
    void ShowFiles();
    void DisplayEntityOptions();
    
    bool FileIndicesValid() {
        if (-1 == mCurrentFileIndex.mEnbinIndex || -1 == mCurrentFileIndex.mMapbinIndex) {
            return false;
        }

        if (mCurrentLevelContents.size() <= mCurrentFileIndex.mMapbinIndex) {
            return false;
        }

        return true;
    }

    void SetFileIndices(int a, int b) {
        mCurrentFileIndex.mEnbinIndex = a;
        mCurrentFileIndex.mMapbinIndex = b;
    }

    void InvalidateFileIndices() {
        SetFileIndices(-1, -1);
    }

    void ClearSelectables() {
        mSelectedGimmickSelectables.clear();
        mGimmickSelectables.clear();
    }


private:
    bool mIsActive;
    bool mTryOpenByName;
    bool mLevelOpen;
    std::vector<std::pair<std::string, int>> mLevelList;
    SDL_Texture* mTexture;
    std::string mCurrentLevelPath;
    std::vector<Quilt::File> mCurrentLevelContents;
    EnbinMapbinIndices mCurrentFileIndex;
    Mapdata::Mapbin::FileWrapper mCurrentMapbin;
    Camera mCamera;
    bool mWindowFocused;
    bool mWindowHovered;
    std::vector<LE_Selectable> mGimmickSelectables;
    std::vector<int> mSelectedGimmickSelectables;
};
