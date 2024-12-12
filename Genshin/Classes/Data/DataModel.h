#ifndef _DATA_MODEL_H_
#define _DATA_MODEL_H_

#include "cocos2d.h"
#include<iostream>

USING_NS_CC;
using namespace ui;




class Status : public Node
{

public:
	CREATE_FUNC(Status);//����һ��Player����

	float speed;//�ٶ�
	//����״̬
	bool isDead = false;//�Ƿ�����
	bool isDodge = false;//�Ƿ�����

	//��������
	//�������������ϵ�Ԫ�أ�0��Ϊû�У�1��Ϊ��
	float m_element[8] = { 0,0,0,0,0,0,0,0 };

	std::string m_name = "MM";//��������
	int m_hp = 100;//Ѫ��
	int m_max_hp = 100;//���Ѫ��
	int m_mp = 50;//Ԫ������
	int m_max_mp = 100;//���Ԫ������
	bool m_isElement[8] = { false,false,false,false,false,false,false,false };//Ԫ��״̬
	float m_defense = 0;//�������������������Ǽ���һ���˺�

	//������ȴʱ��
	float m_E_skill1_cd = 0;//E������ȴʱ��
	float m_Q_skill2_cd = 0;//Q������ȴʱ��

};

#endif 
