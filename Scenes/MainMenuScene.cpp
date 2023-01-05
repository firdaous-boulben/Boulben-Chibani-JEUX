#include "MainMenuScene.h"
#include "SelectLevelScene.h"
#include "GameScene.h"
#include <cocostudio/SimpleAudioEngine.h>

USING_NS_CC;

Scene* MainMenu::createScene()
{
    auto scene = Scene::create();
    auto layer = MainMenu::create();

    scene->addChild(layer);

    return scene;
}

bool MainMenu::init()
{
    if (!Layer::init())
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    auto menuTitle = MenuItemImage::create("Game_Title.png", "Game_Title.png");

    auto mode1 = MenuItemImage::create("World_Mode.png", "World_Mode.png", CC_CALLBACK_1(MainMenu::GoToSelectLevelScene, this));
    auto mode2 = MenuItemImage::create("Endless_Mode.png", "Endless_Mode.png", CC_CALLBACK_1(MainMenu::GoToGameScene, this));

    auto menu = Menu::create(menuTitle, mode1, mode2, NULL);
    menu->setPosition(visibleSize.width / 4, visibleSize.height / 4);
    menuTitle->setPosition(Point(visibleSize.width / 4, visibleSize.height / 2));
    mode1->setPosition(Point(visibleSize.width / 12, visibleSize.height / 6));
    mode2->setPosition(Point(visibleSize.width / 2.4, visibleSize.height / 6));
    this->addChild(menu);

    auto backgroundSprite = Sprite::create("Background.png");
    backgroundSprite->setPosition(Point((visibleSize.width / 2) + origin.x, (visibleSize.height / 2) + origin.y));
    this->addChild(backgroundSprite, -1);
    
    return true;
}

void MainMenu::GoToSelectLevelScene(Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audios/Play.mp3");

    auto scene = SelectLevel::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(1.0, scene));
}

void MainMenu::GoToGameScene(Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audios/Play.mp3");

    auto scene = GameScreen::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(1.0, scene));
}
