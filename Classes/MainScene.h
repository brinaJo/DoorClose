#ifndef __MAIN_SCENE__H__
#define __MAIN_SCENE__H__

#include "cocos2d.h"
#include "Passenger.h"
#include "OtherSprite.h"
#include "UILayer.h"
#include <random>
USING_NS_CC;
class MainScene : public cocos2d::Layer
{
private:
	PhysicsBody *body = nullptr;
	Point firstTouch;

	int play_sound = false;
	bool collcheck;
protected:

	bool isTouch = false;
	virtual void L_SetSprite(float delta);							//스케줄이 부르는 갈색 곰 캐릭터
	virtual void M_SetSprite(float delta);							//스케줄이 부르는 뚱뚱한 캐릭터
	virtual void S_SetSprite(float delta);							//빠른 주황색 캐릭터
	virtual void BADS_SetSprite(float delta);						//판다 캐릭터
	virtual void BADL_SetSprite(float delta);						//사이비(너구리)캐릭터
	virtual void BADW_SetSprite(float delta);						//흑곰 캐릭터
	virtual void resetPass(Ref *sender);							//캐릭터 없애는 함수
	virtual void MoonCollPass(Ref *sender);							//캐릭터가 문에 들어왔을때 캐릭터 지우는 함수
	virtual bool onTouchBegan(Touch *touch, Event *unused_event);	//씬에서 캐릭터 선택
	virtual void onTouchEnded(Touch *touch, Event *unused_event);	//캐릭터 선택후 드래그 끝남
	virtual bool onContactBegin(PhysicsContact& contact);			//캐릭터가 문에 들어왔을때

	virtual void update(float delta);

	void PandaSel();					//판다 넣었을때 이펙트 출력
	void SaebiSel(Node* node);			//사이비 넣었을때 이펙트 출력(node = 지하철문)
	
	int Nomal_count = 0;
	int Fat_count = 0;
	int Fat_Tcount = 0;
	int Speed_count = 0;
	int Panda_count = 0;
	int Saebi_count = 0;
	int Saebi_Tcount = 0;
	int Total_count = 0;
	//스코어 카운트 변수
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void MusicLoad();						//음악 미리 로드

	CREATE_FUNC(MainScene);

	Size visibleSize;
	Vec2 origin;

	Passenger P_Passenger;
	NomalPass N_Pass;				//반달곰
	FatPass F_Pass;					//흰곰
	SpeedPass S_Pass;				//랫서팬더
	PandaPass PD_Pass;				//판다
	SaebiPass NG_Pass;				//사이비
	BlackPass BG_Pass;				//흑곰
	OtherSprite m_OtherSp;

	//////////////////////////////
	PhysicsWorld *m_world;

	void SetPhyWorld(PhysicsWorld* world)
	{
		m_world = world;
	}
	///////////////////////////////
	UILayer* uiLayer;
};

#endif // __HELLOWORLD_SCENE_H__
