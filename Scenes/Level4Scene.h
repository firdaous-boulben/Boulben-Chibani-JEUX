#ifndef __LEVEL4_SCENE_H__
#define __LEVEL4_SCENE_H__

#include "cocos2d.h"

class Level4 : public cocos2d::Layer {
    cocos2d::Sprite* roadSprite;
    cocos2d::Sprite* doorSprite;
    cocos2d::Sprite* enemy1;
    cocos2d::Sprite* enemy2;
    cocos2d::Sprite* enemy3;
    cocos2d::Sprite* enemy4;

public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(Level4);

    void GoToPause4Scene(Ref* pSender);
    void update(float dt);

    cocos2d::PhysicsWorld* sceneWorld;
    void SetPhysicsWorld(cocos2d::PhysicsWorld* world) { sceneWorld = world; }
};

#endif
