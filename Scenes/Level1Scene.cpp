#include "Level1Scene.h"
#include "Pause1Scene.h"
#include "GameOver1Scene.h"
#include "LevelUp1Scene.h"
#include <cocostudio/SimpleAudioEngine.h>

// Bitmasks
#define BITMASK_PLAYER 0x0001
#define BITMASK_OBSTACLE 0x0002
#define BITMASK_DOOR 0x0004
#define BITMASK_SCALE 0x0008

USING_NS_CC;

Scene* Level1::createScene()
{
    auto scene = Scene::createWithPhysics();
    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    scene->getPhysicsWorld()->setGravity(Vec2(0, -100.f));

    auto layer = Level1::create();
    layer->SetPhysicsWorld(scene->getPhysicsWorld());

    scene->addChild(layer);

    return scene;
}

bool Level1::init()
{
    if (!Layer::init()) {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    auto backgroundSprite = Sprite::create("Game_Screen_Background.png");
    backgroundSprite->setPosition(Point((visibleSize.width / 2) + origin.x, (visibleSize.height / 2) + origin.y));
    this->addChild(backgroundSprite);

    auto pauseItem = MenuItemImage::create("Pause.png", "Pause(Click).png", CC_CALLBACK_1(Level1::GoToPause1Scene, this));
    auto labelItem = MenuItemImage::create("Label1.png", "Label1.png");

    pauseItem->setPosition(Point(pauseItem->getContentSize().width - (pauseItem->getContentSize().width / 4) + origin.x, visibleSize.height - pauseItem->getContentSize().height + (pauseItem->getContentSize().width / 4) + origin.y));
    labelItem->setPosition(Vec2(880, 580));

    auto menu = Menu::create(pauseItem, labelItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu);


    //Adding Sprites

    auto ground1Sprite = Sprite::create("Ground.png");
    ground1Sprite->setPosition(Vec2(0, 0));
    // Physics body for ground
    PhysicsBody* ground1Body = PhysicsBody::createBox(ground1Sprite->getContentSize(), PhysicsMaterial(1000000000.0f, 1.0f, 1000000000.0f));
    ground1Body->setGravityEnable(false);
    ground1Body->setCategoryBitmask(BITMASK_PLAYER);
    ground1Body->setCollisionBitmask(BITMASK_PLAYER);
    ground1Body->setContactTestBitmask(BITMASK_PLAYER);
    ground1Body->setDynamic(false);
    ground1Sprite->setPhysicsBody(ground1Body);
    this->addChild(ground1Sprite);


    auto ground2Sprite = Sprite::create("Ground.png");
    ground2Sprite->setPosition(Vec2(1000, 0));
    // Physics body for ground
    PhysicsBody* ground2Body = PhysicsBody::createBox(ground2Sprite->getContentSize(), PhysicsMaterial(1000000000.0f, 1.0f, 1000000000.0f));
    ground2Body->setGravityEnable(false);
    ground2Body->setCategoryBitmask(BITMASK_PLAYER);
    ground2Body->setCollisionBitmask(BITMASK_PLAYER);
    ground2Body->setContactTestBitmask(BITMASK_PLAYER);
    ground2Body->setDynamic(false);
    ground2Sprite->setPhysicsBody(ground2Body);
    this->addChild(ground2Sprite);


    auto playerSprite = Sprite::create("Right.png");
    playerSprite->setPosition(Vec2(30, 70));
    // Physics body for player sprite
    PhysicsBody* playerBody = PhysicsBody::createBox(playerSprite->getContentSize(), PhysicsMaterial(1000000000.0f, 1.0f, 1000000000.0f));
    playerBody->setGravityEnable(false);
    playerBody->setCategoryBitmask(BITMASK_PLAYER);
    playerBody->setCollisionBitmask(BITMASK_PLAYER);
    playerBody->setContactTestBitmask(BITMASK_OBSTACLE | BITMASK_DOOR);
    playerBody->setDynamic(true);
    playerBody->setRotationEnable(false);

    playerSprite->setPhysicsBody(playerBody);
    // Add to scene
    this->addChild(playerSprite, 0, 1);


    auto obstacleSprite = Sprite::create("Obstacle.png");
    obstacleSprite->setPosition(Vec2(525, 20));
    // Physics body for obstacle
    PhysicsBody* obstacleBody = PhysicsBody::createBox(obstacleSprite->getContentSize());
    obstacleBody->setCategoryBitmask(BITMASK_OBSTACLE);
    obstacleBody->setContactTestBitmask(BITMASK_PLAYER);
    obstacleBody->setDynamic(false);
    obstacleSprite->setPhysicsBody(obstacleBody);
    // Add to scene
    this->addChild(obstacleSprite);


    auto scaleSprite = Sprite::create("Scale.png");
    scaleSprite->setPosition(Vec2(500, 130));
    // Physics body for scale
    PhysicsBody* scaleBody = PhysicsBody::createBox(scaleSprite->getContentSize(), PhysicsMaterial(1000000000.0f, 1.0f, 1000000000.0f));
    scaleBody->setGravityEnable(false);
    scaleBody->setDynamic(false);
    scaleSprite->setPhysicsBody(scaleBody);
    // Add to scene
    this->addChild(scaleSprite);


    auto doorSprite = Sprite::create("Door.png");
    doorSprite->setPosition(Vec2(975, 90));
    // Physics body for player sprite
    PhysicsBody* doorBody = PhysicsBody::createBox(doorSprite->getContentSize());
    doorBody->setCategoryBitmask(BITMASK_DOOR);
    doorBody->setContactTestBitmask(BITMASK_PLAYER);
    doorBody->setDynamic(false);
    doorSprite->setPhysicsBody(doorBody);
    // Add to scene
    this->addChild(doorSprite);


    auto scaleRect = scaleSprite->getBoundingBox();
    auto ground1Rect = ground1Sprite->getBoundingBox();
    auto playerRect = playerSprite->getBoundingBox();

    if (!playerRect.intersectsRect(ground1Rect))
    {
        playerBody->setGravityEnable(true);
        // Player is not overlapping with the ground, so move the player back onto the ground
        playerSprite->setPosition(playerSprite->getPosition().x, ground1Rect.getMaxY());
    }
    if (!playerRect.intersectsRect(scaleRect))
    {
        // Player is not overlapping with the scale, so move the player back onto the scale
        playerSprite->setPosition(playerSprite->getPosition().x, scaleRect.getMaxY());
    }


    //Create event listener

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
                auto scene = LevelUp1::createScene();
                Director::getInstance()->replaceScene(scene);
            }
            else if (categoryA == BITMASK_OBSTACLE || categoryB == BITMASK_OBSTACLE)
            {
                // Player has collided with an obstacle
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audios/GameOver.mp3");
                auto scene = GameOver1::createScene();
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

void Level1::GoToPause1Scene(cocos2d::Ref* pSender)
{
    auto scene = Pause1Menu::createScene();
    Director::getInstance()->pushScene(scene);
}



