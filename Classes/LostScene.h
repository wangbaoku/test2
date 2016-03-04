#pragma once
#include "cocos2d.h"
USING_NS_CC;

class CLostScene:public Layer
{
public:
	CLostScene(void);
	~CLostScene(void);

	static Scene* createScene();

	virtual bool init();

	void menuCloseCallback(cocos2d::Ref* pSender);

	void menuCloseCallback1(cocos2d::Ref* pSender);
	CREATE_FUNC(CLostScene);
};

