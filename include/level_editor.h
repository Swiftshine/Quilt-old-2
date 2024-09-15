#pragma once

#include "common.h"
#include "game/mapdata.h"

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
    void ProcessLevelContents();
private:
    bool mIsActive;
    bool mTryOpenByName;
    bool mLevelOpen;
    std::vector<std::pair<std::string, int>> mLevelList;
    SDL_Texture* mTexture;
    std::string mCurrentLevelPath;
    std::vector<Quilt::File> mCurrentLevelContents;
    
};