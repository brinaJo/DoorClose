#pragma once
#ifndef  __MANNER_H__
#define  __MANNER_H__

#include "cocos2d.h"

USING_NS_CC;

class Manner : public Layer		//게임방법 출력
{
public:
	static Scene* createScene();
	virtual bool init();
	void changeScene(Ref* sender);

	CREATE_FUNC(Manner);



	
	bool isTouchAble;


};


#endif // __TITLE_SCENE_H__
