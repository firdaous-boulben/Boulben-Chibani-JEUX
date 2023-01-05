#include "Level2Scene.h"
#include "Pause2Scene.h"
#include "GameOver2Scene.h"
#include "LevelUp2Scene.h"
#include <cocostudio/SimpleAudioEngine.h>

// Bitmasks
#define BITMASK_PLAYER 0x0001
#define BITMASK_OBSTACLE 0x0002
#define BITMASK_DOOR 0x0004

USING_NS_CC;

Scene* Level2::createScene()
{
    auto scene = Scene::createWithPhysics();
    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    scene->getPhysicsWorld()->setGravity(Vec2(0, 0));

    auto layer = Level2::create();
    layer->SetPhysicsWorld(scene->getPhysicsWorld());

    scene->addChild(layer);

    return scene;
}

bool Level2::init()
{
    if (!Layer::init()) {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    auto backgroundSprite = Sprite::create("Game_Screen_Background.png");
    backgroundSprite->setPosition(Point((visibleSize.width / 2) + origin.x, (visibleSize.height / 2) + origin.y));
    this->addChild(backgroundSprite);

    auto pauseItem = MenuItemImage::create("Pause.png", "Pause(Click).png", CC_CALLBACK_1(Level2::GoToPause2Scene, this));
    auto labelItem = MenuItemImage::create("Label2.png", "Label2.png");

    pauseItem->setPosition(Point(pauseItem->getContentSize().width - (pauseItem->getContentSize().width / 4) + origin.x, visibleSize.height - pauseItem->getContentSize().height + (pauseItem->getContentSize().width / 4) + origin.y));
    labelItem->setPosition(Vec2(880, 580));

    auto menu = Menu::create(pauseItem, labelItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu);


    //Adding Sprites
    auto roadSprite = Sprite::create("Road.png");
    roadSprite->setPosition(Vec2(500, 0));
    this->addChild(roadSprite);

    auto playerSprite = Sprite::create("Right.png");
    playerSprite->setPosition(Vec2(30, 70));
    PhysicsBody* playerBody = PhysicsBody::createBox(playerSprite->getContentSize());
    playerBody->setCategoryBitmask(BITMASK_PLAYER);
    playerBody->setContactTestBitmask(BITMASK_OBSTACLE | BITMASK_DOOR);
    playerBody->setDynamic(false);
    playerSprite->setPhysicsBody(playerBody);
    this->addChild(playerSprite);

    auto doorSprite = Sprite::create("Door.png");
    doorSprite->setPosition(Vec2(975, 90));
    PhysicsBody* doorBody = PhysicsBody::createBox(doorSprite->getContentSize());
    doorBody->setCategoryBitmask(BITMASK_DOOR);
    doorBody->setContactTestBitmask(BITMASK_PLAYER);
    doorBody->setDynamic(false);
    doorSprite->setPhysicsBody(doorBody);
    this->addChild(doorSprite);

    auto bomb1 = Sprite::create("Bomb_1.png");
    bomb1->setPosition(170, 65);
    PhysicsBody* bomb1Body = PhysicsBody::createBox(bomb1->getContentSize());
    bomb1Body->setCategoryBitmask(BITMASK_OBSTACLE);
    bomb1Body->setContactTestBitmask(BITMASK_PLAYER);
    bomb1Body->setDynamic(false);
    bomb1->setPhysicsBody(bomb1Body);
    this->addChild(bomb1);

    auto bomb2 = Sprite::create("Bomb_2.png");
    bomb2->setPosition(350, 65);
    PhysicsBody* bomb2Body = PhysicsBody::createBox(bomb2->getContentSize());
    bomb2Body->setCategoryBitmask(BITMASK_OBSTACLE);
    bomb2Body->setContactTestBitmask(BITMASK_PLAYER);
    bomb2Body->setDynamic(false);
    bomb2->setPhysicsBody(bomb2Body);
    this->addChild(bomb2);

    auto bomb3 = Sprite::create("Bomb_3.png");
    bomb3->setPosition(780, 65);
    PhysicsBody* bomb3Body = PhysicsBody::createBox(bomb3->getContentSize());
    bomb3Body->setCategoryBitmask(BITMASK_OBSTACLE);
    bomb3Body->setContactTestBitmask(BITMASK_PLAYER);
    bomb3Body->setDynamic(false);
    bomb3->setPhysicsBody(bomb3Body);
    this->addChild(bomb3);

    auto bomb4 = Sprite::create("Bomb_3.png");
    bomb4->setPosition(600, 65);
    PhysicsBody* bomb4Body = PhysicsBody::createBox(bomb4->getContentSize());
    bomb4Body->setCategoryBitmask(BITMASK_OBSTACLE);
    bomb4Body->setContactTestBitmask(BITMASK_PLAYER);
    bomb4Body->setDynamic(false);
    bomb4->setPhysicsBody(bomb4Body);
    this->addChild(bomb4);

    auto bomb5 = Sprite::create("Bomb_1.png");
    bomb5->setPosition(550, 65);
    PhysicsBody* bomb5Body = PhysicsBody::createBox(bomb5->getContentSize());
    bomb5Body->setCategoryBitmask(BITMASK_OBSTACLE);
    bomb5Body->setContactTestBitmask(BITMASK_PLAYER);
    bomb5Body->setDynamic(false);
    bomb5->setPhysicsBody(bomb5Body);
    this->addChild(bomb5);

    auto bomb7 = Sprite::create("Bomb_2.png");
    bomb7->setPosition(750, 65);
    PhysicsBody* bomb7Body = PhysicsBody::createBox(bomb7->getContentSize());
    bomb7Body->setCategoryBitmask(BITMASK_OBSTACLE);
    bomb7Body->setContactTestBitmask(BITMASK_PLAYER);
    bomb7Body->setDynamic(false);
    bomb7->setPhysicsBody(bomb7Body);
    this->addChild(bomb7);


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
                auto scene = LevelUp2::createScene();
                Director::getInstance()->replaceScene(scene);
            }
            else if (categoryA == BITMASK_OBSTACLE || categoryB == BITMASK_OBSTACLE)
            {
                // Player has collided with an obstacle
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audios/GameOver.mp3");
                auto scene = GameOver2::createScene();
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

void Level2::GoToPause2Scene(cocos2d::Ref* pSender)
{
    auto scene = Pause2Menu::createScene();
    Director::getInstance()->pushScene(scene);
}