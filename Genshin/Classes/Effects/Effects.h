#ifndef __EFFECTS_NODE_H__
#define __EFFECTS_NODE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;




class Effects : public Node
{
public:
	virtual bool init();//��ʼ�����������ڳ�������ʱ����
    void update(float dt);//���º�����ÿ֡����һ��

	CREATE_FUNC(Effects);//����һ��Player����
private:
	//Sprite������Ч
	Sprite* effect;


	//��Ч����
	Vector<SpriteFrame*> Explode;
	Vector<SpriteFrame*> walk_back;
	Vector<SpriteFrame*> walk_front;
	Vector<SpriteFrame*> walk_left;
	Vector<SpriteFrame*> walk_right;
	Vector<SpriteFrame*> staticForwards;
};

#endif 
