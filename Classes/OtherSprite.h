#pragma once
#include "cocos2d.h"
USING_NS_CC;

class OtherSprite : public cocos2d::Layer
{
private:
	Size visibleSize;
public:
	OtherSprite();
	~OtherSprite();

	void initSubway(cocos2d::Layer *layer);			//����ö �����ڽ� ���� ���� (�� or ��)
	void initReady(cocos2d::Layer *layer);			//����ö ������ �ִϸ��̼� �Լ�
};