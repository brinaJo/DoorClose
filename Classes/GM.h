#ifndef __GM_H__
#define __GM_H__

#include "cocos2d.h"


USING_NS_CC;

class GM : public cocos2d::Layer
{
private:
	static GM* instance;

	GM();		// ������.
	~GM() {};	// �Ҹ���.

public:
	
	bool Sound;				//���� ����Ұǰ�
	bool Effect;			//����Ʈ ���� ����Ұǰ�

	bool sound_on_off;		//���� on���� off���� üũ
	bool isChaTouch;		//������ ���� or ���� ������ ĳ���� ��ġ�ȵǰ� �� ����
	bool Stage;				//�������� ��ư ������¡

	int StageOne;
	int StageTwo;
	int StageThree;
	int StageFour;
	int StageFive;				//Stage���� �� � �������¡

	Vector<Sprite*> nPass;		//�°��� ��� ���� ����
	static GM* Getinstance();
};

#endif
