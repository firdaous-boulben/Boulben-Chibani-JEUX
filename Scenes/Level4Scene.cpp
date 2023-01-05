#include "Level4Scene.h"
#include "Pause4Scene.h"
#include "GameOver4Scene.h"
#include "LevelUp4Scene.h"
#include <cocostudio/SimpleAudioEngine.h>

// Bitmasks
#define BITMASK_PLAYER 0x0001
#define BITMASK_OBSTACLE 0x0002
#define BITMASK_DOOR 0x0004

USING_NS_CC;

Scene* Level4::createScene()
{
    auto scene = Scene::createWithPhysics();
    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    scene->getPhysicsWorld()->setGravity(Vec2(0, 0));

    auto layer = Level4::create();
    layer->SetPhysicsWorld(scene->getPhysicsWorld());

    scene->addChild(layer);

    return scene;
}

bool Level4::init()
{
    if (!Layer::init()) {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    auto backgroundSprite = Sprite::create("Game_Screen_Background.png");
    backgroundSprite->setPosition(Point((visibleSize.width / 2) + origin.x, (visibleSize.height / 2) + origin.y));
    this->addChild(backgroundSprite);

    auto pauseItem = MenuItemImage::create("Pause.png", "Pause(Click).png", CC_CALLBACK_1(Level4::GoToPause4Scene, this));
    auto labelItem = MenuItemImage::create("Label4.png", "Label4.png");

    pauseItem->setPosition(Point(pauseItem->getContentSize().width - (pauseItem->getContentSize().width / 4) + origin.x, visibleSize.height - pauseItem->getContentSize().height + (pauseItem->getContentSize().width / 4) + origin.y));
    labelItem->setPosition(Vec2(880, 580));

    auto menu = Menu::create(pauseItem, labelItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu);

    this->scheduleUpdate();

    //Adding Sprites
    roadSprite = Sprite::create("Road.png");
    roadSprite->setPosition(Vec2(500, 0));
    PhysicsBody* roadBody = PhysicsBody::createBox(roadSprite->getContentSize());
    roadBody->setCategoryBitmask(BITMASK_DOOR);
    roadBody->setContactTestBitmask(BITMASK_PLAYER);
    roadBody->setDynamic(false);
    roadSprite->setPhysicsBody(roadBody);
    this->addChild(roadSprite);

    auto playerSprite = Sprite::create("Right.png");
    playerSprite->setPosition(Vec2(30, 70));
    PhysicsBody* playerBody = PhysicsBody::createBox(playerSprite->getContentSize());
    playerBody->setCategoryBitmask(BITMASK_PLAYER);
    playerBody->setContactTestBitmask(BITMASK_OBSTACLE | BITMASK_DOOR);
    playerBody->setDynamic(false);
    playerSprite->setPhysicsBody(playerBody);
    this->addChild(playerSprite);

    doorSprite = Sprite::create("Door.png");
    doorSprite->setPosition(Vec2(975, 90));
    PhysicsBody* doorBody = PhysicsBody::createBox(doorSprite->getContentSize());
    doorBody->setCategoryBitmask(BITMASK_DOOR);
    doorBody->setContactTestBitmask(BITMASK_PLAYER);
    doorBody->setDynamic(false);
    doorSprite->setPhysicsBody(doorBody);
    this->addChild(doorSprite);


    enemy1 = Sprite::create("Enemy_1.png");
    enemy1->setPosition(350, 65);
    PhysicsBody* enemy1Body = PhysicsBody::createBox(enemy1->getContentSize());
    enemy1Body->setCategoryBitmask(BITMASK_OBSTACLE);
    enemy1Body->setContactTestBitmask(BITMASK_PLAYER);
    enemy1Body->setDynamic(false);
    enemy1->setPhysicsBody(enemy1Body);
    this->addChild(enemy1);

    enemy2 = Sprite::create("Enemy_2.png");
    enemy2->setPosition(750, 65);
    PhysicsBody* enemy2Body = PhysicsBody::createBox(enemy2->getContentSize());
    enemy2Body->setCategoryBitmask(BITMASK_OBSTACLE);
    enemy2Body->setContactTestBitmask(BITMASK_PLAYER);
    enemy2Body->setDynamic(false);
    enemy2->setPhysicsBody(enemy2Body);
    this->addChild(enemy2);

    enemy3 = Sprite::create("Enemy_3.png");
    enemy3->setPosition(630, 200);
    PhysicsBody* enemy3Body = PhysicsBody::createBox(enemy3->getContentSize());
    enemy3Body->setCategoryBitmask(BITMASK_OBSTACLE);
    enemy3Body->setContactTestBitmask(BITMASK_PLAYER);
    enemy3Body->setDynamic(false);
    enemy3->setPhysicsBody(enemy3Body);
    this->addChild(enemy3);

    enemy4 = Sprite::create("Enemy_3.png");
    enemy4->setPosition(1000, 200);
    PhysicsBody* enemy4Body = PhysicsBody::createBox(enemy4->getContentSize());
    enemy4Body->setCategoryBitmask(BITMASK_OBSTACLE);
    enemy4Body->setContactTestBitmask(BITMASK_PLAYER);
    enemy4Body->setDynamic(false);
    enemy4->setPhysicsBody(enemy4Body);
    this->addChild(enemy4);


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
                auto scene = LevelUp4::createScene();
                Director::getInstance()->replaceScene(scene);
            }
            else if (categoryA == BITMASK_OBSTACLE || categoryB == BITMASK_OBSTACLE)
            {
                // Player has collided with an obstacle
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audios/GameOver.mp3");
                auto scene = GameOver4::createScene();
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

void Level4::update(float dt) {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    auto position = roadSprite->getPosition();
    position.x -= 250 * dt;
    if (position.x < 0 - (roadSprite->getBoundingBox().size.width / 2))
        position.x = this->getBoundingBox().getMaxX() + roadSprite->getBoundingBox().size.width / 2;
    roadSprite->setPosition(position);

    auto position1 = enemy1->getPosition();
    position1.x -= 200 * dt;
    if (position1.x < 0 - (enemy1->getBoundingBox().size.width / 2) - (doorSprite->getBoundingBox().size.width / 2))
        position1.x = this->getBoundingBox().getMaxX() + enemy1->getBoundingBox().size.width / 2;
    enemy1->setPosition(position1);

    auto position2 = enemy2->getPosition();
    position2.x -= 200 * dt;
    if (position2.x < 0 - (enemy2->getBoundingBox().size.width / 2))
        position2.x = this->getBoundingBox().getMaxX() + enemy2->getBoundingBox().size.width / 2;
    enemy2->setPosition(position2);

    auto position3 = enemy3->getPosition();
    position3.x -= 200 * dt;
    if (position3.x < 0 - (enemy3->getBoundingBox().size.width / 2))
        position3.x = this->getBoundingBox().getMaxX() + enemy3->getBoundingBox().size.width / 2;
    enemy3->setPosition(position3);

    auto position4 = enemy4->getPosition();
    position4.x -= 200 * dt;
    if (position4.x < 0 - (enemy4->getBoundingBox().size.width / 2))
        position4.x = this->getBoundingBox().getMaxX() + enemy4->getBoundingBox().size.width / 2;
    enemy4->setPosition(position4);
}

void Level4::GoToPause4Scene(cocos2d::Ref* pSender)
{
    auto scene = Pause4Menu::createScene();
    Director::getInstance()->pushScene(scene);
}