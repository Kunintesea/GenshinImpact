#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "newCamera.h"
#include "bag/bag.h"
class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

	virtual bool init();//��ʼ�����������ڳ�������ʱ����


	//void menuClickCallBack(Ref* sender);//���ƾ�����ƶ�������һ����������ʾ�ƶ��ķ���
	void update(float dt);//���º�����ÿ֡����һ��
	void menuCloseCallback(cocos2d::Ref* pSender);//�˳���ť�Ļص�����

    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
private:
	newCamera* newCamera;//���
	Bag* bag; //����
	MenuItemImage* closeItem;//�رհ�ť
	Vec2 closeItemInitialPosition;//�رհ�ť�ĳ�ʼλ��
};

#endif // __HELLOWORLD_SCENE_H__
