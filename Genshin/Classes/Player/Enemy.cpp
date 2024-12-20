#include "Enemy.h"
//#include "HelloWorldScene.h"



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


	}


	//��ֵ��ʼ��




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








	//���������

	return true;

}

float tttime;
void Enemy::update(float t)
{
	walktime += 0.016;//ÿ֡����0.016
	tttime += 0.016;

	//E������ȴ
	if (m_E_CD > 0)
	{
		m_E_CD -= 0.016;
	}
	else if (m_E_CD < 0)
	{
		m_E_CD = 0;
	}
	//Q������ȴ
	if (m_Q_CD > 0)
	{
		m_Q_CD -= 0.016;
	}
	else if (m_Q_CD < 0)
	{
		m_Q_CD = 0;
	}
	//1������ȴ
	if (m_1_CD > 0)
	{
		m_1_CD -= 0.016;
	}
	else if (m_1_CD < 0)
	{
		m_1_CD = 0;
	}


	//����Ѫ��
	Enemy_hpBar->setPercentage(float(m_hp) / float(m_max_hp) * 100);
	//����Ѫ��
	Enemy_hpLabel->setString(std::to_string(m_hp) + "/" + std::to_string(m_max_hp));
	

	//ÿ�������һ�������ƶ�
	if (walktime >= 1&&leisure)
	{
		walktime = 0;

		//�й��ɵ����������ƶ���ÿ�ε��ƶ���direction����
		if (direction == 0)
		{
			//�ƶ�����moveBy�������ƶ���һ����
			this->runAction(MoveBy::create(1, Vec2(0, 50)));
			//����
			moveAnimation(walk_up, 4);
			direction = 3;
		}
		else if (direction == 1)
		{
			this->runAction(MoveBy::create(1, Vec2(0, -50)));
			moveAnimation(walk_down, 3);
			direction = 2;
		}
		else if (direction == 2)
		{
			this->runAction(MoveBy::create(1, Vec2(-50, 0)));
			moveAnimation(walk_left, 2);
			direction =0;	
		}
		else if (direction == 3)
		{
			this->runAction(MoveBy::create(1, Vec2(50, 0)));
			moveAnimation(walk_right, 1);
			direction = 1;
		}




		//srand(time(NULL));
		////ʵ��һ�����������int�����
		//int direction = rand() % 4;


		//switch (direction)
		//{
		//case 0:

		//	//�ƶ�����moveBy�������ƶ���һ����
		//	this->runAction(MoveBy::create(1, Vec2(0, 50)));

		//	//����
		//	moveAnimation(walk_up, 4);
		//	break;
		//case 1:
		//	this->runAction(MoveBy::create(1, Vec2(0, -50)));
		//	moveAnimation(walk_down, 3);
		//	break;
		//case 2:
		//	this->runAction(MoveBy::create(1, Vec2(-50, 0)));
		//	moveAnimation(walk_left, 2);
		//	break;
		//case 3:
		//	this->runAction(MoveBy::create(1, Vec2(50, 0)));
		//	moveAnimation(walk_right, 1);
		//	break;
		//}
		
	}
	else if (!leisure)
	{
		//�ӵ�ͼ�ϻ�ȡ��ҵ�λ��
		auto player = this->getParent()->getChildByName("Me");
		//û��ȡ��ֱ�ӷ���
		if (player == nullptr)
		{
			return;
		}
		//��ȡ��ҵ�λ��
		Vec2 playerPosition = player->getPosition();



		//����ǵ���Ȯ
		if (m_name == "HellDog")
		{


			//ֻҪQ���˾ͷ�Q
			if (m_Q_CD <= 0)
			{

				//������ҳ��
				//����λ��ֱ�ӳ��
				//����ٶ�
				float dodgeSpeed = 1000;
				//��̾���
				float distance = 500;
				//��̷���
				Vec2 dodgeDirection = playerPosition - this->getPosition();
				//��̷���λ��
				dodgeDirection.normalize();
				//��ʼ���
				this->runAction(Sequence::create(MoveBy::create(distance / dodgeSpeed, dodgeDirection* distance), CallFunc::create([=] {leisure = true; }), nullptr));

				//����һ����Ч
				Effects* effect = Effects::create();
				//λ������������
				effect->setPosition(this->getPosition());
				//�󶨵�����
				this->getParent()->addChild(effect);
				//damage_typeΪ��
				effect->damage_type = Thunder;
				//���ʷ���damage_rate
				effect->damage_rate = 4;
				//����m_effect����
				for (int i = 0;i < 20;i++)
				{
					if (m_effect[i] == nullptr)
					{
						m_effect[i] = effect;
						//���������ֱ�ǩΪi
						effect->setTag(i);
						for (int j = 0; j < 20; j++)
						{
							m_effect_index[i][j] = 1;
						}
						break;
					}
				}
				effect->EffectsAnimation(effect->HellDog_q_explosion, 0);
				//ִ������������ѽڵ��Ƴ������Ұ������Ӧλ�ã�ͨ��tag��ȡ���ÿ�
				//auto removeSelf = CallFunc::create([=] {m_weapon_light->setVisible(false); m_effect[m_weapon_light->getTag()] = nullptr; });
				effect->runAction(Sequence::create(DelayTime::create(0.8), CallFunc::create([=] {effect->removeFromParent(); m_effect[effect->getTag()] = nullptr; }), nullptr));
				//Q������ȴʱ��
				m_Q_CD =8;


			}


			//���������ҳ���300����ԭ���ͷż���
			if (playerPosition.getDistance(this->getPosition()) > 300&& m_E_CD <= 0)
			{
				//�������λ�ô���һ��Ԥ��ͼ�꣬2����ͷż���
				



				//����һ��Ԥ��ͼ��
				Sprite* warning = Sprite::create("Effects/Warning.png");
				//����λ��
				warning->setPosition(playerPosition);
				//�󶨵�������ͼ����50
				this->getParent()->addChild(warning, 50);

				warning->runAction(Sequence::create(DelayTime::create(0.5), CallFunc::create([=] {warning->removeFromParent(); }), nullptr));

				//����������ʱ1��ִ��
				//��ʱ
				this->runAction(Sequence::create(DelayTime::create(0.5), CallFunc::create([=] {
					//����һ����Ч
					Effects* effect = Effects::create();
					//λ������������
					effect->setPosition(playerPosition);
					//�󶨵�����
					this->getParent()->addChild(effect);
					//damage_typeΪ��
					effect->damage_type = Fire;
					//���ʷ���damage_rate
					effect->damage_rate = 2;
					//����m_effect����
					for (int i = 0;i < 20;i++)
					{
						if (m_effect[i] == nullptr)
						{
							m_effect[i] = effect;
							//���������ֱ�ǩΪi
							effect->setTag(i);
							for (int j = 0; j < 20; j++)
							{
								m_effect_index[i][j] = 1;
							}
							break;
						}
					}
					effect->EffectsAnimation(effect->HellDog_explosion, 0);
					//ִ������������ѽڵ��Ƴ������Ұ������Ӧλ�ã�ͨ��tag��ȡ���ÿ�
					//auto removeSelf = CallFunc::create([=] {m_weapon_light->setVisible(false); m_effect[m_weapon_light->getTag()] = nullptr; });
					effect->runAction(Sequence::create(DelayTime::create(1), CallFunc::create([=] {effect->removeFromParent(); m_effect[effect->getTag()] = nullptr; }), nullptr));
						}), nullptr));

			

				//E������ȴʱ��
				m_E_CD = 0.5;



				//�����ͷ���󣬻ص�ԭ��
				leisure = true;
			}
			else
			{

				//���Ҫ���ĸ������ƶ�
				//���������Ϸ�
				if (playerPosition.y > this->getPositionY() + 200)
				{
					//����
					moveAnimation(walk_up, 4);
					//������ײ���С�����ڶ�����һ֡walk_up.at(0);getBoundingBox()
					//this->setBoundingBox(walk_up.at(0)->getBoundingBox());



				}
				//���������·�
				else if (playerPosition.y < this->getPositionY() - 200)
				{
					//����
					moveAnimation(walk_down, 3);
					log("down");
				}
				//����������
				else if (playerPosition.x < this->getPositionX())
				{
					//����
					moveAnimation(walk_left, 2);
					log("left");
				}
				//���������ҷ�
				else if (playerPosition.x > this->getPositionX())
				{
					//����
					moveAnimation(walk_right, 1);

					//log
					log("right");
				}
				//����ҵķ����ƶ���ÿ���ƶ�50
				//����
				Vec2 direction = playerPosition - this->getPosition();
				//��λ��
				direction.normalize();
				//�ƶ�
				this->runAction(MoveBy::create(1, direction * getSpeed()));//1��ʱ�䣬ָ����1�룬direction�Ƿ���*10���ٶ�
			}
		}
		else
		{

			//���Ҫ���ĸ������ƶ�
			//���������Ϸ�
			if (playerPosition.y > this->getPositionY() + 200)
			{
				//����
				moveAnimation(walk_up, 4);
				//������ײ���С�����ڶ�����һ֡walk_up.at(0);getBoundingBox()
				//this->setBoundingBox(walk_up.at(0)->getBoundingBox());



			}
			//���������·�
			else if (playerPosition.y < this->getPositionY() - 200)
			{
				//����
				moveAnimation(walk_down, 3);
				log("down");
			}
			//����������
			else if (playerPosition.x < this->getPositionX())
			{
				//����
				moveAnimation(walk_left, 2);
				log("left");
			}
			//���������ҷ�
			else if (playerPosition.x > this->getPositionX())
			{
				//����
				moveAnimation(walk_right, 1);

				//log
				log("right");
			}
			//����ҵķ����ƶ���ÿ���ƶ�50
			//����
			Vec2 direction = playerPosition - this->getPosition();
			//��λ��
			direction.normalize();
			//�ƶ�
			this->runAction(MoveBy::create(1, direction * getSpeed()));//1��ʱ�䣬ָ����1�룬direction�Ƿ���*10���ٶ�
			}



		//�ƶ�����ҵ�λ��



	}

	//������ײ
	if (m_effect[0])
	{
		//���ж���ʼ�ո��������ߣ��ٰ󶨵�����
		m_effect[0]->setPosition(this->getPosition());
		//ÿ��1����m_effect_count[0]�ص�1
		if (tttime >= 1)
		{
			tttime = 0;
			for (int i = 0;i < 20; i++)
			{
				m_effect_index[0][i] = 1;
			}
		}

	}



}