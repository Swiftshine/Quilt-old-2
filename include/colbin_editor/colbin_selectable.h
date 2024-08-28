#pragma once
#include "selectable.h"

class ColbinEntrySelectable : public Selectable {
public:
    ColbinEntrySelectable(Camera* camera, Vec2f p1, Vec2f p2, key::colbin::wrapper::Entry& entry);
    virtual ~ColbinEntrySelectable();

    inline key::colbin::wrapper::Entry& Entry() { return mEntry; }

    // overridden to take camera position into account
    virtual void HandleDrag() final override;
private:
    key::colbin::wrapper::Entry mEntry;
    Camera* mCamera;
};