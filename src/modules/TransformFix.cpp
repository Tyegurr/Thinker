#include "TransformFix.hpp"

bool TransformFix::onToggled(bool state) {
    return true;
}

CCMenu* TFGJTransformControl::getMenu() {
    auto fields = m_fields.self();

    if (fields->m_menu) return fields->m_menu;
    auto node = m_mainNode->getChildByType<CCNode>(0);
    auto menu = node->getChildByType<CCMenu>(0);

    fields->m_menu = menu;
    return menu;
}

bool TFGJTransformControl::ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event) {
    if (GJTransformControl::ccTouchBegan(touch, event)) return true;
    auto fields = m_fields.self();
    auto ret = getMenu()->ccTouchBegan(touch, event);
    fields->m_touchInMenu = ret;
    return ret;
}

void TFGJTransformControl::ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event) {
    GJTransformControl::ccTouchMoved(touch, event);
    auto fields = m_fields.self();
    if (fields->m_touchInMenu) {
        getMenu()->ccTouchMoved(touch, event);
    }
}

void TFGJTransformControl::ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event) {
    GJTransformControl::ccTouchEnded(touch, event);
    auto fields = m_fields.self();
    if (fields->m_touchInMenu) {
        getMenu()->ccTouchEnded(touch, event);
    }
    fields->m_touchInMenu = false;

}

void TFGJTransformControl::ccTouchCancelled(cocos2d::CCTouch* touch, cocos2d::CCEvent* event) {
    GJTransformControl::ccTouchCancelled(touch, event);
    auto fields = m_fields.self();
    if (fields->m_touchInMenu) {
        getMenu()->ccTouchCancelled(touch, event);
    }
    fields->m_touchInMenu = false;
}

void TFGJTransformControl::scaleButtons(float scale) {
    GJTransformControl::scaleButtons(scale);
    if (tinker::utils::getMod<"razoom.improved_transform_controls">()) return;
    auto spr = m_warpLockButton->getChildByIndex(0);
    m_warpLockButton->setContentSize(spr->getScaledContentSize());
    spr->setPosition(m_warpLockButton->getContentSize()/2);
}

CCMenu* TFGJScaleControl::getMenu() {
    auto fields = m_fields.self();

    if (fields->m_menu) return fields->m_menu;
    auto menu = getChildByType<CCMenu>(0);

    fields->m_menu = menu;
    return menu;
}

bool TFGJScaleControl::ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event) {
    if (GJScaleControl::ccTouchBegan(touch, event)) return true;
    auto fields = m_fields.self();
    auto ret = getMenu()->ccTouchBegan(touch, event);
    fields->m_touchInMenu = ret;
    return ret;
}

void TFGJScaleControl::ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event) {
    GJScaleControl::ccTouchMoved(touch, event);
    auto fields = m_fields.self();
    if (fields->m_touchInMenu) {
        getMenu()->ccTouchMoved(touch, event);
    }
}

void TFGJScaleControl::ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event) {
    GJScaleControl::ccTouchEnded(touch, event);
    auto fields = m_fields.self();
    if (fields->m_touchInMenu) {
        getMenu()->ccTouchEnded(touch, event);
    }
    fields->m_touchInMenu = false;

}

void TFGJScaleControl::ccTouchCancelled(cocos2d::CCTouch* touch, cocos2d::CCEvent* event) {
    GJScaleControl::ccTouchCancelled(touch, event);
    auto fields = m_fields.self();
    if (fields->m_touchInMenu) {
        getMenu()->ccTouchCancelled(touch, event);
    }
    fields->m_touchInMenu = false;
}