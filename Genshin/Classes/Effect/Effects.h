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
	void EffectsAnimation(Vector<SpriteFrame*> frame, int actionTag); // ����


	CREATE_FUNC(Effects);

	//Sprite������Ч
	Sprite* effect;


	//��Ч����
	Vector<SpriteFrame*> Explode;
	Vector<SpriteFrame*> Superconducting;
	Vector<SpriteFrame*> Shocked;
	Vector<SpriteFrame*> Evaporate;
};

#endif 
