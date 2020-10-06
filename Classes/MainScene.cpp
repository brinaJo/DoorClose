#include "MainScene.h"
#include "Definitions.h"
#include "StageScene.h"
#include "SimpleAudioEngine.h"
#include "GM.h"
using namespace CocosDenshion;
USING_NS_CC;


Scene* MainScene::createScene()
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

	auto layer = MainScene::create();
	layer->SetPhyWorld(scene->getPhysicsWorld());

	scene->addChild(layer);
	return scene;
}

void MainScene::MusicLoad()
{
	//배경음악
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sound/main.mp3");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sound/map.mp3");

	//효과음
	SimpleAudioEngine::getInstance()->preloadEffect("sound/Light Melody_Crystal(OK).mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/Subway_com.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("sonud/Sucess.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("sonud/Sec_fast.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("sonud/Fail.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/Light Melody_Crystal(Tap).mp3");

}
// on "init" you need to initialize your instance
bool MainScene::init()
{
	MusicLoad();
	if (GM::Getinstance()->Sound == true && GM::Getinstance()->Effect == true)
	{
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sound/main.mp3", true);
		SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.7f);
		SimpleAudioEngine::getInstance()->playEffect("sound/Subway_com.mp3");
		SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.1f);
	}
	return true;
}



void MainScene::L_SetSprite(float delta)
{
	N_Pass.Passinit(this);

}

void MainScene::M_SetSprite(float delta)
{
	F_Pass.Passinit(this);
}

void MainScene::S_SetSprite(float delta)
{
	S_Pass.Passinit(this);
}

void MainScene::BADS_SetSprite(float delta)
{
	PD_Pass.Passinit(this);
}

void MainScene::BADL_SetSprite(float delta)
{
	NG_Pass.Passinit(this);
}

void MainScene::BADW_SetSprite(float delta)
{
	BG_Pass.Passinit(this);
}


bool MainScene::onTouchBegan(Touch *touch, Event *unused_event)
{
	if (GM::Getinstance()->Sound == true && GM::Getinstance()->Effect == true)
	{
		SimpleAudioEngine::getInstance()->playEffect("sound/Light Melody_Crystal(Tap).mp3");
	}
	if ((!isTouch) && (GM::Getinstance()->isChaTouch == true))
	{
		Point location = touch->getLocation();
		firstTouch = location;
		auto _scene = this->getScene();
		auto arr = _scene->getPhysicsWorld()->getShapes(location);

		auto IFT = Sprite::create("ui/ui_touch_if.png");
		IFT->setPosition(Point(location.x, location.y));
		this->addChild(IFT, 10001);
		IFT->runAction(Sequence::create(FadeOut::create(0.5), NULL));

		body = nullptr;
		for (Sprite* spr : GM::Getinstance()->nPass)
		{
			Rect rect = spr->getBoundingBox();
			rect.origin.x -= 30;
			rect.origin.y -= 30;
			rect.size.width += 60;
			rect.size.height += 60;
			if (rect.containsPoint(location))
			{
				if (spr->getPhysicsBody()->getTag() == TAG_CHA_NOMAL_BODY)
				{
					body = spr->getPhysicsBody();
					break;
				}
			}
		}
		if (body != nullptr)
		{
			if (GM::Getinstance()->Sound == true && GM::Getinstance()->Effect == true)
			{
				SimpleAudioEngine::getInstance()->playEffect("sound/Light Melody_Crystal(Tap).mp3");
			}
			auto IFT = Sprite::create("ui/ui_click_if.png");
			IFT->setPosition(Point(location.x, location.y + 10));
			this->addChild(IFT, 10001);
			IFT->runAction(Sequence::create(FadeOut::create(0.5), NULL));

			auto spr = (Sprite*)body->getOwner();
			spr->stopAllActions();
			N_Pass.NomalTouch(spr);
			collcheck = false;
			isTouch = true;
		}
	}
	return true;
}

void MainScene::onTouchEnded(Touch *touch, Event *unused_event)
{
	if (isTouch)
	{
		Point location = touch->getLocation();
		firstTouch = location - firstTouch;

		if (body != nullptr)
		{
			auto spr = (Sprite*)body->getOwner();
			spr->setTexture("images/cha_nomal_shoot.png");
			spr->stopAllActions();
			body->setVelocity(Vec2(firstTouch.x * 5, firstTouch.y * 5));			//캐릭터 터치가 끝났을때 캐릭터 이동
			body->setMass(100);
			body->setVelocityLimit(1000);
			collcheck = true;
			spr->runAction(Sequence::create(DelayTime::create(0.7), CallFuncN::create(CC_CALLBACK_1(MainScene::resetPass, this)), NULL));
		}
		isTouch = false;
	}
}

void MainScene::resetPass(Ref *sender)
{
	auto sprPass = (Sprite*)sender;
	if (sprPass->getTag() == TAG_CHA_NOMAL)
	{
		GM::Getinstance()->nPass.eraseObject(sprPass);
	}
	collcheck = false;
	this->removeChild(sprPass);
	
}

void MainScene::MoonCollPass(Ref *sender)
{
	auto NodeAB = (Node*)sender;
	NodeAB->removeFromParentAndCleanup(true);
	auto a = (Sprite*)NodeAB;
	if (a->getTag() == TAG_CHA_NOMAL)
	{
		GM::Getinstance()->nPass.eraseObject(a);
	}
}

void MainScene::PandaSel()
{
	auto p_spr = Sprite::create("images/image_panda_sel_1.png");
	p_spr->setAnchorPoint(Point(0, 0));
	p_spr->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(p_spr, 8000);

	auto W_ani = Animation::create();
	W_ani->setDelayPerUnit(0.3);

	W_ani->addSpriteFrameWithFile("images/image_panda_sel_1.png");
	W_ani->addSpriteFrameWithFile("images/image_panda_sel_2.png");

	auto W_animate = Animate::create(W_ani);
	auto action1 = Repeat::create(W_animate, 8);
	auto action2 = RemoveSelf::create();
	auto action3 = CCSequence::create(action1, action2, NULL);
	p_spr->runAction(action3);
}
void MainScene::SaebiSel(Node* node)
{
	auto s_spr = Sprite::create("images/image_saebe_sel_0.png");
	s_spr->setAnchorPoint(Point(0, 0));
	if (node->getTag() == TAG_SUBWAY_DOOR1)
		s_spr->setPosition(Point(220, 300));
	if (node->getTag() == TAG_SUBWAY_DOOR2)
		s_spr->setPosition(Point(1000, 300));
	s_spr->setScale(0.8);
	this->addChild(s_spr, 5);

	auto S_ani = Animation::create();
	S_ani->setDelayPerUnit(0.5);

	for (int i = 0; i <= 11; i++)
	{
		S_ani->addSpriteFrameWithFile(StringUtils::format("images/image_saebe_sel_%d.png", i));
	}

	auto S_animate = Animate::create(S_ani);
	auto action1 = Repeat::create(S_animate, 1);
	auto action2 = RemoveSelf::create();
	auto action3 = CCSequence::create(action1, action2, NULL);
	s_spr->runAction(action3);
}
bool MainScene::onContactBegin(PhysicsContact& contact)
{
	//부딪힌 두 물체를 nodeA와 B에 받아오는 부분
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();


	if (GM::Getinstance()->Sound == true && GM::Getinstance()->Effect == true)
	{
		SimpleAudioEngine::getInstance()->playEffect("sound/Light Melody_Crystal(OK).mp3");
		SimpleAudioEngine::getInstance()->setEffectsVolume(1.0);
	}

	if (nodeA && nodeB)
	{
		////////////////////////nodeA가 문일때 캐릭터는 nodeB
		if (nodeA->getTag() == TAG_SUBWAY_DOOR1 || nodeA->getTag() == TAG_SUBWAY_DOOR2)			//승객들이 문1과 2에 부딪혔을때 nodeA와 nodeB의 태그값을 구해 카운트를 해줌
		{
			if (nodeB->getTag() == TAG_CHA_NOMAL)
				Nomal_count++;
			else if (nodeB->getTag() == TAG_CHA_FAT || nodeB->getTag() == TAG_FAT_SLOW)
			{
				Fat_count++;
				Fat_Tcount += 3;
			}
			else if (nodeB->getTag() == TAG_CHA_SPEED)
				Speed_count++;
			else if (nodeB->getTag() == TAG_CHA_PANDA)
			{
				PandaSel();
				Panda_count++;
			}
			else if (nodeB->getTag() == TAG_CHA_SAEBI)
			{
				SaebiSel(nodeA);
				Saebi_Tcount -= 5;
				Saebi_count++;
			}
			P_Passenger.ChaScore(this, nodeB);
			nodeB->runAction(Sequence::create(FadeOut::create(0.3), CallFuncN::create(CC_CALLBACK_1(MainScene::MoonCollPass, this)), NULL));
			collcheck = false;
		}
		/////////////////////////////////////////nodeB가 문일때 캐릭터는 nodeA
		else if (nodeB->getTag() == TAG_SUBWAY_DOOR1 || nodeB->getTag() == TAG_SUBWAY_DOOR2)		//승객들이 문1과 2에 부딪혔을때 nodeA와 nodeB의 태그값을 구해 카운트를 해줌
		{
			if (nodeA->getTag() == TAG_CHA_NOMAL)
				Nomal_count++;
			else if (nodeA->getTag() == TAG_CHA_FAT || nodeA->getTag() == TAG_FAT_SLOW)
			{
				Fat_count++;
				Fat_Tcount += 3;
			}
			else if (nodeA->getTag() == TAG_CHA_SPEED)
				Speed_count++;
			else if (nodeA->getTag() == TAG_CHA_PANDA)
			{
				PandaSel();

				Panda_count++;
			}
			else if (nodeA->getTag() == TAG_CHA_SAEBI)
			{
				SaebiSel(nodeB);
				Saebi_Tcount -= 5;
				Saebi_count++;
			}
			P_Passenger.ChaScore(this, nodeA);
			nodeA->runAction(Sequence::create(FadeOut::create(0.3), CallFuncN::create(CC_CALLBACK_1(MainScene::MoonCollPass, this)), NULL));
			collcheck = false;
		}
		Total_count = (Nomal_count + Fat_Tcount + Speed_count + Panda_count + Saebi_Tcount);
		if (Total_count <= 0)
		{
			Total_count = 0;
		}

	}
	//bodies can collide
	return true;
}

void MainScene::update(float delta)
{
	if (collcheck)
	{
		if (body != nullptr)
		{
			auto spr = (Sprite*)body->getOwner();

			P_Passenger.PassCollision(this, spr, firstTouch, delta);			//일반 승객과 나머지 승객의 충돌 검사
		}
	}
}

