#ifndef __PLAYER_NODE_H__
#define __PLAYER_NODE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "newCamera.h"
#include "Effect/Effects.h"
#include "mapManager\mapManager.h"
#include "BasePlayer.h"
#include "Scene/MapScene.h"
#include "json/rapidjson.h"
#include "json/writer.h"
#include "json/document.h"
#include "json/prettywriter.h"
#include "json/stringbuffer.h"
//direct.h
#include <direct.h>

#define PI 3.1415926535897

USING_NS_CC;
using namespace ui;
class newCamera;
class PlayerStatusUI;
class HelloWorld;

struct MyButton
{
      ui::Button* button; //按钮
      Sprite* item; //物品
      bool isEmpty; //是否有物品
      bool isSelected; //是否被选中
};

struct upgradeLevel
{
      int weaponLevel = 0;
      int nowExpCost = 0;
      const int needExpCost = 10;
      Label* showLevel;
};




class Player : public BasePlayer
{
public:
	friend class PlayerStatusUI;//友元类
	friend class Enemy;
	friend class HelloWorld;
	virtual bool init();//初始化函数，会在场景创建时调用

	void update(float dt);//更新函数，每帧调用一次


	void getPlayerOrientation(Vec2 position);//监听鼠标事件，更新人物朝向
	void dodge(Vec2 position);//闪避
	void swordOrdinaryAttack(); //剑普通攻击
	void bowOrdinaryAttack(); //弓箭普通攻击

	void updatePlayerOrientation(); //更新人物朝向
	void updatePlayerPosition(float dt); //更新人物位置
	void weaponRotate(Vec2 position); //武器转动
	void updateWeaponRotation(float dt); //更新武器转动结果

	Sprite* getBody() { return m_body; }//获取身体
	bool getKeyBoardState(EventKeyboard::KeyCode key) { return keyMap[key]; }
	void clearKeyBoardState() {
	      keyMap[EventKeyboard::KeyCode::KEY_LEFT_ARROW] = false;
	      keyMap[EventKeyboard::KeyCode::KEY_RIGHT_ARROW] = false;
	      keyMap[EventKeyboard::KeyCode::KEY_UP_ARROW] = false;
	      keyMap[EventKeyboard::KeyCode::KEY_DOWN_ARROW] = false;
	      keyMap[EventKeyboard::KeyCode::KEY_M] = false;
	      keyMap[EventKeyboard::KeyCode::KEY_F] = false;
	}


	void getCamera(newCamera* camera) { myCamera = camera; }
	//攻击敌人的函数
	void attackEnemy();

	void e(); //e技能
	void q(); //q技能

	//人物换装
	void selectButton(Ref* sender);
	void upgradeEquipment(Ref* sender);

	//获取对话状态
	bool getIsDialog() { return isdialog; }
	//设置对话状态
	void setIsDialog(bool is) { isdialog = is; }
	void resetKeyF() { keyMap[EventKeyboard::KeyCode::KEY_F] = false; }

	CREATE_FUNC(Player);//创建一个Player对象
private:

      bool isdialog = false;//是否在对话，如果是，则除了鼠标以外的操作都无效

	newCamera* myCamera; //相机精灵
	float angleSpeed;
	//人物身体其他组成部分
	Sprite* m_equipment;//装备
	//Sprite* m_e;//e技能


	//基础属性
	int base_attack = 10;//基础攻击力
	float base_defense = 0.1;//基础防御力
	int base_hp = 100;//基础血量
	//额外属性
	int extra_attack = 0;//额外攻击力
	float extra_defense = 0;//额外防御力
	int extra_hp = 0;//额外血量


	bool haveQ = false;//是否解锁Q技能
	bool haveE = false;//是否解锁E技能


	//e技能
	bool isE = false;

	//武器
	Sprite* m_weapon;
	Sprite* m_weapon2;
	Vec2 weaponPosition;
	float weaponAngle; //武器旋转角度
	upgradeLevel upgradeSwordLevel[4] = {}; //武器等级
	upgradeLevel upgradeBowLevel[4] = {}; //武器等级

	//键盘事件监听
	std::map<EventKeyboard::KeyCode, bool> keyMap;//创建一个map，用来存储按键的状态
	//鼠标事件监听
	std::vector<bool>mouseState = { false,false,false,false }; //上下左右

	//人物动画
	Vector<SpriteFrame*> sword1_walk_back;
	Vector<SpriteFrame*> sword1_walk_front;
	Vector<SpriteFrame*> sword1_walk_left;
	Vector<SpriteFrame*> sword1_walk_right;
	Vector<SpriteFrame*> sword1_staticForwards;
	Vector<SpriteFrame*> bow1_walk_back;
	Vector<SpriteFrame*> bow1_walk_front;
	Vector<SpriteFrame*> bow1_walk_left;
	Vector<SpriteFrame*> bow1_walk_right;
	Vector<SpriteFrame*> bow1_staticForwards;
	Vector<SpriteFrame*> sword2_walk_back;
	Vector<SpriteFrame*> sword2_walk_front;
	Vector<SpriteFrame*> sword2_walk_left;
	Vector<SpriteFrame*> sword2_walk_right;
	Vector<SpriteFrame*> sword2_staticForwards;
	Vector<SpriteFrame*> bow2_walk_back;
	Vector<SpriteFrame*> bow2_walk_front;
	Vector<SpriteFrame*> bow2_walk_left;
	Vector<SpriteFrame*> bow2_walk_right;
	Vector<SpriteFrame*> bow2_staticForwards;

	float m_stamina = 100;//体力
	float m_max_stamina = 100;//最大体力

	int m_exp = 20;//经验值
	int m_max_exp = 100;//最大经验值
	int cost_exp = 0;//已用经验值

	//人物换装
	bool isOnBoard = false;
	MyButton swordButtons[6] = {};
	MyButton bowButtons[6] = {};
	ui::Button* upgrade[4] = {}; //升级
};

#endif 
