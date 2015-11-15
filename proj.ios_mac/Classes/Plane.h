#include "cocos2d.h"
USING_NS_CC;
class DefaultPlane : public cocos2d::Sprite {
public:
    DefaultPlane();
    ~DefaultPlane();
    static DefaultPlane* create();
    
    void initOptions();
    
    void addEvents();
    void touchEvent(cocos2d::Touch* touch);
    
private:
    int plane_hp;
    bool isEnemy;
    
};