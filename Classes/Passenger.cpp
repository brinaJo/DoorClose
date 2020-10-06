#include "Passenger.h"
#include "GM.h"
#include "Definitions.h"
//1296x810

#define RANDOM_VALUE		50
Passenger::Passenger()
{
	visibleSize = Director::getInstance()->getVisibleSize();
	TimePlus = 0.0f;
}


Passenger::~Passenger()
{
}

int Passenger::Passinit()
{
	std::random_device rd;
	std::mt19937 rEngine(rd());
	std::uniform_int_distribution<> dix(0, 4);		//화면사이즈 반 랜덤값 생성

	//0~405

	auto random = dix(rEngine);
	float a = CCRANDOM_0_1();

	if (a < 1.0f / 2.0f)
	{
		result = RANDOM_VALUE*random;

		sprite->setAnchorPoint(Point(0.5, 1));
		if (sprite->getTag() == TAG_CHA_NOMAL)
			sprite->setPosition(Point(0, visibleSize.height / 2 - result - 30));
		else
			sprite->setPosition(Point(0, visibleSize.height / 2 - result));
		RL_Check = true;
	}
	else
	{
		result = RANDOM_VALUE*random;

		sprite->setAnchorPoint(Point(0.5, 1));
		if (sprite->getTag() == TAG_CHA_NOMAL)
			sprite->setPosition(Point(visibleSize.width, visibleSize.height / 2 - result - 30));
		else
			sprite->setPosition(Point(visibleSize.width, visibleSize.height / 2 - result));
		RL_Check = false;
	}
	return (int)result;
}

void Passenger::PassRun()
{
	auto animate = Animate::create(animation);
	auto Foraction = RepeatForever::create(animate);
	sprite->runAction(Foraction);
	if (RL_Check)
	{
		if (sprite->getTag() == TAG_CHA_NOMAL)
		{
			auto Moveaction = MoveTo::create(4, Point(visibleSize.width, visibleSize.height / 2 - result));
			auto action2 = Sequence::create(Moveaction, RemoveSelf::create(), NULL);
			sprite->runAction(action2);
		}
		if (sprite->getTag() == TAG_CHA_FAT)
		{
			auto Moveaction = MoveTo::create(6, Point(visibleSize.width, visibleSize.height / 2 - result));
			auto action2 = Sequence::create(Moveaction, RemoveSelf::create(), NULL);
			sprite->setTag(TAG_CHA_FAT_R);
			sprite->runAction(action2);
		}
		if (sprite->getTag() == TAG_CHA_SAEBI || sprite->getTag() == TAG_CHA_PANDA)
		{
			auto Moveaction = MoveTo::create(8, Point(visibleSize.width, visibleSize.height / 2 - result));
			auto action2 = Sequence::create(Moveaction, RemoveSelf::create(), NULL);
			sprite->runAction(action2);
		}
		if (sprite->getTag() == TAG_CHA_SPEED)
		{
			auto Moveaction = MoveTo::create(2.6, Point(visibleSize.width, visibleSize.height / 2 - result));
			auto action2 = Sequence::create(Moveaction, RemoveSelf::create(), NULL);
			sprite->runAction(action2);
		}
	}
	else if (!RL_Check)
	{
		if (sprite->getTag() == TAG_CHA_NOMAL)
		{
			auto Moveaction = MoveTo::create(4, Point(0, visibleSize.height / 2 - result));
			auto action2 = Sequence::create(Moveaction, RemoveSelf::create(), NULL);
			sprite->runAction(action2);
		}
		if (sprite->getTag() == TAG_CHA_FAT)
		{
			auto Moveaction = MoveTo::create(6, Point(0, visibleSize.height / 2 - result));
			auto action2 = Sequence::create(Moveaction, RemoveSelf::create(), NULL);
			sprite->setTag(TAG_CHA_FAT_L);
			sprite->runAction(action2);
		}
		if (sprite->getTag() == TAG_CHA_SAEBI || sprite->getTag() == TAG_CHA_PANDA)
		{
			auto Moveaction = MoveTo::create(8, Point(0, visibleSize.height / 2 - result));
			auto action2 = Sequence::create(Moveaction, RemoveSelf::create(), NULL);
			sprite->runAction(action2);
		}
		if (sprite->getTag() == TAG_CHA_SPEED)
		{
			auto Moveaction = MoveTo::create(2.6, Point(0, visibleSize.height / 2 - result));
			auto action2 = Sequence::create(Moveaction, RemoveSelf::create(), NULL);
			sprite->runAction(action2);
		}
	}

}


void Passenger::PassAni()
{
	animation = Animation::create();
}


//일반승객과 나머지 승객들이 부딪혔을때 나머지 승객들을 움직이는 함수
void Passenger::PassCollision(cocos2d::Layer *layer, Sprite* spr, Point location, float delta)
{
	Rect rectPlayer = spr->getBoundingBox();

	auto removePass = Sprite::create();

	auto _scene = layer->getScene();
	auto sprlocation = spr->getPosition();
	auto arr = _scene->getPhysicsWorld()->getShapes(Point(sprlocation.x, sprlocation.y));

	for (auto* sprPass : arr)
	{
		auto sprB = (Sprite*)sprPass->getBody()->getOwner();
		int TagInput = sprB->getTag();
		TagSpriteChange(TagInput, sprB);
		if ((TagInput == TAG_FAT_SLOW) || (TagInput == TAG_CHA_NOMAL) || (TagInput == TAG_CHA_SAEBI) || (TagInput == TAG_CHA_SPEED) || (TagInput == TAG_CHA_PANDA))
		{
			Rect rectPass = sprB->getBoundingBox();
			if (rectPlayer.intersectsRect(rectPass))
			{
				sprB->stopAllActions();

				auto sprBody = sprB->getPhysicsBody();

				sprBody->setVelocity(Vec2(location.x * 4, location.y * 4));
				sprBody->setVelocityLimit(1000);
				sprBody->setMass(100);
				sprB->runAction(Sequence::create(DelayTime::create(0.5), CallFuncN::create(CC_CALLBACK_1(Passenger::MoonCollPass, this)), RemoveSelf::create(), NULL));
				//layer->removeChild(sprB);
			}
		}
		///////////플레이어가 나머지 캐릭터랑 부딪혔을때

		if (TagInput == TAG_CHA_FAT_R)
		{
			Rect rectPass = sprB->getBoundingBox();
			if (rectPlayer.intersectsRect(rectPass))
			{
				sprB->stopAllActions();
				Point pt = sprB->getPosition();
				auto Moveaction = MoveTo::create((visibleSize.width - pt.x) * 0.01, Point(visibleSize.width, pt.y));
				auto action2 = Sequence::create(Moveaction,RemoveSelf::create(), NULL);
				sprB->runAction(action2);
				TimePlus += delta;
				if (TimePlus >= 0.2f)
				{
					sprB->setTag(TAG_FAT_SLOW);
					sprB->setTexture("images/cha_fat_break3.png");
					TimePlus = 0;
				}
				
			}
		}
		if (TagInput == TAG_CHA_FAT_L)
		{
			Rect rectPass = sprB->getBoundingBox();
			if (rectPlayer.intersectsRect(rectPass))
			{
				sprB->stopAllActions();
				Point pt = sprB->getPosition();
				auto Moveaction = MoveTo::create(pt.x * 0.01, Point(0, pt.y));//
				auto action2 = Sequence::create(Moveaction, RemoveSelf::create(), NULL);
				sprB->runAction(action2);
				TimePlus += delta;
				if (TimePlus >= 0.2f)
				{
					sprB->setTag(TAG_FAT_SLOW);
					sprB->setTexture("images/cha_fat_break3.png");
					TimePlus = 0;
				}

			}
		}
		////////플레이어가 뚱땡이랑 부딪혔을때
	}

}


void Passenger::MoonCollPass(Ref *sender)
{
	auto NodeAB = (Node*)sender;
	NodeAB->removeFromParentAndCleanup(true);
	auto a = (Sprite*)NodeAB;
	if (a->getTag() == TAG_CHA_NOMAL)
	{
		GM::Getinstance()->nPass.eraseObject(a);
	}
}

void Passenger::ChaScore(cocos2d::Layer *layer, Node *sender)
{
	auto Location = sender->getPosition();
	auto Score_Sprite = Sprite::create();
	auto In_Sprite = Sprite::create();
	auto In_F_Sprite = Sprite::create();
	auto node = sender;

	if (node->getTag() == TAG_CHA_NOMAL || node->getTag() == TAG_CHA_SPEED || node->getTag() == TAG_CHA_PANDA)
	{
		Score_Sprite = Sprite::create("ui/ui_count_plus_1.png");
		In_Sprite = Sprite::create("ui/ui_in_suc.png");
		In_Sprite->setScale(0.5);
	}
	else if (node->getTag() == TAG_FAT_SLOW)
	{
		Score_Sprite = Sprite::create("ui/ui_count_plus_3.png");
		In_Sprite = Sprite::create("ui/ui_in_suc.png");
		In_Sprite->setScale(0.5);
	}
	else if (node->getTag() == TAG_CHA_SAEBI)
	{
		Score_Sprite = Sprite::create("ui/ui_count_minus_5.png");
		In_Sprite = Sprite::create("ui/ui_in_suc.png");
	}
	Score_Sprite->setPosition(Location.x, Location.y + 100);
	In_Sprite->setPosition(Location.x + 10, Location.y + 50);
	layer->addChild(Score_Sprite, 501);
	layer->addChild(In_Sprite, 500);
	Score_Sprite->runAction(Sequence::create(FadeOut::create(0.5), CallFuncN::create(CC_CALLBACK_1(Passenger::MoonCollPass, this)), NULL));
	In_Sprite->runAction(Sequence::create(FadeOut::create(0.5), CallFuncN::create(CC_CALLBACK_1(Passenger::MoonCollPass, this)), NULL));

}


void Passenger::TagSpriteChange(int tag, Sprite* spr)
{
	if (tag == TAG_CHA_NOMAL)
		spr->setTexture("images/cha_nomal_shoot.png");
	else if (tag == TAG_CHA_FAT_R || tag == TAG_CHA_FAT_L)
		spr->setTexture("images/cha_fat_shoot.png");
	else if (tag == TAG_CHA_SAEBI)
		spr->setTexture("images/cha_saebi_shoot.png");
	else if (tag == TAG_CHA_PANDA)
		spr->setTexture("images/cha_sel_shoot.png");
	else if (tag == TAG_CHA_SPEED)
		spr->setTexture("images/Cha_Speed_Shoot.png");
}

void NomalPass::Passinit(cocos2d::Layer *layer)
{
	sprite = Sprite::create("images/cha_nomal_walk_r_2.png");
	int z = Passenger::Passinit();
	auto material = PhysicsMaterial(0.1f, 3.0f, 0.5f);

	////////////////////////////////////////////////////////물리바디설정
	auto body = PhysicsBody::createBox(sprite->getContentSize());
	body->setTag(TAG_CHA_NOMAL_BODY);
	sprite->setPhysicsBody(body);
	
	body->setRotationEnable(false);
	body->setCategoryBitmask(0x08);			//1000
	body->setContactTestBitmask(0x02);		//0010
	body->setCollisionBitmask(0x01);		//0001
	/////////////////////////////////////////////////////////////////
	sprite->setTag(TAG_CHA_NOMAL);
	layer->addChild(sprite, z+3);

	GM::Getinstance()->nPass.pushBack(sprite);
	PassRun();
}

void NomalPass::NomalTouch(cocos2d::Sprite *m_nomal)
{
	auto animation = Animation::create();
	animation->setDelayPerUnit(0.3);
	animation->addSpriteFrameWithFile("images/cha_nomal_hold_1.png");
	animation->addSpriteFrameWithFile("images/cha_nomal_hold_2.png");
	auto animate = Animate::create(animation);
	auto Foraction = RepeatForever::create(animate);
	auto body = PhysicsBody::createBox(m_nomal->getContentSize());
	m_nomal->setPhysicsBody(body);
	m_nomal->runAction(Foraction);
}

void NomalPass::PassRun()
{
	Passenger::PassAni();
	animation->setDelayPerUnit(0.3);
	if (RL_Check)
	{
		animation->addSpriteFrameWithFile("images/cha_nomal_walk_r_1.png");
		animation->addSpriteFrameWithFile("images/cha_nomal_walk_r_2.png");
	}
	else if (!RL_Check)
	{
		animation->addSpriteFrameWithFile("images/cha_nomal_walk_l_1.png");
		animation->addSpriteFrameWithFile("images/cha_nomal_walk_l_2.png");
	}
	Passenger::PassRun();
}

void FatPass::Passinit(cocos2d::Layer *layer)
{
	sprite = Sprite::create("images/cha_fat_walk_r_1.png");

	int z = Passenger::Passinit();
	///밀도 반발력 마찰력
	auto material = PhysicsMaterial(0.1f, 3.0f, 0.5f);
	////////////////////////////////////////////////////////물리바디설정
	auto body = PhysicsBody::createBox(sprite->getContentSize());
	body->setTag(TAG_CHA_FAT_BODY);
	sprite->setPhysicsBody(body);
	body->setRotationEnable(false);
	body->setCategoryBitmask(0x08);			//1000
	body->setContactTestBitmask(0x02);		//0010
	body->setCollisionBitmask(0x01);		//0001
	/////////////////////////////////////////////////////////////////
	sprite->setTag(TAG_CHA_FAT);
	layer->addChild(sprite, z + 5);

	PassRun();
}
void FatPass::PassRun()
{
	Passenger::PassAni();
	animation->setDelayPerUnit(0.3);
	if (RL_Check)
	{
		animation->addSpriteFrameWithFile("images/cha_fat_walk_r_1.png");
		animation->addSpriteFrameWithFile("images/cha_fat_walk_r_2.png");
	}
	else if (!RL_Check)
	{
		animation->addSpriteFrameWithFile("images/cha_fat_walk_l_1.png");
		animation->addSpriteFrameWithFile("images/cha_fat_walk_l_2.png");
	}
	Passenger::PassRun();

}

void SpeedPass::Passinit(cocos2d::Layer *layer)
{
	sprite = Sprite::create("images/Cha_Speed_Walk_R_1.png");

	int z = Passenger::Passinit();
	auto material = PhysicsMaterial(0.1f, 3.0f, 0.5f);
	////////////////////////////////////////////////////////물리바디설정
	auto body = PhysicsBody::createBox(sprite->getContentSize());
	body->setTag(TAG_CHA_SPEED_BODY);
	body->setRotationEnable(false);
	sprite->setPhysicsBody(body);
	body->setCategoryBitmask(0x08);			//1000
	body->setContactTestBitmask(0x02);		//0010
	body->setCollisionBitmask(0x01);		//0001
	/////////////////////////////////////////////////////////////////
	sprite->setTag(TAG_CHA_SPEED);
	layer->addChild(sprite, z);

	PassRun();
}
void SpeedPass::PassRun()
{
	Passenger::PassAni();
	animation->setDelayPerUnit(0.3);
	if (RL_Check)
	{
		animation->addSpriteFrameWithFile("images/Cha_Speed_Walk_R_1.png");
		animation->addSpriteFrameWithFile("images/Cha_Speed_Walk_R_2.png");
	}
	else if (!RL_Check)
	{
		animation->addSpriteFrameWithFile("images/Cha_Speed_Walk_L_1.png");
		animation->addSpriteFrameWithFile("images/Cha_Speed_Walk_L_2.png");
	}
	Passenger::PassRun();
}

void PandaPass::Passinit(cocos2d::Layer *layer)
{
	sprite = Sprite::create("images/cha_sel_walk_r_1.png");

	int z = Passenger::Passinit();
	auto material = PhysicsMaterial(0.1f, 3.0f, 0.5f);
	////////////////////////////////////////////////////////물리바디설정
	auto body = PhysicsBody::createBox(sprite->getContentSize());
	body->setTag(TAG_CHA_PANDA_BODY);
	body->setRotationEnable(false);
	sprite->setPhysicsBody(body);
	body->setCategoryBitmask(0x08);			//1000
	body->setContactTestBitmask(0x02);		//0010
	body->setCollisionBitmask(0x01);		//0001
	/////////////////////////////////////////////////////////////////
	sprite->setTag(TAG_CHA_PANDA);
	layer->addChild(sprite, z+4);

	PassRun();
}

void PandaPass::PassRun()
{
	Passenger::PassAni();
	animation->setDelayPerUnit(0.3);
	if (RL_Check)
	{
		animation->addSpriteFrameWithFile("images/cha_sel_walk_r_1.png");
		animation->addSpriteFrameWithFile("images/cha_sel_walk_r_2.png");
	}
	else if (!RL_Check)
	{
		animation->addSpriteFrameWithFile("images/cha_sel_walk_l_1.png");
		animation->addSpriteFrameWithFile("images/cha_sel_walk_l_2.png");
	}
	Passenger::PassRun();
}

void SaebiPass::Passinit(cocos2d::Layer *layer)
{
	sprite = Sprite::create("images/cha_saebi_walk_r_1.png");

	int z = Passenger::Passinit();
	auto material = PhysicsMaterial(0.1f, 3.0f, 0.5f);
	////////////////////////////////////////////////////////물리바디설정
	auto body = PhysicsBody::createBox(sprite->getContentSize());
	body->setTag(TAG_CHA_SAEBI_BODY);
	body->setRotationEnable(false);
	sprite->setPhysicsBody(body);
	body->setCategoryBitmask(0x08);			//1000
	body->setContactTestBitmask(0x02);		//0010
	body->setCollisionBitmask(0x01);		//0001
	/////////////////////////////////////////////////////////////////
	sprite->setTag(TAG_CHA_SAEBI);
	layer->addChild(sprite, z+4);

	PassRun();
}

void SaebiPass::PassRun()
{
	Passenger::PassAni();
	animation->setDelayPerUnit(0.3);
	if (RL_Check)
	{
		animation->addSpriteFrameWithFile("images/cha_saebi_walk_r_1.png");
		animation->addSpriteFrameWithFile("images/cha_saebi_walk_r_2.png");
	}
	else if (!RL_Check)
	{
		animation->addSpriteFrameWithFile("images/cha_saebi_walk_l_1.png");
		animation->addSpriteFrameWithFile("images/cha_saebi_walk_l_2.png");
	}
	Passenger::PassRun();
}

void BlackPass::Passinit(cocos2d::Layer *layer)
{
	sprite = Sprite::create("images/cha_wall_walk_r_1.png");

	Passenger::Passinit();
	auto material = PhysicsMaterial(0.1f, 3.0f, 0.5f);
	////////////////////////////////////////////////////////물리바디설정
	auto body = PhysicsBody::createBox(sprite->getContentSize());
	body->setTag(TAG_CHA_BLACK_BODY);
	sprite->setPhysicsBody(body);
	body->setDynamic(false);
	body->setRotationEnable(false);
	/////////////////////////////////////////////////////////////////
	sprite->setTag(TAG_CHA_BLACK);
	layer->addChild(sprite);

	PassRun();
}

void BlackPass::PassRun()
{
	Passenger::PassAni();
	animation->setDelayPerUnit(0.3f);
	animation->addSpriteFrameWithFile("images/cha_wall_walk_r_1.png");
	animation->addSpriteFrameWithFile("images/cha_wall_walk_r_2.png");
	PassRun_BD();
}

void BlackPass::PassRun_BD()			//게임이 끝날때까지 계속 있을예정이라 빼둠(흑곰)
{
	auto animate = Animate::create(animation);
	auto Foraction = RepeatForever::create(animate);
	sprite->runAction(Foraction);
	sprite->setPosition(Point(0, visibleSize.height / 2 - 20));
	sprite->setAnchorPoint(Point(0, 0));
	auto Moveaction_1 = MoveTo::create(10.0, Point(visibleSize.width - 200, visibleSize.height / 2 - 20));
	auto Moveaction_2 = MoveTo::create(10.0, Point(100, visibleSize.height / 2 - 30));
	auto action_sp = FlipX::create(true);;
	auto action_sp2 = FlipX::create(false);;
	auto action_1 = Sequence::create(Moveaction_1, action_sp, Moveaction_2, action_sp2, NULL);
	auto action_2 = RepeatForever::create(action_1);

	sprite->runAction(action_2);

}
//애들 등장하는거 따로 만들어둬야함