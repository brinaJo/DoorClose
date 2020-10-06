#ifndef __GM_H__
#define __GM_H__

#include "cocos2d.h"


USING_NS_CC;

class GM : public cocos2d::Layer
{
private:
	static GM* instance;

	GM();		// 생성자.
	~GM() {};	// 소멸자.

public:
	
	bool Sound;				//사운드 출력할건가
	bool Effect;			//이펙트 사운드 출력할건가

	bool sound_on_off;		//사운드 on인지 off인지 체크
	bool isChaTouch;		//게임이 성공 or 실패 했을때 캐릭터 터치안되게 할 변수
	bool Stage;				//스테이지 버튼 눌렀는징

	int StageOne;
	int StageTwo;
	int StageThree;
	int StageFour;
	int StageFive;				//Stage마다 별 몇개 얻었ㄴ느징

	Vector<Sprite*> nPass;		//승객들 담아 놓는 벡터
	static GM* Getinstance();
};

#endif
