#ifndef __GAMEOVER1_SCENE_H__
#define __GAMEOVER1_SCENE_H__

#include "cocos2d.h"

class GameOver1 : public cocos2d::Layer {
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(GameOver1);

    void GoToLevel1Scene(Ref* pSender);
    void GoToMainMenuScene(Ref* pSender);
};

#endif

