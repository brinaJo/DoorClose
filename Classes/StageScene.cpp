#include "StageScene.h"
#include "TitleScene.h"
#include "GameSceneA.h"
#include "GameSceneB.h"
#include "GameSceneC.h"
#include "GameSceneD.h"
#include "GameSceneE.h"
#include "SetupScene.h"
#include "Definitions.h"
#include "SimpleAudioEngine.h"
#include "GM.h"

using namespace CocosDenshion;


Scene * StageScene::createScene()
{
	auto scene = Scene::create();
	auto layer = StageScene::create();
	scene->addChild(layer);
	return scene;

}
void StageScene::Stageinit()
{
	stage[0] = UserDefault::getInstance()->getIntegerForKey("STAGE1");
	stage[1] = UserDefault::getInstance()->getIntegerForKey("STAGE2");
	stage[2] = UserDefault::getInstance()->getIntegerForKey("STAGE3");
	stage[3] = UserDefault::getInstance()->getIntegerForKey("STAGE4");
	stage[4] = UserDefault::getInstance()->getIntegerForKey("STAGE5");
}
bool StageScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	//터치
	Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
	auto listener = EventListenerTouchOneByOne::create();	//터치 시작했을때랑 뗐을때
	listener->onTouchBegan = CC_CALLBACK_2(StageScene::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(StageScene::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);
	isTouchAble = true;
	//

	Size visibleSize = Director::getInstance()->getVisibleSize();//이거 안하면 검은거 나옴

	//배경 그림을 띄운다
	auto backGround = Sprite::create("images/playgame_back_1.png");
	backGround->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	backGround->setScaleY(2.4);
	this->addChild(backGround);

	MenuItemImage* itemArr[STAGE_CNT];

	Stageinit();		//UserDefault값 불러옴
	//////////////////////////////////////////////////////////////처음엔 first말구 다 비활성화
	spr[0] = Sprite::create("ui/ui_map_1_nomal.png");
	spr[1] = Sprite::create("ui/Ui_Map_2_nomal_not.png");
	spr[2] = Sprite::create("ui/Ui_Map_3_nomal_not.png");
	spr[3] = Sprite::create("ui/Ui_Map_4_nomal_not.png");
	spr[4] = Sprite::create("ui/Ui_Map_5_nomal_not.png");
	////////////////////////////////////////////////////////////
	if (stage[0] > 0)
		spr[1] = Sprite::create("ui/ui_map_2_nomal.png");
	if (stage[1] > 0)
		spr[2] = Sprite::create("ui/ui_map_3_nomal.png");
	if (stage[2] > 0)
		spr[3] = Sprite::create("ui/ui_map_4_nomal.png");
	if (stage[3] > 0)
		spr[4] = Sprite::create("ui/ui_map_5_nomal.png");
	/////////////////////////////////////////////////////////// 해당 스테이지 별이 0 보다 크면 그다음 스테이지 활성화
	for (int i = 3; i > 0; i--)
	{
		if (stage[0] == i)
			spr[0] = Sprite::create(StringUtils::format("ui/ui_map_1_star%d.png", i));
		if (stage[1] == i)
			spr[1] = Sprite::create(StringUtils::format("ui/ui_map_2_star%d.png", i));
		if (stage[2] == i)
			spr[2] = Sprite::create(StringUtils::format("ui/ui_map_3_star%d.png", i));
		if (stage[3] == i)
			spr[3] = Sprite::create(StringUtils::format("ui/ui_map_4_star%d.png", i));
		if (stage[4] == i)
			spr[4] = Sprite::create(StringUtils::format("ui/ui_map_5_star%d.png", i));
	}////////////////////////////////스테이지마다 별 출력


	for (int i = 0; i < STAGE_CNT; i++)	//여기가 원만 터치되도록
	{
		itemArr[i] = MenuItemImage::create("ui/ui_map_circle.png", "ui/ui_map_circle.png", CC_CALLBACK_1(StageScene::changeScene, this));	//토끼굴
		spr[i]->setTag(0);
		Size size = itemArr[i]->getContentSize();
		spr[i]->setPosition(size.width * 0.5f, size.height * 0.4f);
		itemArr[i]->addChild(spr[i]);
	}

	//itemArr[0]->setb

	//float width = 1280;
	for (int i = 0; i < STAGE_CNT; i++)
	{
		itemArr[i]->setAnchorPoint(Point(0.5, 0.5));
		itemArr[i]->setPosition(Point(visibleSize.width / 2 + (visibleSize.width * i), visibleSize.height * 0.55f));
		itemArr[i]->setTag(i);
	}


	//메뉴를 등록한다
	//auto menu1 = Menu::create(itemArr[0], NULL);

	auto menu1 = Menu::create(itemArr[0], itemArr[1], itemArr[2], itemArr[3], itemArr[4], NULL);
	
	menu1->setTag(TAG_MENU1);
	menu1->setAnchorPoint(Point(0, 0.0));
	menu1->setPosition(Point::ZERO);
	this->addChild(menu1);

	//설정 들어가기
	auto item5 = MenuItemImage::create("ui/ui_set_set.png", "ui/ui_set_set.png", CC_CALLBACK_1(StageScene::changeScene, this));
	auto item6 = MenuItemImage::create("ui/ui_set_cos.png", "ui/ui_set_cos.png", CC_CALLBACK_1(StageScene::changeScene, this));
	item5->setScale(0.75);
	item6->setScale(0.75);
	item5->setTag(5);

	auto menu2 = Menu::create(item6, item5, NULL);
	menu2->alignItemsHorizontallyWithPadding(30);
	menu2->setPosition(1180, 650);
	this->addChild(menu2);
	if (GM::Getinstance()->Sound == true && GM::Getinstance()->Effect == true)
	{
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sound/map.mp3", true);
	}

	return true;
}
//메뉴를 구현한다
void StageScene::changeScene(Ref * sender)
{
	auto menuItem = (MenuItem*)sender; 

	Stageinit();
	switch (menuItem->getTag())	//얘네들은 전부다 게임 화면으로 보내는거야
	{
	case 0:	//토끼
		Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
		Director::getInstance()->replaceScene(GameSceneA::createScene());
		break;
	case 1://여우굴
		if (stage[0] < 1)
			break;
		else
		{
			Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
			Director::getInstance()->replaceScene(GameSceneB::createScene());
		}
		break;
	case 2:
		if (stage[1] < 1)
			break;
		else
		{
			Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
			Director::getInstance()->replaceScene(GameSceneC::createScene());
		}
		break;
	case 3:
		if (stage[2]< 1)
			break;
		else
		{
			Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
			Director::getInstance()->replaceScene(GameSceneD::createScene());
		}
		break;
	case 4:
		if (stage[3] < 1)
			break;
		else
		{
			Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
			Director::getInstance()->replaceScene(GameSceneE::createScene());
		}
		break;
	case 5:
		GM::Getinstance()->Stage = true;
		Director::getInstance()->replaceScene(SetupScene::createScene());
		break;
	default:
		break;
	}
}

bool StageScene::onTouchBegan(Touch * touch, Event * event)
{
	if (!isTouchAble) //isTouchAble이 true가 아닐때 즉 거짓일때 터치가 안될 때
		return true; //리턴 그냥 여기서 끝 이밑으로 안함

	Point pos = touch->getLocation();
	FirstDot = pos;

	CCLOG("Began x : %f / y: %f", pos.x, pos.y);
	return true;
}

void StageScene::onTouchEnded(Touch * touch, Event * event)
{
	Point pos = touch->getLocation();
	LastDot = pos;
	float Direc = 0;//거리
	Direc = FirstDot.x - LastDot.x;
	if (Direc >= 200)
	{
		CCLOG("left");
		MoveMenu(true);

	}
	if (Direc <= -200)
	{
		CCLOG("right");
		MoveMenu(false);
	}


	//CCLOG("Ended x : %f / y: %f", pos.x, pos.y);
	CCLOG("dis = %f", Direc);
}

void StageScene::MoveMenu(bool isMoveLeft)
{
	auto menu = this->getChildByTag(TAG_MENU1);//나 받는다 내 아이 태그

											   //action = Node?
	float x = menu->getPosition().x;
	CCLOG("menuPos1 x = %f", menu->getPosition().x);
	float dir;
	if (isMoveLeft)
	{
		if (x <= -((STAGE_CNT - 1) * 1280))
			return;
		else
			dir = -1280;
	}
	else
	{
		if (x >= 0)
			return;
		else
			dir = 1280;
	}

	menu->runAction(Sequence::create(
		CallFuncN::create(CC_CALLBACK_1(StageScene::SetTouchAble, this, false)), //SetTouchAble 함수를 호출하는데 sender는 menu고 isAble 은 false
		MoveBy::create(0.3f, Point(dir, 0)), //움직여
		CallFuncN::create(CC_CALLBACK_1(StageScene::SetTouchAble, this, true)), //SetTouchAble 함수를 호출하는데 sender는 menu고 isAble 은 true
		NULL
		));

	CCLOG("menuPos2 x = %f", menu->getPosition().x);
}

void StageScene::SetTouchAble(Ref* sender, bool isAble)
{
	isTouchAble = isAble; //isTouchAble을 isAble로 참이면 터치되고 거짓이면 터치가 안됨. 즉 움직이질 않는다고.
}