#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include <iostream>
#include "cocos2d.h"
#include "EnemyPlane.h"
#include "Plane.h"
#include "Bullet.h"
#include "ui/CocosGUI.h"

class GameScene : public cocos2d::Layer 
{
public:
    void setPhysicsWorld(cocos2d::PhysicsWorld* world)
	{
        mWorld = world;
        mWorld->setGravity(cocos2d::Vect(0,0));  // No gravity
    }
    cocos2d::PhysicsWorld* mWorld;
    void update(float delta) override;
    static cocos2d::Scene* createScene();
    bool onContactBegin(cocos2d::PhysicsContact &contact);
    virtual bool init() override;
    
	DefaultPlane* GetPlayerPlane();

    CREATE_FUNC(GameScene);
private:
	void SetDefaultBackground();
    int score = 0;
    Vector<Bullet*> bulletsMas;
	DefaultPlane* _player_plane;

};

#endif // __GAMESCENE_H__
