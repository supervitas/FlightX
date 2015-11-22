//
//  EnemyPlane.cpp
//  FlightX
//
//  Created by Виталий on 21.11.15.
//
//

#include "EnemyPlane.hpp"
USING_NS_CC;

static EnemyPlane* create(){
    EnemyPlane* pSprite = new DefaultPlane();
    
    if (pSprite->initWithFile("plane.png"))
    {
        pSprite->autorelease();
        
        pSprite->initOptions();
        
        pSprite->addEvents();
        
        return pSprite;
    }
    
    CC_SAFE_DELETE(pSprite);
    return NULL;

    
    
    
//   EnemyPlane *plane =  DefaultPlane::create();
//    plane->initialize();
    return plane;
    
}

void EnemyPlane::initOptions(){
    this->_isEnemy = true;
    this->_baseHP = kDefaultPlaneHP;
    this->_currentHP = _baseHP;
    this->_maximalSpeed = kDefaultPlaneMaxSpeed;
    this->_movementDirection = Vec2();
    this->setScale(0.15);
    this->setRotation(90);
    this->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
}


void EnemyPlane::touchEvent(cocos2d::Touch* touch)
{
    setRotation(getRotation() + 15);
    CCLOG("Health = %d", _currentHP);
    CCLOG("Rotation = %f", getRotation());
    
}