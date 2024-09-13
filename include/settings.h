#pragma once

#include "common.h"

class Settings {
public:
    /** @return The settings instance. */
    static Settings* Instance() {
        static Settings inst;
        return &inst;
    }

    /** @return The game root path. */
    std::string GetGameRoot() {
        return mGameRoot;
    }

    /** @param gameRoot The game root path. */
    void SetGameRoot(std::string gameRoot) {
        if (fs::exists(gameRoot)) {
            mGameRoot = gameRoot;
        }
    }

    /** @note Loads "quilt-settings.json" from disk.
     *  @return Boolean indicating if the settings were loaded successfully.
     */
    bool LoadFromDisk();

    /** @note Saves "quilt-settings.json" to disk. */
    void SaveToDisk();

    /** @return Boolean indicating if the settings were loaded successfully. */
    bool IsLoaded() {
        return mSettingsLoaded;
    }
    
private:
    Settings();
    ~Settings();

private:
    bool mSettingsLoaded;
    std::string mGameRoot;
};
