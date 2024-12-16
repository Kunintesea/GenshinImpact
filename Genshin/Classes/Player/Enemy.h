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

	int direction;


	virtual bool init();//��ʼ�����������ڳ�������ʱ����

	void update(float dt);//���º�����ÿ֡����һ��
	//bool testCol(Sprite* other);


	void ordinaryAttack(); //��ͨ����

	//void moveAnimation(Vector<SpriteFrame*> frame, int actionTag); // �����ƶ�����
	void updatePlayerOrientation(); //�������ﳯ��
	//void updatePlayerPosition(float dt); //��������λ��

	//Sprite* getBody() { return m_body; }//��ȡ����
	//float getSpeed() { return speed; }//��ȡ�ٶ�

	CREATE_FUNC(Enemy);//����һ��Enemy����
private:
	float walktime;

	//���ﶯ��
	Vector<SpriteFrame*> walk_up;
	Vector<SpriteFrame*> walk_down;
	Vector<SpriteFrame*> walk_left;
	Vector<SpriteFrame*> walk_right;


	ProgressTimer* Enemy_hpBar;//Ѫ��
	Sprite* Enemy_hpBar_bg;//Ѫ������
	Label* Enemy_hpLabel;//Ѫ����ǩ




};
#endif 