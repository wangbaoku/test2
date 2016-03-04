#pragma once
#include <cocos2d.h>
#include <vector>
#include <string>
using namespace std;

struct Content
{
	string content;		
	string name;		
};

class Ctalk : public cocos2d::Node
{
public:
	Ctalk(void);
	~Ctalk(void);
	virtual bool init();
	bool onTouchDown();
	void update(float delta);
	void inserContent(const char * name, const char * content);
	CREATE_FUNC(Ctalk);
	
private:
	int m_size;
	cocos2d::Label * m_label;
	cocos2d::Label * m_label1;
	vector<Content> TalkContent;
};

