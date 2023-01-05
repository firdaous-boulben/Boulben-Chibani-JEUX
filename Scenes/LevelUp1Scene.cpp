#include "LevelUp1Scene.h"
#include "Level2Scene.h"
#include "SelectLevelScene.h"

USING_NS_CC;

Scene* LevelUp1::createScene()
{
    auto scene = Scene::create();
    auto layer = LevelUp1::create();

    scene->addChild(layer);
    return scene;
}

bool LevelUp1::init()
{
    if (!Layer::init())
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    auto backItem = MenuItemImage::create("Back.png", "Back(Click).png", CC_CALLBACK_1(LevelUp1::GoToSelectLevelScene, this));
    auto nextItem = MenuItemImage::create("Next.png", "Next(Click).png", CC_CALLBACK_1(LevelUp1::GoToLevel2Scene, this));

    auto menu = Menu::create(backItem, nextItem, NULL);
    menu->alignItemsHorizontallyWithPadding(visibleSize.height / 2);
    backItem->setPosition(Vec2(-450, 12));
    nextItem->setPosition(Vec2(420, 12));
    this->addChild(menu);

    auto backgroundSprite = Sprite::create("LevelUp1_Background.png");
    backgroundSprite->setPosition(Point((visibleSize.width / 2) + origin.x, (visibleSize.height / 2) + origin.y));
    this->addChild(backgroundSprite, -1);

    return true;
}

void LevelUp1::GoToLevel2Scene(cocos2d::Ref* pSender)
{
    auto scene = Level2::createScene();
    Director::getInstance()->replaceScene(scene);
}

void LevelUp1::GoToSelectLevelScene(cocos2d::Ref* pSender)
{
    auto scene = SelectLevel::createScene();
    Director::getInstance()->replaceScene(scene);
}