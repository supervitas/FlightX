#include "GameScene.h"
#include "EnemyPlane.h"
#include "Plane.h"
#include "Bullet.h"

USING_NS_CC;

namespace 
{
	const int kPlaneZIndex = 1;
	const int kBulletZIndex = 2;
};

Scene* GameScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GameScene::create();
    scene->addChild(layer);
    return scene;
}

bool GameScene::init()
{
    if (!Layer::init())
    {
        return false;	
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	SetDefaulBackground();

    DefaultPlane *plane = DefaultPlane::create();
    plane->setScale(0.15);
	plane->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 8));
	this->addChild(plane, kPlaneZIndex);
    
    EnemyPlane *enemy_plane = EnemyPlane::create();
    this->addChild(enemy_plane, kPlaneZIndex);
  
	// Keyboard input
	{
		auto listener = EventListenerKeyboard::create();
		listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, cocos2d::Event * event) 
		{
			Bullet *bullet;
			switch (keyCode)
			{
				// Plane Movement
			case cocos2d::EventKeyboard::KeyCode::KEY_NONE:
				break;
			case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
				plane->MovePlane(Vec2(-1.0f, .0f));
				break;
			case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
				plane->MovePlane(Vec2(1.0f, .0f));
				break;
			case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
				plane->MovePlane(Vec2(.0f, 1.0f));
				break;
			case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
				plane->MovePlane(Vec2(.0f, -1.0f));
				break;
            case cocos2d::EventKeyboard::KeyCode::KEY_K:
                {
                    bullet = Bullet::create(enemy_plane);
                    this->addChild(bullet, kBulletZIndex);
                    CCLOG("Bullet Rotation = %f", bullet->GetRotation()*(180.0f/3.14156));
                }
                break;

			case cocos2d::EventKeyboard::KeyCode::KEY_SPACE:
				// Spawn Bullet
			{
				bullet = Bullet::create(plane);
				this->addChild(bullet, kBulletZIndex);
				CCLOG("Bullet Rotation = %f", bullet->GetRotation()*(180.0f/3.14156));
			}
				break;
			default:
				break;
			}
		};

		listener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event)
		{

			switch (keyCode) 
			{
				// Plane Movement
			case cocos2d::EventKeyboard::KeyCode::KEY_NONE:
				break;
			case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
				plane->MovePlane(Vec2(1.0f, .0f));
				break;
			case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
				plane->MovePlane(Vec2(-1.0f, .0f));
				break;
			case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
				plane->MovePlane(Vec2(.0f, -1.0f));
				break;
			case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
				plane->MovePlane(Vec2(.0f, 1.0f));
				break;
			default:
				break;
			};
		};

		this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, plane);
	}

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