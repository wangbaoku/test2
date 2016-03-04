#pragma once
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
class CSound
{
public:


	void playBG(const char* file, bool isPlay);
	void setIsPlay(bool isPlay);
	bool getIsPlay(){return isPlay;};
	static CSound * getInstance();
	void preloadEffect(const char* filePath);
	unsigned int playEffect(const char* filePath);
protected:
	


private:
	CSound(void);
	~CSound(void);
	bool isPlay;
};

