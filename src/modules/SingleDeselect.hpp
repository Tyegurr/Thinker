#pragma once

#include "../Module.hpp"
#include <Geode/modify/EditorUI.hpp>

class $editorModule(SingleDeselect) {
	void onEditor() override;
    bool onToggled(bool state) override;
    bool onSettingChanged(std::string_view key, const matjson::Value& value) override;
	
	bool m_keyHeld;
};

class $modify(SDEditorUI, EditorUI) {
	$registerEditorHooks(SingleDeselect)

	void deselectSpecificObject();
	void selectObject(GameObject* p0, bool p1);
    void selectObjects(CCArray* p0, bool p1);
    void ccTouchEnded(CCTouch* p0, CCEvent* p1);
	bool getKeyPressed();
};

