#pragma once
#ifndef  __STAGE_SCENE_H__
#define  __STAGE_SCENE_H__

#include "cocos2d.h"
#define TAG_MENU1 100	//�޴��� �ҷ��� �±׸� ���� 

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
	
	Point FirstDot;		//ó�� ��ġ �� ��ġ
	Point LastDot;		//�������� ����
	float deltaTime;	//�ɸ��ð�
	bool isTouchAble;

	bool onTouchBegan(Touch *touch, Event *event);
	void onTouchEnded(Touch *touch, Event *event);

	void MoveMenu(bool isMoveLeft);
	void SetTouchAble(Ref* sender, bool isAble);
};


#endif // __STAGE_SCENE_H__

