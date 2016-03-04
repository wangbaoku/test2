#include "RankingList.h"
#include "Tools.h"
#include "ReadFile.h"
#include "HelloWorldScene.h"
CRankingList::CRankingList(void)
{
}


CRankingList::~CRankingList(void)
{
}


Scene* CRankingList::createScene()
{
	auto scene = Scene::create();	 

	auto layer = CRankingList::create();

	scene->addChild(layer);			  

	return scene;					
}

bool CRankingList::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();	
	Vec2 origin = Director::getInstance()->getVisibleOrigin();	

	auto back = MenuItemImage::create(
		"back1.png",
		"back1.png",
		CC_CALLBACK_1(CRankingList::menuCloseCallback,this));

	back->setPosition(Vec2(visibleSize.width - back->getContentSize().width/2 ,
		visibleSize.height - back->getContentSize().height/2));
	auto menu = Menu::create(back, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu,3);

	auto paihangbangPic = Sprite::create("picture/123.png");
	Size sprSize = paihangbangPic->getContentSize();

	paihangbangPic->setScaleX(visibleSize.width/sprSize.width);
	paihangbangPic->setScaleY(visibleSize.height/sprSize.height);
	paihangbangPic->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	this->addChild(paihangbangPic);
	auto userList = CReadFile::getInstance()->getUserList();
	string str = userList.at(0)->name;
	Tools::GBKToUTF8(str);
	auto paihangshuju = Label::createWithTTF("111222555", "fonts/msyh.ttc",24);
	paihangshuju->setPosition(visibleSize/2);
	paihangbangPic->addChild(paihangshuju,2);
	this->addChild(paihangshuju,2);


	return true;

}


void CRankingList::menuCloseCallback(cocos2d::Ref* pSender)
{
	auto scene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(scene);
}