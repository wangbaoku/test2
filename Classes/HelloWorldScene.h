#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Sound.h"
class HelloWorld : public cocos2d::Layer
{
public:
    
	

    static cocos2d::Scene* createScene();
	
    virtual bool init();
	
    void menuCloseCallback(cocos2d::Ref* pSender);
	
	void menuCloseCallback1(cocos2d::Ref* pSender);
	
	void menuCloseCallback3(cocos2d::Ref* pSender);

	void menuCloseCallback4(cocos2d::Ref* pSender);

	void menuCloseCallback5(cocos2d::Ref* pSender);

    CREATE_FUNC(HelloWorld);
private:
	
};

#endif
