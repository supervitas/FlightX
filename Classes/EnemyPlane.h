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

USING_NS_CC;
class EnemyPlane : public DefaultPlane
{
public:
    EnemyPlane();
    ~EnemyPlane();
    static EnemyPlane* create();
    void initOptions();
    void Spawn();
    void addEvents();
    void update(float delta) override;
//    void randomMove(EnemyPlane *plane);
    
    

};

#endif /* EnemyPlane_hpp */
