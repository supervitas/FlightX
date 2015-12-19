#include "Star.h"
#include "math.h"
#include <iostream>
USING_NS_CC;



Star::Star()
{

}

Star::~Star()
{

}


Star* Star::create(StarType type)
{
	Star* star = new Star();
	bool initialization_succeded = false;
	float speed = 0.f;
	float scale = 1.0f;
	
	switch (type)
	{
	case kFarFarStar:
		initialization_succeded = star->initWithFile("star.png");
		speed = 25.0f;
		scale = 0.05f;
		break;
	case kFarStar:
		initialization_succeded = star->initWithFile("star.png");
		speed = 40.0f;
		scale = 0.1f;
		break;
	case kNearStar:
		initialization_succeded = star->initWithFile("fast_star.png");
		speed = 150.0f;
		scale = 0.2f;
		break;
	default:
		break;
	}


	if (initialization_succeded)
	{
		star->autorelease();
		star->_max_speed = speed;
        star->_currentSpeed = Vec2(0, -1);
		star->setScale(scale);
		star->differColorAndSize();
		
        float width = RandomHelper::random_real(0.f, Director::getInstance()->getVisibleSize().width);
        float height = RandomHelper::random_real(0.f, Director::getInstance()->getVisibleSize().height);
        star->setPosition(Vec2(width, height));
        
		star->scheduleUpdate();
		// Should be called after all work is done.
		return star;
    }
    
	CC_SAFE_DELETE(star);
    return NULL;

}

void Star::applySpeed(float deltaTime)
{
	auto currentPosition = getPosition();
	currentPosition += _currentSpeed * _max_speed * deltaTime;

	// There may be some more complex logic.
	setPosition(currentPosition);
}


void Star::update(float delta)
{
	applySpeed(delta);
	// If bullet is offscreen, destroy it.
	if (this->getPosition().y < 0)
		moveBackToRandomPlace();
	
}

void Star::differColorAndSize()
{
	float size_deviation = RandomHelper::random_real(0.9f, 1.1f);
	float r_deviation = RandomHelper::random_real(-0.05f, 0.05f);
	float g_deviation = RandomHelper::random_real(-0.05f, 0.05f);
	float b_deviation = RandomHelper::random_real(-0.05f, 0.05f);
	float a_deviation = RandomHelper::random_real(-0.05f, 0.05f);

	this->setScale(this->getScale() * size_deviation);
	this->setColor(Color3B((int) ((0.95f + r_deviation) * 255), (int) ((0.95f + g_deviation) * 255), (int) ((0.95f + b_deviation) * 255)));
	this->setOpacity((int) ((0.95f + a_deviation) * 255));
}
void Star::moveBackToRandomPlace()
{
	float width = RandomHelper::random_real(0.f, Director::getInstance()->getVisibleSize().width);
	float height = Director::getInstance()->getVisibleSize().height;

	this->setPosition(Vec2(width, height));
}


