#ifndef __GAMEOVER3_SCENE_H__
#define __GAMEOVER3_SCENE_H__

#include "cocos2d.h"

class GameOver3 : public cocos2d::Layer {
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(GameOver3);

    void GoToLevel3Scene(Ref* pSender);
    void GoToMainMenuScene(Ref* pSender);
};

#endif