#include "Enemy.h"




bool Enemy::init()
{
	if (!Node::init())
	{
		return false;
	}
	//���������
	this->scheduleUpdate();//��������ÿ֡����һ��update����


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



	//��ɫѪ��
	//����һ��Ѫ��
	Enemy_hpBar = ProgressTimer::create(Sprite::create("Me/InfoUI/hp_bar.png"));
	Enemy_hpBar_bg = Sprite::create("Me/InfoUI/hp_bar_bg.png");
	//����Ѫ��������Ϊ����
	Enemy_hpBar->setType(ProgressTimer::Type::BAR);
	//����Ѫ������㣬��������
	Enemy_hpBar->setMidpoint(Vec2(0, 0.5));//��������������0��ʾx�ᣬ0.5��ʾy�ᣬ��ʾѪ�������������м�
	//����Ѫ���ı仯��
	Enemy_hpBar->setBarChangeRate(Vec2(1, 0));
	//����Ѫ���Ĵ�С������ֱ���200��30
	Enemy_hpBar->setScaleX(100 / Enemy_hpBar->getContentSize().width);
	Enemy_hpBar->setScaleY(10 / Enemy_hpBar->getContentSize().height);
	Enemy_hpBar_bg->setScaleX(100 / Enemy_hpBar_bg->getContentSize().width);
	Enemy_hpBar_bg->setScaleY(10 / Enemy_hpBar_bg->getContentSize().height);
	//����Ѫ����λ�ã���������ͷ��
	Enemy_hpBar->setPosition(Vec2(0, this->getPositionY() + m_body->getContentSize().height));
	Enemy_hpBar_bg->setPosition(Vec2(0, this->getPositionY() + m_body->getContentSize().height ));


	this->addChild(Enemy_hpBar_bg);//��Ѫ��������ӵ��ڵ�
	this->addChild(Enemy_hpBar);//����Ѫ����ӵ��ڵ�

	//Ѫ����ǩ
	Enemy_hpLabel = Label::createWithTTF("100/100", "fonts/Marker Felt.ttf", 12);//��������Ϊ��100/100��������Ϊ��Marker Felt������СΪ24
	//�����ɫ���
	Enemy_hpLabel->enableOutline(Color4B::BLACK, 2);
	//����λ�ã���Ѫ����λ��һ��
	Enemy_hpLabel->setPosition(Vec2(0, this->getPositionY() + m_body->getContentSize().height));
	this->addChild(Enemy_hpLabel);//��Ѫ����ǩ��ӵ��ڵ�




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


void Enemy::update(float t)
{
	walktime += 0.016;//ÿ֡����0.016



	//ÿ3�������һ�������ƶ�
	if (walktime >= 1)
	{
		walktime = 0;
		//��ȡ������ʱ�䣬��Enemy�ĸ��ڵ㣬�Ӷ��������������������




		srand(time(NULL));
		//ʵ��һ�����������int�����
		int direction = rand() % 4;


		switch (direction)
		{
		case 0:

			//�ƶ�����moveBy�������ƶ���һ����
			this->runAction(MoveBy::create(1, Vec2(0, 50)));

			//����
			moveAnimation(walk_up, 4);
			break;
		case 1:
			this->runAction(MoveBy::create(1, Vec2(0, -50)));
			moveAnimation(walk_down, 3);
			break;
		case 2:
			this->runAction(MoveBy::create(1, Vec2(-50, 0)));
			moveAnimation(walk_left, 2);
			break;
		case 3:
			this->runAction(MoveBy::create(1, Vec2(50, 0)));
			moveAnimation(walk_right, 1);
			break;
		}
		
	}


	//����Ѫ��
	Enemy_hpBar->setPercentage(float(m_hp) / float(m_max_hp) * 100);
	//����Ѫ��
	Enemy_hpLabel->setString(std::to_string(m_hp) + "/"+ std::to_string(m_max_hp));

}