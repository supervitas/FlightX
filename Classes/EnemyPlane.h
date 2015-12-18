//
//  EnemyPlane.hpp
//  FlightX
//
//  Created by Виталий on 21.11.15.
//
//
#ifndef EnemyPlane_hpp
#define EnemyPlane_hpp
#include "cocos2d.h"
#include "Plane.h"
#include "Behaviour.h"

USING_NS_CC;
class EnemyPlane : public DefaultPlane
{
public:
	EnemyPlane(DefaultPlane* const player_plane);
    ~EnemyPlane();
	static EnemyPlane* create(DefaultPlane* const player_plane);
    void initOptions();
    void Spawn();
    void addEvents();
    void update(float delta) override;
    void randomMove(Vec2 coord);
    bool isStillOnScreen();
    void ChangeBehavoiur(DefaultPlane* const player_plane, int type = 0);
    

protected:
	AbstractPlaneBehavoiur* _behaviour;
        

};

#endif /* EnemyPlane_hpp */
