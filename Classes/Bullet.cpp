#include "Bullet.h"
USING_NS_CC;

namespace
{
	static float kMaximumBulletSpeed = 200.0f;
};

Bullet::Bullet() 
{
	//CCLOG("Bullet created!");
}

Bullet::~Bullet() 
{
	//CCLOG("Bullet destroyed!");
}

Bullet*  Bullet::create(Vec2 position,  bool isEnemyBullet,  unsigned int *bulletType)
{
	Bullet* bullet = new Bullet();
    
	if (bullet->initWithFile("bullet.png"))	// Ha-ha! Plane shoot bullets that looks like planes!
    {
		bullet->autorelease();
		bullet->initOptions(position, isEnemyBullet, bulletType);
		bullet->addEvents();
        
		// Should be called after all work is done.
		bullet->scheduleUpdate();
		return bullet;
    }
    
	CC_SAFE_DELETE(bullet);
    return NULL;

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
	auto bulletWillLeaveScreenOnNextFrame = boundings.intersectsCircle(getPosition(), kMaximumBulletSpeed);
	
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
	
	//CCLOG("Bullet updated!");
}

// Probably we should pass SimplePlane instance here to get all the values: plane type, isEnemy bool and initial rotation...
void Bullet::initOptions( Vec2 position,  bool isEnemyBullet, unsigned int *bulletType)
{
	// What about an offset?
	setPosition(position);

	_max_speed = kMaximumBulletSpeed;	// Should depend on bullet type.

	_isEnemyBullet = isEnemyBullet;
	_isEnemyBullet ? this->setColor(ccc3(255, 0, 0)) : this->setColor(ccc3(0, 255, 0));
	setScale(0.2f);

	_currentSpeed = Vec2(0.0f, 1.0f).getNormalized() * kMaximumBulletSpeed;	// Think how to get Plane's position and set initial rotation.
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

}

void Bullet::touchEvent(cocos2d::Touch* touch)
{
    //CCLOG("Sprite touched");
    CCLOG("%s", this->_isEnemyBullet? "Enemy bullet!" : "Keep calm, it's my bullet.");

}