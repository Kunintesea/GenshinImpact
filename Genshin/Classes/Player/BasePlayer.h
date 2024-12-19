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
	//virtual bool init();//��ʼ�����������ڳ�������ʱ����

		//�����˺����֣����20��
	Label* m_damage_label[20];
	//Ԫ�ط�Ӧ������֣����20��
	Label* m_element_label[20];

	//ʵ����ֵ�ı�
	//���˺�������Ϊ�˺�ֵ���˺������Լ��Ƿ�Ҫ����Ԫ�ط�Ӧ
	void hurt(int damage, int damage_type, bool reaction);
	//����Ԫ�ظ���ͼ��ĺ���
	void setElementSprite(int element_type);

	//Ч����������������Ч��ʱ����
	void effectTrigger(std::string effect_type);
	void moveAnimation(Vector<SpriteFrame*> frame, int actionTag);

	//�ж������Ƿ����еĺ���
	//���������࣬�ж���û��
	bool PlayerAttack(Effects* me, BasePlayer* other);
	//��ȡ������
	int getAttack() { return m_attack; }

	//���ݳ�ʼ������
	void initData();
	float getSpeed() { return speed; }//��ȡ�ٶ�

	//�ж���
	Rect m_bodyRect;

	int getmp() { return m_mp; }//��ȡԪ������
	//��ȡ����
	Sprite* getBody() { return m_body; }
	//��ȡ����
	std::string getNaming() { return m_name; }
	void naming(std::string nn) { m_name = nn; }//��������

	//�洢�����Ч�����飬����������ֵ����Ч�Լ���ı��
	Effects* m_effect[20];
	//дһ���������ܣ���Ҫʵ��Ч����ÿһ�ι�����ͬһ������ֻ�����һ���˺����Բ�ͬ����û��������ơ��������������Ҫ������ÿһ����Чֻ�ܶ�ͬһ���������һ���˺�
	//���������һ����ά���飬��һ��ά������Ч���ڶ���ά���ǵ��ˣ������Ӧλ��Ϊ0�����ܶ������������˺�
	int m_effect_index[20][20] = { 0 };



	//��������
	//void setName(std::string name) { m_name = name; }
	bool isDead = false;//�Ƿ�����

protected:

	float speed;

	//���ﶯ��
	Vector<SpriteFrame*> walk_up;
	Vector<SpriteFrame*> walk_down;
	Vector<SpriteFrame*> walk_left;
	Vector<SpriteFrame*> walk_right;

	//����������ɲ���
	Sprite* m_body;//����
	//����״̬
	bool isDodge = false;//�Ƿ�����
	bool isWeapon = false;//�Ƿ�����������
	bool isflying = false; //�������������ڷ���

	//��������
	//�������������ϵ�Ԫ�أ�0��Ϊû�У�1��Ϊ��
	float m_element[8] = { 0,0,0,0,0,0,0,0 };

	std::string m_name = "MM";//��������

	//������
	int m_attack = 10;

	//����
	int m_shield = 0;//����ֵ
	int m_hp = 100;//Ѫ��
	int m_max_hp = 100;//���Ѫ��

	int m_mp = 50;//Ԫ������
	int m_max_mp = 100;//���Ԫ������
	bool m_isElement[8] = { false,false,false,false,false,false,false,false };//Ԫ��״̬
	float m_defense_origin = 0;
	float m_defense = m_defense_origin;//�������������������Ǽ���һ���˺�
	int level = 1;//�ȼ�

	//һЩ״̬Ч��
	float m_superconductivity = 0;//����״̬����ɼ���


	//������ȴʱ��
	float m_E_CD = 0;//E������ȴʱ��
	float m_Q_CD = 0;//Q������ȴʱ��

	//�����ȴʱ��
	float m_max_E_CD = 5;//E������ȴʱ��
	float m_max_Q_CD = 10;//Q������ȴʱ��

	//����ͷ����ʾԪ�ظ���������������ͼ��
	Sprite* m_element_sprite[2];
	int m_element_sprite_type[2] = {};//Ԫ�ظ���ͼ������

	//����ĳ�ֹ���
	bool m_immune[8] = { false,false,false,true,false,false,false,false };

	//��ʾ״̬������
	statement m_statement[99];
	//��¼״̬ʱ�������
	float m_statement_time[99];

	//״̬����
	//int m_statement_count=0;


};
#endif 