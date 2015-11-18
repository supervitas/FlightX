#ifndef __BULLET_H__
#define __BULLET_H__

#include "cocos2d.h"
USING_NS_CC;

class Bullet : public cocos2d::Sprite {
public:

	static Bullet* create(static Vec2 position, static bool isEnemyBullet = false, static unsigned int bulletType = 0);
	void update(float delta) override;

    void touchEvent(cocos2d::Touch* touch);
    
private:

	Bullet();
	~Bullet();

	void initOptions(static Vec2 position, static bool isEnemyBullet = false, static unsigned int bulletType = 0);
	void addEvents();
	void applySpeed(float deltaTime);
	bool isStillOnScreen();
	void unscheduleUpdateAndDelete();

    bool _isEnemyBullet; // Much better than owner_id. :)
	float _max_speed;
	Vec2 _currentSpeed;
    
};

#endif