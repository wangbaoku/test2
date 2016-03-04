#pragma once
#include "CMyCard.h"
#include <cocos2d.h>
using namespace cocos2d;


class MyScene : public cocos2d::Layer	
{
public:
	MyScene();
	~MyScene();
	cocos2d::Sprite *sprite;	
	static cocos2d::Scene* createScene();		
	virtual bool init();				
	void menuCloseCallback(cocos2d::Ref* pSender);	
	void menuCloseCallback2(cocos2d::Ref* pSender);
	void createRandCards();
	bool ccMyTouchBegan(Touch *pTouch, Event *pEvent);		
	void ccMyTouchMoved(Touch *pTouch, Event *pEvent);		
	void ccMyTouchEnded(Touch *pTouch, Event *pEvent);		
	void ccMyMouseMove(Event *pEvent);						
	void update(float delta);
	void ShowUpdate(float delta);
	CREATE_FUNC(MyScene);		
protected:
	Sprite * m_progressBar;			
	Sprite * m_progressBarBox;		
	int m_time;
	int showtime;
	Label * m_labelTime;
	bool TimeRun;
	std::vector<CMyCard*> card_list;		

};

