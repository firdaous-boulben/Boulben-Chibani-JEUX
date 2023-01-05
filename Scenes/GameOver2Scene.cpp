#include "GameOver2Scene.h"
#include "MainMenuScene.h"
#include "Level2Scene.h"

USING_NS_CC;

Scene* GameOver2::createScene()
{
    auto scene = Scene::create();
    auto layer = GameOver2::create();

    scene->addChild(layer);
    return scene;
}

bool GameOver2::init()
{
    if (!Layer::init())
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    auto retryItem = MenuItemImage::create("Retry.png", "Retry.png", CC_CALLBACK_1(GameOver2::GoToLevel2Scene, this));

    auto mainMenuItem = MenuItemImage::create("Menu.png", "Menu.png", CC_CALLBACK_1(GameOver2::GoToMainMenuScene, this));

    auto menu = Menu::create(retryItem, mainMenuItem, NULL);
    menu->alignItemsHorizontallyWithPadding(visibleSize.height / 15);
    this->addChild(menu);

    auto backgroundSprite = Sprite::create("Game_Over_Screen_Background.png");
    backgroundSprite->setPosition(Point((visibleSize.width / 2) + origin.x, (visibleSize.height / 2) + origin.y));
    this->addChild(backgroundSprite, -1);

    return true;
}

void GameOver2::GoToLevel2Scene(cocos2d::Ref* pSender)
{
    auto scene = Level2::createScene();
    Director::getInstance()->replaceScene(scene);
}

void GameOver2::GoToMainMenuScene(cocos2d::Ref* pSender)
{
    auto scene = MainMenu::createScene();
    Director::getInstance()->replaceScene(scene);
}