#ifndef __PLAYER_NODE_H__
#define __PLAYER_NODE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "newCamera.h"
#include "Effect/Effects.h"
#include "mapManager\mapManager.h"
#include "BasePlayer.h"
#define PI 3.1415926535897

USING_NS_CC;
using namespace ui;
class newCamera;
class PlayerStatusUI;





class Player : public BasePlayer
{
public:
	friend class PlayerStatusUI;//��Ԫ��
	friend class Enemy;
	virtual bool init();//��ʼ�����������ڳ�������ʱ����

	void update(float dt);//���º�����ÿ֡����һ��


	void getPlayerOrientation(Vec2 position);//��������¼����������ﳯ��
	void dodge(Vec2 position);//����
	void ordinaryAttack(); //��ͨ����

	void updatePlayerOrientation(); //�������ﳯ��
	void updatePlayerPosition(float dt); //��������λ��
	void weaponRotate(Vec2 position); //����ת��
	void updateWeaponRotation(float dt); //��������ת�����

	Sprite* getBody() { return m_body; }//��ȡ����
	bool getKeyBoardState(EventKeyboard::KeyCode key) { return keyMap[key]; }


	void getCamera(newCamera* camera) { myCamera = camera; }
	//�������˵ĺ���
	void attackEnemy();




	CREATE_FUNC(Player);//����һ��Player����
private:
	newCamera* myCamera; //�������
	float angleSpeed;
	//��������������ɲ���
	Sprite* m_head;//ͷ��
	Sprite* m_equipment;//װ��

	//����
	Sprite* m_weapon;
	//Sprite* m_weapon_light;
	Vec2 weaponPosition;
	float weaponAngle; //������ת�Ƕ�

	//�����¼�����
	std::map<EventKeyboard::KeyCode, bool> keyMap;//����һ��map�������洢������״̬
	//����¼�����
	std::vector<bool>mouseState = { false,false,false,false }; //��������

	//���ﶯ��
	Vector<SpriteFrame*> staticForwards;


	float m_stamina = 100;//����
	float m_max_stamina = 100;//�������

	int m_exp = 20;//����ֵ
	int m_max_exp = 100;//�����ֵ

	
};

#endif 
