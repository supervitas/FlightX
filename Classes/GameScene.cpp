#include "GameScene.h"
#include "HelloWorldScene.h"
#include "Bullet.h"
#include "Bonus.h"
#include "Star.h"

USING_NS_CC;

namespace 
{
	const int kPlaneZIndex = 1;
	const int kBulletZIndex = 2;
    const float kEnemySpawnDelay = 0.9f;
    const float kBonusSpawnDelay = 6.f;
    const int kMaxBonusCount = 2;
    const int kDefaultBulletDamgeMultiplier = 4;
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

void GameScene::bonusCreate()
{
    
    if (bonusCount < kMaxBonusCount )
    {
        bonusCount++;
        Bonus* bon = Bonus::create();
        this->addChild(bon, 1);
    }
}

void GameScene::enemyCreate()
{
    int plane_type = cocos2d::RandomHelper::random_int(0, 3) == 0? 1 : 0;
    EnemyPlane* en = factory->createPlane(plane_type);
    
    float x = 50.f + cocos2d::RandomHelper::random_int(0, int(Director::getInstance()->getVisibleSize().width - 100.f));
    en->setPosition(x, Director::getInstance()->getVisibleSize().height - 50);
    this->addChild(en, 1);
}

bool GameScene::init()
{
    if (!Layer::init())
    {
        return false;	
    }

    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
	_player_plane = DefaultPlane::create();
	this->addChild(_player_plane, kPlaneZIndex);
    
	setDefaultBackground();
	makeWorldPhysical();
	createUI();
    bonusTimer = 0;
    enemyTimer = 0;
    bonusCount = 0;
    factory = new EnemyPlaneFactory(GetPlayerPlane());
    
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

    if ((1 == a->getCollisionBitmask() && 2 == b->getCollisionBitmask()) || (2 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask())) // столкновения нашего и вражеского самолета
    {
        if (a->getNode()->getTag() == 2)
        {
            auto enemy_plane = dynamic_cast<EnemyPlane*>(a->getNode());
            enemy_plane->ApplyDamage(100);
            GetPlayerPlane()->ApplyDamage(50);
            should_update_UI = true;
        }
        else {
            GetPlayerPlane()->ApplyDamage(50);
            ((EnemyPlane*) b->getNode())->ApplyDamage(100);
            should_update_UI = true;

        }
    }
    
    if (3 == a->getCollisionBitmask() && 2 == b->getCollisionBitmask()) // вражеский самолет и наша пуля
    {
		((EnemyPlane*) b->getNode())->ApplyDamage(((Bullet*) a->getNode())->GetDamage()*kDefaultBulletDamgeMultiplier);
        ((Bullet*) a->getNode())->unscheduleUpdateAndDelete();
        
        score++;
		should_update_UI = true;
    }
    
    if (1 == b->getCollisionBitmask() && 4 == a->getCollisionBitmask()) // вражеская пуля и наш самолет
    {
		((DefaultPlane*) b->getNode())->ApplyDamage(((Bullet*) a->getNode())->GetDamage());
        ((Bullet*) a->getNode())->unscheduleUpdateAndDelete();
		should_update_UI = true;
    }
    
    
    if (8 == a->getCollisionBitmask() || 8 == b->getCollisionBitmask() ) // бонусы и наш самолет
    {
        if (a->getCollisionBitmask() == 1)
        {
            b->getNode()->removeFromParent();
            GetPlayerPlane()->ApplyDamage(-30);
             bonusCount--;
            should_update_UI = true;
        }
        if (b->getCollisionBitmask() == 1)
        {
            a->getNode()->removeFromParent();
            GetPlayerPlane()->ApplyDamage(-30);
             bonusCount--;
            should_update_UI = true;
        }
        if (b->getCollisionBitmask() == 2)
        {
            a->getNode()->removeFromParent();
            ((EnemyPlane*) b->getNode())->ApplyDamage(-20);
             bonusCount--;
        }
        if (a->getCollisionBitmask() == 2)
        {
            b->getNode()->removeFromParent();
            ((EnemyPlane*) a->getNode())->ApplyDamage(-20);
            bonusCount--;
            
        }
    }
    
	if (should_update_UI)
		updateUI();
    return true;
}

void GameScene::makeWorldPhysical()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 10);
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
        if (gameOver == false)
		drawGameOver();
}

void GameScene::drawGameOver()
{
    gameOver = true;
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
		switch	 (type)
		{
		case ui::Widget::TouchEventType::ENDED:
                gameOver = false;
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


	auto back = Sprite::create("black_background.jpg");
	back->setFlippedY(true);
	back->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    back->setScale(2);
	this->addChild(back, 0);

	for (int i = 0; i < 750; ++i)
		back->addChild(Star::create(), 10);

	for (int i = 0; i < 250; ++i)
		back->addChild(Star::create(StarType::kFarStar), 10);

	for (int i = 0; i < 50; ++i)
		back->addChild(Star::create(StarType::kNearStar), 10);
	
    
}

void GameScene::update(float delta)
{
    if (!gameOver)
    {
        enemyTimer += delta;
        bonusTimer += delta;
        if (enemyTimer >= kEnemySpawnDelay)
        {
            enemyCreate();
            enemyTimer = 0;
        }
            
        if (bonusTimer >= kBonusSpawnDelay)
        {
            bonusCreate();
            bonusTimer = 0;
        }
    }
}

