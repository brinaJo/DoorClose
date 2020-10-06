#pragma once
#include "cocos2d.h"
USING_NS_CC;
class Passenger : public cocos2d::Layer
{
private:
	int result;													//랜덤위치 결과값
	float TimePlus;												//뚱뚱한캐릭터 1~3번 부딪히기 위한 시간 누적
	void TagSpriteChange(int tag, Sprite* spr);					//태그에따라 부딪혔을때 스프라이트 바꿔주는 함수
protected:
	Sprite* sprite = NULL;
	Animation* animation;
public:
	Size visibleSize;
	bool RL_Check;												//캐릭터가 오른쪽으로 가는지 왼쪽으로 가는지

	Passenger();
	~Passenger();
	void PassAni();
	virtual int Passinit();										//캐릭터 위치 랜덤으로 배정
	virtual void PassRun();										//캐릭터 움직이는 함수
	void PassCollision(cocos2d::Layer *layer, Sprite*, Point location,float delta);	//일반승객과 나머지 승객들이 부딪혔을때 나머지 승객들을 움직이는 함수
	
	void ChaScore(cocos2d::Layer *layer, Node *sender);			//캐릭터 위에 +1 +3 -5 뜨는 함수
	void MoonCollPass(Ref *sender);								//캐릭터 사라지는 함수
	void RemoveVec(Ref *sender);
};

class NomalPass : public Passenger								//반달곰(노멀)
{
public:
	NomalPass(){ }
	virtual void Passinit(cocos2d::Layer *layer);				//반달곰(노멀) 캐릭터 정보 세팅
	virtual void PassRun();										//스프라이트 애니메이션

	
	void NomalTouch(cocos2d::Sprite *m_nomal);					//반달곰 캐릭터를 터치했을때  
};
class FatPass : public Passenger								//흰곰
{
public:
	virtual void Passinit(cocos2d::Layer *layer);
	virtual void PassRun();
};
class SpeedPass : public Passenger								//랫서팬더
{
public:
	virtual void Passinit(cocos2d::Layer *layer);
	virtual void PassRun();
};
class PandaPass : public Passenger								//판다
{
public:
	virtual void Passinit(cocos2d::Layer *layer);
	virtual void PassRun();
};
class SaebiPass : public Passenger
{
public:
	virtual void Passinit(cocos2d::Layer *layer);
	virtual void PassRun();
};
class BlackPass : public Passenger
{
public:
	virtual void Passinit(cocos2d::Layer *layer);
	virtual void PassRun();		//R쪽으로 달릴때
	void PassRun_BD();			//L쪽으로 방향 틀때
};