
#include "MyScene.h"
#include "HelloWorldScene.h"
#include "Tools.h"
#include "LostScene.h"
USING_NS_CC;
using namespace cocos2d;
const int sx = 100;
const int sy = 100;

MyScene::MyScene()
{
	sprite = NULL;
	m_time = 60;
	TimeRun = true;
	showtime = 10;
}

MyScene::~MyScene()
{
}

Scene* MyScene::createScene()
{
	auto scene = Scene::create();
	auto layer = MyScene::create();	
	scene->addChild(layer); 
	return scene;			
}

bool MyScene::init()
{
	if ( !Layer::init() )
	{
		return false;	 
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();		
	Vec2 origin = Director::getInstance()->getVisibleOrigin();			

	
	auto closeItem = MenuItemImage::create(
		"picture/back1.png",
		"picture/back1.png",
		CC_CALLBACK_1(MyScene::menuCloseCallback, this));

	
	closeItem->setPosition(Vec2(visibleSize.width - closeItem->getContentSize().width/2 ,
		visibleSize.height - closeItem->getContentSize().height/2));
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	
	auto dis = Director::getInstance()->getEventDispatcher();   
	auto test = EventListenerTouchOneByOne::create();			
	auto mouse = EventListenerMouse::create();					
	mouse->onMouseMove = CC_CALLBACK_1(MyScene::ccMyMouseMove, this);	
	test->onTouchBegan = CC_CALLBACK_2(MyScene::ccMyTouchBegan, this);	
	test->onTouchMoved = CC_CALLBACK_2(MyScene::ccMyTouchMoved, this);	
	test->onTouchEnded = CC_CALLBACK_2(MyScene::ccMyTouchEnded, this);	
	dis->addEventListenerWithSceneGraphPriority(test, this);		
	dis->addEventListenerWithSceneGraphPriority(mouse, this);

	
	sprite = Sprite::create("picture/bg.jpg");
	Size sprSize = sprite->getContentSize();
	sprite->setScaleX(visibleSize.width/sprSize.width);
	sprite->setScaleY(visibleSize.height/sprSize.height);
	sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	this->addChild(sprite, 0);

	m_progressBar = Sprite::create("picture/bosshp1.png");
	m_progressBarBox = Sprite::create("picture/bosshp0.png");
	m_progressBar->setAnchorPoint(Vec2(0,0));
	m_progressBar->setPosition(m_progressBarBox->getPositionX()+15,0);
	m_progressBar->setScaleX(2.0f);
	m_progressBarBox->setAnchorPoint(Vec2(0,0));
	m_progressBarBox->setPosition(0,0);
	m_progressBarBox->setScaleX(2.0f);
	this->addChild(m_progressBarBox);
	this->addChild(m_progressBar);
	CCString * str = CCString::createWithFormat("Time Remaining :%d",m_time);
	m_labelTime = Label::create(str->getCString(),"fonts/msyh.ttc",24);
	
	createRandCards();



	m_progressBar->runAction(ScaleTo::create(showtime,0,1.0f));
	m_progressBar->runAction(TintTo::create(showtime,Color3B(255,0,0)));
	schedule(CC_SCHEDULE_SELECTOR(MyScene::ShowUpdate),1.0f);

	return true;
}


void MyScene::createRandCards()
{
	CMyCard::cardState = MyStruct();
	
	if (card_list.size() > 0)	
	{
		for (int i = 0; i < card_list.size(); i++)
		{
			card_list.at(i)->removecard();
		}
		card_list.clear();
	}

	int znum = 1;	

	for (int i = 0; i < 48; i++)	
	{
		int w = i / 6;	
		int h = i % 6;

		znum++;
		if (znum >= 9)	
		{
			znum = 1;
		}
		CMyCard * mycard = CMyCard::create();	
		mycard->m_iZ = rand() % 48;		
		mycard->setPosition(sx + (58+48)  * w, sy + (66+18) * h);	
		CCString * picName = CCString::createWithFormat("picture/%d.jpg",znum);	
		mycard->setFontPicName(picName->getCString(), "picture/cardbg.png");	
		card_list.push_back(mycard);	
		i++;
		w = i / 6;
		h = i % 6;
		CMyCard * mycard2 = CMyCard::create();
		mycard2->m_iZ = rand() % 48;
		mycard2->setPosition(sx + (58+48)  * w, sy + (66+18) * h);
		picName = CCString::createWithFormat("picture/%d.jpg",znum);
		mycard2->setFontPicName(picName->getCString(), "picture/cardbg.png");
		card_list.push_back(mycard2);
	}
	
	for (int i=0; i<card_list.size(); i++)
	{
		for (int j=0; j<card_list.size(); j++)
		{
			if (i == j)
			{
				continue;
			}

			if (card_list.at(i)->m_iZ > card_list.at(j)->m_iZ)
			{
				int x = 0;
				int y = 0;
				x = card_list.at(i)->getPositionX();
				y = card_list.at(i)->getPositionY();

				card_list.at(i)->setPosition(card_list.at(j)->getPositionX(), card_list.at(j)->getPositionY());
				card_list.at(j)->setPosition(x, y);
			}
		}
	}

	for (int i=0; i<48; i++)
	{
		this->addChild(card_list.at(i),0);
	}
	
}
		
void MyScene::menuCloseCallback(cocos2d::Ref* pSender)
{
	this->pauseSchedulerAndActions();
	m_progressBar->pauseSchedulerAndActions();
	CSound::getInstance()->preloadEffect("pew-pew-lei.wav");
	CSound::getInstance()->playEffect("pew-pew-lei.wav");
	Size visibleSize = Director::getInstance()->getVisibleSize();		
	Vec2 origin = Director::getInstance()->getVisibleOrigin();			


	auto pause = LayerColor::create(Color4B(120,120,120,255));
	
	auto test = EventListenerTouchOneByOne::create();
	
	test->setSwallowTouches(true);
	TimeRun = false;
	test->onTouchBegan = [](Touch *pTouch, Event *pEvent)->bool{return true;};	
	
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(test,pause);

	auto quit = MenuItemImage::create(
		"picture/pauseBackRoom.png",
		"picture/pauseBackRoom.png",
		CC_CALLBACK_1(MyScene::menuCloseCallback2,this));
	quit->setPosition(480,250);

	auto back = MenuItemImage::create(
		"picture/pauseResume.png",
		"picture/pauseResume.png",
		[=](cocos2d::Ref* pSender)
		{

			auto act1 = MoveBy::create(1.0f, Vec2(pause->getContentSize().width, 0));
			auto act2 = CallFuncN::create([=](Node * node)
				{
					removeChild(pause);
					this->resumeSchedulerAndActions();
					m_progressBar->resumeSchedulerAndActions();
				});
			auto action = Sequence::create(act1,act2,nullptr);
			pause->runAction(action);
			TimeRun = true;

		});
	back->setPosition(480,380);
	auto backbg = Sprite::create("picture/backbg.jpg");
	auto backbgsize = backbg->getContentSize();
	backbg->setScaleX(visibleSize.width/backbgsize.width);
	backbg->setScaleY(visibleSize.height/backbgsize.height);
	backbg->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	pause->addChild(backbg);
	auto menu = Menu::create(quit,back,NULL);
	menu->setPosition(Vec2::ZERO);
	pause->addChild(menu);
	this->addChild(pause,0);
}


void MyScene::menuCloseCallback2(cocos2d::Ref* pSender)
{
	CSound::getInstance()->preloadEffect("pew-pew-lei.wav");
	CSound::getInstance()->playEffect("pew-pew-lei.wav");
	auto scene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(scene);
}


bool MyScene::ccMyTouchBegan(Touch *pTouch, Event *pEvent)
{

	return false;
}


void MyScene::ccMyTouchMoved(Touch *pTouch, Event *pEvent)
{

}

void MyScene::ccMyTouchEnded(Touch *pTouch, Event *pEvent)
{

}

void MyScene::ccMyMouseMove(Event *pEvent)
{

}

void MyScene::update(float delta)
{
	
	if (m_time>0&&TimeRun == true)
	{
		m_time--;
	}
	
	if (m_time == 0)
	{
		m_time = 60;
		Size visibleSize = Director::getInstance()->getVisibleSize();  
		Vec2 origin = Director::getInstance()->getVisibleOrigin();	

		auto scene = CLostScene::createScene();
		Director::getInstance()->replaceScene(scene);
		unschedule(CC_SCHEDULE_SELECTOR(MyScene::update));
	}
}

void MyScene::ShowUpdate(float delta)
{
	if (showtime>0)
	{
		showtime--;
	}
	
	if (showtime==0)
	{
		for (int i = 0; i < card_list.size(); ++i)
		{
			card_list.at(i)->callInitCallBack(0);
		}
		showtime = 10;

		unschedule(CC_SCHEDULE_SELECTOR(MyScene::ShowUpdate));
		m_progressBar->stopAllActions();
		m_progressBar->setScaleX(2.0f);
		m_progressBar->setColor(Color3B(255,255,255));
		m_progressBar->runAction(ScaleTo::create(m_time,0,1.0f));
		m_progressBar->runAction(TintTo::create(m_time,Color3B(255,0,0)));
		schedule(CC_SCHEDULE_SELECTOR(MyScene::update),1.0f);
	}
}
