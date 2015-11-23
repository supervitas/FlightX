//
//  EnemyPlane.cpp
//  FlightX
//
//  Created by Виталий on 21.11.15.
//
//

#include "EnemyPlane.h"
USING_NS_CC;
EnemyPlane::EnemyPlane(){
    
}
EnemyPlane::~EnemyPlane(){
    
}

EnemyPlane*  EnemyPlane::create(){
    EnemyPlane* pSprite = new EnemyPlane();
    
    if (pSprite->initWithFile("plane.png"))
    {
        pSprite->autorelease();
        
        pSprite->initOptions();
        
        pSprite->addEvents();
        
        return pSprite;
    }
    
    CC_SAFE_DELETE(pSprite);
    return NULL;

}


void EnemyPlane::initOptions(){
    this->_isEnemy = true;
    this->_baseHP = 100;
    this->_currentHP = _baseHP;
    this->_maximalSpeed = 100.0f;
    this->_movementDirection = Vec2();
    this->setScale(0.15);
    this->setRotation(180);
    this->setColor(Color3B(255,0,5));
    this->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height / 1.2));
}

void EnemyPlane::addEvents() {
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
    
    scheduleUpdate();
}


//void EnemyPlane::touchEvent(cocos2d::Touch* touch)
//{
//    setRotation(getRotation() + 15);
//    CCLOG("Health = %d", _currentHP);
//    CCLOG("Rotation = %f", getRotation());
//    
//}