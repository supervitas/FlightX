#ifndef __BEHAVIOR_H__
#define __BEHAVIOR_H__

#include "cocos2d.h"
#include "Plane.h"

USING_NS_CC;

namespace DefaultValues
{
	const float kDefaultShootCooldown = 1.0f; // 1 second
}

// TODO: fix a typo.
class AbstractPlaneBehavoiur
{
public: 
	AbstractPlaneBehavoiur(DefaultPlane* owner, DefaultPlane* player_plane);
	~AbstractPlaneBehavoiur();

	virtual void Behave(float deltaT) = 0;

	DefaultPlane* GetOwner();
	DefaultPlane* GetPlayerPlane();

protected:
	DefaultPlane* _owner;
	DefaultPlane* _player_plane;

protected:
	Vec2 directionToPlayer();
	float distanceToPlayer();
	Vec2 vectorToPlayer();
	// In degrees from axis OX.
	float angleToPlayer();
};


class SimplePlaneBehaviour : public AbstractPlaneBehavoiur 
{
public:
	SimplePlaneBehaviour(DefaultPlane* owner, DefaultPlane* player_plane);
	void Behave(float deltaT) override;

protected:
	float _time_since_last_shot;
};

#endif