#include "Sound.h"

static CSound * sound = nullptr;

CSound::CSound(void)
{
	isPlay = true;
}


CSound::~CSound(void)
{
}

CSound * CSound::getInstance()
{
	if (nullptr == sound)
	{
		sound = new CSound();
	}
	return sound;

}


void CSound::setIsPlay(bool isPlay)
{
	CSound::isPlay = isPlay;
}

void CSound::playBG(const char* file, bool isPlay)
{
	 isPlay = CSound::isPlay;
	if (SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
	{// 正在播放
		if (isPlay)
		{// 要求播放

			// 停止当前播放的音乐
			SimpleAudioEngine::getInstance()->stopBackgroundMusic();
			// 播放新音乐
			SimpleAudioEngine::getInstance()->playBackgroundMusic(file,true);
		}
		else
		{
			// 停止当前播放的音乐
			SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		}
	}
	else
	{
		if (isPlay)
		{// 要求播放
			// 播放新音乐
			SimpleAudioEngine::getInstance()->playBackgroundMusic(file,true);
		}
	}
}

void CSound::preloadEffect(const char* filePath)
{
	SimpleAudioEngine::getInstance()->preloadEffect(filePath);
}

unsigned int CSound::playEffect(const char* filePath)
{
	SimpleAudioEngine::getInstance()->playEffect(filePath);
	return 0;
}