#include "Level3Scene.h"
#include "Pause3Scene.h"
#include "GameOver3Scene.h"
#include "LevelUp3Scene.h"
#include <cocostudio/SimpleAudioEngine.h>

// Bitmasks
#define BITMASK_PLAYER 0x0001
#define BITMASK_OBSTACLE 0x0002
#define BITMASK_DOOR 0x0004

USING_NS_CC;

Scene* Level3::createScene()
{
    auto scene = Scene::createWithPhysics();
    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    scene->getPhysicsWorld()->setGravity(Vec2(0, 0));

    auto layer = Level3::create();
    layer->SetPhysicsWorld(scene->getPhysicsWorld());

    scene->addChild(layer);

    return scene;
}

bool Level3::init()
{
    if (!Layer::init()) {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    auto backgroundSprite = Sprite::create("Game_Screen_Background.png");
    backgroundSprite->setPosition(Point((visibleSize.width / 2) + origin.x, (visibleSize.height / 2) + origin.y));
    this->addChild(backgroundSprite);

    auto pauseItem = MenuItemImage::create("Pause.png", "Pause(Click).png", CC_CALLBACK_1(Level3::GoToPause3Scene, this));
    auto labelItem = MenuItemImage::create("Label3.png", "Label3.png");

    pauseItem->setPosition(Point(pauseItem->getContentSize().width - (pauseItem->getContentSize().width / 4) + origin.x, visibleSize.height - pauseItem->getContentSize().height + (pauseItem->getContentSize().width / 4) + origin.y));
    labelItem->setPosition(Vec2(880, 580));

    auto menu = Menu::create(pauseItem, labelItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu);


    //Adding Sprites

    auto playerSprite = Sprite::create("Right.png");
    playerSprite->setPosition(Vec2(30, 70));
    PhysicsBody* playerBody = PhysicsBody::createBox(playerSprite->getContentSize());
    playerBody->setCategoryBitmask(BITMASK_PLAYER);
    playerBody->setContactTestBitmask(BITMASK_OBSTACLE | BITMASK_DOOR);
    playerBody->setDynamic(false);
    playerSprite->setPhysicsBody(playerBody);
    this->addChild(playerSprite);

    auto scale1 = Sprite::create("Scale.png");
    scale1->setPosition(90, 19);
    this->addChild(scale1);

    auto obstacle1 = Sprite::create("shortObstacle.png");
    obstacle1->setPosition(250, 19);
    PhysicsBody* obstacle1Body = PhysicsBody::createBox(obstacle1->getContentSize());
    obstacle1Body->setCategoryBitmask(BITMASK_OBSTACLE);
    obstacle1Body->setContactTestBitmask(BITMASK_PLAYER);
    obstacle1Body->setDynamic(false);
    obstacle1->setPhysicsBody(obstacle1Body);
    this->addChild(obstacle1);

    auto scale2 = Sprite::create("Scale.png");
    scale2->setPosition(390, 19);
    this->addChild(scale2);

    auto obstacle2 = Sprite::create("shortObstacle.png");
    obstacle2->setPosition(550, 19);
    PhysicsBody* obstacle2Body = PhysicsBody::createBox(obstacle2->getContentSize());
    obstacle2Body->setCategoryBitmask(BITMASK_OBSTACLE);
    obstacle2Body->setContactTestBitmask(BITMASK_PLAYER);
    obstacle2Body->setDynamic(false);
    obstacle2->setPhysicsBody(obstacle2Body);
    this->addChild(obstacle2);

    auto scale3 = Sprite::create("Scale.png");
    scale3->setPosition(700, 19);
    this->addChild(scale3);

    auto obstacle = Sprite::create("Obstacle.png");
    obstacle->setPosition(950, 19);
    PhysicsBody* obstacleBody = PhysicsBody::createBox(obstacle->getContentSize());
    obstacleBody->setCategoryBitmask(BITMASK_OBSTACLE);
    obstacleBody->setContactTestBitmask(BITMASK_PLAYER);
    obstacleBody->setDynamic(false);
    obstacle->setPhysicsBody(obstacleBody);
    this->addChild(obstacle);

    auto scale = Sprite::create("Scale.png");
    scale->setPosition(970, 100);
    this->addChild(scale);

    auto enemy = Sprite::create("Enemy.png");
    enemy->setPosition(750, 60);
    PhysicsBody* enemyBody = PhysicsBody::createBox(enemy->getContentSize());
    enemyBody->setCategoryBitmask(BITMASK_OBSTACLE);
    enemyBody->setContactTestBitmask(BITMASK_PLAYER);
    enemyBody->setDynamic(false);
    enemy->setPhysicsBody(enemyBody);
    this->addChild(enemy);

    auto bomb5 = Sprite::create("Bomb_1.png");
    bomb5->setPosition(413, 60);
    PhysicsBody* bomb5Body = PhysicsBody::createBox(bomb5->getContentSize());
    bomb5Body->setCategoryBitmask(BITMASK_OBSTACLE);
    bomb5Body->setContactTestBitmask(BITMASK_PLAYER);
    bomb5Body->setDynamic(false);
    bomb5->setPhysicsBody(bomb5Body);
    this->addChild(bomb5);

    auto bomb4 = Sprite::create("Bomb_2.png");
    bomb4->setPosition(435, 60);
    PhysicsBody* bomb4Body = PhysicsBody::createBox(bomb4->getContentSize());
    bomb4Body->setCategoryBitmask(BITMASK_OBSTACLE);
    bomb4Body->setContactTestBitmask(BITMASK_PLAYER);
    bomb4Body->setDynamic(false);
    bomb4->setPhysicsBody(bomb4Body);
    this->addChild(bomb4);


    auto doorSprite = Sprite::create("Door.png");
    doorSprite->setPosition(Vec2(975, 170));
    PhysicsBody* doorBody = PhysicsBody::createBox(doorSprite->getContentSize());
    doorBody->setCategoryBitmask(BITMASK_DOOR);
    doorBody->setContactTestBitmask(BITMASK_PLAYER);
    doorBody->setDynamic(false);
    doorSprite->setPhysicsBody(doorBody);
    this->addChild(doorSprite);
    

    EventListenerPhysicsContact* listener = EventListenerPhysicsContact::create();
    listener->onContactBegin = [playerBody](PhysicsContact& contact) {
        int categoryA = contact.getShapeA()->getBody()->getCategoryBitmask();
        int categoryB = contact.getShapeB()->getBody()->getCategoryBitmask();

        if (contact.getShapeA()->getBody() == playerBody || contact.getShapeB()->getBody() == playerBody)
        {
            // Check which category the player's sprite is colliding with
            if (categoryA == BITMASK_DOOR || categoryB == BITMASK_DOOR)
            {
                // Player has reached the door
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audios/LevelUp.mp3");
                auto scene = LevelUp3::createScene();
                Director::getInstance()->replaceScene(scene);
            }
            else if (categoryA == BITMASK_OBSTACLE || categoryB == BITMASK_OBSTACLE)
            {
                // Player has collided with an obstacle
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audios/GameOver.mp3");
                auto scene = GameOver3::createScene();
                Director::getInstance()->replaceScene(scene);
            }
        }
        return true;
    };
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);


    //Moving player with keyboard

    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = [playerSprite, visibleSize](EventKeyboard::KeyCode keyCode, Event* event)
    {
        Vec2 loc = event->getCurrentTarget()->getPosition();
        switch (keyCode)
        {
        case EventKeyboard::KeyCode::KEY_UP_ARROW:
            //Check to prevent the player from going off the screen
            if (playerSprite->getPositionX() >= visibleSize.width - (playerSprite->getContentSize().width / 2)) {
                playerSprite->setPositionX(visibleSize.width - (playerSprite->getContentSize().width / 2));
            }
            else {
                event->getCurrentTarget()->runAction(JumpBy::create(0.5, Vec2(100, 0), 100, 1));
                playerSprite->setTexture("Jump_right.png");
            }
            break;
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            if (playerSprite->getPositionX() <= 0 + (playerSprite->getContentSize().width / 2)) {
                playerSprite->setPositionX(playerSprite->getContentSize().width / 2);
            }
            else {
                event->getCurrentTarget()->runAction(MoveBy::create(0.01, Vec2(-40, 0)));
                playerSprite->setTexture("Left.png");
            }
            break;
        case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
            if (playerSprite->getPositionX() <= 0 + (playerSprite->getContentSize().width / 2)) {
                playerSprite->setPositionX(playerSprite->getContentSize().width / 2);
            }
            else {
                event->getCurrentTarget()->runAction(JumpBy::create(0.5, Vec2(-100, 0), 100, 1));
                playerSprite->setTexture("Jump_left.png");
            }
            break;
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            if (playerSprite->getPositionX() >= visibleSize.width - (playerSprite->getContentSize().width / 2)) {
                playerSprite->setPositionX(visibleSize.width - (playerSprite->getContentSize().width / 2));
            }
            else {
                event->getCurrentTarget()->runAction(MoveBy::create(0.01, Vec2(40, 0)));
                playerSprite->setTexture("Right.png");
            }
            break;
        }
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, playerSprite);

    return true;
}

void Level3::GoToPause3Scene(cocos2d::Ref* pSender)
{
    auto scene = Pause3Menu::createScene();
    Director::getInstance()->pushScene(scene);
}