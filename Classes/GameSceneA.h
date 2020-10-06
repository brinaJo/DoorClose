#ifndef __GAME_SCENE_A_H__
#define __GAME_SCENE_A_H__

#include "cocos2d.h"
#include "Passenger.h"
#include "OtherSprite.h"
#include "MainScene.h"
#include "UILayer.h"
#include <random>
USING_NS_CC;
class GameSceneA : public MainScene				//MainScene ªÛº”πﬁøÚ
{
private:
	PhysicsBody *body = nullptr;
	Point firstTouch;
	//bool doorCollCheck = false;

	bool collcheck;

	int Nomal_score = 0;
	int Fat_score = 0;
	int Speed_score = 0;
	int Panda_score = 0;
	int Saebi_score = 0;
	int score = 0;
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	CREATE_FUNC(GameSceneA);

	Size visibleSize;
	Vec2 origin;

	Passenger P_Passenger;
	NomalPass N_Pass;				//π›¥ﬁ∞ı
	FatPass F_Pass;					//»Ú∞ı
	SpeedPass S_Pass;				//∑ßº≠∆“¥ı
	PandaPass PD_Pass;				//∆«¥Ÿ
	SaebiPass NG_Pass;				//ªÁ¿Ã∫Ò
	BlackPass BG_Pass;				//»Ê∞ı
	OtherSprite m_OtherSp;

	//////////////////////////////
	PhysicsWorld *m_world;

	void SetPhyWorld(PhysicsWorld* world)
	{
		m_world = world;
	}
	///////////////////////////////
public:
	UILayer* uiLayer;
	void initUI(float delta);
	virtual bool onContactBegin(PhysicsContact& contact);
	std::unordered_map<int, Node*> _mouses;
};

#endif // __HELLOWORLD_SCENE_H__
