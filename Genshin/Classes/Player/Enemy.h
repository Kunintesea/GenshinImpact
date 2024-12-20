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
	void updatePlayerOrientation(); //更新人物朝向

	//获取冷却时间
	float get1CD() { return m_1_CD; }
	//进入冷却
	void set1CD() { m_1_CD = m_1_max_CD; }

	CREATE_FUNC(Enemy);//创建一个Enemy对象
private:
	float walktime;

	//技能1冷却时间
	float m_1_CD = 0;
	float m_1_max_CD = 10;







};
#endif 
