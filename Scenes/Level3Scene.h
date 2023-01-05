#ifndef __LEVEL3_SCENE_H__
#define __LEVEL3_SCENE_H__

#include "cocos2d.h"

class Level3 : public cocos2d::Layer {

public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(Level3);

    void GoToPause3Scene(Ref* pSender);

    cocos2d::PhysicsWorld* sceneWorld;
    void SetPhysicsWorld(cocos2d::PhysicsWorld* world) { sceneWorld = world; }
};

#endif
