#include "cocos2d.h"
USING_NS_CC;



class MySprite : public cocos2d::Sprite
{
public:
    MySprite();
    ~MySprite();
    static MySprite* create();
    
    void initOptions();
    
    void addEvents();
    void touchEvent(cocos2d::Touch* touch);
    
private:
    
};