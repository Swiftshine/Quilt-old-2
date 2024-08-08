#include "colbin_editor.h"

bool ColbinEditor::IsRunning = false;

void ColbinEditor::Run() {
    if (!IsRunning) {
        return;
    }
    ImGui::Begin("Colbin Editor", &IsRunning);
    // ...
    ImGui::End();
}

ColbinEditor::ColbinEditor() { }

ColbinEditor::~ColbinEditor() { }