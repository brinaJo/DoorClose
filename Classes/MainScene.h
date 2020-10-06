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
	virtual void L_SetSprite(float delta);							//�������� �θ��� ���� �� ĳ����
	virtual void M_SetSprite(float delta);							//�������� �θ��� �׶��� ĳ����
	virtual void S_SetSprite(float delta);							//���� ��Ȳ�� ĳ����
	virtual void BADS_SetSprite(float delta);						//�Ǵ� ĳ����
	virtual void BADL_SetSprite(float delta);						//���̺�(�ʱ���)ĳ����
	virtual void BADW_SetSprite(float delta);						//��� ĳ����
	virtual void resetPass(Ref *sender);							//ĳ���� ���ִ� �Լ�
	virtual void MoonCollPass(Ref *sender);							//ĳ���Ͱ� ���� �������� ĳ���� ����� �Լ�
	virtual bool onTouchBegan(Touch *touch, Event *unused_event);	//������ ĳ���� ����
	virtual void onTouchEnded(Touch *touch, Event *unused_event);	//ĳ���� ������ �巡�� ����
	virtual bool onContactBegin(PhysicsContact& contact);			//ĳ���Ͱ� ���� ��������

	virtual void update(float delta);

	void PandaSel();					//�Ǵ� �־����� ����Ʈ ���
	void SaebiSel(Node* node);			//���̺� �־����� ����Ʈ ���(node = ����ö��)
	
	int Nomal_count = 0;
	int Fat_count = 0;
	int Fat_Tcount = 0;
	int Speed_count = 0;
	int Panda_count = 0;
	int Saebi_count = 0;
	int Saebi_Tcount = 0;
	int Total_count = 0;
	//���ھ� ī��Ʈ ����
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void MusicLoad();						//���� �̸� �ε�

	CREATE_FUNC(MainScene);

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
	UILayer* uiLayer;
};

#endif // __HELLOWORLD_SCENE_H__
