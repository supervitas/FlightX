#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include <iostream>
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class GameScene : public cocos2d::Layer {
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void TouchEnd(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
    CREATE_FUNC(GameScene);
private:
	void SetDefaulBackground();
};

#endif // __GAMESCENE_H__
