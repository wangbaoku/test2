
#include "LostScene.h"
#include "MyScene.h"
#include "Tools.h"
#include "HelloWorldScene.h"
CLostScene::CLostScene(void)
{
}


CLostScene::~CLostScene(void)
{
}

Scene* CLostScene::createScene()
{
	auto scene = Scene::create();

	auto layer = CLostScene::create();

	scene->addChild(layer);

	return scene;
}

bool CLostScene::init()
{
	if (!Layer::init())
	{
		return false;
	}


	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto LostBG = Sprite::create("picture/shibai.jpg");
	Size LostBGSize = LostBG->getContentSize();
	LostBG->setScaleX(visibleSize.width/LostBGSize.width);
	LostBG->setScaleY(visibleSize.height/LostBGSize.height);
	LostBG->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	this->addChild(LostBG);

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	auto shibai = Label::createWithTTF(Tools::Unicode2Utf8(L"失				败"),"fonts/msyh.ttc",38);
#else
	auto shibai = Label::createWithTTF("失                败","fonts/msyh.ttc",38);
#endif
	shibai->setColor(Color3B(255,0,0));
	shibai->setPosition(500,500);
	this->addChild(shibai);
	auto again = MenuItemImage::create(
		"picture/blue1_menu.png",
		"picture/blue2_menu.png",
		CC_CALLBACK_1(CLostScene::menuCloseCallback,this));
	again->setScale(0.5f);
	again->setPosition(Vec2(origin.x + visibleSize.width - again->getContentSize().width/2-310 ,
		origin.y + again->getContentSize().height/2+330));
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	auto againLable = Label::createWithTTF(Tools::Unicode2Utf8(L"再来一次"),"fonts/msyh.ttc",24);
#else
	auto againLable = Label::createWithTTF("再来一次","fonts/msyh.ttc",24);
#endif
	againLable->setPosition(Vec2(again->getPositionX(),again->getPositionY()));
	this->addChild(againLable);



	auto quit = MenuItemImage::create(
		"picture/blue1_menu.png",
		"picture/blue2_menu.png",
		CC_CALLBACK_1(CLostScene::menuCloseCallback1,this));
	quit->setScale(0.5f);
	quit->setPosition(Vec2(origin.x + visibleSize.width - quit->getContentSize().width/2-310 ,
		origin.y + quit->getContentSize().height/2+160));

	quit->setPosition(Vec2(origin.x + visibleSize.width - quit->getContentSize().width/2-310 ,
		origin.y + quit->getContentSize().height/2+160));
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	auto quitLable = Label::createWithTTF(Tools::Unicode2Utf8(L"退出"),"fonts/msyh.ttc",24);
#else
	auto quitLable = Label::createWithTTF("退出","fonts/msyh.ttc",24);
#endif
	quitLable->setPosition(Vec2(quit->getPositionX(),quit->getPositionY()));
	this->addChild(quitLable);
	auto menu = Menu::create(again,quit, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
	return true;
}

void CLostScene::menuCloseCallback(cocos2d::Ref* pSender)
{
	auto scene = MyScene::createScene();
	Director::getInstance()->replaceScene(scene);
}

void CLostScene::menuCloseCallback1(cocos2d::Ref* pSender)
{
	auto scene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(scene);
}
