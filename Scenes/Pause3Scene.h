#ifndef __PAUSE3_SCENE_H__
#define __PAUSE3_SCENE_H__

#include "cocos2d.h"

class Pause3Menu : public cocos2d::Layer {
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(Pause3Menu);

    void Resume(Ref* pSender);
    void GoToMainMenuScene(Ref* pSender);
    void Retry(Ref* pSender);
};

#endif
