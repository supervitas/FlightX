#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include <iostream>
#include "cocos2d.h"
#include "EnemyPlane.h"
#include "ui/CocosGUI.h"

class GameScene : public cocos2d::Layer {
public:
    void setPhysicsWorld(cocos2d::PhysicsWorld* world){
        mWorld = world;
        mWorld->setGravity(cocos2d::Vect(0,0));  // No g*ravity
    }
    cocos2d::PhysicsWorld* mWorld;
    void applySpeed(float deltaTime);
    static cocos2d::Scene* createScene();
    bool checkColision();
    void update(float delta);
    void unscheduleUpdateAndDelete();
    bool onContactBegin(cocos2d::PhysicsContact &contact, DefaultPlane *plane);
    virtual bool init();
    
    CREATE_FUNC(GameScene);
private:
	void SetDefaulBackground();
    int score = 0;
    cocos2d::ccArray *bullets;
    cocos2d::ccArray *planes;
};

#endif // __GAMESCENE_H__
