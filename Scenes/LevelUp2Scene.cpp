#include "LevelUp2Scene.h"
#include "GameScene.h"
#include "SelectLevelScene.h"
#include "Level3Scene.h"

USING_NS_CC;

Scene* LevelUp2::createScene()
{
    auto scene = Scene::create();
    auto layer = LevelUp2::create();

    scene->addChild(layer);
    return scene;
}

bool LevelUp2::init()
{
    if (!Layer::init())
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    auto backItem = MenuItemImage::create("Back.png", "Back(Click).png", CC_CALLBACK_1(LevelUp2::GoToSelectLevelScene, this));
    auto nextItem = MenuItemImage::create("Next.png", "Next(Click).png", CC_CALLBACK_1(LevelUp2::GoToLevel3Scene, this));

    auto menu = Menu::create(backItem, nextItem, NULL);
    menu->alignItemsHorizontallyWithPadding(visibleSize.height / 2);
    backItem->setPosition(Vec2(-420, 12));
    nextItem->setPosition(Vec2(420, 12));
    this->addChild(menu);

    auto backgroundSprite = Sprite::create("LevelUp2_Background.png");
    backgroundSprite->setPosition(Point((visibleSize.width / 2) + origin.x, (visibleSize.height / 2) + origin.y));
    this->addChild(backgroundSprite, -1);

    return true;
}


void LevelUp2::GoToSelectLevelScene(cocos2d::Ref* pSender)
{
    auto scene = SelectLevel::createScene();
    Director::getInstance()->replaceScene(scene);
}

void LevelUp2::GoToLevel3Scene(cocos2d::Ref* pSender)
{
    auto scene = Level3::createScene();
    Director::getInstance()->replaceScene(scene);
}