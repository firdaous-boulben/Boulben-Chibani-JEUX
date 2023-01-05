#ifndef __LEVELUP4_SCENE_H__
#define __LEVELUP4_SCENE_H__

#include "cocos2d.h"

class LevelUp4 : public cocos2d::Layer {
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(LevelUp4);

    void GoToMainMenuScene(Ref* pSender);
    void GoToSelectLevelScene(Ref* pSender);
};

#endif
