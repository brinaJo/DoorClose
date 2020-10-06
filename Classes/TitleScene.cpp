#include "TitleScene.h"
#include "StageScene.h"
#include "SetupScene.h"
#include "Definitions.h"
#include "SimpleAudioEngine.h"
#include "Manner.h"
#include "GM.h"
using namespace CocosDenshion;

Scene * TitleScene::createScene()
{
	auto scene = Scene::create();
	auto layer = TitleScene::create();
	scene->addChild(layer);
	return scene;
}

bool TitleScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	//그림을 띄운다

	auto backGround = Sprite::create("images/popup_back.png");
	backGround->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(backGround);

	auto mainLogo = Sprite::create("ui/title.png");
	mainLogo->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2 + 50));
	mainLogo->setScale(1.1);
	this->addChild(mainLogo);

	//메뉴 아이템을 만든다
	auto item1 = MenuItemImage::create("ui/ui_title_start.png", "ui/ui_title_start.png", CC_CALLBACK_1(TitleScene::changeScene, this));
	auto item2 = MenuItemImage::create("ui/ui_title_manner.png", "ui/ui_title_manner.png", CC_CALLBACK_1(TitleScene::changeScene, this));
	auto item3 = MenuItemImage::create("ui/ui_title_exit.png", "ui/ui_title_exit.png", CC_CALLBACK_1(TitleScene::changeScene, this));
	auto item4 = MenuItemImage::create("ui/ui_set_set.png", "ui/ui_set_set.png", CC_CALLBACK_1(TitleScene::changeScene, this));
	item1->setScale(1.1);
	item2->setScale(1.1);
	item3->setScale(1.1);
	item4->setScale(1.1);
	item1->setTag(1);
	item2->setTag(2);
	item3->setTag(3);
	item4->setTag(4);

	//메뉴를 등록한다
	auto menu = Menu::create(item1, item2, item3, NULL);
	menu->alignItemsHorizontallyWithPadding(20);
	menu->setPosition(Point(visibleSize.width / 2, visibleSize.height * 0.1));
	this->addChild(menu);

	auto menu2 = Menu::create(item4, NULL);
	menu2->setPosition(1180, 650);
	this->addChild(menu2);
	if (GM::Getinstance()->Sound == true && GM::Getinstance()->Effect == true)
	{
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sound/main.mp3", true);
		SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.2);
	}



	return true;
}

void TitleScene::changeScene(Ref* sender)
{
	auto menuItem = (MenuItem*)sender;
	switch (menuItem->getTag())
	{
	case 1:
	{
		Director::getInstance()->replaceScene(StageScene::createScene());
	}
	break;
	case 2:
	{
		Director::getInstance()->replaceScene(Manner::createScene());
	}
		break;
	case 3:
	{
		Director::getInstance()->end();
	}
	break;
	case 4:
	{
		GM::Getinstance()->Stage = false;
		Director::getInstance()->replaceScene(SetupScene::createScene());
	}
	default:
		break;
	}

}