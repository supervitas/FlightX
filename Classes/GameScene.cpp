#include "GameScene.h"
#include "Plane.h"

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
	plane->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(plane, 1);
    
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