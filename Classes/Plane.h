#ifndef __PLANE_H__
#define __PLANE_H__
#include "cocos2d.h"
USING_NS_CC;
class DefaultPlane : public cocos2d::Sprite
{
public:
    DefaultPlane();
    ~DefaultPlane();
    static DefaultPlane* create();
    
	bool IsEnemy() const;
	void ApplyDamage(const int damage);
	int	 GetCurrentHP();
	void Shoot();

	bool MovePlane(const Vec2 direction);
	bool StopPlane();
	Vec2 GetCurrentSpeed();
    
	void update(float delta) override;
	
    void initOptions();
    void addEvents();
    void touchEvent(cocos2d::Touch* touch);
	
	void skewOnMovement();
	void applySpeed(float deltaTime);
	void unscheduleUpdateAndDelete();
    void makeBoom();
    
    void setMaximumSpeed(float);
protected:
    int _currentHP;
	int _baseHP;
    bool _isEnemy;
	float _maximalSpeed;
	Vec2 _movementDirection;
    
};

#endif