#pragma once
#ifndef  __Set_up_H_
#define  __Set_up_H_

#include "cocos2d.h"

USING_NS_CC;

class SetupScene : public Layer
{
public:
	static Scene* createScene();
	virtual bool init();

	CREATE_FUNC(SetupScene);

	void changeScene(Ref* sender);
};


#endif // __GAME_SCENE_C_H__
