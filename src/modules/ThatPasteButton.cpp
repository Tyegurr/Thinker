#include "ThatPasteButton.hpp"
#include "../Utils.hpp"

bool ThatPasteButton::onToggled(bool state) {
    if (state) {
        onEditor();
    }
    return true;
}

bool ThatPasteButton::onSettingChanged(std::string_view key, const matjson::Value& value) {
    return true;
}

void ThatPasteButton::onEditor() {
    auto buttons = m_editorUI->getChildByID("editor-buttons-menu");
    if (!buttons) return;

    if (auto pasteStateButton = typeinfo_cast<CCMenuItemSpriteExtra*>(buttons->getChildByID("paste-state-button"))) {
        if (pasteStateButton->getUserObject("hijack"_spr)) return;

        tinker::utils::hijackButton(pasteStateButton, [this, pasteStateButton] (auto orig, auto sender) {
            if (!ThatPasteButton::isEnabled() || !getSetting<bool, "toggle-paste-state">()) return orig(sender);

            bool alwaysShow = getSetting<bool, "always-show">();
            bool hasMultiple = m_editorUI->m_selectedObjects && m_editorUI->m_selectedObjects->count() > 1;

            if (((alwaysShow && m_editorUI->m_selectedObject || hasMultiple) || (!alwaysShow && hasMultiple)) && pasteStateButton->getOpacity() == 255) {
                createQuickPopup("Paste State?", "Pasting state is <cr>dangerous</c>! Are you sure?", "Cancel", "Yes", [this, orig, sender] (FLAlertLayer*, bool yes) {
                    if (yes) orig(sender);
                });
            }
            else orig(sender);
        });
    }

    if (auto pasteColorButton = typeinfo_cast<CCMenuItemSpriteExtra*>(buttons->getChildByID("paste-color-button"))) {
        if (pasteColorButton->getUserObject("hijack"_spr)) return;

        tinker::utils::hijackButton(pasteColorButton, [this, pasteColorButton] (auto orig, auto sender) {
            if (!ThatPasteButton::isEnabled() || !getSetting<bool, "toggle-paste-color">()) return orig(sender);
            
            bool alwaysShow = getSetting<bool, "always-show">();
            bool hasMultiple = m_editorUI->m_selectedObjects && m_editorUI->m_selectedObjects->count() > 1;
            
            if (((alwaysShow && m_editorUI->m_selectedObject || hasMultiple) || (!alwaysShow && hasMultiple)) && pasteColorButton->getOpacity() == 255) {
                createQuickPopup("Paste Color?", "Pasting color is <cr>dangerous</c>! Are you sure?", "Cancel", "Yes", [this, orig, sender] (FLAlertLayer*, bool yes) {
                    if (yes) orig(sender);
                });
            } 
            else orig(sender);
        });
    }
}

void ThatPasteButton::onSetGroupIDLayer(SetGroupIDLayer* setGroupIDLayer, GameObject* obj, CCArray* objs) {
    auto actions = setGroupIDLayer->m_mainLayer->getChildByID("actions-menu");
    if (!actions) return;

    auto pasteButton = typeinfo_cast<CCMenuItemSpriteExtra*>(actions->getChildByID("paste-button"));
    if (!pasteButton) return;

    if (pasteButton->getUserObject("hijack"_spr)) return;

    tinker::utils::hijackButton(pasteButton, [this] (auto orig, auto sender) {
        if (!ThatPasteButton::isEnabled() || !getSetting<bool, "toggle-paste-state-group">()) return orig(sender);

        bool alwaysShow = getSetting<bool, "always-show">();
        bool hasMultiple = m_editorUI->m_selectedObjects && m_editorUI->m_selectedObjects->count() > 1;
                
        if (((alwaysShow && m_editorUI->m_selectedObject || hasMultiple) || (!alwaysShow && hasMultiple))) {
            createQuickPopup("Paste State?", "Pasting state is <cr>dangerous</c>! Are you sure?", "Cancel", "Yes", [this, orig, sender] (FLAlertLayer*, bool yes) {
                if (yes) orig(sender);
            });
        } 
        else orig(sender);
    });
}
