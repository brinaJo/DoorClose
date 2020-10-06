#include "GameSceneE.h"
#include "Definitions.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;


Scene* GameSceneE::createScene()
{
	Size visibleSize;
	visibleSize.width = 1480;
	visibleSize.height = 920;
	Vect gravity = Vect(0.0f, 0.0f);

	auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(gravity);

	auto body = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	auto edgeNode = Node::create();
	edgeNode->setAnchorPoint(Point(0.5, 0.5));
	edgeNode->setPosition(Point(visibleSize.width / 2 - 100, visibleSize.height / 2 - 100));
	edgeNode->setPhysicsBody(body);
	scene->addChild(edgeNode);

	auto layer = GameSceneE::create();
	layer->SetPhyWorld(scene->getPhysicsWorld());

	scene->addChild(layer);
	return scene;
}

// on "init" you need to initialize your instance
bool GameSceneE::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	MainScene::init();
	m_OtherSp.initReady(this);

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	//////////////////////터치 리스너
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameSceneE::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameSceneE::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);
	///////////////////////충돌리스너
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameSceneE::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	m_OtherSp.initSubway(this);

	this->scheduleUpdate();
	this->schedule(schedule_selector(GameSceneE::L_SetSprite), 1.0f, CC_REPEAT_FOREVER, 6.8f);				//많이 출현
	this->schedule(schedule_selector(GameSceneE::M_SetSprite), 3.0f, CC_REPEAT_FOREVER, 8.8f);				//보통으로 출현
	this->schedule(schedule_selector(GameSceneE::S_SetSprite), 3.2f, CC_REPEAT_FOREVER, 9.0f);				//적게 출현
	this->schedule(schedule_selector(GameSceneE::BADS_SetSprite), 8.3f, CC_REPEAT_FOREVER, 15.1f);			//나쁜곰탱이 출현(제일적음)
	this->schedule(schedule_selector(GameSceneE::BADL_SetSprite), 10.5f, CC_REPEAT_FOREVER, 16.8f);				//나쁜곰탱이 출현(그나마보통)
	this->schedule(schedule_selector(GameSceneE::BADW_SetSprite), 0.0f, 1, 6.8f);
	this->schedule(schedule_selector(GameSceneE::initUI), 0.0f, 1, 6.8f);

	return true;
}

void GameSceneE::initUI(float delta)
{
	uiLayer = UILayer::create();
	uiLayer->initUI(GAMESCENEE);
	this->addChild(uiLayer,TAG_ZORDER);
}
bool GameSceneE::onContactBegin(PhysicsContact& contact)
{

	MainScene::onContactBegin(contact);
	uiLayer->initPassCountE(Total_count, Nomal_count, Fat_count, Speed_count, Panda_count, Saebi_count);
	//bodies can collide
	return true;
}