#include "Enemy.h"

USING_NS_CC;


bool Enemy::init()
{
	if (!Node::init())
	{
		return false;
	}
	//��������
	m_body = Sprite::create("Enemy/Bat_Fire/up_1.png");
	//��������ӵ��ڵ�
	this->addChild(m_body);

	//����ͷ����ʾԪ�ظ���
	//��ʼ��Ԫ�ظ��š����ֻ��һ��Ԫ�ظ��ž���ʾ�����Ϸ��������������������Ϸ�����������
	for (int i = 0; i < 2; i++)
	{
		m_element_sprite[i] = Sprite::create("Effects/Element/Rock.png");
		m_element_sprite[i]->setScale(0.4);

		m_element_sprite[i]->setVisible(false);
		//Ĭ�����������Ϸ�
		m_element_sprite[i]->setPosition(Vec2(this->getPositionX(), this->getPositionY() + m_body->getContentSize().height / 3));
		this->addChild(m_element_sprite[i]);
	}





	//���˺�������Ԫ�ط�Ӧ���ֳ�ʼ��
	for (int i = 0; i < 20; i++)
	{
		//��ʼ��Ԫ�ط�Ӧ���֣�֧������
		m_element_label[i] = Label::createWithTTF("��Ӧ", "fonts/HarmonyOS_Sans_SC_Medium.TTF", 40);
		m_damage_label[i] = Label::createWithTTF("0", "fonts/HarmonyOS_Sans_SC_Medium.TTF", 30);


		//�Ӻ�ɫ���
		m_element_label[i]->enableOutline(Color4B::BLACK, 2);
		m_damage_label[i]->enableOutline(Color4B::BLACK, 2);
		m_element_label[i]->setVisible(false);//���ò��ɼ�
		m_damage_label[i]->setVisible(false);//���ò��ɼ�
		
	}

	// ���ض���
	Size bodySize = m_body->getContentSize();
	//�˶�����֡
	//"D:\Github_Document\GenshinImpact\Genshin\Resources\Enemy\Bat_Fire\up_1.png"
	SpriteFrame* up_1 = SpriteFrame::create("Enemy/Bat_Fire/up_1.png", Rect(0, 0, bodySize.width, bodySize.height));
	SpriteFrame* up_2 = SpriteFrame::create("Enemy/Bat_Fire/up_2.png", Rect(0, 0, bodySize.width, bodySize.height));
	walk_up.pushBack(up_1);
	walk_up.pushBack(up_2);
	SpriteFrame* down_1 = SpriteFrame::create("Enemy/Bat_Fire/down_1.png", Rect(0, 0, bodySize.width, bodySize.height));
	SpriteFrame* down_2 = SpriteFrame::create("Enemy/Bat_Fire/down_2.png", Rect(0, 0, bodySize.width, bodySize.height));
	walk_down.pushBack(down_1);
	walk_down.pushBack(down_2);
	SpriteFrame* left_1 = SpriteFrame::create("Enemy/Bat_Fire/left_1.png", Rect(0, 0, bodySize.width, bodySize.height));
	SpriteFrame* left_2 = SpriteFrame::create("Enemy/Bat_Fire/left_2.png", Rect(0, 0, bodySize.width, bodySize.height));
	walk_left.pushBack(left_1);
	walk_left.pushBack(left_2);
	SpriteFrame* right_1 = SpriteFrame::create("Enemy/Bat_Fire/right_1.png", Rect(0, 0, bodySize.width, bodySize.height));
	SpriteFrame* right_2 = SpriteFrame::create("Enemy/Bat_Fire/right_2.png", Rect(0, 0, bodySize.width, bodySize.height));
	walk_right.pushBack(right_1);
	walk_right.pushBack(right_2);

	//���������

	return true;

}