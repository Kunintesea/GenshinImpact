#ifndef __PLAYER_NODE_H__
#define __PLAYER_NODE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "newCamera.h"
#include "Effect/Effects.h"

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





class Player : public Node
{
public:
	friend class PlayerStatusUI;//��Ԫ��
	virtual bool init();//��ʼ�����������ڳ�������ʱ����

	//void update(float dt);//���º�����ÿ֡����һ��

	void getPlayerOrientation(Vec2 position);//��������¼����������ﳯ��
	void dodge(Vec2 position);//����
	void moveAnimation(Vector<SpriteFrame*> frame, int actionTag); // �����ƶ�����
	void updatePlayerOrientation(); //�������ﳯ��
	void updatePlayerPosition(float dt); //��������λ��

	Sprite* getBody() { return m_body; }//��ȡ����
	bool getKeyBoardState(EventKeyboard::KeyCode key) { return keyMap[key]; }
	float getSpeed() { return speed; }//��ȡ�ٶ�

	void getCamera(newCamera* camera) { myCamera = camera; }




	//ʵ����ֵ�ı�
	//���˺�������Ϊ�˺�ֵ���˺�����
	void hurt(int damage,int damage_type);


	//�����˺����֣����20��
	Label* m_damage_label[20];
	//Ԫ�ط�Ӧ������֣����20��
	Label* m_element_label[20];



	CREATE_FUNC(Player);//����һ��Player����
private:
	newCamera* myCamera; //�������
	float speed;
	//����������ɲ���
	Sprite* m_body;//����
	Sprite* m_head;//ͷ��


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

	//����״̬
	bool isDead = false;//�Ƿ�����
	bool isDodge = false;//�Ƿ�����

	//��������
	//�������������ϵ�Ԫ�أ�0��Ϊû�У�1��Ϊ��
	bool m_element[8] = { 0,0,0,0,0,0,0,0 };

	std::string m_name="MM";//��������
	int m_hp=100;//Ѫ��
	int m_max_hp=100;//���Ѫ��
	int m_mp = 50;//Ԫ������
	int m_max_mp = 100;//���Ԫ������
	bool m_isElement[8] = { false,false,false,false,false,false,false,false };//Ԫ��״̬
	float m_defense = 0;//�������������������Ǽ���һ���˺�

	//������ȴʱ��
	float m_E_skill1_cd = 0;//E������ȴʱ��
	float m_Q_skill2_cd = 0;//Q������ȴʱ��
	
};

#endif 
