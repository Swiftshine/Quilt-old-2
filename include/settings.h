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

    bool& GetAutoSaveSettings() {
        return mAutoSaveSettings;
    }

    void SetAutoSaveSettings(bool autoSaveSettings) {
        mAutoSaveSettings = autoSaveSettings;
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

    std::string mGameRoot;
    bool mAutoSaveSettings;
};
