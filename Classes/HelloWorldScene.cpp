#include "HelloWorldScene.h"
#include "GameScene.h"
#include "Star.h"

USING_NS_CC;

Scene* HelloWorld::createScene() {
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
//    auto back = Sprite::create("menuback.jpg");
//    back->setPosition(Vec2(visibleSize.width/2
//                           , visibleSize.height/2));
//    this->addChild(back, 0);
//    back->setScale(1.2);
    
    auto back = Sprite::create("black_background.jpg");
    back->setFlippedY(true);
    back->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    back->setScale(2);
    this->addChild(back, 0);
    
    for (int i = 0; i < 1750; ++i)
        back->addChild(Star::create(), 10);
    
    for (int i = 0; i < 550; ++i)
        back->addChild(Star::create(StarType::kFarStar), 10);
    
    for (int i = 0; i < 10; ++i)
        back->addChild(Star::create(StarType::kNearStar), 10);
    
    
    auto gameLabel = Label::createWithTTF("fonts/arial.ttf", "FlightX");
    gameLabel->setColor(Color3B(255, 0 , 0));
    gameLabel->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height/2 + 30));
    this->addChild(gameLabel,1);
    auto startGameButton = ui::Button::create();
    startGameButton->setTitleText("Play");
    startGameButton->setColor(Color3B(0, 255, 0));
    
    startGameButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        switch (type) {
            case ui::Widget::TouchEventType::ENDED:
				Director::getInstance()->replaceScene(GameScene::createScene());
                break;
            default:
                break;
        }
    });
    startGameButton->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height/2));

    this->addChild(startGameButton, 1);
    
    auto QuitGameButton = ui::Button::create();
    QuitGameButton->setTitleText("Exit");
    QuitGameButton->setColor(Color3B(0, 0, 150));
    
    QuitGameButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        switch (type) {
            case ui::Widget::TouchEventType::ENDED:
                Director::getInstance()->end();
                break;
            default:
                break;
        }
    });
    QuitGameButton->setPosition(Vec2(origin.x + visibleSize.width/2,
                                      origin.y + visibleSize.height/2-30));
    
    this->addChild(QuitGameButton, 1);
    
    return true;
}

