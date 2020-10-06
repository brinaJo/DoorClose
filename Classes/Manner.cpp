#include"Manner.h"
#include"TitleScene.h"
#include "Definitions.h"

USING_NS_CC;

Scene* Manner::createScene()
{
	auto scene = Scene::create();
	auto layer = Manner::create();
	scene->addChild(layer);
	return scene;
}

bool Manner::init()
{
		if (!Layer::init())
		{
			return false;
		}
		Size visibleSize = Director::getInstance()->getVisibleSize();

		

		auto BG = Sprite::create("images/popup_back.png");	//배경
		BG->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
		this->addChild(BG);

		auto Play = MenuItemImage::create("images/image_howto.png", "images/image_howto.png", CC_CALLBACK_1(Manner::changeScene, this));
		Play->setTag(1);
		
		Play->setAnchorPoint(Point(0.5, 0.5));
		Play->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
		auto menu = Menu::create(Play, NULL);
		menu->alignItemsHorizontallyWithPadding(30);
		//menu->setPosition(1180, 650);
		this->addChild(menu);

	

		return true;
		
}

void Manner::changeScene(Ref* sender)
{
	auto menuItem = (MenuItem*)sender;
	switch (menuItem->getTag())	//얘네들은 전부다 게임 화면으로 보내는거야
	{
	case 1:
	{
		Director::getInstance()->replaceScene(TitleScene::createScene());
	}
	
	default:
		break;
	}
}