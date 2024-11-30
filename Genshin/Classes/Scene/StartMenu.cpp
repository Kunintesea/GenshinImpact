#include"StartMenu.h"
#include"HelloWorldScene.h"



Scene* StartMenu::createScene()
{
	return StartMenu::create();
}

bool StartMenu::init()//初始化函数，会在场景创建时调用
{

	if (!Scene::init())//如果初始化失败
	{
		return false;//返回false
	}
	//创建一个精灵，背景图片是GenshinStart.jpg,位置设在左上角
	auto background = Sprite::create("GenshinStart.jpg");
	background->setPosition(Vec2(0, 0));
	background->setAnchorPoint(Vec2(0, 0));//设置锚点
	//适当缩放背景图片，使其铺满整个屏幕
	background->setScale(1.25);
	this->addChild(background, 0);//将背景图片添加到场景中

	//加按钮，使点击屏幕任意位置都能进入HelloWorld场景
	auto listener = EventListenerTouchOneByOne::create();//创建一个触摸监听器
	listener->onTouchBegan = [=](Touch* touch, Event* event)//当触摸开始时调用
		{
			Director::getInstance()->replaceScene(HelloWorld::createScene());//跳转场景到HelloWorld
			return true;
		};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);//将监听器加入到事件分发器中





	return true;
}