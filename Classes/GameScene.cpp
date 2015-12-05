#include "GameScene.h"
#include "HelloWorldScene.h"
#include "Bullet.h"


USING_NS_CC;

namespace 
{
	const int kPlaneZIndex = 10;
	const int kBulletZIndex = 2;
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
    
	_player_plane = DefaultPlane::create();
	this->addChild(_player_plane, kPlaneZIndex);
    
	setDefaultBackground();
	makeWorldPhysical();
	createUI();
   

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
	bool should_update_UI = false;

    if ((1 == a->getCollisionBitmask() && 2 == b->getCollisionBitmask()) || (2 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask()))
    {
		((EnemyPlane*) a->getNode())->ApplyDamage(((EnemyPlane*) a->getNode())->GetCurrentHP());
        ((DefaultPlane*) b->getNode())->ApplyDamage(50);
		should_update_UI = true;
    }
    
    if (3 == a->getCollisionBitmask() && 2 == b->getCollisionBitmask())
    {
		((EnemyPlane*) b->getNode())->ApplyDamage(((Bullet*) a->getNode())->GetDamage());
        ((Bullet*) a->getNode())->unscheduleUpdateAndDelete();
        
        score++;
		should_update_UI = true;
    }
    
    if (1 == b->getCollisionBitmask() && 4 == a->getCollisionBitmask())
    {
		((DefaultPlane*) b->getNode())->ApplyDamage(((Bullet*) a->getNode())->GetDamage());
        ((Bullet*) a->getNode())->unscheduleUpdateAndDelete();
		should_update_UI = true;
    }
    
	if (should_update_UI)
		updateUI();
    return true;
}

void GameScene::makeWorldPhysical()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 2);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	edgeNode->setPhysicsBody(edgeBody);
	this->addChild(edgeNode);
}

void GameScene::updateUI()
{
	if (_player_plane->GetCurrentHP() > 0)
	{
		playerHpLabel->setString(std::to_string(_player_plane->GetCurrentHP()));
		scoreLabel->setString(std::to_string(score));
	} else
		drawGameOver();
}

void GameScene::drawGameOver()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	playerHpLabel->setString(std::to_string(0));
	
	auto game_over_label = Label::createWithTTF("fonts/arial.ttf", std::string("Game Over!\n"));
	game_over_label->setColor(Color3B(255, 255, 255));
	game_over_label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2 + game_over_label->getBoundingBox().size.height * 3));
	
	// Rotate
	game_over_label->setRotation(-15);
	auto rotate1 = RotateBy::create(1, 30);
	auto rotate2 = RotateBy::create(1, -30);
	auto rot_seq = Sequence::create(rotate1, rotate2, rotate1->clone(), rotate2->clone(), nullptr);
	// Scale
	auto scale1 = ScaleTo::create(2, 2);
	auto scale2 = ScaleTo::create(4, 1);
	auto sca_seq = Sequence::createWithTwoActions(scale1, scale2);
	// Continiously
	game_over_label->runAction(RepeatForever::create(sca_seq));
	game_over_label->runAction(RepeatForever::create(rot_seq));
	this->addChild(game_over_label);


	auto startGameButton = ui::Button::create();
	startGameButton->setTitleText("Play again");
	game_over_label->setScale(1.5f);
	startGameButton->setColor(Color3B(0, 255, 0));
	startGameButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::ENDED:
			Director::getInstance()->replaceScene(GameScene::createScene());
			break;
		default:
			break;
		}
	});
	startGameButton->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2));
	this->addChild(startGameButton);



	auto mainMenuButton = ui::Button::create();
	mainMenuButton->setTitleText("Main menu");
	mainMenuButton->setColor(Color3B(127, 0, 127));
	mainMenuButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::ENDED:
			Director::getInstance()->replaceScene(HelloWorld::createScene());
			break;
		default:
			break;
		}
	});
	mainMenuButton->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2 - mainMenuButton->getBoundingBox().size.height*2));
	this->addChild(mainMenuButton);
}

void GameScene::createUI()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto gameLabel = Label::createWithTTF("fonts/arial.ttf", "Score:");
	gameLabel->setColor(Color3B(255, 255, 255));
	gameLabel->setPosition(Vec2(origin.x + visibleSize.width - 40,
		origin.y + visibleSize.height - 10));
	this->addChild(gameLabel);

	scoreLabel = Label::create();
	scoreLabel->setString(std::to_string(score));
	scoreLabel->setColor(Color3B(255, 0, 0));
	scoreLabel->setPosition(Vec2(origin.x + visibleSize.width - 15,
		origin.y + visibleSize.height - 10));
	this->addChild(scoreLabel, 0);

	auto hpLabel = Label::createWithTTF("fonts/arial.ttf", "Health:");
	hpLabel->setColor(Color3B(255, 255, 255));
	hpLabel->setPosition(Vec2(origin.x + visibleSize.width / 20,
		origin.y + visibleSize.height - 10));
	this->addChild(hpLabel);

	playerHpLabel = Label::create();
	playerHpLabel->setString(std::to_string(_player_plane->GetCurrentHP()));
	playerHpLabel->setColor(Color3B(255, 0, 0));
	playerHpLabel->setPosition(Vec2(origin.x + visibleSize.width / 8,
		origin.y + visibleSize.height - 10));
	this->addChild(playerHpLabel, 0);
}

void GameScene::setDefaultBackground()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto back = Sprite::create("background.jpg");
	back->setFlippedY(true);
	back->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    back->setScale(0.7);
	this->addChild(back, 0);

}

