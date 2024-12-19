#ifndef __Enemy_NODE_H__
#define __Enemy_NODE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Effect/Effects.h"
#include "BasePlayer.h"
#include "stdlib.h"


USING_NS_CC;
using namespace ui;
class Enemy : public BasePlayer
{
public:
	friend class Player;//友元类
	int direction;
	bool leisure=true;//是否在休闲状态


	virtual bool init();//初始化函数，会在场景创建时调用

	void update(float dt);//更新函数，每帧调用一次
	//bool testCol(Sprite* other);


	void ordinaryAttack(); //普通攻击
	//e技能
	void skillE();
	void skillQ();

	//void moveAnimation(Vector<SpriteFrame*> frame, int actionTag); // 人物移动动画
	void updatePlayerOrientation(); //更新人物朝向

	CREATE_FUNC(Enemy);//创建一个Enemy对象
private:
	float walktime;




	ProgressTimer* Enemy_hpBar;//血条
	Sprite* Enemy_hpBar_bg;//血条背景
	Label* Enemy_hpLabel;//血量标签




};
#endif 
