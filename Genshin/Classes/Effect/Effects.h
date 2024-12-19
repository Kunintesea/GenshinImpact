#ifndef __EFFECTS_NODE_H__
#define __EFFECTS_NODE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;



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


class Effects : public Node
{
public:
	virtual bool init();//��ʼ�����������ڳ�������ʱ����
	void EffectsAnimation(Vector<SpriteFrame*> frame, int actionTag); // ����

	//�Ƕ�����ģ�ֻ��Ҫ�����СΪ��ӦͼƬ�����������Ļ���
	void EffectsSize(std::string mm);


	CREATE_FUNC(Effects);

	//Sprite������Ч
	Sprite* effect;

	//�˺�����
	int damage_type= Physical;
	//�˺�����
	float damage_rate = 1;


	//��Ч�İ�Χ��
	Rect effectRect;


	//��Ч����
	Vector<SpriteFrame*> Explode;
	Vector<SpriteFrame*> Superconducting;
	Vector<SpriteFrame*> Shocked;
	Vector<SpriteFrame*> Evaporate;
	Vector<SpriteFrame*>saber_normal;//����ͨ����

	//����Ȯ����
	Vector<SpriteFrame*> HellDog_explosion;
	Vector<SpriteFrame*> HellDog_q_explosion;

	//��������ײ��
	Sprite* Bat_Fire;
	
};

#endif 
