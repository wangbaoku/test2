#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "ReadFile.h"
#include "Sound.h"
USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// If you want to use packages manager to install more packages, 
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
		glview = GLViewImpl::create("My Game");
		//glview = GLViewImpl::createWithRect("My Game",Rect(0,0,320,500),1);
        director->setOpenGLView(glview);
    }

	////ÉèÖÃ·Ö±æÂÊ
	//glview->setDesignResolutionSize(320, 500, ResolutionPolicy::FIXED_WIDTH);
	//std::vector<std::string> SearchPath;
	//SearchPath.push_back("w640");
	//CCFileUtils::getInstance()->setSearchPaths(SearchPath);
	//director->setContentScaleFactor(640.0 / 320.0);

    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    register_all_packages();
    // create a scene. it's an autorelease object
	CReadFile::getInstance()->setshuomingkg(true);

	//CSound::getInstance()->playBG("Butter-Fly.mp3",CSound::getInstance()->getIsPlay());
	//CSound::getInstance()->setIsPlay(true);

    auto scene = HelloWorld::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
