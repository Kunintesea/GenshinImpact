#ifndef __BASEPLAYER_NODE_H__
#define __BASEPLAYER_NODE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Effect/Effects.h"

USING_NS_CC;
using namespace ui;

//对各种类型的元素伤害的定义。有物理、风、岩、雷、草、水、火、冰，对应数字0-7
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





class BasePlayer : public Node
{
public:
	virtual bool init();//初始化函数，会在场景创建时调用

	Sprite* getBody() { return m_body; }//获取身体

	//实现数值改变
	//受伤害，参数为伤害值和伤害类型以及是否触发元素反应
	void hurt(int damage, int damage_type, bool reaction);



	//人物伤害数字，最多20个
	Label* m_damage_label[20];
	//元素反应相关文字，最多20个
	Label* m_element_label[20];


protected:
	CREATE_FUNC(BasePlayer);//创建一个Player对象

	//人物身体组成部分
	Sprite* m_body;//身体
	//人物状态
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
