#include "Plane.h"
using namespace cocos2d;

DefaultPlane::DefaultPlane() {
    plane_hp = 100;
}

DefaultPlane::~DefaultPlane() {}

DefaultPlane* DefaultPlane::create()
{
    DefaultPlane* pSprite = new DefaultPlane();
    
    if (pSprite->initWithFile("DefaultPlane.png"))
    {
        pSprite->autorelease();
        
        pSprite->initOptions();
        
        pSprite->addEvents();
        
        return pSprite;
    }
    
    CC_SAFE_DELETE(pSprite);
    return NULL;
}

void DefaultPlane::initOptions() {
//     do things here like setTag(), setPosition(), any custom logic.
}

void DefaultPlane::addEvents() {
    auto listener = cocos2d::EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = [&](cocos2d::Touch* touch, cocos2d::Event* event) {
        cocos2d::Vec2 p = touch->getLocation();
        cocos2d::Rect rect = this->getBoundingBox();
        
        if(rect.containsPoint(p)) {
            return true; // to indicate that we have consumed it.
        }
        
        return false; // we did not consume this event, pass thru.
    };
    
    listener->onTouchEnded = [=](cocos2d::Touch* touch, cocos2d::Event* event) {
        touchEvent(touch);
    };
    
    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 30);
}

void DefaultPlane::touchEvent(cocos2d::Touch* touch)
{
    CCLOG("Sprite touched");
    CCLOG("Health = %d", this->plane_hp);
}