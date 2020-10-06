#pragma once
#ifndef  __STAGE_SCENE_H__
#define  __STAGE_SCENE_H__

#include "cocos2d.h"
#define TAG_MENU1 100	//메뉴를 불러올 태그를 선언 

#define STAGE_CNT	5

USING_NS_CC;
//using namespace cocos2d::ui;

class StageScene : public Layer
{

private:
	Sprite* spr[STAGE_CNT];

	int stage[5];
public:
	static Scene* createScene();
	virtual bool init();
	void Stageinit();
	CREATE_FUNC(StageScene);

	void changeScene(Ref* sender);
	
	Point FirstDot;		//처음 터치 된 위치
	Point LastDot;		//마지막에 뗀거
	float deltaTime;	//걸린시간
	bool isTouchAble;

	bool onTouchBegan(Touch *touch, Event *event);
	void onTouchEnded(Touch *touch, Event *event);

	void MoveMenu(bool isMoveLeft);
	void SetTouchAble(Ref* sender, bool isAble);
};


#endif // __STAGE_SCENE_H__

