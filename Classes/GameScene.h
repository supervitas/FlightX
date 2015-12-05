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

    static cocos2d::Scene* createScene();
    bool onContactBegin(cocos2d::PhysicsContact &contact);
    virtual bool init() override;
    
	DefaultPlane* GetPlayerPlane();

    CREATE_FUNC(GameScene);
private:
    int score = 0;
	DefaultPlane* _player_plane;
	Label *scoreLabel;
	Label *playerHpLabel;
	Vector<EnemyPlane*> vectorEnemyPlanes;

private:
	void setDefaultBackground();
	void makeWorldPhysical();
	void createUI();
	void updateUI();
	void drawGameOver();

};

#endif // __GAMESCENE_H__
