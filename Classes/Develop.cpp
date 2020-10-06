
#include "Develop.h"
#include "TitleScene.h"
#include "SetupScene.h"

USING_NS_CC;

Scene* Develop::createScene()
{
	auto scene = Scene::create();
	auto layer = Develop::create();
	scene->addChild(layer);
	return scene;
}
bool Develop::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto BG = Sprite::create("images/popup_back.png");	//¹è°æ
	BG->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(BG);

	auto develop = Sprite::create("images/image_developer.png");
	develop->setAnchorPoint(Point(0.5, 0.5));
	develop->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(develop);

	auto dev = MenuItemImage::create("images/image_developer.png", "images/image_developer.png", CC_CALLBACK_1(Develop::changeScene, this));
	dev->setTag(1);
	dev->setAnchorPoint(Point(0.5, 0.5));
	dev->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));

	auto menu = Menu::create(dev, NULL);
	menu->alignItemsHorizontallyWithPadding(30);
	//menu->setPosition(1180, 650);
	this->addChild(menu);

	return true;
}

void Develop::changeScene(Ref* sender)
{
	auto menuItem = (MenuItem*)sender;
	switch (menuItem->getTag())
	{
	case 1:
	{
		Director::getInstance()->replaceScene(SetupScene::createScene());

	}
	default:
		break;
	}
}