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

	void initSubway(cocos2d::Layer *layer);			//지하철 물리박스 정보 세팅 (문 or 벽)
	void initReady(cocos2d::Layer *layer);			//지하철 들어오는 애니메이션 함수
};