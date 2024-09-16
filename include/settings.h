#pragma once

#include "common.h"

class Settings {
public:
    static Settings* Instance() {
        static Settings inst;
        return &inst;
    }

    std::string& GetGameRoot() {
        return mGameRoot;
    }

    void SetGameRoot(std::string gameRoot) {
        if (!fs::is_directory(gameRoot)) {
            return;
        }

        mGameRoot = gameRoot;
        
        if (mAutoSaveSettings) {
            SaveToDisk();
        }
    }

    bool GetAutoSaveSettings() {
        return mAutoSaveSettings;
    }

    void SetAutoSaveSettings(bool autoSaveSettings) {
        mAutoSaveSettings = autoSaveSettings;
    }

    bool GetLEDisplayLevelPath() {
        return mLEDisplayLevelPath;
    }

    void SetLEDisplayLevelPath(bool displayLevelPath) {
        mLEDisplayLevelPath = displayLevelPath;

        if (mAutoSaveSettings) {
            SaveToDisk();
        }
    }


    bool LoadFromDisk();
    void SaveToDisk();

    bool IsLoaded() {
        return mSettingsLoaded;
    }
    
private:
    Settings();
    ~Settings();

private:
    bool mSettingsLoaded;

    // Quilt settings

    bool mAutoSaveSettings;
    std::string mGameRoot;
    
    // Level editor settings
    bool mLEDisplayLevelPath;
};
