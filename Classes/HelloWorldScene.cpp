
#include "HelloWorldScene.h"
#include "MyScene.h"
#include "Tools.h"
#include "Ctalk.h"
#include "CMyCard.h"
#include "Sound.h"
#include "ReadFile.h"
#include "RankingList.h"
USING_NS_CC;

Scene* HelloWorld::createScene()
{

	auto scene = Scene::create();

	auto layer = HelloWorld::create();

	scene->addChild(layer);	

	CSound::getInstance()->playBG("Butter-Fly.mp3",CSound::getInstance()->getIsPlay());
	return scene;
}

bool HelloWorld::init()
{

	if ( !Layer::init() )
	{
		return false;
	}

	CReadFile::getInstance()->init();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto closeItem = MenuItemImage::create(
		"picture/blue1_menu.png",
		"picture/blue2_menu.png" 
		, CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
	closeItem->setScale(0.3f);
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2-310 ,
		origin.y + closeItem->getContentSize().height/2+160));

	auto closeItem1 = MenuItemImage::create(
		"picture/blue1_menu.png",
		"picture/blue2_menu.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback1, this));

	closeItem1->setScale(0.5f);

	closeItem1->setPosition(Vec2(origin.x + visibleSize.width - closeItem1->getContentSize().width/2-310 ,
		origin.y + closeItem1->getContentSize().height/2+330));

	auto SetMenu = MenuItemImage::create(
		"picture/shezhi2_cover.png",
		"picture/shezhi1_cover.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback3, this));
	SetMenu->setScale(0.8f);

	SetMenu->setPosition(Vec2(origin.x + visibleSize.width - SetMenu->getContentSize().width/2-390 ,
		origin.y + SetMenu->getContentSize().height/2+260));

	auto menu = Menu::create(closeItem,closeItem1,SetMenu, NULL);
	menu->setPosition(Vec2::ZERO);		
	this->addChild(menu, 1);
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	auto label = Label::createWithTTF(Tools::Unicode2Utf8(L"开始游戏"), "fonts/msyh.ttc", 24);
#else
	auto label = Label::createWithTTF("开始游戏", "fonts/msyh.ttc", 24);
#endif
	label->setPosition(Vec2(closeItem1->getPositionX(), closeItem1->getPositionY()));
	label->setScale(0.8f);
	this->addChild(label, 1);
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	auto label1 = Label::createWithTTF(Tools::Unicode2Utf8(L"退出"), "fonts/msyh.ttc", 24);
#else
	auto label1 = Label::createWithTTF("退出", "fonts/msyh.ttc", 24);
#endif
	label1->setPosition(Vec2(closeItem->getPositionX(), closeItem->getPositionY()));
	label1->setScale(0.8f);
	this->addChild(label1,1);

	auto sprite = Sprite::create("picture/shumabaobei.jpg");

	Size sprSize = sprite->getContentSize();

	sprite->setScaleX(visibleSize.width/sprSize.width);
	sprite->setScaleY(visibleSize.height/sprSize.height);
	sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	this->addChild(sprite, 0);	

	auto logo = Sprite::create("picture/logo.png");
	Size logoSize = logo->getContentSize();

	auto spark = Sprite::create("picture/spark.png");
	spark->setPosition(-logoSize.width,0);
	auto clippingNode = ClippingNode::create();
	clippingNode->setPosition(500,560);
	this->addChild(clippingNode);
	clippingNode->setAlphaThreshold(0.05f);
	clippingNode->setContentSize(logoSize);

	clippingNode->setStencil(logo);
	clippingNode->addChild(logo,1);
	clippingNode->addChild(spark,2);

	auto moveAction = MoveTo::create(2.0f,Vec2(logoSize.width,0));
	auto moveBackAction = MoveTo::create(2.0f,Vec2(-logoSize.width,0));
	spark->runAction(RepeatForever::create(Sequence::create(moveAction,moveBackAction,NULL)));
	if (CReadFile::getInstance()->getshuomingkg())
	{
		CReadFile::getInstance()->setshuomingkg(false);
		CSound::getInstance()->playBG("Butter-Fly.mp3",CSound::getInstance()->getIsPlay());
		CSound::getInstance()->setIsPlay(true);


		auto shuominglayer = LayerColor::create(Color4B(120,120,120,200));
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
		auto wenzi = Label::createWithTTF(Tools::Unicode2Utf8(L"欢迎来到宝库设计的数码宝贝记忆消除游戏"),"fonts/msyh.ttc", 28);
#else
		auto wenzi = Label::createWithTTF("欢迎来到宝库设计的数码宝贝记忆消除游戏","fonts/msyh.ttc", 28);
#endif
		wenzi->setMaxLineWidth(460);
		wenzi->setLineBreakWithoutSpace(true);
		wenzi->setPosition(480,520);
		wenzi->setColor(ccc3(0,0,0));
		shuominglayer->runAction(FadeOut::create(5));
		wenzi->runAction(FadeOut::create(3));
		shuominglayer->addChild(wenzi,2);
		this->addChild(shuominglayer,2);
	}
	return true;
}



void HelloWorld::menuCloseCallback1(cocos2d::Ref* pSender)
{


	CSound::getInstance()->preloadEffect("pew-pew-lei.wav");
	CSound::getInstance()->playEffect("pew-pew-lei.wav");
	auto scene = MyScene::createScene();
	Director::getInstance()->replaceScene(scene);

}


void HelloWorld::menuCloseCallback(Ref* pSender)
{

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void HelloWorld::menuCloseCallback3(cocos2d::Ref* pSender)
{
	CSound::getInstance()->preloadEffect("pew-pew-lei.wav");
	CSound::getInstance()->playEffect("pew-pew-lei.wav");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto SetLayer = LayerColor::create(Color4B(120,120,120,255));
	auto SetLayerSize = SetLayer->getContentSize();
	SetLayer->setScaleX(visibleSize.width/SetLayerSize.width);
	SetLayer->setScaleY(visibleSize.height/SetLayerSize.height);
	SetLayer->ignoreAnchorPointForPosition(false);
	SetLayer->setAnchorPoint(Vec2(0.5f,0.5f));
	SetLayer->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

	auto setbg = Sprite::create("picture/setbg.png"); 
	auto setbgsize = setbg->getContentSize();
	setbg->setScaleX(visibleSize.width/setbgsize.width);
	setbg->setScaleY(visibleSize.height/setbgsize.height);
	setbg->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	SetLayer->addChild(setbg);

	auto dis = Director::getInstance()->getEventDispatcher();	
	auto test = EventListenerTouchOneByOne::create();	
	test->setSwallowTouches(true);		

	test->onTouchBegan = [=](Touch *pTouch, Event *pEvent)->bool{
		return true;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(test,SetLayer);

	auto paihangbang = MenuItemImage::create(
		"picture/blue1_menu.png",
		"picture/blue2_menu.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback5,this));
	paihangbang->setPosition(Vec2(origin.x + visibleSize.width - paihangbang->getContentSize().width/2-300 ,
		origin.y + paihangbang->getContentSize().height/2+180));
	paihangbang->setScale(0.8f);
	auto menu = Menu::create(paihangbang, NULL);
	menu->setPosition(Vec2::ZERO);		
	SetLayer->addChild(menu, 1);
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	auto paihangbanglabel =  Label::createWithTTF(Tools::Unicode2Utf8(L"排行榜"), "fonts/msyh.ttc", 30);
#else
	auto paihangbanglabel =  Label::createWithTTF("排行榜", "fonts/msyh.ttc", 30);
#endif
	paihangbanglabel->setPosition(paihangbang->getPositionX(),paihangbang->getPositionY());
	paihangbanglabel->setAnchorPoint(Vec2(0,0));
	SetLayer->addChild(paihangbanglabel,1);

	string str;
	if (CSound::getInstance()->getIsPlay())
		str = "picture/soundon1_cover.png";
	else
		str = "picture/soundon2_cover.png";
	auto musicsprite = Sprite::create(str);
	musicsprite->setPosition(Vec2(origin.x + visibleSize.width - musicsprite->getContentSize().width/2-320 ,
		origin.y + musicsprite->getContentSize().height/2+400));
	auto dis1 = Director::getInstance()->getEventDispatcher();	
	auto test1 = EventListenerTouchOneByOne::create();	
	test1->setSwallowTouches(true);		

	test1->onTouchBegan = [=](Touch *pTouch, Event *pEvent)->bool{
		Vec2 pos = pTouch->getLocation();
		if (musicsprite->getBoundingBox().containsPoint(pos))
		{
			if (CSound::getInstance()->getIsPlay())
			{
				Texture2D* tex = Director::getInstance()->getTextureCache()->addImage("picture/soundon2_cover.png");
				musicsprite->setTexture(tex);
			}
			else
			{
				Texture2D* tex = Director::getInstance()->getTextureCache()->addImage("picture/soundon1_cover.png");
				musicsprite->setTexture(tex);
			}

			CSound::getInstance()->setIsPlay(!CSound::getInstance()->getIsPlay());
			CSound::getInstance()->playBG("Butter-Fly.mp3",CSound::getInstance()->getIsPlay());
			CReadFile::getInstance()->saveUserInfo();
			return true;
		}
		return false;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(test1,musicsprite);
	SetLayer->addChild(musicsprite);
	auto back = MenuItemImage::create(
		"picture/pauseBackRoom.png",
		"picture/pauseBackRoom.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback4,this));
	back->setPosition(Vec2(origin.x + visibleSize.width - back->getContentSize().width/2-310 ,
		origin.y + back->getContentSize().height/2+280)); 

	auto menu1 = Menu::create(back, NULL);
	menu1->setPosition(Vec2::ZERO);		
	SetLayer->addChild(menu1, 1);
	this->addChild(SetLayer, 1);
}



void HelloWorld::menuCloseCallback4(cocos2d::Ref* pSender)
{
	CSound::getInstance()->preloadEffect("pew-pew-lei.wav");
	CSound::getInstance()->playEffect("pew-pew-lei.wav");
	auto senen = HelloWorld::createScene();
	Director::getInstance()->replaceScene(senen);
}

void HelloWorld::menuCloseCallback5(cocos2d::Ref* pSender)
{
	auto scene = CRankingList::createScene();
	Director::getInstance()->replaceScene(scene);
}
