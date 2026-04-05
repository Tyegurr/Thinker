#pragma once

#include "../Module.hpp"

class $editorModule(AlternateLassoLocation) {
    void onEditor() override;
    void onLasso(CCObject* sender);

    Ref<CCMenuItemToggler> m_originalToggler;
};