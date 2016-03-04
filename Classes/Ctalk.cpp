#include "Ctalk.h"
#include "Tools.h"
#include "ui/UIScale9Sprite.h"
USING_NS_CC;
using namespace ui;

Ctalk::Ctalk(void)
{
	m_label = nullptr;
	m_label1 = nullptr;
	m_size = 0;
}


Ctalk::~Ctalk(void)
{
}

void Ctalk::inserContent(const char * name, const char * content)
{
	Content con = {name, content};
	Tools::GBKToUTF8(con.name);
	Tools::GBKToUTF8(con.content);
	TalkContent.insert(TalkContent.begin(), con);
}

bool Ctalk::init()
{
	if ( !Node::init() )
	{
		return false;	
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto layer = cocos2d::Layer::create();
	layer->setContentSize(visibleSize);
	auto onebyone = EventListenerTouchOneByOne::create();
	onebyone->setSwallowTouches(true);
	onebyone->onTouchBegan = CC_CALLBACK_0(Ctalk::onTouchDown, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(onebyone,layer);
	this->addChild(layer);

	auto scale9 = Scale9Sprite::create("123.png");
	scale9->setContentSize(Size(visibleSize.width, 200));
	scale9->setPositionX(visibleSize.width*0.5f);
	scale9->setPositionY(100);
	this->addChild(scale9,10);
	
	{
		m_label = Label::createWithTTF("","fonts/msyh.ttc",20);
		m_label->setLineBreakWithoutSpace(true);
		m_label->setMaxLineWidth(200);
		m_label->setPosition(50,180);
		m_label->setAnchorPoint(Vec2(0,1));
		scale9->addChild(m_label);
	}
	{
		m_label1 = Label::createWithTTF("","fonts/msyh.ttc",20);
		m_label1->setLineBreakWithoutSpace(true);
		m_label1->setMaxLineWidth(200);
		m_label1->setPosition(50,150);
		m_label1->setAnchorPoint(Vec2(0,1));
		scale9->addChild(m_label1);
	}


	schedule(schedule_selector(Ctalk::update),0.2);
	return true;
}

bool Ctalk::onTouchDown()
{
	return true;
}


void Ctalk::update(float delta)
{
	string showTest = TalkContent.at(0).name;
	string showText = TalkContent.at(0).content;
	showTest = showTest.substr(0,m_size);
	//showText = showText.substr(0,m_size);
	m_label1->setString(showTest);
	m_label->setString(showText);
	m_size++;
}
