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
	{// ���ڲ���
		if (isPlay)
		{// Ҫ�󲥷�

			// ֹͣ��ǰ���ŵ�����
			SimpleAudioEngine::getInstance()->stopBackgroundMusic();
			// ����������
			SimpleAudioEngine::getInstance()->playBackgroundMusic(file,true);
		}
		else
		{
			// ֹͣ��ǰ���ŵ�����
			SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		}
	}
	else
	{
		if (isPlay)
		{// Ҫ�󲥷�
			// ����������
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