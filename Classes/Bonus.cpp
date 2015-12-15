//
//  Bonus.cpp
//  FlightX
//
//  Created by Виталий on 15.12.15.
//
//

#include "Bonus.hpp"
USING_NS_CC;

Bonus* Bonus::create()
{
    Bonus* pSprite = new Bonus();
    
    
    if (pSprite->initWithFile("firstaid.png"))
    {
        pSprite->autorelease();
        
        pSprite->initOptions();
        
        
        return pSprite;
    }
    
    CC_SAFE_DELETE(pSprite);
    return NULL;
}

void Bonus::initOptions()
{
    auto bonus_body = PhysicsBody::createBox(this->getContentSize(), PhysicsMaterial(0,0,0));
    bonus_body->setCollisionBitmask(4);
    bonus_body->setContactTestBitmask(true);
    bonus_body->setDynamic(true);// Физика
//    this->setTag(2);
    this->setPhysicsBody(bonus_body);
    this->setScale(0.5);
//    this->setRotation(180);
//    this->setColor(Color3B(255,0,5));
    this->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height / 2));
}