#ifndef __LEVELUP1_SCENE_H__
#define __LEVELUP1_SCENE_H__

#include "cocos2d.h"

class LevelUp1 : public cocos2d::Layer {
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(LevelUp1);

    void GoToLevel2Scene(Ref* pSender);
    void GoToSelectLevelScene(Ref* pSender);
};

#endif
