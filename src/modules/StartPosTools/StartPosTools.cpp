#include "StartPosTools.hpp"
#include "StartPosOverlay.hpp"

using namespace tinker::ui;

void StartPosTools::onEditor() {
    m_overlay = StartPosOverlay::create();
	m_overlay->setID("start-pos-controls"_spr);
	m_editorLayer->m_objectLayer->addChild(m_overlay);
}

void StartPosTools::updateOverlay() {
    if (!m_editorUI->m_selectedObject || (m_editorUI->m_selectedObjects && m_editorUI->m_selectedObjects->count() > 1)) {
        m_overlay->setStartPos(nullptr);
        return;
    }
    if (auto startPos = typeinfo_cast<StartPosObject*>(m_editorUI->m_selectedObject)) {
        m_overlay->setStartPos(startPos);
    }
}

void SPTEditorUI::deselectAll() {
	EditorUI::deselectAll();
	StartPosTools::get()->updateOverlay();
};

void SPTEditorUI::deselectObject(GameObject* object) {
	EditorUI::deselectObject(object);
	StartPosTools::get()->updateOverlay();
}

void SPTEditorUI::selectObject(GameObject* object, bool ignoreFilter) {
	EditorUI::selectObject(object, ignoreFilter);
	StartPosTools::get()->updateOverlay();
}

void SPTEditorUI::selectObjects(CCArray* objects, bool ignoreFilter) {
	EditorUI::selectObjects(objects, ignoreFilter);
	StartPosTools::get()->updateOverlay();
}

bool SPTEditorUI::shouldDeleteObject(GameObject* object) {
    auto ret = EditorUI::shouldDeleteObject(object);
    if (ret) {
        StartPosTools::get()->m_overlay->checkDeletedObject(object);
    }
    return ret;
}

void SPTGJBaseGameLayer::orderSpawnObjects() {
    auto startPos = StartPosTools::get()->m_overlay->getLastStartPos();
    if (startPos) {
        LevelEditorLayer::get()->setStartPosObject(startPos);
    }
    GJBaseGameLayer::orderSpawnObjects();
}
