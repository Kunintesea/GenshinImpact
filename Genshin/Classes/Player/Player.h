#ifndef __PLAYER_NODE_H__
#define __PLAYER_NODE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "newCamera.h"
#include "Effect/Effects.h"
#include "mapManager\mapManager.h"
#define PI 3.1415926535897

USING_NS_CC;
using namespace ui;
class newCamera;
class PlayerStatusUI;

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

struct statement
{
	float time;
	std::string name;
};




class Player : public Node
{
public:
	friend class PlayerStatusUI;//友元类
	virtual bool init();//初始化函数，会在场景创建时调用

	void update(float dt);//更新函数，每帧调用一次
	bool testCol(Sprite* other);


	void getPlayerOrientation(Vec2 position);//监听鼠标事件，更新人物朝向
	void dodge(Vec2 position);//闪避
	void ordinaryAttack(); //普通攻击

	void moveAnimation(Vector<SpriteFrame*> frame, int actionTag); // 人物移动动画
	void updatePlayerOrientation(); //更新人物朝向
	void updatePlayerPosition(float dt); //更新人物位置
	void weaponRotate(Vec2 position); //武器转动
	void updateWeaponRotation(float dt); //更新武器转动结果

	Sprite* getBody() { return m_body; }//获取身体
	bool getKeyBoardState(EventKeyboard::KeyCode key) { return keyMap[key]; }
	float getSpeed() { return speed; }//获取速度

	void getCamera(newCamera* camera) { myCamera = camera; }




	//实现数值改变
	//受伤害，参数为伤害值和伤害类型以及是否要触发元素反应
	void hurt(int damage,int damage_type,bool reaction);
	//设置元素附着图标的函数
	void setElementSprite(int element_type);

	//效果触发函数，触发效果时调用
	//void effectTrigger(std::string effect_type);


	//人物伤害数字，最多20个
	Label* m_damage_label[20];
	//元素反应相关文字，最多20个
	Label* m_element_label[20];



	CREATE_FUNC(Player);//创建一个Player对象
private:
	newCamera* myCamera; //相机精灵
	float speed;
	float angleSpeed;
	//人物身体组成部分
	Sprite* m_body;//身体
	Sprite* m_head;//头部

	//武器
	Sprite* m_weapon;
	Sprite* m_weapon_light;
	Vec2 weaponPosition;
	float weaponAngle; //武器旋转角度

	//键盘事件监听
	std::map<EventKeyboard::KeyCode, bool> keyMap;//创建一个map，用来存储按键的状态
	//鼠标事件监听
	std::vector<bool>mouseState = { false,false,false,false }; //上下左右

	//人物动画
	Vector<SpriteFrame*> walk_back;
	Vector<SpriteFrame*> walk_front;
	Vector<SpriteFrame*> walk_left;
	Vector<SpriteFrame*> walk_right;
	Vector<SpriteFrame*> staticForwards;


	//人物头顶显示元素附着情况，最多两个图标
	Sprite* m_element_sprite[2];
	int m_element_sprite_type[2] = {};//元素附着图标种类




	//人物状态
	bool isDead = false;//是否死亡
	bool isDodge = false;//是否闪避
	bool isWeapon = false;//是否是武器攻击
	bool isflying = false; //剑气或武器正在飞行

	//人物数据
	//附着在人物身上的元素，0则为没有，1则为有
	float m_element[8] = { 0,0,0,0,0,0,0,0 };

	std::string m_name="MM";//人物名字

	//护盾
	int m_shield = 50;//护盾值
	int m_hp=100;//血量
	int m_max_hp=100;//最大血量
	float m_stamina = 100;//体力
	float m_max_stamina = 100;//最大体力
	int m_mp = 50;//元素能量
	int m_max_mp = 100;//最大元素能量
	bool m_isElement[8] = { false,false,false,false,false,false,false,false };//元素状态
	float m_defense = 0;//防御。防御力的作用是减少一切伤害
	int level = 1;//等级

	//技能冷却时间
	float m_E_CD = 0;//E技能冷却时间
	float m_Q_CD = 0;//Q技能冷却时间

	//最大冷却时间
	float m_max_E_CD = 5;//E技能冷却时间
	float m_max_Q_CD = 10;//Q技能冷却时间


	//表示状态的数组
	std::vector<statement> m_statement;

	
};

#endif 
