#include "LevelUp4Scene.h"
#include "SelectLevelScene.h"
#include "MainMenuScene.h"

USING_NS_CC;

Scene* LevelUp4::createScene()
{
    auto scene = Scene::create();
    auto layer = LevelUp4::create();

    scene->addChild(layer);
    return scene;
}

bool LevelUp4::init()
{
    if (!Layer::init())
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    auto backItem = MenuItemImage::create("Back.png", "Back(Click).png", CC_CALLBACK_1(LevelUp4::GoToSelectLevelScene, this));
    auto nextItem = MenuItemImage::create("Next.png", "Next(Click).png", CC_CALLBACK_1(LevelUp4::GoToMainMenuScene, this));

    auto menu = Menu::create(backItem, nextItem, NULL);
    menu->alignItemsHorizontallyWithPadding(visibleSize.height / 2);
    backItem->setPosition(Vec2(-420, 12));
    nextItem->setPosition(Vec2(440, 12));
    this->addChild(menu);

    auto backgroundSprite = Sprite::create("LevelUp4_Background.png");
    backgroundSprite->setPosition(Point((visibleSize.width / 2) + origin.x, (visibleSize.height / 2) + origin.y));
    this->addChild(backgroundSprite, -1);

    return true;
}


void LevelUp4::GoToSelectLevelScene(cocos2d::Ref* pSender)
{
    auto scene = SelectLevel::createScene();
    Director::getInstance()->replaceScene(scene);
}

void LevelUp4::GoToMainMenuScene(cocos2d::Ref* pSender)
{
    auto scene = MainMenu::createScene();
    Director::getInstance()->replaceScene(scene);
}