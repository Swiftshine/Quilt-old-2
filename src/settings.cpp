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
    
    if ('/' != mGameRoot[mGameRoot.length() - 1]) {
        mGameRoot += "/";
    }
    

    mLEDisplayLevelPath = contents[Settings_LE_DisplayLevelPath];

    mSettingsLoaded = true;
    return true;
}

void Settings::SaveToDisk() {
    // ordered_json is used to preserve the order of json fields --
    // they are written to disk in the order they are written in code.
    // this is useful for maintaining organisation if the user
    // ever wanted to edit a json (in this case, settings) manually

    ordered_json contents;

    if ('/' != mGameRoot[mGameRoot.length() - 1]) {
        mGameRoot += "/";
    }

    contents[Settings_AutoSaveSettings] = mAutoSaveSettings;
    contents[Settings_GameRoot] = mGameRoot;
    contents[Settings_LE_DisplayLevelPath] = mLEDisplayLevelPath;

    std::ofstream out(Quilt::SettingsPath);
    out << contents.dump(4);
    out.close();
}
