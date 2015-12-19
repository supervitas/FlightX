//
//  EnemyPlane.cpp
//  FlightX
//
//  Created by Виталий on 21.11.15.
//
//
#include "EnemyPlane.h"
#include "Behaviour.h"
#include "GameScene.h"
USING_NS_CC;
EnemyPlane::EnemyPlane(DefaultPlane* const player_plane){}
EnemyPlane::~EnemyPlane(){}

EnemyPlane*  EnemyPlane::create(DefaultPlane* const player_plane)
{
    EnemyPlane* pSprite = new EnemyPlane(player_plane);
    
    if (pSprite->initWithFile("enemyplane.png"))
    {
        pSprite->autorelease();
        
        pSprite->initOptions();
        
        pSprite->addEvents();
        
        pSprite->ChangeBehavoiur(player_plane);
        
        return pSprite;
    }
    CC_SAFE_DELETE(pSprite);
    return NULL;

}

void EnemyPlane::ChangeBehavoiur(DefaultPlane* const player_plane, int type)
{
    switch (type)
    {
        case 0:
            _behaviour = new SimplePlaneBehaviour(this, player_plane);
            break;
        
        case 1:
            _behaviour = new KamikazePlaneBehaviour(this, player_plane);
            break;
            
        default:
            break;
    }
}

void EnemyPlane::initOptions()
{
    auto plane_body = PhysicsBody::createBox(this->getContentSize(), PhysicsMaterial(0,0,0));
    plane_body->setCollisionBitmask(2);
    plane_body->setContactTestBitmask(true);
    plane_body->setDynamic(true);// Физика
    this->setTag(2);
    this->setPhysicsBody(plane_body);
    this->setScale(0.15);
    _isEnemy = true;
    _baseHP = 100;
    _currentHP = _baseHP;
    _maximalSpeed = 50.0f;
    _movementDirection = Vec2();
    this->setRotation(180);
//    this->setColor(Color3B(255,0,5));

}
void EnemyPlane::update(float delta)
{
	_behaviour->Behave(delta);
    applySpeed(delta);
    this->setRotation(180);
    if (!isStillOnScreen()) {
        
        unscheduleUpdateAndDelete();
    }
    
}
bool EnemyPlane::isStillOnScreen()
{
    auto boundings = getParent()->getBoundingBox();
    bool planeIsOnScreen = ( this->getPositionX()-17 < boundings.getMaxX() && this->getPositionX()-17 > boundings.getMinX() &&
    this->getPositionY()-17 < boundings.getMaxY() && this->getPositionY()-17  > boundings.getMinY());
    

    return planeIsOnScreen;
}


void EnemyPlane::randomMove(Vec2 coord)
{
    

}

void EnemyPlane::addEvents() {

    scheduleUpdate();
}

