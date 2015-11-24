#include "Bullet.h"
#include "math.h"
#include <iostream>
USING_NS_CC;

namespace
{
	static float kMaximumBulletSpeed = 200.0f;
	float DegreesToRadians(float degrees)
	{
		return degrees * (M_PI / 180);
	}
};

Bullet::Bullet() 
{
	//CCLOG("Bullet created!");
}

Bullet::~Bullet() 
{
	//CCLOG("Bullet destroyed!");
}

Bullet*  Bullet::create(const DefaultPlane *plane)
{
	Bullet* bullet = new Bullet();
    
	if (bullet->initWithFile("bullet.png"))
    {
		bullet->autorelease();
		bullet->initOptions(plane);
		bullet->addEvents();
        
		// Should be called after all work is done.
		return bullet;
    }
    
	CC_SAFE_DELETE(bullet);
    return NULL;

}

float Bullet::GetRotation() const
{
	return _currentSpeed.getAngle();
}

void Bullet::unscheduleUpdateAndDelete()
{
	// Obviously, we don't want all update() functions called after object was destroyed.
	this->unscheduleUpdate();
	removeFromParentAndCleanup(true);
}

void Bullet::applySpeed(float deltaTime)
{
	auto currentPosition = getPosition();
	currentPosition += _currentSpeed * deltaTime;

	// There may be some more complex logic.
	setPosition(currentPosition);
}

bool Bullet::isStillOnScreen()
{
    
	auto boundings = getParent()->getBoundingBox();
	auto bulletWillLeaveScreenOnNextFrame = boundings.intersectsCircle(getPosition(), 0);
    
    // There may be some more complex logic.
	return bulletWillLeaveScreenOnNextFrame;
}

void Bullet::update(float delta)
{
	applySpeed(delta);
	// If bullet is offscreen, destroy it.
	if (!isStillOnScreen())
		// There should not be any modifications to bullet beyond this point, otherwise you will probably try read 0xFEEEFF46.
		// So, first update all the parameters, then check if bullets needs to be deleted. 
		unscheduleUpdateAndDelete();
	
}

// Probably we should pass SimplePlane instance here to get all the values: plane type, isEnemy bool and initial rotation...
void Bullet::initOptions(const DefaultPlane *plane)
{
    auto bullet_body = PhysicsBody::createBox(this->getContentSize(), PhysicsMaterial(0,1,0));
    bullet_body->setCollisionBitmask(3);
    bullet_body->setContactTestBitmask(true);
    this->setPhysicsBody(bullet_body);
    this->setScale(0.2f);
    
	setPosition(plane->getPosition());

	_max_speed = kMaximumBulletSpeed;	// Should depend on bullet type.

	_isEnemyBullet = plane->IsEnemy();
	_isEnemyBullet ? this->setColor(Color3B(255, 0, 0)) : this->setColor(Color3B(0, 255, 0));
	

    
	// I hate Maths.
	_currentSpeed = Vec2(-1.0f, 0.0f).rotateByAngle(Vec2(), -DegreesToRadians(plane->getRotation() + 90)).getNormalized() * kMaximumBulletSpeed;
}

// Some undescribable horror.
void Bullet::addEvents() 
{
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

void Bullet::touchEvent(cocos2d::Touch* touch)
{
    //CCLOG("Sprite touched");
    CCLOG("%s", this->_isEnemyBullet? "Enemy bullet!" : "Keep calm, it's my bullet.");

}