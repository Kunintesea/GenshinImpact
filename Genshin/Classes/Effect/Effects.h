#ifndef __EFFECTS_NODE_H__
#define __EFFECTS_NODE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;



enum ElementType
{
	Physical = 0,
	Wind = 1,
	Rock = 2,
	Thunder = 3,
	Grass = 4,
	Water = 5,
	Fire = 6,
	Ice = 7
};


class Effects : public Node
{
public:
	virtual bool init();//初始化函数，会在场景创建时调用
	void EffectsAnimation(Vector<SpriteFrame*> frame, int actionTag); // 动画

	//非动画类的，只需要重设大小为对应图片。比如火蝙蝠的火焰
	void EffectsSize(std::string mm);


	CREATE_FUNC(Effects);

	//Sprite，放特效
	Sprite* effect;

	//伤害类型
	int damage_type= Physical;
	//伤害倍率
	float damage_rate = 1;


	//特效的包围盒
	Rect effectRect;


	//特效动画
	Vector<SpriteFrame*> Explode;
	Vector<SpriteFrame*> Superconducting;
	Vector<SpriteFrame*> Shocked;
	Vector<SpriteFrame*> Evaporate;
	Vector<SpriteFrame*>saber_normal;//剑普通攻击

	//地狱犬攻击
	Vector<SpriteFrame*> HellDog_explosion;
	Vector<SpriteFrame*> HellDog_q_explosion;

	//火蝙蝠碰撞箱
	Sprite* Bat_Fire;
	
};

#endif 
