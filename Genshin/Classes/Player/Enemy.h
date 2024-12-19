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

	//void moveAnimation(Vector<SpriteFrame*> frame, int actionTag); // �����ƶ�����
	void updatePlayerOrientation(); //�������ﳯ��

	CREATE_FUNC(Enemy);//����һ��Enemy����
private:
	float walktime;




	ProgressTimer* Enemy_hpBar;//Ѫ��
	Sprite* Enemy_hpBar_bg;//Ѫ������
	Label* Enemy_hpLabel;//Ѫ����ǩ




};
#endif 
