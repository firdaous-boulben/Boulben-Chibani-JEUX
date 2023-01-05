#ifndef __LEVELUP2_SCENE_H__
#define __LEVELUP2_SCENE_H__

#include "cocos2d.h"

class LevelUp2 : public cocos2d::Layer {
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(LevelUp2);

    void GoToSelectLevelScene(Ref* pSender);
    void GoToLevel3Scene(Ref* pSender);
};

#endif
