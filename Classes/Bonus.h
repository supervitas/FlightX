//
//  Bonus.hpp
//  FlightX
//
//  Created by Виталий on 15.12.15.
//
//

#ifndef Bonus_hpp
#define Bonus_hpp

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
class Bonus : public cocos2d::Sprite
{
public:
    Bonus();
    ~Bonus();
    static Bonus* create();
    void initOptions();
    void Spawn();

//    void update(float delta);
    bool isStillOnScreen();
    
protected:
//    AbstractPlaneBehavoiur* _behaviour;
    
    
};


#endif /* Bonus_hpp */
