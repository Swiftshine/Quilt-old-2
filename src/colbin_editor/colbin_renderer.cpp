#include "colbin_editor/colbin_renderer.h"

ColbinRenderer::ColbinRenderer()
    : mActive(false)
{ }

ColbinRenderer::~ColbinRenderer() { }

void ColbinRenderer::Render(const std::unique_ptr<key::colbin::wrapper::Colbin>& colbin) {
    if (!mActive) {
        return;
    }

    
}