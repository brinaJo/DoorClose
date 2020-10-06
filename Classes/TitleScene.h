#pragma once
#ifndef  __TITLE_SCENE_H__
#define  __TITLE_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class TitleScene : public Layer
{
public:
	static Scene* createScene();
	virtual bool init();

	int play_sound = false;

	CREATE_FUNC(TitleScene);

	void changeScene(Ref* sender);
};


#endif // __TITLE_SCENE_H__

