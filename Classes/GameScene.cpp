#include "GameScene.h"
#include "Bullet.h"


USING_NS_CC;

namespace 
{
	const int kPlaneZIndex = 1;
	const int kBulletZIndex = 2;
    Label *scoreLabel;
    Label *playerHpLabel;
    int bulcount = 0;
    Vector<EnemyPlane*> vectorEnemyPlanes;    
    
};

Scene* GameScene::createScene()
{
    auto scene = Scene::createWithPhysics();  // For physics
    scene->getPhysicsWorld()->setDebugDrawMask( PhysicsWorld::DEBUGDRAW_NONE);
    auto layer = GameScene::create();
    layer->setPhysicsWorld(scene->getPhysicsWorld());
    scene->addChild(layer);
    
    // return the scene
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
	SetDefaultBackground();
    
    auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 2);
    auto edgeNode = Node::create();
    edgeNode ->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y ));
    edgeNode->setPhysicsBody(edgeBody);
    this->addChild(edgeNode);

   
    
	_player_plane = DefaultPlane::create();
	this->addChild(_player_plane);
    
   

    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
 
	{
		auto listener = EventListenerKeyboard::create();
		listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, cocos2d::Event * event) 
		{
			Bullet *bullet;
			switch (keyCode)
			{
			case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
				GetPlayerPlane()->MovePlane(Vec2(-1.0f, .0f));
				break;
			case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
				GetPlayerPlane()->MovePlane(Vec2(1.0f, .0f));
				break;
			case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
				GetPlayerPlane()->MovePlane(Vec2(.0f, 1.0f));
				break;
			case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
				GetPlayerPlane()->MovePlane(Vec2(.0f, -1.0f));
				break;
            case cocos2d::EventKeyboard::KeyCode::KEY_K:
                {
					EnemyPlane *en_plane = EnemyPlane::create(GetPlayerPlane());
                    this->addChild(en_plane);
                    vectorEnemyPlanes.pushBack(en_plane);
                    break;

                }
                

			case cocos2d::EventKeyboard::KeyCode::KEY_SPACE:
			{
				bullet = Bullet::create(GetPlayerPlane());
                this->addChild(bullet, kBulletZIndex);

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
				// GetPlayerPlane() Movement
			case cocos2d::EventKeyboard::KeyCode::KEY_NONE:
				break;

			case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
				GetPlayerPlane()->MovePlane(Vec2(1.0f, .0f));
				break;
			case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
				GetPlayerPlane()->MovePlane(Vec2(-1.0f, .0f));

				break;
			case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
				GetPlayerPlane()->MovePlane(Vec2(.0f, -1.0f));
				break;
			case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
				GetPlayerPlane()->MovePlane(Vec2(.0f, 1.0f));
                    
				break;
          
			default:
				break;
			};
		};

		this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, GetPlayerPlane());
	}
	// Update everything in this scene.
	this->scheduleUpdate();
    return true;
}

DefaultPlane* GameScene::GetPlayerPlane()
{
	return _player_plane;
}

bool GameScene::onContactBegin(cocos2d::PhysicsContact& contact)
{
    PhysicsBody *a = contact.getShapeA()->getBody();
    PhysicsBody *b = contact.getShapeB()->getBody();
    if ((1 == a->getCollisionBitmask() && 2 == b->getCollisionBitmask()) || (2 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask()))
    {
        ((EnemyPlane*) b->getNode())->ApplyDamage(100);
        ((DefaultPlane*) a->getNode())->ApplyDamage(100);
        playerHpLabel->setString(std::to_string(0));
    }
    
    if (3 == a->getCollisionBitmask() && 2 == b->getCollisionBitmask())
    {
        ((EnemyPlane*) b->getNode())->ApplyDamage(20);
        ((Bullet*) a->getNode())->unscheduleUpdateAndDelete();
        
        score++;
        scoreLabel->setString(std::to_string(score));
//        for (int i = 0; i < bulletsMas.size(); i++)
//        {
//            if (bulletsMas.at(i)->getTag() == a->getNode()->getTag()) {
//                bulletsMas.at(i)->unscheduleUpdateAndDelete();
//            }
//        }
    }
    
    if (1 == b->getCollisionBitmask() && 4 == a->getCollisionBitmask())
    {
        ((DefaultPlane*) b->getNode())->ApplyDamage(10);
         ((Bullet*) a->getNode())->unscheduleUpdateAndDelete();
        playerHp -= 10;
        playerHpLabel->setString(std::to_string(playerHp));
    }
    
    return true;
}

void GameScene::SetDefaultBackground()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto back = Sprite::create("background.jpg");
	back->setFlippedY(true);
	back->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    back->setScale(0.7);
	this->addChild(back, 0);
    
    auto gameLabel = Label::createWithTTF("fonts/arial.ttf", "Score:");
    gameLabel->setColor(Color3B(255, 255 , 255));
    gameLabel->setPosition(Vec2(origin.x + visibleSize.width - 40,
                                origin.y + visibleSize.height - 10));
    this->addChild(gameLabel);
    
    scoreLabel = Label::create();
    scoreLabel->setString(std::to_string(score));
    scoreLabel->setColor(Color3B(255, 0 , 0));
    scoreLabel->setPosition(Vec2(origin.x + visibleSize.width-15,
                                 origin.y + visibleSize.height-10));
    this->addChild(scoreLabel, 0);
    
    auto hpLabel = Label::createWithTTF("fonts/arial.ttf", "Health:");
    hpLabel->setColor(Color3B(255, 255 , 255));
    hpLabel->setPosition(Vec2(origin.x + visibleSize.width / 20,
                                origin.y + visibleSize.height - 10));
    this->addChild(hpLabel);
    
    playerHpLabel = Label::create();
    playerHpLabel->setString(std::to_string(playerHp));
    playerHpLabel->setColor(Color3B(255, 0 , 0));
    playerHpLabel->setPosition(Vec2(origin.x + visibleSize.width / 8,
                                 origin.y + visibleSize.height - 10));
    this->addChild(playerHpLabel, 0);
}

