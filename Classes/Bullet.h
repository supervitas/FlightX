#ifndef __BULLET_H__
#define __BULLET_H__

#include "Plane.h"
#include "cocos2d.h"
USING_NS_CC;

class Bullet : public cocos2d::Sprite
{
public:

    static Bullet* create(const DefaultPlane *plane);
	void update(float delta) override;
    void touchEvent(cocos2d::Touch* touch);
    void unscheduleUpdateAndDelete();
	float GetRotation() const;
    void buldelete();
private:

	Bullet();
	~Bullet();

	void initOptions(const DefaultPlane *plane);
	void addEvents();
	void applySpeed(float deltaTime);
	bool isStillOnScreen();
	

private:
	int _damadge;
    bool _isEnemyBullet; // Much better than owner_id. :)
	float _max_speed;
	Vec2 _currentSpeed;
    
};

#endif