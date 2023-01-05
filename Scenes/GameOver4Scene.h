#ifndef __GAMEOVER4_SCENE_H__
#define __GAMEOVER4_SCENE_H__

#include "cocos2d.h"

class GameOver4 : public cocos2d::Layer {
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(GameOver4);

    void GoToLevel4Scene(Ref* pSender);
    void GoToMainMenuScene(Ref* pSender);
};

#endif