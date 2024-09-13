#include "settings.h"


Settings::Settings() {
    mSettingsLoaded = false;
    mGameRoot = "";

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

    mGameRoot = contents["Game Root"];

    mSettingsLoaded = true;

    return true;
}

void Settings::SaveToDisk() {
    json contents;

    contents["Game Root"] = mGameRoot;

    std::ofstream out(Quilt::SettingsPath);
    out << contents.dump(4);
    out.close();
}
