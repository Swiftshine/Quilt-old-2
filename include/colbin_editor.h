#pragma once

#include "common.h"
#include "key/colbin.h"

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

    /* gui functions */
    void Menu();

    /* file io */
    void OpenFile();
    void SaveFile(bool saveAs = false);
    // loads file from mFileOpen
    void LoadFile();
    
    /* editor */
    
    // renders lines
    void FileProperties();
    void RenderFile();
private:
    std::string mColbinFilepath;
    bool mFileOpen;
    std::unique_ptr<key::colbin::wrapper::Colbin> mpColbinFile;
    Camera mCamera;
};