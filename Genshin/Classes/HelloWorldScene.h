#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "newCamera.h"
#include "bag/bag.h"
class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

	virtual bool init();//初始化函数，会在场景创建时调用


	//void menuClickCallBack(Ref* sender);//控制精灵的移动，传入一个参数，表示移动的方向
	void update(float dt);//更新函数，每帧调用一次
	void menuCloseCallback(cocos2d::Ref* pSender);//退出按钮的回调函数

    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
private:
	newCamera* newCamera;//相机
	Bag* bag; //背包
	MenuItemImage* closeItem;//关闭按钮
	Vec2 closeItemInitialPosition;//关闭按钮的初始位置
};

#endif // __HELLOWORLD_SCENE_H__
