#ifndef _DATA_MODEL_H_
#define _DATA_MODEL_H_

#include "cocos2d.h"
#include<iostream>

USING_NS_CC;
using namespace ui;




class Status : public Node
{

public:
	CREATE_FUNC(Status);//创建一个Player对象

	float speed;//速度
	//人物状态
	bool isDead = false;//是否死亡
	bool isDodge = false;//是否闪避

	//人物数据
	//附着在人物身上的元素，0则为没有，1则为有
	float m_element[8] = { 0,0,0,0,0,0,0,0 };

	std::string m_name = "MM";//人物名字
	int m_hp = 100;//血量
	int m_max_hp = 100;//最大血量
	int m_mp = 50;//元素能量
	int m_max_mp = 100;//最大元素能量
	bool m_isElement[8] = { false,false,false,false,false,false,false,false };//元素状态
	float m_defense = 0;//防御。防御力的作用是减少一切伤害

	//技能冷却时间
	float m_E_skill1_cd = 0;//E技能冷却时间
	float m_Q_skill2_cd = 0;//Q技能冷却时间

};

#endif 
