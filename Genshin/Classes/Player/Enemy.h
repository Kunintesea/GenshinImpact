#ifndef __Enemy_NODE_H__
#define __Enemy_NODE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Effect/Effects.h"
#include "BasePlayer.h"
#include "stdlib.h"


USING_NS_CC;
using namespace ui;
class Enemy : public BasePlayer
{
public:
	friend class Player;//��Ԫ��
	int direction;
	bool leisure=true;//�Ƿ�������״̬


	virtual bool init();//��ʼ�����������ڳ�������ʱ����

	void update(float dt);//���º�����ÿ֡����һ��
	//bool testCol(Sprite* other);


	void ordinaryAttack(); //��ͨ����
	//e����
	void skillE();
	void skillQ();
	void updatePlayerOrientation(); //�������ﳯ��

	//��ȡ��ȴʱ��
	float get1CD() { return m_1_CD; }
	//������ȴ
	void set1CD() { m_1_CD = m_1_max_CD; }

	CREATE_FUNC(Enemy);//����һ��Enemy����
private:
	float walktime;

	//����1��ȴʱ��
	float m_1_CD = 0;
	float m_1_max_CD = 10;







};
#endif 
