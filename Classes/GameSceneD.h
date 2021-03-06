#ifndef __GAME_SCENE_D_H__
#define __GAME_SCENE_D_H__

#include "cocos2d.h"
#include "Passenger.h"
#include "OtherSprite.h"
#include "MainScene.h"
#include <random>
USING_NS_CC;

class GameSceneD : public MainScene
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
	CREATE_FUNC(GameSceneD);

	Size visibleSize;
	Vec2 origin;

	Passenger P_Passenger;
	NomalPass N_Pass;				//�ݴް�
	FatPass F_Pass;					//���
	SpeedPass S_Pass;				//�����Ҵ�
	PandaPass PD_Pass;				//�Ǵ�
	SaebiPass NG_Pass;				//���̺�
	BlackPass BG_Pass;				//���
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
	std::unordered_map<int, Node*> _mouses;
	virtual bool onContactBegin(PhysicsContact& contact);
};

#endif // __HELLOWORLD_SCENE_H__
