#include "CMyCard.h"
MyStruct CMyCard::cardState = MyStruct();

CMyCard::CMyCard()
{

	isBg = false;
	boolkg = false;
}


CMyCard::~CMyCard()
{

}


bool CMyCard::init()
{
	if (false == Sprite::init())
	{
		return false;
	}
	auto spr = this;
	auto dis = Director::getInstance()->getEventDispatcher();	
	auto test = EventListenerTouchOneByOne::create();	
	test->setSwallowTouches(true);	
	test->onTouchBegan = [=](Touch *pTouch, Event *pEvent)->bool{
		Vec2 pos = pTouch->getLocation();	
		if (boolkg)	
		{
			if (spr->getBoundingBox().containsPoint(pos))	
			{
				CSound::getInstance()->preloadEffect("pew-pew-lei.wav");
				CSound::getInstance()->playEffect("pew-pew-lei.wav");
				boolkg = false;	
				auto rbc1 = RotateBy::create(0.1f, Vec3(0,90,0));	
				auto act1 = CCCallFuncND::create(spr, callfuncND_selector(CMyCard::callBack1),spr);
				auto rbc2 = RotateBy::create(0.1f, Vec3(0,90,0));	
				auto act2 = CCCallFuncND::create(spr, callfuncND_selector(CMyCard::callBack2),spr);
				auto action = Sequence::create(rbc1, act1, rbc2 ,act2,nullptr);	
				spr->runAction(action);
				return true;
			}
		}
		return false;
	};

	test->onTouchEnded = [spr](Touch *pTouch, Event *pEvent){
		Color3B rgb(255,255,255);
		spr->setColor(rgb);
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(test,this);
	return true;
}

void CMyCard::setFontPicName(const char * name, const char * bgName)
{
	fontPicName = name;
	cardBgPicName = bgName;
	this->Sprite::initWithFile(fontPicName);

}



void CMyCard::callBack1(Node * node, void * spr)
{
	std::string temp;
	if (isBg)
	{
		temp = fontPicName;
	}
	else
	{
		temp = cardBgPicName;
	}
	Sprite * sprite = (Sprite*)spr;
	Texture2D * texture = Director::getInstance()->getTextureCache()->addImage(temp);
	sprite->setTexture(texture);
	isBg = !isBg;
}

void CMyCard::callBack3(Node * node, void * spr)
{
	boolkg = true;
}


void CMyCard::callBack2(Node * node, void * spr)
{
	CMyCard * sprite = (CMyCard*)spr;
	if (cardState.showCardNum == 0)
	{
		cardState.showCardNum ++;
		cardState.card1 = sprite;
	}
	else if(cardState.showCardNum == 1)
	{
		cardState.showCardNum++;
		if (((CMyCard*)(cardState.card1))->fontPicName != sprite->fontPicName)		
		{
			{
				CSound::getInstance()->preloadEffect("pew-pew-lei.wav");
				CSound::getInstance()->playEffect("pew-pew-lei.wav");
				auto act1 = CCCallFuncND::create(cardState.card1, callfuncND_selector(CMyCard::callBack1),cardState.card1);
				auto act3 = CCCallFuncND::create(cardState.card1, callfuncND_selector(CMyCard::callBack3),cardState.card1);
				auto action = Sequence::create(RotateBy::create(0.5f, Vec3(0,90,0)), act1, RotateBy::create(0.5f, Vec3(0,90,0)),act3,nullptr);
				cardState.card1->runAction(action);
				

			}
			{
				CSound::getInstance()->preloadEffect("pew-pew-lei.wav");
				CSound::getInstance()->playEffect("pew-pew-lei.wav");
				auto act1 = CCCallFuncND::create(sprite, callfuncND_selector(CMyCard::callBack1),sprite);
				auto act3 = CCCallFuncND::create(sprite, callfuncND_selector(CMyCard::callBack3),sprite);
				auto action = Sequence::create(RotateBy::create(0.5f, Vec3(0,90,0)), act1, RotateBy::create(0.5f, Vec3(0,90,0)),act3,nullptr);
				sprite->runAction(action);
			}
		}
		else
		{
			cardState.card1->removeFromParent();
			sprite->removeFromParent();
		}
		cardState = MyStruct();
	}
}


void CMyCard::callInitCallBack(float dt)
{

	auto act1 = CCCallFuncND::create(this, callfuncND_selector(CMyCard::callBack1),this);
	auto act3 = CCCallFuncND::create(this, callfuncND_selector(CMyCard::callBack3),this);
	auto action = Sequence::create(RotateBy::create(0.3f, Vec3(0,90,0)), act1, RotateBy::create(0.3f, Vec3(0,90,0)),act3,nullptr);
	this->runAction(action);
}

void CMyCard::removecard()
{
	removeFromParent();
}
