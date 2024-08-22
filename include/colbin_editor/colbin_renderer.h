#pragma once
#include "key/colbin.h"
#include "selectable.h"
#include <memory>
class ColbinRenderer {
public:
    static ColbinRenderer* Instance() {
        static ColbinRenderer inst;
        return &inst;
    }

    void Render(const std::unique_ptr<key::colbin::wrapper::Colbin>&);
private:
    ColbinRenderer();
    ~ColbinRenderer();
private:
    bool mActive;
};