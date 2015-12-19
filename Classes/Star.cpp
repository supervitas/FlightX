#include "Star.h"
#include "math.h"
#include <iostream>
USING_NS_CC;

namespace
{
	static float kMaximumBulletSpeed = 200.0f;
	static int kDefaultDamage = 10;
	float DegreesToRadians(float degrees)
	{
		return degrees * (M_PI / 180);
	}
};


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
		speed = 50.0f;
		scale = 0.7f;
		break;
	case kFarStar:
		initialization_succeded = star->initWithFile("star.png");
		speed = 150.0f;
		scale = 1.2f;
		break;
	case kNearStar:
		initialization_succeded = star->initWithFile("fast_star.png");
		speed = 150.0f;
		scale = 1.2f;
		break;
	default:
		break;
	}


	if (initialization_succeded)
	{
		star->autorelease();
		star->_max_speed = speed;
		star->setScale(scale);
		star->differColorAndSize();
		star->setPosition(Vec2());
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
	currentPosition += _currentSpeed * deltaTime;

	// There may be some more complex logic.
	setPosition(currentPosition);
}


void Star::update(float delta)
{
	applySpeed(delta);
	// If bullet is offscreen, destroy it.
	if (this->getPosition().y < -20)
		moveBackToRandomPlace();
	
}

void Star::differColorAndSize()
{
	float size_deviation = RandomHelper::random_real(-0.1f, 0.1f);
	float r_deviation = RandomHelper::random_real(-0.2f, 0.2f);
	float g_deviation = RandomHelper::random_real(-0.2f, 0.2f);
	float b_deviation = RandomHelper::random_real(-0.2f, 0.2f);
	float a_deviation = RandomHelper::random_real(-0.2f, 0.2f);

	this->setScale(this->getScale() + size_deviation);
	this->setColor(Color3B((int) ((0.8f + r_deviation) * 255), (int) ((0.8f + g_deviation) * 255), (int) ((0.8f + b_deviation) * 255)));
	this->setOpacity((int) ((0.8f + a_deviation) * 255));
}
void Star::moveBackToRandomPlace()
{
	float width = RandomHelper::random_real(0.f, Director::getInstance()->getVisibleSize().width);
	float height = RandomHelper::random_real(0.f, Director::getInstance()->getVisibleSize().height);

	this->setPosition(Vec2(width, height + 20));
}


