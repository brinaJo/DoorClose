#pragma once
#ifndef  __DEVELOP_H__
#define  __DEVELOP_H__

#include "cocos2d.h"

USING_NS_CC;

class Develop : public Layer	//개발자 출력
{
public:
	static Scene* createScene();
	virtual bool init();
	void changeScene(Ref* sender);
	

	CREATE_FUNC(Develop);

	
};


#endif // __TITLE_SCENE_H__
