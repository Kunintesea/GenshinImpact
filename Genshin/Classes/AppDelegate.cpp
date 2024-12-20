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

static cocos2d::Size designResolutionSize = cocos2d::Size(1980, 1080);//��Ʒֱ��ʴ�С����������Ϸ�Ļ����С
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
void AppDelegate::initGLContextAttrs()//����OpenGL����������
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

bool AppDelegate::applicationDidFinishLaunching() {//�ص㣬���ǳ������ں�������������￪ʼִ��
    // initialize director
	auto director = Director::getInstance();//��ȡ����ʵ�������Ƴ����л�
	auto glview = director->getOpenGLView();//��ȡOpenGL��ͼ
    if(!glview) {//��������
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
		glview = GLViewImpl::createWithRect("Genshin", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));//�ֱ��ʴ�С
#else
        glview = GLViewImpl::create("Genshin");
#endif
        director->setOpenGLView(glview);
    }

	//�Ƿ�Ҫ��ʾ֡��
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
	//���ö���֡�ʣ�Ĭ����1.0/60Ҳ����60֡ÿ��
    director->setAnimationInterval(1.0f / 60);

	//������Ʒֱ��ʴ�С
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
	//�ؼ����룬����һ������
	auto scene = HelloWorld::createScene();//����һ����ʼ�˵�����

	//�õ������г���
	director->runWithScene(scene);//runWithScene�����ڵ�һ�����г�����֮����replaceScene�����泡������pushScene��ѹ�볡����

    return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {//����������̨ʱ����
	Director::getInstance()->stopAnimation();//ֹͣ����

#if USE_AUDIO_ENGINE//���ʹ����Ƶ����
	AudioEngine::pauseAll();//��ͣ������Ƶ
#elif USE_SIMPLE_AUDIO_ENGINE//���ʹ�ü���Ƶ����
	SimpleAudioEngine::getInstance()->pauseBackgroundMusic();//��ͣ��������
	SimpleAudioEngine::getInstance()->pauseAllEffects();//��ͣ������Ч
#endif
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {//���������ǰ̨ʱ����
	Director::getInstance()->startAnimation();//��ʼ����

#if USE_AUDIO_ENGINE
    AudioEngine::resumeAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    SimpleAudioEngine::getInstance()->resumeAllEffects();
#endif
}

Vec2 operator*(const Vec2& lhs, const Size& rhs) {
      // ������ Vec2 �� x �� y �ֱ����
      return Vec2(lhs.x * rhs.width, lhs.y * rhs.height);
}