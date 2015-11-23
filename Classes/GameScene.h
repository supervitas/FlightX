#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include <iostream>
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class GameScene : public cocos2d::Layer {
public:
    static cocos2d::Scene* createScene();
    void checkColision();
    virtual bool init();
    
    CREATE_FUNC(GameScene);
private:
	void SetDefaulBackground();
};

#endif // __GAMESCENE_H__
