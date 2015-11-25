#include "Plane.h"
USING_NS_CC;

namespace
{
	const int kDefaultPlaneHP = 100;
	const bool kDefaultPlaneOwnerFlag = false;
	const float kDefaultPlaneMaxSpeed = 100.0f;
}

DefaultPlane::DefaultPlane() {}

DefaultPlane::~DefaultPlane() {}

DefaultPlane* DefaultPlane::create()
{
    DefaultPlane* pSprite = new DefaultPlane();
    

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

void DefaultPlane::initOptions() 
{
    auto plane_body = PhysicsBody::createBox(this->getContentSize(), PhysicsMaterial(0,1,0));
    plane_body->setCollisionBitmask(1);
    plane_body->setContactTestBitmask(true);
    plane_body->setDynamic(true);
    this->setPhysicsBody(plane_body);
    this->setScale(0.15);
    this->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height / 8));
	_isEnemy = kDefaultPlaneOwnerFlag;
	_baseHP = kDefaultPlaneHP;
	_currentHP = _baseHP;
	_maximalSpeed = kDefaultPlaneMaxSpeed;
	_movementDirection = Vec2();
}

void DefaultPlane::ApplyDamage(const int damage)
{
	_currentHP -= damage;
	//Play animation.
	if (_currentHP <= 0)
		unscheduleUpdateAndDelete();
}

bool DefaultPlane::IsEnemy() const
{
	return _isEnemy;
}

void DefaultPlane::unscheduleUpdateAndDelete()
{
	// Obviously, we don't want all update() functions called after object was destroyed.
	this->unscheduleUpdate();
	removeFromParentAndCleanup(true);
}

Vec2 DefaultPlane::GetCurrentSpeed()
{
	return _movementDirection * _maximalSpeed;
}

void DefaultPlane::applySpeed(float deltaTime)
{
	auto currentPosition = getPosition();
	currentPosition += GetCurrentSpeed() * deltaTime;

	// There may be some more complex logic.
	auto screen = this->getParent()->getBoundingBox();
	if (screen.containsPoint(currentPosition))
		setPosition(currentPosition);
}

bool DefaultPlane::MovePlane(const Vec2 direction)
{
	_movementDirection += direction;
	return true;
}

void DefaultPlane::update(float delta)
{
	applySpeed(delta);
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
    
    listener->onTouchEnded = [=](cocos2d::Touch* touch, cocos2d::Event* event){
        touchEvent(touch);
    };
    
    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 30);

	scheduleUpdate();
}

void DefaultPlane::touchEvent(cocos2d::Touch* touch)
{
	setRotation(getRotation() + 15);
    CCLOG("Health = %d", _currentHP);
    CCLOG("Enemy = %d",_isEnemy);
	CCLOG("Rotation = %f", getRotation());

}