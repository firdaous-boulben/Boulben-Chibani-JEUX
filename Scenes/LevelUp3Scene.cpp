#include "LevelUp3Scene.h"
#include "SelectLevelScene.h"
#include "Level4Scene.h"

USING_NS_CC;

Scene* LevelUp3::createScene()
{
    auto scene = Scene::create();
    auto layer = LevelUp3::create();

    scene->addChild(layer);
    return scene;
}

bool LevelUp3::init()
{
    if (!Layer::init())
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    auto backItem = MenuItemImage::create("Back.png", "Back(Click).png", CC_CALLBACK_1(LevelUp3::GoToSelectLevelScene, this));
    auto nextItem = MenuItemImage::create("Next.png", "Next(Click).png", CC_CALLBACK_1(LevelUp3::GoToLevel4Scene, this));

    auto menu = Menu::create(backItem, nextItem, NULL);
    menu->alignItemsHorizontallyWithPadding(visibleSize.height / 2);
    backItem->setPosition(Vec2(-420, 12));
    nextItem->setPosition(Vec2(420, 12));
    this->addChild(menu);

    auto backgroundSprite = Sprite::create("LevelUp3_Background.png");
    backgroundSprite->setPosition(Point((visibleSize.width / 2) + origin.x, (visibleSize.height / 2) + origin.y));
    this->addChild(backgroundSprite, -1);

    return true;
}

void LevelUp3::GoToSelectLevelScene(cocos2d::Ref* pSender)
{
    auto scene = SelectLevel::createScene();
    Director::getInstance()->replaceScene(scene);
}

void LevelUp3::GoToLevel4Scene(cocos2d::Ref* pSender)
{
    auto scene = Level4::createScene();
    Director::getInstance()->replaceScene(scene);
}