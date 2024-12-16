#ifndef __Enemy_NODE_H__
#define __Enemy_NODE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Effect/Effects.h"
#include "BasePlayer.h"

USING_NS_CC;
using namespace ui;
class Enemy : public BasePlayer
{
public:
	virtual bool init();//初始化函数，会在场景创建时调用

	void update(float dt);//更新函数，每帧调用一次
	bool testCol(Sprite* other);


	void ordinaryAttack(); //普通攻击

	void moveAnimation(Vector<SpriteFrame*> frame, int actionTag); // 人物移动动画
	void updatePlayerOrientation(); //更新人物朝向
	void updatePlayerPosition(float dt); //更新人物位置

	Sprite* getBody() { return m_body; }//获取身体
	float getSpeed() { return speed; }//获取速度

	CREATE_FUNC(Enemy);//创建一个Enemy对象
private:
	float angleSpeed;

	//人物动画
	Vector<SpriteFrame*> walk_up;
	Vector<SpriteFrame*> walk_down;
	Vector<SpriteFrame*> walk_left;
	Vector<SpriteFrame*> walk_right;


};
#endif 
