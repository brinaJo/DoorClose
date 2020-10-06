#pragma once
#include "cocos2d.h"
USING_NS_CC;
class Passenger : public cocos2d::Layer
{
private:
	int result;													//������ġ �����
	float TimePlus;												//�׶���ĳ���� 1~3�� �ε����� ���� �ð� ����
	void TagSpriteChange(int tag, Sprite* spr);					//�±׿����� �ε������� ��������Ʈ �ٲ��ִ� �Լ�
protected:
	Sprite* sprite = NULL;
	Animation* animation;
public:
	Size visibleSize;
	bool RL_Check;												//ĳ���Ͱ� ���������� ������ �������� ������

	Passenger();
	~Passenger();
	void PassAni();
	virtual int Passinit();										//ĳ���� ��ġ �������� ����
	virtual void PassRun();										//ĳ���� �����̴� �Լ�
	void PassCollision(cocos2d::Layer *layer, Sprite*, Point location,float delta);	//�Ϲݽ°��� ������ �°����� �ε������� ������ �°����� �����̴� �Լ�
	
	void ChaScore(cocos2d::Layer *layer, Node *sender);			//ĳ���� ���� +1 +3 -5 �ߴ� �Լ�
	void MoonCollPass(Ref *sender);								//ĳ���� ������� �Լ�
	void RemoveVec(Ref *sender);
};

class NomalPass : public Passenger								//�ݴް�(���)
{
public:
	NomalPass(){ }
	virtual void Passinit(cocos2d::Layer *layer);				//�ݴް�(���) ĳ���� ���� ����
	virtual void PassRun();										//��������Ʈ �ִϸ��̼�

	
	void NomalTouch(cocos2d::Sprite *m_nomal);					//�ݴް� ĳ���͸� ��ġ������  
};
class FatPass : public Passenger								//���
{
public:
	virtual void Passinit(cocos2d::Layer *layer);
	virtual void PassRun();
};
class SpeedPass : public Passenger								//�����Ҵ�
{
public:
	virtual void Passinit(cocos2d::Layer *layer);
	virtual void PassRun();
};
class PandaPass : public Passenger								//�Ǵ�
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
	virtual void PassRun();		//R������ �޸���
	void PassRun_BD();			//L������ ���� Ʋ��
};