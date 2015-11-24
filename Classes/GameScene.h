#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include <iostream>
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class GameScene : public cocos2d::Layer {
public:
    void setPhysicsWorld(cocos2d::PhysicsWorld* world){
        mWorld = world;
        mWorld->setGravity(cocos2d::Vect(0,0));  // No gravity
    }
    cocos2d::PhysicsWorld* mWorld;
    
    static cocos2d::Scene* createScene();
    void checkColision();
    bool onContactBegin(cocos2d::PhysicsContact &contact );
    virtual bool init();
    
    CREATE_FUNC(GameScene);
private:
	void SetDefaulBackground();
};

#endif // __GAMESCENE_H__
