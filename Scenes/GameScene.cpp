#include "GameScene.h"
#include "PauseScene.h"
#include "GameOverScene.h"
#include <cocostudio/SimpleAudioEngine.h>

USING_NS_CC;

Scene* GameScreen::createScene()
{
    auto scene = Scene::createWithPhysics();

    auto layer = GameScreen::create();
    layer->setPhysicsWorld(scene->getPhysicsWorld());

    scene->addChild(layer);

    return scene;
}

bool GameScreen::init()
{
    if (!Layer::init()) {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    auto pauseItem = MenuItemImage::create("Pause.png", "Pause(Click).png", CC_CALLBACK_1(GameScreen::GoToPauseScene, this));

    pauseItem->setPosition(
        Point(pauseItem->getContentSize().width - (pauseItem->getContentSize().width / 4) + origin.x,
            visibleSize.height - pauseItem->getContentSize().height + (pauseItem->getContentSize().width / 4) + origin.y));

    auto menu = Menu::create(pauseItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu);

    this->scheduleUpdate();
    this->schedule(SEL_SCHEDULE(&GameScreen::spawnBomb), 1.0);

    for (int i = 0; i < 2; i++) {
        backgroundSpriteArray[i] = Sprite::create("Game_Screen_Background.png");
        backgroundSpriteArray[i]->setPosition(
            Point((visibleSize.width / 2) + origin.x,
                (visibleSize.height / 2) + origin.y));
        this->addChild(backgroundSpriteArray[i], -2);
    }

    playerSprite = Sprite::create("playerRight.png");

    auto body = PhysicsBody::createCircle(playerSprite->getContentSize().width / 2);
    body->setContactTestBitmask(true);
    body->setDynamic(true);

    playerSprite->setPosition(Point((visibleSize.width / 2),(visibleSize.height / 1.5)));
    playerSprite->setPhysicsBody(body);
    this->addChild(playerSprite, -1);

    auto listener = EventListenerTouchOneByOne::create();

    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(GameScreen::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameScreen::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameScreen::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(GameScreen::onTouchCancelled, this);

    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    this->isTouching = false;
    this->touchPosition = 0;

    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameScreen::onContactBegin, this);

    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

    return true;
}

void GameScreen::GoToPauseScene(cocos2d::Ref* pSender)
{
    auto scene = PauseMenu::createScene();
    Director::getInstance()->pushScene(scene);
}

void GameScreen::GoToGameOverScene(cocos2d::Ref* pSender)
{
    auto scene = GameOver::createScene();
    Director::getInstance()->replaceScene(scene);
}

void GameScreen::update(float dt)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    for (int i = 0; i < bombs.size(); i++) {
        bombs[i]->setPosition(
            Point(bombs[i]->getPositionX(),
                bombs[i]->getPositionY() + (0.75 * visibleSize.height * dt)));

        if (bombs[i]->getPosition().y > visibleSize.height + (bombs[i]->getContentSize().height / 2)) {
            this->removeChild(bombs[i]);
            bombs.erase(bombs.begin() + i);
        }
    }

    if (isTouching) {
        if (touchPosition < visibleSize.width / 2) {
            //move the player to the left
            playerSprite->setPositionX(playerSprite->getPositionX() - (0.50 * visibleSize.width * dt));
            playerSprite->setTexture("playerLeft.png");

            //check to prevent the player from going off the screen (left side)
            if (playerSprite->getPositionX() <= 0 + (playerSprite->getContentSize().width / 2)) {
                playerSprite->setPositionX(playerSprite->getContentSize().width / 2);
            }
        }
        else {
            // move the player to the right
            playerSprite->setPositionX(playerSprite->getPositionX() + (0.50 * visibleSize.width * dt));
            playerSprite->setTexture("playerRight.png");
            //check to prevent the player from going off the screen (right side)
            if (playerSprite->getPositionX() >= visibleSize.width - (playerSprite->getContentSize().width / 2)) {
                playerSprite->setPositionX(visibleSize.width - (playerSprite->getContentSize().width / 2));
            }
        }
    }
}

void GameScreen::spawnBomb(float dt)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    int bombIndex = (random() % 3) + 1;
    std::string bombString = StringUtils::format("Bomb_%i.png", bombIndex);

    Sprite* tempBomb = Sprite::create(bombString.c_str());

    int xRandomPosition = (random() % (int)(visibleSize.width - (tempBomb->getContentSize().width / 2))) + (tempBomb->getContentSize().width / 2);
    tempBomb->setPosition(Point(xRandomPosition + origin.x, -tempBomb->getContentSize().height + origin.y));

    bombs.push_back(tempBomb);

    auto body = PhysicsBody::createCircle(bombs[bombs.size() - 1]->getContentSize().width / 2);
    body->setContactTestBitmask(true);
    body->setDynamic(true);
    bombs[bombs.size() - 1]->setPhysicsBody(body);

    this->addChild(bombs[bombs.size() - 1], -1);
}

bool GameScreen::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
    isTouching = true;
    touchPosition = touch->getLocation().x;
    return true;
}
void GameScreen::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{
}

void GameScreen::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
    isTouching = false;
}

void GameScreen::onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event)
{
    onTouchEnded(touch, event);
}

bool GameScreen::onContactBegin(cocos2d::PhysicsContact& contact) {
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audios/GameOver.mp3");

    playerSprite->setTexture("playerDead.png");
    GoToGameOverScene(this);
    return true;
}
