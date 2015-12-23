#include "Plane.h"
#include "Bullet.h"
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
    

    if (pSprite->initWithFile("playerjet.png"))
    {
        
        pSprite->initOptions();
        
        pSprite->addEvents();
        
        return pSprite;
    }
    
    CC_SAFE_DELETE(pSprite);
    return NULL;
}
void DefaultPlane::setMaximumSpeed(float speed){
    _maximalSpeed = speed;
}

int DefaultPlane::GetCurrentHP()
{
	return _currentHP;
}

void DefaultPlane::initOptions() 
{
    auto plane_body = PhysicsBody::createBox(this->getContentSize(), PhysicsMaterial(0,0,0));
    plane_body->setCollisionBitmask(1);
    plane_body->setContactTestBitmask(true);
    plane_body->setDynamic(true);
    this->setPhysicsBody(plane_body);
    this->setScale(0.75);
    this->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height / 8));
	_isEnemy = kDefaultPlaneOwnerFlag;
	_baseHP = kDefaultPlaneHP;
	_currentHP = _baseHP;
	_maximalSpeed = kDefaultPlaneMaxSpeed;
	_movementDirection = Vec2();
}

void DefaultPlane::makeBoom()
{
    auto emitter = ParticleFire::create();
    emitter->setEmitterMode(ParticleSystem::Mode::RADIUS);
    emitter->setDuration(0.3);
    emitter->setStartRadius(0.2);
    emitter->setPosition(this->getPosition());
    emitter->setEndRadius(10);
    this->getParent()-> addChild(emitter, 1);
}

void DefaultPlane::ApplyDamage(const int damage)
{
    if (this != NULL)
    {
	_currentHP -= damage;
        
    if (_currentHP <= 0)
        {
            makeBoom();
            unscheduleUpdateAndDelete();
        }
    }
}

bool DefaultPlane::IsEnemy() const
{
	return _isEnemy;
}

void DefaultPlane::unscheduleUpdateAndDelete()
{

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

	auto screen = this->getParent()->getBoundingBox();
	if (screen.containsPoint(currentPosition))
		setPosition(currentPosition);
}

bool DefaultPlane::MovePlane(const Vec2 direction)
{
	_movementDirection += direction;
	return true;
}

bool DefaultPlane::StopPlane()
{
	_movementDirection = Vec2();
	return true;
}

void DefaultPlane::update(float delta)
{
	applySpeed(delta);
    this->setRotation(0);
}


void DefaultPlane::Shoot()
{
	Bullet *bullet = Bullet::create(this);
	this->getParent()->addChild(bullet);
}

void DefaultPlane::addEvents() {

	scheduleUpdate();
}

void DefaultPlane::touchEvent(cocos2d::Touch* touch)
{

    CCLOG("Health = %d", _currentHP);
    CCLOG("Enemy = %d",_isEnemy);

}