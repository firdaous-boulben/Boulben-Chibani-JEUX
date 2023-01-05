#ifndef __GAMEOVER2_SCENE_H__
#define __GAMEOVER2_SCENE_H__

#include "cocos2d.h"

class GameOver2 : public cocos2d::Layer {
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(GameOver2);

    void GoToLevel2Scene(Ref* pSender);
    void GoToMainMenuScene(Ref* pSender);
};

#endif
