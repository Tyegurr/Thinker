#include "ObjectTooltips.hpp"
#include <alphalaneous.editortab_api/include/EditorTabAPI.hpp>
#include "TooltipHover.hpp"

using namespace tinker::ui;

void ObjectTooltips::onEditor() {
    auto hover = TooltipHover::create();
    m_editorUI->addChild(hover);
    m_editorUI->m_uiItems->addObject(hover);

    alpha::editor_tabs::addTabSwitchCallback([hover] (auto tab) {
        hover->resetTooltip();
    });

    alpha::editor_tabs::addModeSwitchCallback([hover] (auto mode) {
        hover->resetTooltip();
    });
}
