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
	//��ġ
	Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
	auto listener = EventListenerTouchOneByOne::create();	//��ġ ������������ ������
	listener->onTouchBegan = CC_CALLBACK_2(StageScene::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(StageScene::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);
	isTouchAble = true;
	//

	Size visibleSize = Director::getInstance()->getVisibleSize();//�̰� ���ϸ� ������ ����

	//��� �׸��� ����
	auto backGround = Sprite::create("images/playgame_back_1.png");
	backGround->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	backGround->setScaleY(2.4);
	this->addChild(backGround);

	MenuItemImage* itemArr[STAGE_CNT];

	Stageinit();		//UserDefault�� �ҷ���
	//////////////////////////////////////////////////////////////ó���� first���� �� ��Ȱ��ȭ
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
	/////////////////////////////////////////////////////////// �ش� �������� ���� 0 ���� ũ�� �״��� �������� Ȱ��ȭ
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
	}////////////////////////////////������������ �� ���


	for (int i = 0; i < STAGE_CNT; i++)	//���Ⱑ ���� ��ġ�ǵ���
	{
		itemArr[i] = MenuItemImage::create("ui/ui_map_circle.png", "ui/ui_map_circle.png", CC_CALLBACK_1(StageScene::changeScene, this));	//�䳢��
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


	//�޴��� ����Ѵ�
	//auto menu1 = Menu::create(itemArr[0], NULL);

	auto menu1 = Menu::create(itemArr[0], itemArr[1], itemArr[2], itemArr[3], itemArr[4], NULL);
	
	menu1->setTag(TAG_MENU1);
	menu1->setAnchorPoint(Point(0, 0.0));
	menu1->setPosition(Point::ZERO);
	this->addChild(menu1);

	//���� ����
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
//�޴��� �����Ѵ�
void StageScene::changeScene(Ref * sender)
{
	auto menuItem = (MenuItem*)sender; 

	Stageinit();
	switch (menuItem->getTag())	//��׵��� ���δ� ���� ȭ������ �����°ž�
	{
	case 0:	//�䳢
		Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
		Director::getInstance()->replaceScene(GameSceneA::createScene());
		break;
	case 1://���챼
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
	if (!isTouchAble) //isTouchAble�� true�� �ƴҶ� �� �����϶� ��ġ�� �ȵ� ��
		return true; //���� �׳� ���⼭ �� �̹����� ����

	Point pos = touch->getLocation();
	FirstDot = pos;

	CCLOG("Began x : %f / y: %f", pos.x, pos.y);
	return true;
}

void StageScene::onTouchEnded(Touch * touch, Event * event)
{
	Point pos = touch->getLocation();
	LastDot = pos;
	float Direc = 0;//�Ÿ�
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
	auto menu = this->getChildByTag(TAG_MENU1);//�� �޴´� �� ���� �±�

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
		CallFuncN::create(CC_CALLBACK_1(StageScene::SetTouchAble, this, false)), //SetTouchAble �Լ��� ȣ���ϴµ� sender�� menu�� isAble �� false
		MoveBy::create(0.3f, Point(dir, 0)), //������
		CallFuncN::create(CC_CALLBACK_1(StageScene::SetTouchAble, this, true)), //SetTouchAble �Լ��� ȣ���ϴµ� sender�� menu�� isAble �� true
		NULL
		));

	CCLOG("menuPos2 x = %f", menu->getPosition().x);
}

void StageScene::SetTouchAble(Ref* sender, bool isAble)
{
	isTouchAble = isAble; //isTouchAble�� isAble�� ���̸� ��ġ�ǰ� �����̸� ��ġ�� �ȵ�. �� �������� �ʴ´ٰ�.
}