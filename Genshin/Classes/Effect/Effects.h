#ifndef __EFFECTS_NODE_H__
#define __EFFECTS_NODE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;



class Effects : public Node
{
public:
	virtual bool init();//初始化函数，会在场景创建时调用
	void EffectsAnimation(Vector<SpriteFrame*> frame, int actionTag); // 动画


	CREATE_FUNC(Effects);

	//Sprite，放特效
	Sprite* effect;


	//特效动画
	Vector<SpriteFrame*> Explode;
	Vector<SpriteFrame*> Superconducting;
	Vector<SpriteFrame*> Shocked;
	Vector<SpriteFrame*> Evaporate;
};

#endif 
