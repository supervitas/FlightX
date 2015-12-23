#ifndef __STAR_H__
#define __STAR_H__

#include "Plane.h"
#include "cocos2d.h"
USING_NS_CC;

enum StarType
{
    kFarFarStar, kFarStar, kNearStar
};

class Star : public cocos2d::Sprite
{
public:

    static Star* create(StarType type = kFarFarStar);
	void update(float delta) override;

private:
	Star();
	~Star();

	void differColorAndSize();
	void applySpeed(float deltaTime);
	void moveBackToRandomPlace();

private:
	float _max_speed;
	Vec2 _currentSpeed;
    
};

#endif