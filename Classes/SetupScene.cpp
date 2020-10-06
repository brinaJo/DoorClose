#include "StageScene.h"
#include "TitleScene.h"
#include "SetupScene.h"
#include "Definitions.h"
#include "SimpleAudioEngine.h"
#include "GM.h"
#include "Develop.h"
using namespace CocosDenshion;

Scene * SetupScene::createScene()
{
	auto scene = Scene::create();
	auto layer = SetupScene::create();
	scene->addChild(layer);
	return scene;
}

bool SetupScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto BG = Sprite::create("images/popup_back.png");	//배경
	BG->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(BG);


	//이거 제대로 다시
	auto spr = MenuItemImage::create("ui/ui_sound_on.png", "ui/ui_sound_on_touch.png", CC_CALLBACK_1(SetupScene::changeScene, this));//사운드 on
	auto spr_2 = MenuItemImage::create("ui/ui_sound_off.png", "ui/ui_sound_off_touch.png", CC_CALLBACK_1(SetupScene::changeScene, this));//사운드 off

	auto Sound_onoff = MenuItemToggle::create();
	if (GM::Getinstance()->Effect == false)
		Sound_onoff = MenuItemToggle::createWithCallback(CC_CALLBACK_1(SetupScene::changeScene, this), spr_2, spr, NULL);
	else if (GM::Getinstance()->Effect == true)
		Sound_onoff = MenuItemToggle::createWithCallback(CC_CALLBACK_1(SetupScene::changeScene, this), spr, spr_2, NULL);
	auto spr3 = MenuItemImage::create("ui/ui_develop.png", "ui/ui_develop.png", CC_CALLBACK_1(SetupScene::changeScene, this));
	auto Exit = MenuItemImage::create("ui/ui_title_exit.png", "ui/ui_title_exit.png", CC_CALLBACK_1(SetupScene::changeScene, this));
	auto M_Success = MenuItemImage::create("ui/ui_success_main.png", "ui/ui_success_main_touch.png", CC_CALLBACK_1(SetupScene::changeScene, this));
	//여기 메인으로 추가햇당

	Exit->setScale(1.22);
	Sound_onoff->setTag(1);
	spr3->setTag(3);
	Exit->setTag(4);
	M_Success->setTag(TAG_MAIN);

	auto Menu = Menu::create(Sound_onoff, spr3, Exit, M_Success, NULL);//메뉴로 묶음
	Menu->alignItemsVerticallyWithPadding(20);
	Menu->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(Menu);

	return true;
}

void SetupScene::changeScene(Ref* sender)
{
	auto menuItem = (MenuItem*)sender;
	switch (menuItem->getTag())	//얘네들은 전부다 게임 화면으로 보내는거야
	{
	case 1:
	{
		if (GM::Getinstance()->Sound == true && GM::Getinstance()->Effect == true)
		{
			SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
			GM::Getinstance()->Sound = false;
			GM::Getinstance()->Effect = false;
			GM::Getinstance()->sound_on_off = false;
		}
		else if (GM::Getinstance()->Sound == false && GM::Getinstance()->Effect == false)
		{
			SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
			GM::Getinstance()->Sound = true;
			GM::Getinstance()->Effect = true;
			GM::Getinstance()->sound_on_off = true;
		}
		break;
	}
	case TAG_MAIN:
	{
		Director::getInstance()->replaceScene(TitleScene::createScene());
	}
	break;
	case 3:
	{
		Director::getInstance()->replaceScene(Develop::createScene());
	}
	break;
	case 4:
		if (GM::Getinstance()->Stage == false)
			Director::getInstance()->replaceScene(TitleScene::createScene());	//나가기버튼 누르면 메인 화면으로 가게끔
		else if (GM::Getinstance()->Stage == true)
			Director::getInstance()->replaceScene(StageScene::createScene());
		break;
	default:
		break;
	}
}