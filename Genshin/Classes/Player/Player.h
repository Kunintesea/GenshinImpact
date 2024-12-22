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
      ui::Button* button; //��ť
      Sprite* item; //��Ʒ
      bool isEmpty; //�Ƿ�����Ʒ
      bool isSelected; //�Ƿ�ѡ��
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
	friend class PlayerStatusUI;//��Ԫ��
	friend class Enemy;
	friend class HelloWorld;
	virtual bool init();//��ʼ�����������ڳ�������ʱ����

	void update(float dt);//���º�����ÿ֡����һ��


	void getPlayerOrientation(Vec2 position);//��������¼����������ﳯ��
	void dodge(Vec2 position);//����
	void swordOrdinaryAttack(); //����ͨ����
	void bowOrdinaryAttack(); //������ͨ����

	void updatePlayerOrientation(); //�������ﳯ��
	void updatePlayerPosition(float dt); //��������λ��
	void weaponRotate(Vec2 position); //����ת��
	void updateWeaponRotation(float dt); //��������ת�����

	Sprite* getBody() { return m_body; }//��ȡ����
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
	//�������˵ĺ���
	void attackEnemy();

	void e(); //e����
	void q(); //q����

	//���ﻻװ
	void selectButton(Ref* sender);
	void upgradeEquipment(Ref* sender);

	//��ȡ�Ի�״̬
	bool getIsDialog() { return isdialog; }
	//���öԻ�״̬
	void setIsDialog(bool is) { isdialog = is; }
	void resetKeyF() { keyMap[EventKeyboard::KeyCode::KEY_F] = false; }

	CREATE_FUNC(Player);//����һ��Player����
private:

      bool isdialog = false;//�Ƿ��ڶԻ�������ǣ�������������Ĳ�������Ч

	newCamera* myCamera; //�������
	float angleSpeed;
	//��������������ɲ���
	Sprite* m_equipment;//װ��
	//Sprite* m_e;//e����


	//��������
	int base_attack = 10;//����������
	float base_defense = 0.1;//����������
	int base_hp = 100;//����Ѫ��
	//��������
	int extra_attack = 0;//���⹥����
	float extra_defense = 0;//���������
	int extra_hp = 0;//����Ѫ��


	bool haveQ = false;//�Ƿ����Q����
	bool haveE = false;//�Ƿ����E����


	//e����
	bool isE = false;

	//����
	Sprite* m_weapon;
	Sprite* m_weapon2;
	Vec2 weaponPosition;
	float weaponAngle; //������ת�Ƕ�
	upgradeLevel upgradeSwordLevel[4] = {}; //�����ȼ�
	upgradeLevel upgradeBowLevel[4] = {}; //�����ȼ�

	//�����¼�����
	std::map<EventKeyboard::KeyCode, bool> keyMap;//����һ��map�������洢������״̬
	//����¼�����
	std::vector<bool>mouseState = { false,false,false,false }; //��������

	//���ﶯ��
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

	float m_stamina = 100;//����
	float m_max_stamina = 100;//�������

	int m_exp = 20;//����ֵ
	int m_max_exp = 100;//�����ֵ
	int cost_exp = 0;//���þ���ֵ

	//���ﻻװ
	bool isOnBoard = false;
	MyButton swordButtons[6] = {};
	MyButton bowButtons[6] = {};
	ui::Button* upgrade[4] = {}; //����
};

#endif 
