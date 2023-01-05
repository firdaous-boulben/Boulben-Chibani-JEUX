#include "SelectLevelScene.h"
#include "Level1Scene.h"
#include "Level2Scene.h"
#include "Level3Scene.h"
#include "Level4Scene.h"
#include <cocostudio/SimpleAudioEngine.h>

USING_NS_CC;

Scene* SelectLevel::createScene()
{
    auto scene = Scene::create();
    auto layer = SelectLevel::create();

    scene->addChild(layer);
    return scene;
}

bool SelectLevel::init()
{
    if (!Layer::init())
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    auto Item1 = MenuItemImage::create("Level1.png", "Level1(Click).png", CC_CALLBACK_1(SelectLevel::GoToLevel1Scene, this));
    auto Item2 = MenuItemImage::create("Level2.png", "Level2(Click).png", CC_CALLBACK_1(SelectLevel::GoToLevel2Scene, this));
    auto Item3 = MenuItemImage::create("Level3.png", "Level3(Click).png", CC_CALLBACK_1(SelectLevel::GoToLevel3Scene, this));
    auto Item4 = MenuItemImage::create("Level4.png", "Level4(Click).png", CC_CALLBACK_1(SelectLevel::GoToLevel4Scene, this));

    auto menu = Menu::create(Item1, Item2, Item3,Item4, NULL);
    menu->alignItemsHorizontallyWithPadding(visibleSize.height / 8);
    this->addChild(menu);

    auto backgroundSprite = Sprite::create("Select_Level_Background.png");
    backgroundSprite->setPosition(Point((visibleSize.width / 2) + origin.x, (visibleSize.height / 2) + origin.y));
    this->addChild(backgroundSprite, -1);

    return true;
}

void SelectLevel::GoToLevel1Scene(cocos2d::Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audios/SelectLevel.mp3");

    auto scene = Level1::createScene();
    Director::getInstance()->replaceScene(scene);
}

void SelectLevel::GoToLevel2Scene(cocos2d::Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audios/SelectLevel.mp3");

    auto scene = Level2::createScene();
    Director::getInstance()->replaceScene(scene);
}

void SelectLevel::GoToLevel3Scene(cocos2d::Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audios/SelectLevel.mp3");

    auto scene = Level3::createScene();
    Director::getInstance()->replaceScene(scene);
}

void SelectLevel::GoToLevel4Scene(cocos2d::Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audios/SelectLevel.mp3");

    auto scene = Level4::createScene();
    Director::getInstance()->replaceScene(scene);
}