#include "settings.h"

const char* Settings_GameRoot = "game_root";
const char* Settings_AutoSaveSettings = "save_settings_on_change";

Settings::Settings() {
    mSettingsLoaded = false;
    mGameRoot = "";
    mAutoSaveSettings = true;

    LoadFromDisk();
}

Settings::~Settings() { }

bool Settings::LoadFromDisk() {
    if (!fs::exists(Quilt::SettingsPath)) {
        return false;
    }

    json contents;

    std::ifstream in(Quilt::SettingsPath);
    in >> contents;
    in.close();

    mGameRoot = contents[Settings_GameRoot];
    mAutoSaveSettings = contents[Settings_AutoSaveSettings];

    mSettingsLoaded = true;

    return true;
}

void Settings::SaveToDisk() {
    json contents;

    contents[Settings_GameRoot] = mGameRoot;
    contents[Settings_AutoSaveSettings] = mAutoSaveSettings;

    std::ofstream out(Quilt::SettingsPath);
    out << contents.dump(4);
    out.close();
}
