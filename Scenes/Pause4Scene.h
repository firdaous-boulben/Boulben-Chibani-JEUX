#ifndef __PAUSE4_SCENE_H__
#define __PAUSE4_SCENE_H__

#include "cocos2d.h"

class Pause4Menu : public cocos2d::Layer {
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(Pause4Menu);

    void Resume(Ref* pSender);
    void GoToMainMenuScene(Ref* pSender);
    void Retry(Ref* pSender);
};

#endif

