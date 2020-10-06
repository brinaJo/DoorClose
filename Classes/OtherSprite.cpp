#include "OtherSprite.h"
#include "Definitions.h"
OtherSprite::OtherSprite()
{
	visibleSize = Director::getInstance()->getVisibleSize();
	
}
OtherSprite::~OtherSprite()
{

}
void OtherSprite::initSubway(cocos2d::Layer *layer)
{
	auto spr1 = CCSprite::create("images/null.png");
	spr1->setPosition(Point(-100, visibleSize.height / 2 + 40));
	spr1->setAnchorPoint(Point(0, 0));
	spr1->setScale(239, 176);
	spr1->setTag(TAG_CHA_WALL);
	auto body = PhysicsBody::createBox(spr1->getContentSize());
	body->setDynamic(false);
	body->setTag(TAG_SUBWAY_BODY);
	spr1->setPhysicsBody(body);

	auto spr2 = CCSprite::create("images/null.png");
	spr2->setPosition(Point(visibleSize.width / 2 + 6, visibleSize.height / 2 + 40));
	spr2->setAnchorPoint(Point(0.5, 0));
	spr2->setScale(625, 176);
	spr2->setTag(TAG_CHA_WALL);
	auto body2 = PhysicsBody::createBox(spr2->getContentSize());
	body2->setDynamic(false); 
	body2->setTag(TAG_SUBWAY_BODY);
	spr2->setPhysicsBody(body2);

	auto spr3 = CCSprite::create("images/null.png");
	spr3->setPosition(Point(1150, visibleSize.height / 2 + 40));
	spr3->setAnchorPoint(Point(0, 0));
	spr3->setScale(293, 176);
	spr3->setTag(TAG_CHA_WALL);
	auto body3 = PhysicsBody::createBox(spr3->getContentSize());
	body3->setDynamic(false);
	body3->setTag(TAG_SUBWAY_BODY);
	spr3->setPhysicsBody(body3);

	auto spr4 = CCSprite::create("images/null.png");
	spr4->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2 + 216));
	spr4->setAnchorPoint(Point(0.5,0));
	spr4->setScale(1613, 200);
	spr4->setTag(TAG_CHA_WALL);
	auto body4 = PhysicsBody::createBox(spr4->getContentSize());
	body4->setMass(PHYSICS_INFINITY);
	body4->setDynamic(false);
	body4->setTag(TAG_SUBWAY_BODY);
	spr4->setPhysicsBody(body4);
	
	auto spr5 = CCSprite::create("images/null.png");
	spr5->setPosition(Point(139, visibleSize.height / 2+108));
	spr5->setAnchorPoint(Point(0, 0));
	spr5->setScale(198, 108);
	spr5->setTag(TAG_SUBWAY_DOOR1);
	auto body5 = PhysicsBody::createBox(spr5->getContentSize());
	body5->setDynamic(false);
	body5->setCategoryBitmask(0x02);				 // 0010
	body5->setContactTestBitmask(0x08);				 //1000
	body5->setCollisionBitmask(0x01);				 //0001
	body5->setTag(TAG_SUBWAY_DOOR_BODY1);
	spr5->setPhysicsBody(body5);

	auto spr6 = CCSprite::create("images/null.png");
	spr6->setPosition(Point(952, visibleSize.height / 2 + 108));
	spr6->setAnchorPoint(Point(0, 0));
	spr6->setScale(198, 108);
	spr6->setTag(TAG_SUBWAY_DOOR2);
	auto body6 = PhysicsBody::createBox(spr6->getContentSize());
	body6->setDynamic(false);
	body6->setCategoryBitmask(0x02);				 // 0010
	body6->setContactTestBitmask(0x08);				 //1000
	body6->setCollisionBitmask(0x01);				 //0001
	body6->setTag(TAG_SUBWAY_DOOR_BODY2);
	spr6->setPhysicsBody(body6);

//	layer->addChild(spr);
	layer->addChild(spr1);
	layer->addChild(spr2);
	layer->addChild(spr3);
	layer->addChild(spr4);
	layer->addChild(spr5);
	layer->addChild(spr6);
}

void OtherSprite::initReady(cocos2d::Layer *layer)
{
	auto spr_1 = CCSprite::create("images/playgame_back.png");
	spr_1->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));

	auto spr1 = CCSprite::create("images/Playgame_back2_BL.png");
	spr1->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2 + 3));

	auto spr2 = CCSprite::create("ui/ui_play_ready.png");
	spr2->setAnchorPoint(Point(0.5, 0.5));
	spr2->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2 + 3));

	auto spr3 = CCSprite::create("ui/ui_play_start.png");
	spr3->setAnchorPoint(Point(0.5, 0.5));
	spr3->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2 + 3));


	//닫힘
	auto spr_2 = CCSprite::create("images/subway_1.png");
	spr_2->setPosition(Point(0, visibleSize.height / 2));
	spr_2->setAnchorPoint(Point(0.5, 0));

	//중간
	auto spr_3 = CCSprite::create("images/subway_2.png");
	spr_3->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2 + 3));
	spr_3->setAnchorPoint(Point(0.5, 0));

	//열림
	auto spr_4 = CCSprite::create("images/subway_3.png");
	spr_4->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2 + 3));
	spr_4->setAnchorPoint(Point(0.5, 0));

	//들어오는 액션
	auto delay = DelayTime::create(2.0f);
	auto delay_1 = DelayTime::create(6.8f);
	auto Moveaction = MoveTo::create(1, Point(visibleSize.width / 2, visibleSize.height / 2 + 3));
	auto action_1 = Sequence::create(Moveaction, delay_1, RemoveSelf::create(), NULL);
	spr_2->runAction(action_1);

	//중간액션
	spr_3->setOpacity(0);
	auto delay_2 = DelayTime::create(5.0f);
	auto Show_1 = FadeIn::create(0.1);
	auto action_2 = Sequence::create(delay_2, Show_1, delay_2, RemoveSelf::create(), NULL);
	spr_3->runAction(action_2);

	//열림액션
	spr_4->setOpacity(0);
	auto delay_3 = DelayTime::create(5.5f);
	auto Show_2 = FadeIn::create(0.1);
	auto action_3 = Sequence::create(delay_3, Show_2, delay_3, NULL);
	spr_4->runAction(action_3);

	//검은화면
	spr1->setOpacity(0);
	auto delay1 = DelayTime::create(1.5f);
	auto delay1_1 = DelayTime::create(4.3f);
	auto Show1 = FadeIn::create(0.3);
	//auto Hide1 = FadeOut::create(0.1);
	auto action1 = Sequence::create(delay1, Show1, delay1_1, RemoveSelf::create(), NULL);
	spr1->runAction(action1);

	//레디
	spr2->setOpacity(0);
	auto delay2 = DelayTime::create(2.0f);
	auto delay2_1 = DelayTime::create(3.5f);
	auto Show2 = FadeIn::create(0.1);
	auto action2 = Sequence::create(delay2, Show2, delay2_1, RemoveSelf::create(), NULL);
	spr2->runAction(action2);

	//시작
	spr3->setOpacity(0);
	auto delay3 = DelayTime::create(6.0f);
	auto delay3_1 = DelayTime::create(0.8f);
	auto Show3 = FadeIn::create(0.1);
	auto action3 = Sequence::create(delay3, Show3, delay3_1, RemoveSelf::create(), NULL);
	spr3->runAction(action3);

	layer->addChild(spr_1);
	layer->addChild(spr_2);
	layer->addChild(spr_3);
	layer->addChild(spr_4);

	layer->addChild(spr1);
	layer->addChild(spr2);
	layer->addChild(spr3);
}