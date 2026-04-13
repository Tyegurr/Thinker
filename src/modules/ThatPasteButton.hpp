#pragma once

#include "../Module.hpp"

class $editorModule(ThatPasteButton) {
    bool onToggled(bool state) override;
    bool onSettingChanged(std::string_view key, const matjson::Value& value) override;

    void onEditor() override;
    void onSetGroupIDLayer(SetGroupIDLayer* setGroupIDLayer, GameObject* obj, CCArray* objs) override;
};