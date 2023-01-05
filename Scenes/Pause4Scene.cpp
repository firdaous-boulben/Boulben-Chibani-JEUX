#include "Pause4Scene.h"
#include "Level4Scene.h"
#include "MainMenuScene.h"

USING_NS_CC;

Scene* Pause4Menu::createScene()
{
    auto scene = Scene::create();
    auto layer = Pause4Menu::create();

    scene->addChild(layer);
    return scene;
}

bool Pause4Menu::init()
{
    if (!Layer::init())
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    auto resumeItem = MenuItemImage::create("Resume.png", "Resume.png", CC_CALLBACK_1(Pause4Menu::Resume, this));
    auto retryItem = MenuItemImage::create("Retry.png", "Retry.png", CC_CALLBACK_1(Pause4Menu::Retry, this));
    auto mainMenuItem = MenuItemImage::create("Menu.png", "Menu.png", CC_CALLBACK_1(Pause4Menu::GoToMainMenuScene, this));

    auto menu = Menu::create(resumeItem, retryItem, mainMenuItem, NULL);
    menu->alignItemsHorizontallyWithPadding(visibleSize.height / 8);
    this->addChild(menu);

    auto backgroundSprite = Sprite::create("Pause_Background.png");
    backgroundSprite->setPosition(Point((visibleSize.width / 2) + origin.x, (visibleSize.height / 2) + origin.y));
    this->addChild(backgroundSprite, -1);

    return true;
}

void Pause4Menu::Resume(cocos2d::Ref* pSender)
{
    Director::getInstance()->popScene();
}

void Pause4Menu::GoToMainMenuScene(cocos2d::Ref* pSender)
{
    auto scene = MainMenu::createScene();
    Director::getInstance()->popScene();
    Director::getInstance()->replaceScene(scene);
}

void Pause4Menu::Retry(cocos2d::Ref* pSender)
{
    auto scene = Level4::createScene();
    Director::getInstance()->popScene();
    Director::getInstance()->replaceScene(scene);
}