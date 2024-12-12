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

//�Ը������͵�Ԫ���˺��Ķ��塣�������硢�ҡ��ס��ݡ�ˮ���𡢱�����Ӧ����0-7
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
	friend class PlayerStatusUI;//��Ԫ��
	virtual bool init();//��ʼ�����������ڳ�������ʱ����

	void update(float dt);//���º�����ÿ֡����һ��
	bool testCol(Sprite* other);


	void getPlayerOrientation(Vec2 position);//��������¼����������ﳯ��
	void dodge(Vec2 position);//����
	void ordinaryAttack(); //��ͨ����

	void moveAnimation(Vector<SpriteFrame*> frame, int actionTag); // �����ƶ�����
	void updatePlayerOrientation(); //�������ﳯ��
	void updatePlayerPosition(float dt); //��������λ��
	void weaponRotate(Vec2 position); //����ת��
	void updateWeaponRotation(float dt); //��������ת�����

	Sprite* getBody() { return m_body; }//��ȡ����
	bool getKeyBoardState(EventKeyboard::KeyCode key) { return keyMap[key]; }
	float getSpeed() { return speed; }//��ȡ�ٶ�

	void getCamera(newCamera* camera) { myCamera = camera; }




	//ʵ����ֵ�ı�
	//���˺�������Ϊ�˺�ֵ���˺������Լ��Ƿ�Ҫ����Ԫ�ط�Ӧ
	void hurt(int damage,int damage_type,bool reaction);
	//����Ԫ�ظ���ͼ��ĺ���
	void setElementSprite(int element_type);

	//Ч����������������Ч��ʱ����
	//void effectTrigger(std::string effect_type);


	//�����˺����֣����20��
	Label* m_damage_label[20];
	//Ԫ�ط�Ӧ������֣����20��
	Label* m_element_label[20];



	CREATE_FUNC(Player);//����һ��Player����
private:
	newCamera* myCamera; //�������
	float speed;
	float angleSpeed;
	//����������ɲ���
	Sprite* m_body;//����
	Sprite* m_head;//ͷ��

	//����
	Sprite* m_weapon;
	Sprite* m_weapon_light;
	Vec2 weaponPosition;
	float weaponAngle; //������ת�Ƕ�

	//�����¼�����
	std::map<EventKeyboard::KeyCode, bool> keyMap;//����һ��map�������洢������״̬
	//����¼�����
	std::vector<bool>mouseState = { false,false,false,false }; //��������

	//���ﶯ��
	Vector<SpriteFrame*> walk_back;
	Vector<SpriteFrame*> walk_front;
	Vector<SpriteFrame*> walk_left;
	Vector<SpriteFrame*> walk_right;
	Vector<SpriteFrame*> staticForwards;


	//����ͷ����ʾԪ�ظ���������������ͼ��
	Sprite* m_element_sprite[2];
	int m_element_sprite_type[2] = {};//Ԫ�ظ���ͼ������




	//����״̬
	bool isDead = false;//�Ƿ�����
	bool isDodge = false;//�Ƿ�����
	bool isWeapon = false;//�Ƿ�����������
	bool isflying = false; //�������������ڷ���

	//��������
	//�������������ϵ�Ԫ�أ�0��Ϊû�У�1��Ϊ��
	float m_element[8] = { 0,0,0,0,0,0,0,0 };

	std::string m_name="MM";//��������

	//����
	int m_shield = 50;//����ֵ
	int m_hp=100;//Ѫ��
	int m_max_hp=100;//���Ѫ��
	float m_stamina = 100;//����
	float m_max_stamina = 100;//�������
	int m_mp = 50;//Ԫ������
	int m_max_mp = 100;//���Ԫ������
	bool m_isElement[8] = { false,false,false,false,false,false,false,false };//Ԫ��״̬
	float m_defense = 0;//�������������������Ǽ���һ���˺�
	int level = 1;//�ȼ�

	//������ȴʱ��
	float m_E_CD = 0;//E������ȴʱ��
	float m_Q_CD = 0;//Q������ȴʱ��

	//�����ȴʱ��
	float m_max_E_CD = 5;//E������ȴʱ��
	float m_max_Q_CD = 10;//Q������ȴʱ��


	//��ʾ״̬������
	std::vector<statement> m_statement;

	
};

#endif 
