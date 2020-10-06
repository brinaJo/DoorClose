#include "GameSceneA.h"
#include "Definitions.h"
#include "StageScene.h"
#include "SimpleAudioEngine.h"
#include "GM.h"

USING_NS_CC;
using namespace CocosDenshion;


Scene* GameSceneA::createScene()
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

	auto layer = GameSceneA::create();
	layer->SetPhyWorld(scene->getPhysicsWorld());

	scene->addChild(layer);
	return scene;
}

// on "init" you need to initialize your instance
bool GameSceneA::init()
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
	//////////////////////��ġ ������
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameSceneA::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameSceneA::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);
	///////////////////////�浹������
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameSceneA::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	m_OtherSp.initSubway(this);

	this->scheduleUpdate();
	this->schedule(schedule_selector(GameSceneA::L_SetSprite), 1.0f, CC_REPEAT_FOREVER, 6.8f);				//���� ���� (��� ĳ����)
	this->schedule(schedule_selector(GameSceneA::M_SetSprite), 3.0f, CC_REPEAT_FOREVER, 8.8f);				//�������� ���� (��� ĳ����)
	this->schedule(schedule_selector(GameSceneA::S_SetSprite), 3.2f, CC_REPEAT_FOREVER, 9.0f);				//���� ���� (��Ȳ�����Ҵ� ĳ����)
	this->schedule(schedule_selector(GameSceneA::initUI), 0.0f, 1, 6.8f);									//6.8���� UI���


	return true;
}

void GameSceneA::initUI(float delta)
{
	uiLayer = UILayer::create();
	uiLayer->initUI(GAMESCENEA);
	this->addChild(uiLayer,TAG_ZORDER);
}

bool GameSceneA::onContactBegin(PhysicsContact& contact)
{
	MainScene::onContactBegin(contact);			//��ӹ��� MainScene�浹 �Լ� ������
												//UI���̾ ī��Ʈ �Լ� ���ڸ� ����
	uiLayer->initPassCountA(Total_count, Nomal_count, Fat_count, Speed_count, Panda_count, Saebi_count);
	//bodies can collide
	return true;
}