#ifndef __BASEPLAYER_NODE_H__
#define __BASEPLAYER_NODE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Effect/Effects.h"

USING_NS_CC;
using namespace ui;

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





class BasePlayer : public Node
{
public:
	virtual bool init();//��ʼ�����������ڳ�������ʱ����

	Sprite* getBody() { return m_body; }//��ȡ����

	//ʵ����ֵ�ı�
	//���˺�������Ϊ�˺�ֵ���˺������Լ��Ƿ񴥷�Ԫ�ط�Ӧ
	void hurt(int damage, int damage_type, bool reaction);



	//�����˺����֣����20��
	Label* m_damage_label[20];
	//Ԫ�ط�Ӧ������֣����20��
	Label* m_element_label[20];


protected:
	CREATE_FUNC(BasePlayer);//����һ��Player����

	//����������ɲ���
	Sprite* m_body;//����
	//����״̬
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
