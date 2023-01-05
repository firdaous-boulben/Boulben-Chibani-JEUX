#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

class GameScreen : public cocos2d::Layer {

    cocos2d::Sprite* playerSprite;
    cocos2d::Sprite* backgroundSpriteArray[2];
    cocos2d::PhysicsWorld* mWorld;

    std::vector<cocos2d::Sprite*> bombs;

    bool isTouching;
    float touchPosition;

public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(GameScreen);

    void GoToPauseScene(Ref* pSender);
    void GoToGameOverScene(Ref* pSender);
    void update(float dt);
    void spawnBomb(float dt);

    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event);

    //Physics

    void setPhysicsWorld(cocos2d::PhysicsWorld* world)
    {
        mWorld = world;
        mWorld->setGravity(cocos2d::Vect(0, 0));

    }

    bool onContactBegin(cocos2d::PhysicsContact& contact);
};

#endif
