#pragma once

#include <cocos2d.h>
#include "Sound.h"
using namespace cocos2d;

struct MyStruct
{
	int showCardNum;
	Sprite * card1;
	Sprite * card2;
};

class CMyCard:public Sprite
{
public:
	CMyCard();
	~CMyCard();
	bool init();
	CREATE_FUNC(CMyCard);
	void callBack1(Node * node, void * spr);
	void callBack2(Node * node, void * spr);
	void callBack3(Node * node, void * spr);
	void setFontPicName(const char * name, const char * bgName);	
	void callInitCallBack(float dt);	
	void removecard();
	static MyStruct cardState;
	int m_iZ; 
	bool isBg;
	bool boolkg;	
	std::string fontPicName;
	std::string cardBgPicName;
	
};

