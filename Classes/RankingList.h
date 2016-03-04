#pragma once
#ifndef __CRANKINGLIST_SCENE_H__
#define __CRANKINGLIST_SCENE_H__
#include "cocos2d.h"
using namespace cocos2d;
class CRankingList:public Layer
{
public:
	CRankingList(void);
	~CRankingList(void);
	static cocos2d::Scene* createScene();

	virtual bool init();

	void menuCloseCallback(cocos2d::Ref* pSender);
 
	CREATE_FUNC(CRankingList);



};
#endif
