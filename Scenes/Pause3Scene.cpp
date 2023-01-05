#include "Pause3Scene.h"
#include "Level3Scene.h"
#include "MainMenuScene.h"

USING_NS_CC;

Scene* Pause3Menu::createScene()
{
    auto scene = Scene::create();
    auto layer = Pause3Menu::create();

    scene->addChild(layer);
    return scene;
}

bool Pause3Menu::init()
{
    if (!Layer::init())
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    auto resumeItem = MenuItemImage::create("Resume.png", "Resume.png", CC_CALLBACK_1(Pause3Menu::Resume, this));
    auto retryItem = MenuItemImage::create("Retry.png", "Retry.png", CC_CALLBACK_1(Pause3Menu::Retry, this));
    auto mainMenuItem = MenuItemImage::create("Menu.png", "Menu.png", CC_CALLBACK_1(Pause3Menu::GoToMainMenuScene, this));

    auto menu = Menu::create(resumeItem, retryItem, mainMenuItem, NULL);
    menu->alignItemsHorizontallyWithPadding(visibleSize.height / 8);
    this->addChild(menu);

    auto backgroundSprite = Sprite::create("Pause_Background.png");
    backgroundSprite->setPosition(Point((visibleSize.width / 2) + origin.x, (visibleSize.height / 2) + origin.y));
    this->addChild(backgroundSprite, -1);

    return true;
}

void Pause3Menu::Resume(cocos2d::Ref* pSender)
{
    Director::getInstance()->popScene();
}

void Pause3Menu::GoToMainMenuScene(cocos2d::Ref* pSender)
{
    auto scene = MainMenu::createScene();
    Director::getInstance()->popScene();
    Director::getInstance()->replaceScene(scene);
}

void Pause3Menu::Retry(cocos2d::Ref* pSender)
{
    auto scene = Level3::createScene();
    Director::getInstance()->popScene();
    Director::getInstance()->replaceScene(scene);
}