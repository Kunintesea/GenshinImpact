#ifndef __PLAYER_NODE_H__
#define __PLAYER_NODE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "newCamera.h"
#include "Effect/Effects.h"
#include "mapManager\mapManager.h"
#include "BasePlayer.h"
#include "Scene/MapScene.h"
#define PI 3.1415926535897

USING_NS_CC;
using namespace ui;
class newCamera;
class PlayerStatusUI;
class HelloWorld;


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

	CREATE_FUNC(Player);//创建一个Player对象
private:
	newCamera* myCamera; //相机精灵
	float angleSpeed;
	//人物身体其他组成部分
	Sprite* m_head;//头部
	Sprite* m_equipment;//装备
	Sprite* m_e;//e技能


	//e技能
	bool isE = false;

	//武器
	Sprite* m_weapon;
	Sprite* m_weapon2;
	Vec2 weaponPosition;
	float weaponAngle; //武器旋转角度

	//键盘事件监听
	std::map<EventKeyboard::KeyCode, bool> keyMap;//创建一个map，用来存储按键的状态
	//鼠标事件监听
	std::vector<bool>mouseState = { false,false,false,false }; //上下左右

	//人物动画
	Vector<SpriteFrame*> sword_walk_back;
	Vector<SpriteFrame*> sword_walk_front;
	Vector<SpriteFrame*> sword_walk_left;
	Vector<SpriteFrame*> sword_walk_right;
	Vector<SpriteFrame*> sword_staticForwards;
	Vector<SpriteFrame*> bow_walk_back;
	Vector<SpriteFrame*> bow_walk_front;
	Vector<SpriteFrame*> bow_walk_left;
	Vector<SpriteFrame*> bow_walk_right;
	Vector<SpriteFrame*> bow_staticForwards;

	float m_stamina = 100;//体力
	float m_max_stamina = 100;//最大体力

	int m_exp = 20;//经验值
	int m_max_exp = 100;//最大经验值

	
};

#endif 
