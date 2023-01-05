#ifndef __SELECTLEVEL_SCENE_H__
#define __SELECTLEVEL_SCENE_H__

#include "cocos2d.h"

class SelectLevel : public cocos2d::Layer {
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(SelectLevel);

    void GoToLevel1Scene(Ref* pSender);
    void GoToLevel2Scene(Ref* pSender);
    void GoToLevel3Scene(Ref* pSender);
    void GoToLevel4Scene(Ref* pSender);
};

#endif
