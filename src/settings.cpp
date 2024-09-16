#include "settings.h"

const char* Settings_GameRoot = "game_root";
const char* Settings_AutoSaveSettings = "save_settings_on_change";
const char* Settings_LE_DisplayLevelPath = "le_display_level_path";

Settings::Settings() {
    mSettingsLoaded = false;
    mGameRoot = "";
    mAutoSaveSettings = true;
    mLEDisplayLevelPath = false;

    LoadFromDisk();
}

Settings::~Settings() { }

bool Settings::LoadFromDisk() {
    if (!fs::exists(Quilt::SettingsPath)) {
        return false;
    }

    ordered_json contents;

    std::ifstream in(Quilt::SettingsPath);
    in >> contents;
    in.close();

    mAutoSaveSettings = contents[Settings_AutoSaveSettings];
    
    mGameRoot = contents[Settings_GameRoot];
    if (mGameRoot[mGameRoot.length() - 1] != '/') {
        mGameRoot += "/";
    }
    

    mLEDisplayLevelPath = contents[Settings_LE_DisplayLevelPath];

    mSettingsLoaded = true;
    return true;
}

void Settings::SaveToDisk() {
    ordered_json contents;

    contents[Settings_AutoSaveSettings] = mAutoSaveSettings;
    contents[Settings_GameRoot] = mGameRoot;
    contents[Settings_LE_DisplayLevelPath] = mLEDisplayLevelPath;

    std::ofstream out(Quilt::SettingsPath);
    out << contents.dump(4);
    out.close();
}
