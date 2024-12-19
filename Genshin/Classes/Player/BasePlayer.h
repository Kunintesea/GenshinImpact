#pragma once
#ifndef __BASEPLAYER_NODE_H__
#define __BASEPLAYER_NODE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Effect/Effects.h"
#include <string>
#include <vector>
#include "Effect/Effects.h"


USING_NS_CC;
using namespace ui;




struct statement
{
	float time;
	std::string name;
};

class BasePlayer : public Node
{
public:
	//virtual bool init();//初始化函数，会在场景创建时调用

		//人物伤害数字，最多20个
	Label* m_damage_label[20];
	//元素反应相关文字，最多20个
	Label* m_element_label[20];

	//实现数值改变
	//受伤害，参数为伤害值和伤害类型以及是否要触发元素反应
	void hurt(int damage, int damage_type, bool reaction);
	//设置元素附着图标的函数
	void setElementSprite(int element_type);

	//效果触发函数，触发效果时调用
	void effectTrigger(std::string effect_type);
	void moveAnimation(Vector<SpriteFrame*> frame, int actionTag);

	//判定攻击是否命中的函数
	//传入两个类，判定打没打到
	bool PlayerAttack(Effects* me, BasePlayer* other);
	//获取攻击力
	int getAttack() { return m_attack; }

	//数据初始化函数
	void initData();
	float getSpeed() { return speed; }//获取速度

	//判定框
	Rect m_bodyRect;

	int getmp() { return m_mp; }//获取元素能量
	//获取身体
	Sprite* getBody() { return m_body; }
	//获取名字
	std::string getNaming() { return m_name; }
	void naming(std::string nn) { m_name = nn; }//设置名字

	//存储玩家特效的数组，存了两个数值：特效以及其的编号
	Effects* m_effect[20];
	//写一个索引功能，需要实现效果：每一次攻击对同一个敌人只能造成一次伤害，对不同敌人没有这个限制。因此人物身上需要索引，每一个特效只能对同一个敌人造成一次伤害
	//这个索引是一个二维数组，第一个维度是特效，第二个维度是敌人，如果对应位置为0，则不能对这个敌人造成伤害
	int m_effect_index[20][20] = { 0 };



	//设置名字
	//void setName(std::string name) { m_name = name; }
	bool isDead = false;//是否死亡

protected:

	float speed;

	//人物动画
	Vector<SpriteFrame*> walk_up;
	Vector<SpriteFrame*> walk_down;
	Vector<SpriteFrame*> walk_left;
	Vector<SpriteFrame*> walk_right;

	//人物身体组成部分
	Sprite* m_body;//身体
	//人物状态
	bool isDodge = false;//是否闪避
	bool isWeapon = false;//是否是武器攻击
	bool isflying = false; //剑气或武器正在飞行

	//人物数据
	//附着在人物身上的元素，0则为没有，1则为有
	float m_element[8] = { 0,0,0,0,0,0,0,0 };

	std::string m_name = "MM";//人物名字

	//攻击力
	int m_attack = 10;

	//护盾
	int m_shield = 0;//护盾值
	int m_hp = 100;//血量
	int m_max_hp = 100;//最大血量

	int m_mp = 50;//元素能量
	int m_max_mp = 100;//最大元素能量
	bool m_isElement[8] = { false,false,false,false,false,false,false,false };//元素状态
	float m_defense_origin = 0;
	float m_defense = m_defense_origin;//防御。防御力的作用是减少一切伤害
	int level = 1;//等级

	//一些状态效果
	float m_superconductivity = 0;//超导状态，造成减防


	//技能冷却时间
	float m_E_CD = 0;//E技能冷却时间
	float m_Q_CD = 0;//Q技能冷却时间

	//最大冷却时间
	float m_max_E_CD = 5;//E技能冷却时间
	float m_max_Q_CD = 10;//Q技能冷却时间

	//人物头顶显示元素附着情况，最多两个图标
	Sprite* m_element_sprite[2];
	int m_element_sprite_type[2] = {};//元素附着图标种类

	//免疫某种攻击
	bool m_immune[8] = { false,false,false,true,false,false,false,false };

	//表示状态的数组
	statement m_statement[99];
	//记录状态时间的数组
	float m_statement_time[99];

	//状态数量
	//int m_statement_count=0;


};
#endif 