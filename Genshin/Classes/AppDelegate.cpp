#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "Scene\StartMenu.h"

// #define USE_AUDIO_ENGINE 1
// #define USE_SIMPLE_AUDIO_ENGINE 1

#if USE_AUDIO_ENGINE && USE_SIMPLE_AUDIO_ENGINE
#error "Don't use AudioEngine and SimpleAudioEngine at the same time. Please just select one in your game!"
#endif

#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
#elif USE_SIMPLE_AUDIO_ENGINE
#include "audio/include/SimpleAudioEngine.h"
using namespace CocosDenshion;
#endif

USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size(1980, 1080);//设计分辨率大小，决定了游戏的画面大小
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate() 
{
#if USE_AUDIO_ENGINE
    AudioEngine::end();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::end();
#endif
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()//设置OpenGL上下文属性
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil,multisamplesCount
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8, 0};

    GLView::setGLContextAttrs(glContextAttrs);
}

// if you want to use the package manager to install more packages,  
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {//重点，这是程序的入口函数，程序从这里开始执行
    // initialize director
	auto director = Director::getInstance();//获取导演实例，控制场景切换
	auto glview = director->getOpenGLView();//获取OpenGL视图
    if(!glview) {//窗口适配
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
		glview = GLViewImpl::createWithRect("Genshin", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));//分辨率大小
#else
        glview = GLViewImpl::create("Genshin");
#endif
        director->setOpenGLView(glview);
    }

	//是否要显示帧率
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
	//设置动画帧率，默认是1.0/60也就是60帧每秒
    director->setAnimationInterval(1.0f / 60);

	//设置设计分辨率大小
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
    auto frameSize = glview->getFrameSize();
    // if the frame's height is larger than the height of medium size.
    if (frameSize.height > mediumResolutionSize.height)
    {        
        director->setContentScaleFactor(MIN(largeResolutionSize.height/designResolutionSize.height, largeResolutionSize.width/designResolutionSize.width));
    }
    // if the frame's height is larger than the height of small size.
    else if (frameSize.height > smallResolutionSize.height)
    {        
        director->setContentScaleFactor(MIN(mediumResolutionSize.height/designResolutionSize.height, mediumResolutionSize.width/designResolutionSize.width));
    }
    // if the frame's height is smaller than the height of medium size.
    else
    {        
        director->setContentScaleFactor(MIN(smallResolutionSize.height/designResolutionSize.height, smallResolutionSize.width/designResolutionSize.width));
    }

    register_all_packages();

    // create a scene. it's an autorelease object
	//关键代码，创建一个场景
	auto scene = HelloWorld::createScene();//创建一个开始菜单场景

	//用导演运行场景
	director->runWithScene(scene);//runWithScene仅用于第一次运行场景，之后用replaceScene（代替场景）或pushScene（压入场景）

    return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {//当程序进入后台时调用
	Director::getInstance()->stopAnimation();//停止动画

#if USE_AUDIO_ENGINE//如果使用音频引擎
	AudioEngine::pauseAll();//暂停所有音频
#elif USE_SIMPLE_AUDIO_ENGINE//如果使用简单音频引擎
	SimpleAudioEngine::getInstance()->pauseBackgroundMusic();//暂停背景音乐
	SimpleAudioEngine::getInstance()->pauseAllEffects();//暂停所有音效
#endif
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {//当程序进入前台时调用
	Director::getInstance()->startAnimation();//开始动画

#if USE_AUDIO_ENGINE
    AudioEngine::resumeAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    SimpleAudioEngine::getInstance()->resumeAllEffects();
#endif
}

Vec2 operator*(const Vec2& lhs, const Size& rhs) {
      // 将两个 Vec2 的 x 和 y 分别相乘
      return Vec2(lhs.x * rhs.width, lhs.y * rhs.height);
}