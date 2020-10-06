#pragma once
#ifndef  __UI_LAYER_H__
#define  __UI_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class UILayer : public Layer
{
public:
	virtual bool init();

	CREATE_FUNC(UILayer);
	Size visibleSize;
	void changeScene(Ref* sender);
	void initUI(int stage);

	void initCountUIA();
	void initPassCountA(int Total_Count, int Nomal_Count, int Fat_count, int Speed_count, int Panda_count, int Saebi_count);
	void initCountUIB();
	void initPassCountB(int Total_Count, int Nomal_Count, int Fat_count, int Speed_count, int Panda_count, int Saebi_count);
	void initCountUIC();
	void initPassCountC(int Total_Count, int Nomal_Count, int Fat_count, int Speed_count, int Panda_count, int Saebi_count);
	void initCountUID();
	void initPassCountD(int Total_Count, int Nomal_Count, int Fat_count, int Speed_count, int Panda_count, int Saebi_count);
	void initCountUIE();
	void initPassCountE(int Total_Count, int Nomal_Count, int Fat_count, int Speed_count, int Panda_count, int Saebi_count);

	void Success(int star);
	void Fail();
	void StageAndStar(int _Star);
	//void changeScene(Ref* sender);

	Label* timeLabel;
	Label* totalLabel;
	int limitTime;
	void CalcPlayTime(float dt);
	int stage;

	int Nm_count = 0;
	int Ft_count = 0;
	int Sed_count = 0;
	int Pd_count = 0;
	int Sb_count = 0;
	int To_count = 100;

	int Nm3_count = 0;
	int Sed3_count = 0;
	int Ft3_count = 0;
	int Ft4_count = 0;

	bool isTwostar = false;
	bool isThreestar = false;
};


#endif // __UI_LAYER_H__

