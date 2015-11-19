#include "GameScene.h"
#include "Plane.h"
#include "Bullet.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GameScene::create();
    scene->addChild(layer);
    return scene;
}

bool GameScene::init() {
    if (!Layer::init()) {
        return false;	
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	SetDefaulBackground();

    DefaultPlane *plane = DefaultPlane::create();
    plane->setScale(0.15);
	plane->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 8));
	this->addChild(plane, 1);




	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [=](EventKeyboard::KeyCode code, cocos2d::Event * event) {
        Bullet *bullet;
		switch (code) {
		case cocos2d::EventKeyboard::KeyCode::KEY_NONE:
			break;
        case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			plane->setPositionX(plane->getPositionX() - 10.0f);
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			plane->setPositionX(plane->getPositionX() + 10.0f);
			break;
        
		case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
            plane->setPositionY(plane->getPositionY() + 10.0f);
		break;
		case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
            plane->setPositionY(plane->getPositionY() - 10.0f);
		break;
        case cocos2d::EventKeyboard::KeyCode::KEY_SPACE:
            bullet = Bullet::create(plane->getPosition(), true);
			this->addChild(bullet, 1);
			break;
        default:
			break;
		}
	};
    listener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event){

        CCLOG("lol");
    };

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, plane);

	// End of bullets. I mean, out of bullets.
    //

	// Update everything in this scene.
	this->scheduleUpdate();
    return true;
}



void GameScene::SetDefaulBackground()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto back = Sprite::create("background.jpg");
	back->setFlippedY(true);
	back->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(back, 0);
	back->setScale(0.7);
}