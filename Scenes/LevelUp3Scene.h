#ifndef __LEVELUP3_SCENE_H__
#define __LEVELUP3_SCENE_H__

#include "cocos2d.h"

class LevelUp3 : public cocos2d::Layer {
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(LevelUp3);

    void GoToSelectLevelScene(Ref* pSender);
    void GoToLevel4Scene(cocos2d::Ref* pSender);
};

#endif
