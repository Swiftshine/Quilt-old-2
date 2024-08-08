#pragma once

#include "common.h"

class ColbinEditor {
public:
    // returns the colbin editor instance
    static ColbinEditor* Instance() {
        static ColbinEditor inst;
        return &inst;
    }

    // colbin editor loop
    void Run();

    // indicates if the editor should be processed
    static bool IsRunning;
private:
    ColbinEditor();
    ~ColbinEditor();

    bool isRunning();
};