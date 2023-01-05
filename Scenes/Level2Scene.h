#ifndef __LEVEL2_SCENE_H__
#define __LEVEL2_SCENE_H__

#include "cocos2d.h"

class Level2 : public cocos2d::Layer {

public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(Level2);

    void GoToPause2Scene(Ref* pSender);

    cocos2d::PhysicsWorld* sceneWorld;
    void SetPhysicsWorld(cocos2d::PhysicsWorld* world) { sceneWorld = world; }
};

#endif