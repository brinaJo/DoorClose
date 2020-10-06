#include "UILayer.h"
#include "TitleScene.h"
#include "StageScene.h"
#include "GameSceneA.h"
#include "GameSceneB.h"
#include "GameSceneC.h"
#include "GameSceneD.h"
#include "GameSceneE.h"
#include "Definitions.h"
#include "CountDefinitions.h"
#include "SimpleAudioEngine.h"
#include "GM.h"

using namespace CocosDenshion;

bool UILayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();

	
	return true;
}

void UILayer::changeScene(Ref* sender)
{
	auto menuItem = (MenuItem*)sender;
	Director::getInstance()->replaceScene(StageScene::createScene());
	GM::Getinstance()->isChaTouch = true;
	GM::Getinstance()->nPass.clear();
	switch (menuItem->getTag())
	{
	case TAG_MAIN:
	{
		Director::getInstance()->replaceScene(StageScene::createScene());
	}
		break;
	case TAG_REPLAY:
	{
		Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
		switch (stage)
		{
		case 1:
			Director::getInstance()->replaceScene(GameSceneA::createScene());
			break;
		case 2:
			Director::getInstance()->replaceScene(GameSceneB::createScene());
			break;
		case 3:
			Director::getInstance()->replaceScene(GameSceneC::createScene());
			break;
		case 4:
			Director::getInstance()->replaceScene(GameSceneD::createScene());
			break;
		case 5:
			Director::getInstance()->replaceScene(GameSceneE::createScene());
			break;
		default:
			break;
		}
	}
	default:
		break;
		//break;
	}
}

void UILayer::initUI(int stage)
{
	this->stage = stage;

	limitTime = 45;
	
	auto time = Sprite::create("ui/ui_play_time.png");
	time->setAnchorPoint(Point(1, 1));
	time->setPosition(Point(visibleSize.width * 0.98, visibleSize.height * 0.98));
	this->addChild(time);

	Size timeSize = time->getContentSize();

	timeLabel = Label::createWithCharMap("ui/ui_time_num_big.png", 38, 46, '0');
	timeLabel->setPosition(Point(timeSize.width * 0.5, timeSize.height * 0.55));
	timeLabel->setTag(TAG_LABEL_LIMIT_TIME);
	timeLabel->setString("45");
	time->addChild(timeLabel);

	schedule(schedule_selector(UILayer::CalcPlayTime), 1);

	switch (stage)
	{
	case GAMESCENEA:
	{
		auto pass = Sprite::create("ui/ui_quest_nomal.png");
		pass->setAnchorPoint(Point(0, 1));
		pass->setScale(0.98);
		pass->setPosition(Point(visibleSize.width*0.02, visibleSize.height * 0.98));
		this->addChild(pass);

		auto All = Sprite::create("ui/ui_quest_1.png");
		All->setAnchorPoint(Point(0, 1));
		All->setPosition(Point(visibleSize.width*0.20, visibleSize.height*0.98));
		this->addChild(All);
		initCountUIA();
	}
		break;
	case GAMESCENEB:
	{
		auto pass = Sprite::create("ui/ui_quest_nomal.png");
		pass->setAnchorPoint(Point(0, 1));
		pass->setScale(0.98);
		pass->setPosition(Point(visibleSize.width*0.02, visibleSize.height * 0.98));
		this->addChild(pass);

		auto All = Sprite::create("ui/ui_quest_1.png");
		All->setAnchorPoint(Point(0, 1));
		All->setPosition(Point(visibleSize.width*0.20, visibleSize.height*0.98));
		this->addChild(All);
		initCountUIB();
	}
		break;
	case GAMESCENEC:
	{
		auto pass = Sprite::create("ui/ui_quest_nomal.png");
		pass->setAnchorPoint(Point(0, 1));
		pass->setScale(0.98);
		pass->setPosition(Point(visibleSize.width*0.02, visibleSize.height * 0.98));
		this->addChild(pass);

		auto All = Sprite::create("ui/ui_quest_3.png");
		All->setAnchorPoint(Point(0, 1));
		All->setPosition(Point(visibleSize.width*0.20, visibleSize.height*0.98));
		this->addChild(All);

		initCountUIC();
	}
		break;
	case GAMESCENED:
	{
		auto pass = Sprite::create("ui/ui_quest_nomal.png");
		pass->setAnchorPoint(Point(0, 1));
		pass->setScale(0.98);
		pass->setPosition(Point(visibleSize.width*0.02, visibleSize.height * 0.98));
		this->addChild(pass);

		auto All = Sprite::create("ui/ui_quest_4.png");
		All->setAnchorPoint(Point(0, 1));
		All->setPosition(Point(visibleSize.width*0.20, visibleSize.height*0.98));
		this->addChild(All);

		initCountUID();
	}
		break;
	case GAMESCENEE:
	{
		auto pass = Sprite::create("ui/ui_quest_nomal.png");
		pass->setAnchorPoint(Point(0, 1));
		pass->setScale(0.98);
		pass->setPosition(Point(visibleSize.width*0.02, visibleSize.height * 0.98));
		this->addChild(pass);

		auto All = Sprite::create("ui/ui_quest_5.png");
		All->setAnchorPoint(Point(0, 1));
		All->setPosition(Point(visibleSize.width*0.20, visibleSize.height*0.98));
		this->addChild(All);

		initCountUIE();
	}
		break;
	default:
		break;
	}
	
	////돌아가기 메뉴 아이템을 만든다
	//auto item1 = MenuItemImage::create("UI/Ui_Title_Exit.png", "UI/Ui_Title_Exit.png", CC_CALLBACK_1(UILayer::changeScene, this));

	////돌아가기 메뉴를 등록한다
	//auto menu = Menu::create(item1, NULL);
	//menu->alignItemsHorizontallyWithPadding(-10);
	//menu->setPosition(visibleSize.width / 2, 180);
	//this->addChild(menu);

}
void UILayer::StageAndStar(int _Star)
{
	for (int i = 0; i <= 3; i++)
	{
		if (stage == 1 && _Star == i)
		{
			GM::Getinstance()->StageOne = _Star;
			int a = UserDefault::getInstance()->getInstance()->getIntegerForKey("STAGE1");
			if (a < _Star)
				UserDefault::getInstance()->setIntegerForKey("STAGE1", GM::Getinstance()->StageOne);
		}
		else if (stage == 2 && _Star == i)
		{
			GM::Getinstance()->StageTwo = _Star;
			int a = UserDefault::getInstance()->getInstance()->getIntegerForKey("STAGE2");
			if (a < _Star)
				UserDefault::getInstance()->setIntegerForKey("STAGE2", GM::Getinstance()->StageTwo);
		}
		else if (stage == 3 && _Star == i)
		{
			GM::Getinstance()->StageThree = _Star;
			int a = UserDefault::getInstance()->getInstance()->getIntegerForKey("STAGE3");
			if (a < _Star)
				UserDefault::getInstance()->setIntegerForKey("STAGE3", GM::Getinstance()->StageThree);
		}
		else if (stage == 4 && _Star == i)
		{
			GM::Getinstance()->StageFour = _Star;
			int a = UserDefault::getInstance()->getInstance()->getIntegerForKey("STAGE4");
			if (a < _Star)
				UserDefault::getInstance()->setIntegerForKey("STAGE4", GM::Getinstance()->StageFour);
		}
		else if (stage == 5 && _Star == i)
		{
			GM::Getinstance()->StageFive = _Star;
			int a = UserDefault::getInstance()->getInstance()->getIntegerForKey("STAGE5");
			if (a < _Star)
				UserDefault::getInstance()->setIntegerForKey("STAGE5", GM::Getinstance()->StageFive);
		}
	}
	UserDefault::getInstance()->flush();
}
void UILayer::Success(int star)
{
	//Director::getInstance()->pause();	//멈추는 함수

	unscheduleAllSelectors();

	GM::Getinstance()->isChaTouch = false;
	auto Black = Sprite::create("images/Playgame_back2_BL.png");
	Black->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2 + 50));
	this->addChild(Black);
	auto Success = Sprite::create();
	if (star == 1)
	{
		Success = Sprite::create("ui/ui_success_star1.png");
	}
	else if (star == 2)
	{
		Success = Sprite::create("ui/ui_success_star2.png");
	}
	else if (star == 3)
	{
		Success = Sprite::create("ui/ui_success_star3.png");
	}
	StageAndStar(star);

	Success->setAnchorPoint(Point(0.5, 0.5));
	Success->setPosition(Point(visibleSize.width / 2, visibleSize.height / 1.75));
	this->addChild(Success);

	auto M_Success = MenuItemImage::create("ui/ui_success_main.png", "ui/ui_success_main_touch.png", CC_CALLBACK_1(UILayer::changeScene, this));
	auto M_Re = MenuItemImage::create("ui/ui_success_replay.png", "ui/ui_success_replay_touch.png", CC_CALLBACK_1(UILayer::changeScene, this));

	M_Success->setTag(TAG_MAIN);
	M_Re->setTag(TAG_REPLAY);

	auto Menu = Menu::create(M_Success, M_Re, NULL);
	Menu->alignItemsHorizontallyWithPadding(22);
	Menu->setPosition(Point(visibleSize.width / 2, visibleSize.height / 6.5));
	this->addChild(Menu);
	//Director::getInstance()->resume();
}
void UILayer::Fail()
{
	unscheduleAllSelectors();
	GM::Getinstance()->isChaTouch = false;
	auto Black = Sprite::create("images/Playgame_back2_BL.png");
	Black->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2 + 50));
	this->addChild(Black);

	auto Fail = Sprite::create("ui/ui_fail.png");
	Fail->setAnchorPoint(Point(0.5, 0.5));
	Fail->setPosition(Point(visibleSize.width / 2, visibleSize.height / 1.75));

	this->addChild(Fail);
	StageAndStar(0);
	auto F_Main = MenuItemImage::create("ui/ui_fail_main.png", "ui/ui_fail_main.png", CC_CALLBACK_1(UILayer::changeScene, this));
	auto F_Re = MenuItemImage::create("ui/ui_fail_replay.png", "ui/ui_fail_replay.png", CC_CALLBACK_1(UILayer::changeScene, this));

	F_Main->setTag(TAG_MAIN);
	F_Re->setTag(TAG_REPLAY);

	auto Menu = Menu::create(F_Main, F_Re, NULL);
	Menu->alignItemsHorizontallyWithPadding(22);
	Menu->setPosition(Point(visibleSize.width / 2, visibleSize.height / 6.5));
	this->addChild(Menu);
}
void UILayer::CalcPlayTime(float dt)	//시간 흐르는 함수
{
	limitTime -= 1;
	timeLabel->setString(StringUtils::format("%02d", limitTime));
	if (isThreestar == true && limitTime <= 0)
		Success(3);
	else if (isTwostar == true && limitTime <= 0)
		Success(2);
	else if ((To_count <= 0 ) && limitTime <= 0)
		Success(1);
	else if (limitTime <= 0)
		Fail();
}

void UILayer::initCountUIA()
{
	///////////////////////////별한개//////////////////////////////////
	auto Label = Label::createWithCharMap("ui/ui_que_num.png", 21, 21, '0');
	Label->setAnchorPoint(Point(0.5, 0.5));
	Label->setScale(1.2);
	Label->setPosition(Point(160, visibleSize.height - 49));
	Label->setTag(TAG_LABEL_TOTAL_COUNT);
	Label->setString(StringUtils::format("%02d", STAGE_A_TOTAL_PASS));
	this->addChild(Label);
	//////////////////////////통합///////////////////////
	auto N3_Label = Label::createWithCharMap("ui/ui_que_num.png", 21, 21, '0');
	N3_Label->setAnchorPoint(Point(0.5, 0.5));
	N3_Label->setPosition(Point(410, visibleSize.height - 49));
	N3_Label->setScale(1.2);
	N3_Label->setTag(TAG_LABEL_THREE_NOMAL);
	N3_Label->setString(StringUtils::format("%02d", STAGE_A_THREESTAR_NOMAL));
	this->addChild(N3_Label);

	auto S3_Label = Label::createWithCharMap("ui/ui_que_num.png", 21, 21, '0');
	S3_Label->setAnchorPoint(Point(0.5, 0.5));
	S3_Label->setPosition(Point(510, visibleSize.height - 49));
	S3_Label->setScale(1.2);
	S3_Label->setTag(TAG_LABEL_THREE_SPEED);
	S3_Label->setString(StringUtils::format("%02d", STAGE_A_THREESTAR_SPEED));
	this->addChild(S3_Label);


	auto F3_Label = Label::createWithCharMap("ui/ui_que_num.png", 21, 21, '0');
	F3_Label->setAnchorPoint(Point(0.5, 0.5));
	F3_Label->setPosition(Point(615, visibleSize.height - 49));
	F3_Label->setScale(1.2);
	F3_Label->setTag(TAG_LABEL_THREE_FAT);
	F3_Label->setString(StringUtils::format("%02d", STAGE_A_THREESTAR_FAT));
	this->addChild(F3_Label);


}
void UILayer::initPassCountA(int Total_Count, int Nomal_Count, int Fat_count, int Speed_count, int Panda_count, int Saebi_count)
{
	///////////////////////////별한개//////////////////////////////////
	auto t_Label = (Label*)this->getChildByTag(TAG_LABEL_TOTAL_COUNT);
	To_count = STAGE_A_TOTAL_PASS - Total_Count;
	if (To_count <= 0) To_count = 0;
	t_Label->setString(StringUtils::format("%02d", To_count));
	
	////////////////////////////////별두개///////////////////////////////
	Nm_count = STAGE_A_TWOSTAR_NOMAL - Nomal_Count;
	if (Nm_count <= 0) Nm_count = 0;

	Sed_count = STAGE_A_TWOSTAR_SPEED - Speed_count;
	if (Sed_count <= 0) Sed_count = 0;

	if ((To_count <= 0) && (Nm_count <= 0) && (Sed_count <= 0))
		isTwostar = true;
	else
		isTwostar = false;
	////////////////////////////별세개////////////////////////////////////////
	auto N3_Label = (Label*)this->getChildByTag(TAG_LABEL_THREE_NOMAL);
	Nm3_count = STAGE_A_THREESTAR_NOMAL - Nomal_Count;
	if (Nm3_count <= 0) Nm3_count = 0;
	N3_Label->setString(StringUtils::format("%02d", Nm3_count));
	//
	auto S3_Label = (Label*)this->getChildByTag(TAG_LABEL_THREE_SPEED);
	Sed3_count = STAGE_A_THREESTAR_SPEED - Speed_count;
	if (Sed3_count <= 0) Sed3_count = 0;
	S3_Label->setString(StringUtils::format("%02d", Sed3_count));
	//
	auto F3_Label = (Label*)this->getChildByTag(TAG_LABEL_THREE_FAT);
	Ft3_count = STAGE_A_THREESTAR_FAT - Fat_count;
	if (Ft3_count <= 0) Ft3_count = 0;
	F3_Label->setString(StringUtils::format("%02d", Ft3_count));

	if ((To_count <= 0) && (Nm3_count <= 0) && (Sed3_count <= 0) && (Ft3_count <= 0))
		isThreestar = true;
	else
		isThreestar = false;
}

void UILayer::initCountUIB()
{
	///////////////////////////별한개//////////////////////////////////
	auto Label = Label::createWithCharMap("ui/ui_que_num.png", 21, 21, '0');
	Label->setAnchorPoint(Point(0.5, 0.5));
	Label->setScale(1.2);
	Label->setPosition(Point(160, visibleSize.height - 49));
	Label->setTag(TAG_LABEL_TOTAL_COUNT);
	Label->setString(StringUtils::format("%02d", STAGE_B_TOTAL_PASS));
	this->addChild(Label);

	////////////////////////////////통합///////////////////////////////
	auto N3_Label = Label::createWithCharMap("ui/ui_que_num.png", 21, 21, '0');
	N3_Label->setAnchorPoint(Point(0.5, 0.5));
	N3_Label->setPosition(Point(410, visibleSize.height - 49));
	N3_Label->setScale(1.2);
	N3_Label->setTag(TAG_LABEL_THREE_NOMAL);
	N3_Label->setString(StringUtils::format("%02d", STAGE_B_THREESTAR_NOMAL));
	this->addChild(N3_Label);

	auto S3_Label = Label::createWithCharMap("ui/ui_que_num.png", 21, 21, '0');
	S3_Label->setAnchorPoint(Point(0.5, 0.5));
	S3_Label->setPosition(Point(510, visibleSize.height - 49));
	S3_Label->setScale(1.2);
	S3_Label->setTag(TAG_LABEL_THREE_SPEED);
	S3_Label->setString(StringUtils::format("%02d", STAGE_B_THREESTAR_SPEED));
	this->addChild(S3_Label);


	auto F3_Label = Label::createWithCharMap("ui/ui_que_num.png", 21, 21, '0');
	F3_Label->setAnchorPoint(Point(0.5, 0.5));
	F3_Label->setPosition(Point(615, visibleSize.height - 49));
	F3_Label->setScale(1.2);
	F3_Label->setTag(TAG_LABEL_THREE_FAT);
	F3_Label->setString(StringUtils::format("%02d", STAGE_B_THREESTAR_FAT));
	this->addChild(F3_Label);
}
void UILayer::initPassCountB(int Total_Count, int Nomal_Count, int Fat_count, int Speed_count, int Panda_count, int Saebi_count)
{
	///////////////////////////별한개//////////////////////////////////
	auto t_Label = (Label*)this->getChildByTag(TAG_LABEL_TOTAL_COUNT);
	To_count = STAGE_B_TOTAL_PASS - Total_Count;
	if (To_count <= 0) To_count = 0;
	t_Label->setString(StringUtils::format("%02d", To_count));

	////////////////////////////////별두개///////////////////////////////
	Nm_count = STAGE_B_TWOSTAR_NOMAL - Nomal_Count;
	if (Nm_count <= 0) Nm_count = 0;

	Sed_count = STAGE_B_TWOSTAR_SPEED - Speed_count;
	if (Sed_count <= 0) Sed_count = 0;

	if ((To_count <= 0) && (Nm_count <= 0) && (Sed_count <= 0))
		isTwostar = true;
	else
		isTwostar = false;
	////////////////////////////별세개////////////////////////////////////////
	auto N3_Label = (Label*)this->getChildByTag(TAG_LABEL_THREE_NOMAL);
	Nm3_count = STAGE_B_THREESTAR_NOMAL - Nomal_Count;
	if (Nm3_count <= 0) Nm3_count = 0;
	N3_Label->setString(StringUtils::format("%02d", Nm3_count));
	//
	auto S3_Label = (Label*)this->getChildByTag(TAG_LABEL_THREE_SPEED);
	Sed3_count = STAGE_B_THREESTAR_SPEED - Speed_count;
	if (Sed3_count <= 0) Sed3_count = 0;
	S3_Label->setString(StringUtils::format("%02d", Sed3_count));
	//

	auto F3_Label = (Label*)this->getChildByTag(TAG_LABEL_THREE_FAT);
	Ft3_count = STAGE_B_THREESTAR_FAT - Fat_count;
	if (Ft3_count <= 0) Ft3_count = 0;
	F3_Label->setString(StringUtils::format("%02d", Ft3_count));
	
	if ((To_count <= 0) && (Nm3_count <= 0) && (Sed3_count <= 0) && (Ft3_count <= 0))
		isThreestar = true;
	else
		isThreestar = false;
}

void UILayer::initCountUIC()
{
	///////////////////////////별한개//////////////////////////////////
	auto Label = Label::createWithCharMap("ui/ui_que_num.png", 21, 21, '0');
	Label->setAnchorPoint(Point(0.5, 0.5));
	Label->setScale(1.2);
	Label->setPosition(Point(160, visibleSize.height - 49));
	Label->setTag(TAG_LABEL_TOTAL_COUNT);
	Label->setString(StringUtils::format("%02d", STAGE_C_TOTAL_PASS));
	this->addChild(Label);
	////////////////////////////////통합///////////////////////////////
	auto N2_Label = Label::createWithCharMap("ui/ui_que_num.png", 21, 21, '0');
	N2_Label->setAnchorPoint(Point(0.5, 0.5));
	N2_Label->setScale(1.2);
	N2_Label->setPosition(Point(418, visibleSize.height - 50));
	N2_Label->setTag(TAG_LABEL_THREE_NOMAL);
	N2_Label->setString(StringUtils::format("%02d", STAGE_C_THREESTAR_NOMAL));
	this->addChild(N2_Label);

	auto S2_Label = Label::createWithCharMap("ui/ui_que_num.png", 21, 21, '0');
	S2_Label->setAnchorPoint(Point(0.5, 0.5));
	S2_Label->setScale(1.2);
	S2_Label->setPosition(Point(523, visibleSize.height - 50));
	S2_Label->setTag(TAG_LABEL_THREE_SPEED);
	S2_Label->setString(StringUtils::format("%02d", STAGE_C_THREESTAR_SPEED));
	this->addChild(S2_Label);

	auto F2_Label = Label::createWithCharMap("ui/ui_que_num.png", 21, 21, '0');
	F2_Label->setAnchorPoint(Point(0.5, 0.5));
	F2_Label->setScale(1.2);
	F2_Label->setPosition(Point(625, visibleSize.height - 50));
	F2_Label->setTag(TAG_LABEL_THREE_FAT);
	F2_Label->setString(StringUtils::format("%02d", STAGE_C_THREESTAR_FAT));
	this->addChild(F2_Label);

	auto P2_Label = Label::createWithCharMap("ui/ui_que_num.png", 21, 21, '0');
	P2_Label->setAnchorPoint(Point(0.5, 0.5));
	P2_Label->setScale(1.2);
	P2_Label->setPosition(Point(740, visibleSize.height - 50));
	P2_Label->setTag(TAG_LABEL_THREE_PANDA);
	P2_Label->setString(StringUtils::format("%02d", STAGE_C_THREESTAR_PANDA));
	this->addChild(P2_Label);
}
void UILayer::initPassCountC(int Total_Count, int Nomal_Count, int Fat_count, int Speed_count, int Panda_count, int Saebi_count)
{
	///////////////////////////별한개//////////////////////////////////
	auto t_Label = (Label*)this->getChildByTag(TAG_LABEL_TOTAL_COUNT);
	To_count = STAGE_C_TOTAL_PASS - Total_Count;
	if (To_count <= 0) To_count = 0;
	t_Label->setString(StringUtils::format("%02d", To_count));
	////////////////////////////////별두개///////////////////////////////
	Nm_count = STAGE_C_TWOSTAR_NOMAL - Nomal_Count;
	if (Nm_count <= 0) Nm_count = 0;

	Sed_count = STAGE_C_TWOSTAR_SPEED - Speed_count;
	if (Sed_count <= 0) Sed_count = 0;

	Ft_count = STAGE_C_TWOSTAR_FAT - Fat_count;
	if (Ft_count <= 0) Ft_count = 0;

	if ((To_count <= 0) && (Nm_count <= 0) && (Sed_count <= 0) && (Ft_count <= 0))
		isTwostar = true;
	else
		isTwostar = false;
	////////////////////////////별세개////////////////////////////////////////
	auto N3_Label = (Label*)this->getChildByTag(TAG_LABEL_THREE_NOMAL);
	Nm3_count = STAGE_C_THREESTAR_NOMAL - Nomal_Count;
	if (Nm3_count <= 0) Nm3_count = 0;
	N3_Label->setString(StringUtils::format("%02d", Nm3_count));
	//
	auto S3_Label = (Label*)this->getChildByTag(TAG_LABEL_THREE_SPEED);
	Sed3_count = STAGE_C_THREESTAR_SPEED - Speed_count;
	if (Sed3_count <= 0) Sed3_count = 0;
	S3_Label->setString(StringUtils::format("%02d", Sed3_count));
	//

	auto F3_Label = (Label*)this->getChildByTag(TAG_LABEL_THREE_FAT);
	Ft3_count = STAGE_C_THREESTAR_FAT - Fat_count;
	if (Ft3_count <= 0) Ft3_count = 0;
	F3_Label->setString(StringUtils::format("%02d", Ft3_count));

	auto P3_Label = (Label*)this->getChildByTag(TAG_LABEL_THREE_PANDA);
	Pd_count = STAGE_C_THREESTAR_PANDA - Panda_count;
	if (Pd_count <= 0) Pd_count = 0;
	P3_Label->setString(StringUtils::format("%02d", Pd_count));

	if ((To_count <= 0) && (Nm3_count <= 0) && (Sed3_count <= 0) && (Ft3_count <= 0) && (Pd_count <= 0))
		isThreestar = true;
	else
		isThreestar = false;
}
void UILayer::initCountUID()
{
	///////////////////////////별한개//////////////////////////////////
	
	auto Label = Label::createWithCharMap("ui/ui_que_num.png", 21, 21, '0');
	Label->setAnchorPoint(Point(0.5, 0.5));
	Label->setScale(1.2);
	Label->setPosition(Point(160, visibleSize.height - 49));
	Label->setTag(TAG_LABEL_TOTAL_COUNT);
	Label->setString(StringUtils::format("%02d", STAGE_D_TOTAL_PASS));
	this->addChild(Label);

	////////////////////////////////통합///////////////////////////////
	auto N2_Label = Label::createWithCharMap("ui/ui_que_num.png", 21, 21, '0');
	N2_Label->setAnchorPoint(Point(0.5, 0.5));
	N2_Label->setScale(1.2);
	N2_Label->setPosition(Point(418, visibleSize.height - 50));
	N2_Label->setTag(TAG_LABEL_THREE_NOMAL);
	N2_Label->setString(StringUtils::format("%02d", STAGE_D_THREESTAR_NOMAL));
	this->addChild(N2_Label);

	auto S2_Label = Label::createWithCharMap("ui/ui_que_num.png", 21, 21, '0');
	S2_Label->setAnchorPoint(Point(0.5, 0.5));
	S2_Label->setScale(1.2);
	S2_Label->setPosition(Point(523, visibleSize.height - 50));
	S2_Label->setTag(TAG_LABEL_THREE_SPEED);
	S2_Label->setString(StringUtils::format("%02d", STAGE_D_THREESTAR_SPEED));
	this->addChild(S2_Label);

	auto F2_Label = Label::createWithCharMap("ui/ui_que_num.png", 21, 21, '0');
	F2_Label->setAnchorPoint(Point(0.5, 0.5));
	F2_Label->setScale(1.2);
	F2_Label->setPosition(Point(625, visibleSize.height - 50));
	F2_Label->setTag(TAG_LABEL_THREE_FAT);
	F2_Label->setString(StringUtils::format("%02d", STAGE_D_THREESTAR_FAT));
	this->addChild(F2_Label);

	auto Sb3_Label = Label::createWithCharMap("ui/ui_que_num.png", 21, 21, '0');
	Sb3_Label->setAnchorPoint(Point(0.5, 0.5));
	Sb3_Label->setScale(1.2);
	Sb3_Label->setPosition(Point(740, visibleSize.height - 50));
	Sb3_Label->setTag(TAG_LABEL_THREE_SAEBI);
	Sb3_Label->setString(StringUtils::format("%02d", STAGE_D_THREESTAR_SAEBI));
	this->addChild(Sb3_Label);
}
void UILayer::initPassCountD(int Total_Count, int Nomal_Count, int Fat_count, int Speed_count, int Panda_count, int Saebi_count)
{
	///////////////////////////별한개//////////////////////////////////
	auto t_Label = (Label*)this->getChildByTag(TAG_LABEL_TOTAL_COUNT);
	To_count = STAGE_D_TOTAL_PASS - Total_Count;
	if (To_count <= 0) To_count = 0;
	t_Label->setString(StringUtils::format("%02d", To_count));
	////////////////////////////////별두개///////////////////////////////
	Nm_count = STAGE_D_TWOSTAR_NOMAL - Nomal_Count;
	if (Nm_count <= 0) Nm_count = 0;

	Sed_count = STAGE_D_TWOSTAR_SPEED - Speed_count;
	if (Sed_count <= 0) Sed_count = 0;

	Ft_count = STAGE_D_TWOSTAR_FAT - Fat_count;
	if (Ft_count <= 0) Ft_count = 0;

	if ((To_count <= 0) && (Nm_count <= 0) && (Sed_count <= 0) && (Ft_count <= 0))
		isTwostar = true;
	else
		isTwostar = false;
	////////////////////////////별세개////////////////////////////////////////
	auto N3_Label = (Label*)this->getChildByTag(TAG_LABEL_THREE_NOMAL);
	Nm3_count = STAGE_D_THREESTAR_NOMAL - Nomal_Count;
	if (Nm3_count <= 0) Nm3_count = 0;
	N3_Label->setString(StringUtils::format("%02d", Nm3_count));
	//
	auto S3_Label = (Label*)this->getChildByTag(TAG_LABEL_THREE_SPEED);
	Sed3_count = STAGE_D_THREESTAR_SPEED - Speed_count;
	if (Sed3_count <= 0) Sed3_count = 0;
	S3_Label->setString(StringUtils::format("%02d", Sed3_count));
	//

	auto F3_Label = (Label*)this->getChildByTag(TAG_LABEL_THREE_FAT);
	Ft3_count = STAGE_D_THREESTAR_FAT - Fat_count;
	if (Ft3_count <= 0) Ft3_count = 0;
	F3_Label->setString(StringUtils::format("%02d", Ft3_count));

	auto Sb3_Label = (Label*)this->getChildByTag(TAG_LABEL_THREE_SAEBI);
	Sb_count = STAGE_D_THREESTAR_SAEBI - Saebi_count;
	if (Sb_count <= 0) Sb_count = 0;
	Sb3_Label->setString(StringUtils::format("%02d", Sb_count));

	if ((To_count <= 0) && (Nm3_count <= 0) && (Sed3_count <= 0) && (Ft3_count <= 0) && (Sb_count <= 0))
		isThreestar = true;
	else
		isThreestar = false;
}
void UILayer::initCountUIE()
{
	///////////////////////////별한개//////////////////////////////////
	auto Label = Label::createWithCharMap("ui/ui_que_num.png", 21, 21, '0');
	Label->setAnchorPoint(Point(0.5, 0.5));
	Label->setScale(1.2);
	Label->setPosition(Point(160, visibleSize.height - 49));
	Label->setTag(TAG_LABEL_TOTAL_COUNT);
	Label->setString(StringUtils::format("%02d", STAGE_E_TOTAL_PASS));
	this->addChild(Label);

	////////////////////////////////통합///////////////////////////////
	auto N2_Label = Label::createWithCharMap("ui/ui_que_num.png", 21, 21, '0');
	N2_Label->setAnchorPoint(Point(0.5, 0.5));
	N2_Label->setScale(1.2);
	N2_Label->setPosition(Point(418, visibleSize.height - 50));
	N2_Label->setTag(TAG_LABEL_THREE_NOMAL);
	N2_Label->setString(StringUtils::format("%02d", STAGE_E_THREESTAR_NOMAL));
	this->addChild(N2_Label);

	auto S2_Label = Label::createWithCharMap("ui/ui_que_num.png", 21, 21, '0');
	S2_Label->setAnchorPoint(Point(0.5, 0.5));
	S2_Label->setScale(1.2);
	S2_Label->setPosition(Point(523, visibleSize.height - 50));
	S2_Label->setTag(TAG_LABEL_THREE_SPEED);
	S2_Label->setString(StringUtils::format("%02d", STAGE_E_THREESTAR_SPEED));
	this->addChild(S2_Label);

	auto F2_Label = Label::createWithCharMap("ui/ui_que_num.png", 21, 21, '0');
	F2_Label->setAnchorPoint(Point(0.5, 0.5));
	F2_Label->setScale(1.2);
	F2_Label->setPosition(Point(625, visibleSize.height - 50));
	F2_Label->setTag(TAG_LABEL_THREE_FAT);
	F2_Label->setString(StringUtils::format("%02d", STAGE_E_THREESTAR_FAT));
	this->addChild(F2_Label);

	auto P2_Label = Label::createWithCharMap("ui/ui_que_num.png", 21, 21, '0');
	P2_Label->setAnchorPoint(Point(0.5, 0.5));
	P2_Label->setScale(1.2);
	P2_Label->setPosition(Point(745, visibleSize.height - 50));
	P2_Label->setTag(TAG_LABEL_THREE_PANDA);
	P2_Label->setString(StringUtils::format("%02d", STAGE_E_THREESTAR_PANDA));
	this->addChild(P2_Label);

	auto S1_Label = Label::createWithCharMap("ui/ui_que_num.png", 21, 21, '0');
	S1_Label->setAnchorPoint(Point(0.5, 0.5));
	S1_Label->setScale(1.2);
	S1_Label->setPosition(Point(878, visibleSize.height - 50));
	S1_Label->setTag(TAG_LABEL_THREE_SAEBI);
	S1_Label->setString(StringUtils::format("%02d", STAGE_E_THREESTAR_SAEBI));
	this->addChild(S1_Label);
}
void UILayer::initPassCountE(int Total_Count, int Nomal_Count, int Fat_count, int Speed_count, int Panda_count, int Saebi_count)
{
	///////////////////////////별한개//////////////////////////////////
	auto t_Label = (Label*)this->getChildByTag(TAG_LABEL_TOTAL_COUNT);
	To_count = STAGE_E_TOTAL_PASS - Total_Count;
	if (To_count <= 0) To_count = 0;
	t_Label->setString(StringUtils::format("%02d", To_count));
	////////////////////////////////별두개///////////////////////////////
	Nm_count = STAGE_E_TWOSTAR_NOMAL - Nomal_Count;
	if (Nm_count <= 0) Nm_count = 0;

	Sed_count = STAGE_E_TWOSTAR_SPEED - Speed_count;
	if (Sed_count <= 0) Sed_count = 0;

	Ft_count = STAGE_E_TWOSTAR_FAT - Fat_count;
	if (Ft_count <= 0) Ft_count = 0;

	if ((To_count <= 0) && (Nm_count <= 0) && (Sed_count <= 0) && (Ft_count <= 0))
		isTwostar = true;
	else
		isTwostar = false;
	////////////////////////////별세개////////////////////////////////////////
	auto N3_Label = (Label*)this->getChildByTag(TAG_LABEL_THREE_NOMAL);
	Nm3_count = STAGE_E_THREESTAR_NOMAL - Nomal_Count;
	if (Nm3_count <= 0) Nm3_count = 0;
	N3_Label->setString(StringUtils::format("%02d", Nm3_count));
	//
	auto S3_Label = (Label*)this->getChildByTag(TAG_LABEL_THREE_SPEED);
	Sed3_count = STAGE_E_THREESTAR_SPEED - Speed_count;
	if (Sed3_count <= 0) Sed3_count = 0;
	S3_Label->setString(StringUtils::format("%02d", Sed3_count));
	//

	auto F3_Label = (Label*)this->getChildByTag(TAG_LABEL_THREE_FAT);
	Ft3_count = STAGE_D_THREESTAR_FAT - Fat_count;
	if (Ft3_count <= 0) Ft3_count = 0;
	F3_Label->setString(StringUtils::format("%02d", Ft3_count));

	auto P3_Label = (Label*)this->getChildByTag(TAG_LABEL_THREE_PANDA);
	Pd_count = STAGE_E_THREESTAR_PANDA - Panda_count;
	if (Pd_count <= 0) Pd_count = 0;
	P3_Label->setString(StringUtils::format("%02d", Pd_count));

	auto Sb3_Label = (Label*)this->getChildByTag(TAG_LABEL_THREE_SAEBI);
	Sb_count = STAGE_E_THREESTAR_SAEBI - Saebi_count;
	if (Sb_count <= 0) Sb_count = 0;
	Sb3_Label->setString(StringUtils::format("%02d", Sb_count));

	if ((To_count <= 0) && (Nm3_count <= 0) && (Sed3_count <= 0) && (Ft3_count <= 0) && (Sb_count <= 0) && (Pd_count <= 0))
		isThreestar = true;
	else
		isThreestar = false;
}
