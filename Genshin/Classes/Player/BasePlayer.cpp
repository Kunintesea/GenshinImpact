#include "BasePlayer.h"

void BasePlayer::moveAnimation(Vector<SpriteFrame*> frame, int actionTag) {
	//����
	if (m_body->getActionByTag(actionTag) == 0)
	{
		m_body->stopAllActions();//ֹͣ���ж���
		auto action = RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(frame, 0.2f))); // ���붯��֡
		action->setTag(actionTag);//���ñ�ǩ
		m_body->runAction((action));//ִ���������
	}
}

//�����ж�����������ĳ���˽����˹���ʱ����ã�������������һ���ǹ����ߣ�һ���Ǳ�������
bool BasePlayer::PlayerAttack(Sprite* me, Sprite* other)
{
	//��ȡ��Ҿ����Ŀ�꾫��İ�Χ��
	Rect playerRect = me->getBoundingBox();
	Rect targetRect = other->getBoundingBox();


	// �����������İ�Χ���Ƿ��ཻ
	if (playerRect.intersectsRect(targetRect))
	{

		CCLOG("Collision detected!");
		// ִ����ײ����߼�
		log("Collision detected!");
		return true;
	}

	return false;
}


//�˺�����ʽ��ʵ���˺�=�˺�ֵ-����ֵ*�˺�ֵ�������ﴦ������״ֱ̬�ӷ���0
void BasePlayer::hurt(int damage, int damge_type, bool reaction)
{
	if (isDodge)
	{
		//��ʾ����
		for (int i = 0; i < 20; i++)
		{
			if (!m_element_label[i]->isVisible())
			{
				m_element_label[i]->setColor(Color3B::WHITE);
				m_element_label[i]->setPosition(Vec2(this->getPositionX() + m_body->getContentSize().width / 3 + rand() % 50, this->getPositionY() + m_body->getContentSize().height / 3 + rand() % 50));
				m_element_label[i]->setString("Dodge");
				m_element_label[i]->setVisible(true);
				m_element_label[i]->runAction(Sequence::create(MoveBy::create(0.1, Vec2(0, 20)), nullptr));
				m_element_label[i]->runAction(Sequence::create(DelayTime::create(1.5), CallFunc::create([=] {m_element_label[i]->setVisible(false); }), MoveBy::create(0.1, Vec2(0, -20)), nullptr));

				break;
			}
		}
		return;
	}
	else
	{
		if (reaction)
		{
			//��Ԫ�ط�Ӧ�Ĵ���
			switch (damge_type)
			{

			case Wind:
				break;
			case Rock:
				break;
			case Thunder:
				//������������˺�������������л�Ԫ�أ���������Ч��
				if (m_element[Fire] > 0)
				{

					//�ѻ����Ԫ�ظ���ͼ����ʧ
					for (int i = 0; i < 2; i++)
					{
						if (m_element_sprite[i]->isVisible() && (m_element_sprite_type[i] == Fire || m_element_sprite_type[i] == Thunder))
						{
							m_element_sprite[i]->setOpacity(255);
							m_element_sprite[i]->setVisible(false);
							//��ʧ���⣬�������û��ʧ��Ԫ�ظ��ţ���������ʾ�����Ϸ�
							if (m_element_sprite[1 - i]->isVisible())
							{
								m_element_sprite[1 - i]->setPosition(Vec2(0, m_body->getContentSize().height / 3));
							}
						}
					}

					//����Ч��
					//��ɻ�Ԫ���˺�
					hurt(5, Fire, false);


					//��Ԫ����ʧ
					m_element[Fire] = 0;
					m_element[Thunder] = 0;

					//���ų�����Ч
					Effects* effect = Effects::create();
					//λ������������
					effect->setPosition(this->getPosition());
					//�󶨵�����
					this->getParent()->addChild(effect);

					//���ų�����Ч
					effect->EffectsAnimation(effect->Explode, 0);

					//��ʾ����Ч��
					for (int i = 0; i < 20; i++)
					{
						if (!m_element_label[i]->isVisible())
						{
							m_element_label[i]->setColor(Color3B(249, 85, 9));
							m_element_label[i]->setPosition(Vec2(this->getPositionX() + m_body->getContentSize().width / 3 + rand() % 50, this->getPositionY() + m_body->getContentSize().height / 3 + rand() % 50));
							m_element_label[i]->setString("Explode");
							m_element_label[i]->setVisible(true);
							m_element_label[i]->runAction(Sequence::create(MoveBy::create(0.1, Vec2(0, 20)), nullptr));
							m_element_label[i]->runAction(Sequence::create(DelayTime::create(1.5), CallFunc::create([=] {m_element_label[i]->setVisible(false); }), MoveBy::create(0.1, Vec2(0, -20)), nullptr));

							break;
						}
					}
				}
				else if (m_element[Ice] > 0)
				{
					//����Ч��
					//��ɱ�Ԫ���˺�
					hurt(5, Ice, false);
					m_superconductivity = -0.2;//�����·����½�20%


					//�ѱ�����Ԫ�ظ���ͼ����ʧ
					for (int i = 0; i < 2; i++)
					{
						if (m_element_sprite[i]->isVisible() && (m_element_sprite_type[i] == Ice || m_element_sprite_type[i] == Thunder))
						{
							m_element_sprite[i]->setOpacity(255);
							m_element_sprite[i]->setVisible(false);
							//��ʧ���⣬�������û��ʧ��Ԫ�ظ��ţ���������ʾ�����Ϸ�
							if (m_element_sprite[1 - i]->isVisible())
							{
								m_element_sprite[1 - i]->setPosition(Vec2(0, m_body->getContentSize().height / 3));
							}
						}
					}
					//��Ԫ����ʧ
					m_element[Thunder] = 0;
					m_element[Ice] = 0;

					//�����½�״̬
					for (int i = 0; i < 99; i++)
					{
						if (m_statement[i].name == "def_down")
						{
							m_statement[i].time = 5;
							break;
						}
						else if (m_statement[i].name == "")
						{
							m_statement[i].name = "def_down";
							m_statement[i].time = 5;
							break;
						}
					}

					//���ų�����Ч
					Effects* effect = Effects::create();
					//�Ŵ�2��
					effect->setScale(2);
					//λ������������
					effect->setPosition(this->getPosition());
					//�󶨵�����
					this->getParent()->addChild(effect);
					//���ų�����Ч
					effect->EffectsAnimation(effect->Superconducting, 0);

					//��ʾ����Ч��
					for (int i = 0; i < 20; i++)
					{
						if (!m_element_label[i]->isVisible())
						{
							m_element_label[i]->setColor(Color3B(198, 244, 243));
							m_element_label[i]->setPosition(Vec2(this->getPositionX() + m_body->getContentSize().width / 3 + rand() % 50, this->getPositionY() + m_body->getContentSize().height / 3 + rand() % 50));
							m_element_label[i]->setString("Superconducting");
							m_element_label[i]->setVisible(true);
							m_element_label[i]->runAction(Sequence::create(MoveBy::create(0.1, Vec2(0, 20)), nullptr));
							m_element_label[i]->runAction(Sequence::create(DelayTime::create(1.5), CallFunc::create([=] {m_element_label[i]->setVisible(false); }), MoveBy::create(0.1, Vec2(0, -20)), nullptr));

							break;
						}
					}
				}
				else if (m_element[Water] > 0)
				{
					//�����Ԫ���˺�
					hurt(2, Thunder, false);
					m_element[Thunder] = 5;

					//��ˮ����Ԫ�ظ���ͼ����ʧ
					for (int i = 0; i < 2; i++)
					{
						if (m_element_sprite[i]->isVisible() && (m_element_sprite_type[i] == Water || m_element_sprite_type[i] == Thunder))
						{
							m_element_sprite[i]->setOpacity(255);
							m_element_sprite[i]->setVisible(false);
							//��ʧ���⣬�������û��ʧ��Ԫ�ظ��ţ���������ʾ�����Ϸ�
							if (m_element_sprite[1 - i]->isVisible())
							{
								m_element_sprite[1 - i]->setPosition(Vec2(0, m_body->getContentSize().height / 3));
							}
						}
					}
					//��Ԫ����ʧ
					m_element[Thunder] = 0;
					m_element[Water] = 0;



					//������Ч
					Effects* effect = Effects::create();
					//�Ŵ�2��
					effect->setScale(2);
					//λ������������
					effect->setPosition(this->getPosition());
					//�󶨵�����
					this->getParent()->addChild(effect);
					effect->EffectsAnimation(effect->Shocked, 0);

					//��ʾЧ��
					for (int i = 0; i < 20; i++)
					{
						if (!m_element_label[i]->isVisible())
						{
							m_element_label[i]->setColor(Color3B(172, 43, 231));
							m_element_label[i]->setPosition(Vec2(this->getPositionX() + m_body->getContentSize().width / 3 + rand() % 50, this->getPositionY() + m_body->getContentSize().height / 3 + rand() % 50));
							m_element_label[i]->setString("Shokced");
							m_element_label[i]->setVisible(true);
							m_element_label[i]->runAction(Sequence::create(MoveBy::create(0.1, Vec2(0, 20)), nullptr));
							m_element_label[i]->runAction(Sequence::create(DelayTime::create(1.5), CallFunc::create([=] {m_element_label[i]->setVisible(false); }), MoveBy::create(0.1, Vec2(0, -20)), nullptr));

							break;
						}
					}
					//����е�״̬����m_statement���vector�в��ң�����ҵ���shock���ó���ʱ����5����������shock
					for (int i = 0; i < 99; i++)
					{
						if (m_statement[i].name == "shock")
						{
							m_statement[i].time = 5;
							break;
						}
						else if (m_statement[i].name == "")
						{
							m_statement[i].name = "shock";
							m_statement[i].time = 5;
							break;

						}
						
					}




				}
				else
				{
					if (m_element[Thunder] == 0)
					{
						//����Ԫ�ظ���
						setElementSprite(damge_type);
					}
					m_element[Thunder] = 5;
				}
				break;
			case Grass:
				if (m_element[Grass] == 0)
				{
					//����Ԫ�ظ���
					setElementSprite(damge_type);
				}
				m_element[Grass] = 5;
				break;
			case Water:

				if (m_element[Thunder] > 0)
				{
					//�����Ԫ���˺�
					hurt(2, Thunder, false);
					m_element[Thunder] = 5;

					//��ˮ����Ԫ�ظ���ͼ����ʧ
					for (int i = 0; i < 2; i++)
					{
						if (m_element_sprite[i]->isVisible() && (m_element_sprite_type[i] == Water || m_element_sprite_type[i] == Thunder))
						{
							m_element_sprite[i]->setOpacity(255);
							m_element_sprite[i]->setVisible(false);
							//��ʧ���⣬�������û��ʧ��Ԫ�ظ��ţ���������ʾ�����Ϸ�
							if (m_element_sprite[1 - i]->isVisible())
							{
								m_element_sprite[1 - i]->setPosition(Vec2(0, m_body->getContentSize().height / 3));
							}
						}
					}
					//��Ԫ����ʧ
					m_element[Thunder] = 0;
					m_element[Water] = 0;



					//������Ч
					Effects* effect = Effects::create();
					//�Ŵ�2��
					effect->setScale(2);
					//λ������������
					effect->setPosition(this->getPosition());
					//�󶨵�����
					this->getParent()->addChild(effect);
					effect->EffectsAnimation(effect->Shocked, 0);

					//��ʾЧ��
					for (int i = 0; i < 20; i++)
					{
						if (!m_element_label[i]->isVisible())
						{
							m_element_label[i]->setColor(Color3B(172, 43, 231));
							m_element_label[i]->setPosition(Vec2(this->getPositionX() + m_body->getContentSize().width / 3 + rand() % 50, this->getPositionY() + m_body->getContentSize().height / 3 + rand() % 50));
							m_element_label[i]->setString("Shokced");
							m_element_label[i]->setVisible(true);
							m_element_label[i]->runAction(Sequence::create(MoveBy::create(0.1, Vec2(0, 20)), nullptr));
							m_element_label[i]->runAction(Sequence::create(DelayTime::create(1.5), CallFunc::create([=] {m_element_label[i]->setVisible(false); }), MoveBy::create(0.1, Vec2(0, -20)), nullptr));

							break;
						}
					}
					//����е�״̬����m_statement���vector�в��ң�����ҵ���shock���ó���ʱ����5����������shock
					for (int i = 0; i < 99; i++)
					{
						if (m_statement[i].name == "shock")
						{
							m_statement[i].time = 5;

							break;
						}
						else if (m_statement[i].name == "")
						{
							m_statement[i].name = "shock";
							m_statement[i].time = 5;
							break;

						}

					}
				}
				else if (m_element[Fire] > 0)
				{
					//�˺�����
					damage *= 3;
					for (int i = 0; i < 2; i++)
					{
						if (m_element_sprite[i]->isVisible() && (m_element_sprite_type[i] == Water || m_element_sprite_type[i] == Fire))
						{
							m_element_sprite[i]->setOpacity(255);
							m_element_sprite[i]->setVisible(false);
							//��ʧ���⣬�������û��ʧ��Ԫ�ظ��ţ���������ʾ�����Ϸ�
							if (m_element_sprite[1 - i]->isVisible())
							{
								m_element_sprite[1 - i]->setPosition(Vec2(0, m_body->getContentSize().height / 3));
							}
						}
					}
					m_element[Fire] = 0;
					m_element[Water] = 0;

					//������Ч
					Effects* effect = Effects::create();
					//�Ŵ�2��
					effect->setScale(2);
					//λ������������
					effect->setPosition(this->getPosition());
					//�󶨵�����
					this->getParent()->addChild(effect);
					effect->EffectsAnimation(effect->Evaporate, 0);

					//��ʾЧ��
					for (int i = 0; i < 20; i++)
					{
						if (!m_element_label[i]->isVisible())
						{
							m_element_label[i]->setColor(Color3B(11, 214, 245));
							m_element_label[i]->setPosition(Vec2(this->getPositionX() + m_body->getContentSize().width / 3 + rand() % 50, this->getPositionY() + m_body->getContentSize().height / 3 + rand() % 50));
							m_element_label[i]->setString("Evaporation");
							m_element_label[i]->setVisible(true);
							m_element_label[i]->runAction(Sequence::create(MoveBy::create(0.1, Vec2(0, 20)), nullptr));
							m_element_label[i]->runAction(Sequence::create(DelayTime::create(1.5), CallFunc::create([=] {m_element_label[i]->setVisible(false); }), MoveBy::create(0.1, Vec2(0, -20)), nullptr));

							break;
						}
					}
				}
				else if (m_element[Water] == 0)
				{
					//����Ԫ�ظ���
					setElementSprite(damge_type);
					m_element[Water] = 5;

				}
				break;
			case Fire:
				if (m_element[Thunder] > 0)
				{
					//����Ч��
					//��ɻ�Ԫ���˺�
					hurt(5, Fire, false);

					//�ѻ����Ԫ�ظ���ͼ����ʧ
					for (int i = 0; i < 2; i++)
					{
						if (m_element_sprite[i]->isVisible() && (m_element_sprite_type[i] == Fire || m_element_sprite_type[i] == Thunder))
						{
							m_element_sprite[i]->setOpacity(255);
							m_element_sprite[i]->setVisible(false);
							//��ʧ���⣬�������û��ʧ��Ԫ�ظ��ţ���������ʾ�����Ϸ�
							if (m_element_sprite[1 - i]->isVisible())
							{
								m_element_sprite[1 - i]->setPosition(Vec2(0, m_body->getContentSize().height / 3));
							}
						}
					}
					//��Ԫ����ʧ
					m_element[Fire] = 0;
					m_element[Thunder] = 0;

					//���ų�����Ч
					Effects* effect = Effects::create();
					//λ������������
					effect->setPosition(this->getPosition());
					//�󶨵�����
					this->getParent()->addChild(effect);
					//���ų�����Ч
					effect->EffectsAnimation(effect->Explode, 0);

					//��ʾ����Ч��
					for (int i = 0; i < 20; i++)
					{
						if (!m_element_label[i]->isVisible())
						{
							m_element_label[i]->setColor(Color3B(249, 85, 9));
							m_element_label[i]->setPosition(Vec2(this->getPositionX() + m_body->getContentSize().width / 3 + rand() % 50, this->getPositionY() + m_body->getContentSize().height / 3 + rand() % 50));
							m_element_label[i]->setString("Explode");
							m_element_label[i]->setVisible(true);
							m_element_label[i]->runAction(Sequence::create(MoveBy::create(0.1, Vec2(0, 20)), nullptr));
							m_element_label[i]->runAction(Sequence::create(DelayTime::create(1.5), CallFunc::create([=] {m_element_label[i]->setVisible(false); }), MoveBy::create(0.1, Vec2(0, -20)), nullptr));

							break;
						}
					}
				}
				else if (m_element[Water] > 0)
				{
					//�˺�����
					damage *= 3;
					for (int i = 0; i < 2; i++)
					{
						if (m_element_sprite[i]->isVisible() && (m_element_sprite_type[i] == Fire || m_element_sprite_type[i] == Water))
						{
							m_element_sprite[i]->setOpacity(255);
							m_element_sprite[i]->setVisible(false);
							//��ʧ���⣬�������û��ʧ��Ԫ�ظ��ţ���������ʾ�����Ϸ�
							if (m_element_sprite[1 - i]->isVisible())
							{
								m_element_sprite[1 - i]->setPosition(Vec2(0, m_body->getContentSize().height / 3));
							}
						}
					}
					m_element[Fire] = 0;
					m_element[Water] = 0;

					//������Ч
					Effects* effect = Effects::create();
					//�Ŵ�2��
					effect->setScale(2);
					//λ������������
					effect->setPosition(this->getPosition());
					//�󶨵�����
					this->getParent()->addChild(effect);
					effect->EffectsAnimation(effect->Evaporate, 0);

					//��ʾЧ��
					for (int i = 0; i < 20; i++)
					{
						if (!m_element_label[i]->isVisible())
						{
							m_element_label[i]->setColor(Color3B(249, 85, 9));
							m_element_label[i]->setPosition(Vec2(this->getPositionX() + m_body->getContentSize().width / 3 + rand() % 50, this->getPositionY() + m_body->getContentSize().height / 3 + rand() % 50));
							m_element_label[i]->setString("Evaporation");
							m_element_label[i]->setVisible(true);
							m_element_label[i]->runAction(Sequence::create(MoveBy::create(0.1, Vec2(0, 20)), nullptr));
							m_element_label[i]->runAction(Sequence::create(DelayTime::create(1.5), CallFunc::create([=] {m_element_label[i]->setVisible(false); }), MoveBy::create(0.1, Vec2(0, -20)), nullptr));

							break;
						}
					}
				}
				else if (m_element[Ice] > 0)
				{
					//�˺�����
					damage *= 2;
					for (int i = 0; i < 2; i++)
					{
						if (m_element_sprite[i]->isVisible() && (m_element_sprite_type[i] == Fire || m_element_sprite_type[i] == Ice))
						{
							m_element_sprite[i]->setOpacity(255);
							m_element_sprite[i]->setVisible(false);
							//��ʧ���⣬�������û��ʧ��Ԫ�ظ��ţ���������ʾ�����Ϸ�
							if (m_element_sprite[1 - i]->isVisible())
							{
								m_element_sprite[1 - i]->setPosition(Vec2(0, m_body->getContentSize().height / 3));
							}
						}
					}
					m_element[Fire] = 0;
					m_element[Ice] = 0;

					//������Ч
					Effects* effect = Effects::create();
					//�Ŵ�2��
					effect->setScale(2);
					//λ������������
					effect->setPosition(this->getPosition());
					//�󶨵�����
					this->getParent()->addChild(effect);
					effect->EffectsAnimation(effect->Evaporate, 0);

					//��ʾЧ��
					for (int i = 0; i < 20; i++)
					{
						if (!m_element_label[i]->isVisible())
						{
							m_element_label[i]->setColor(Color3B(249, 85, 9));
							m_element_label[i]->setPosition(Vec2(this->getPositionX() + m_body->getContentSize().width / 3 + rand() % 50, this->getPositionY() + m_body->getContentSize().height / 3 + rand() % 50));
							m_element_label[i]->setString("Melt");
							m_element_label[i]->setVisible(true);
							m_element_label[i]->runAction(Sequence::create(MoveBy::create(0.1, Vec2(0, 20)), nullptr));
							m_element_label[i]->runAction(Sequence::create(DelayTime::create(1.5), CallFunc::create([=] {m_element_label[i]->setVisible(false); }), MoveBy::create(0.1, Vec2(0, -20)), nullptr));

							break;
						}
					}
				}
				else
				{
					if (m_element[Fire] == 0)
					{
						//����Ԫ�ظ���
						setElementSprite(damge_type);
					}
					m_element[Fire] = 5;
				}
				break;
			case Ice:
				if (m_element[Thunder] > 0)
				{
					//����Ч��
					//��ɱ�Ԫ���˺�
					hurt(5, Ice, false);
					m_superconductivity = -0.2;//�����·����½�20%
					//�ѱ�����Ԫ�ظ���ͼ����ʧ
					for (int i = 0; i < 2; i++)
					{
						if (m_element_sprite[i]->isVisible() && (m_element_sprite_type[i] == Ice || m_element_sprite_type[i] == Thunder))
						{
							m_element_sprite[i]->setOpacity(255);
							m_element_sprite[i]->setVisible(false);
							//��ʧ���⣬�������û��ʧ��Ԫ�ظ��ţ���������ʾ�����Ϸ�
							if (m_element_sprite[1 - i]->isVisible())
							{
								m_element_sprite[1 - i]->setPosition(Vec2(0, m_body->getContentSize().height / 3));
							}
						}
					}
					//��Ԫ����ʧ
					m_element[Thunder] = 0;
					m_element[Ice] = 0;

					//���ų�����Ч
					Effects* effect = Effects::create();
					//�Ŵ�2��
					effect->setScale(2);
					//λ������������
					effect->setPosition(this->getPosition());
					//�󶨵�����
					this->getParent()->addChild(effect);
					//���ų�����Ч
					effect->EffectsAnimation(effect->Superconducting, 0);

					//��ʾ����Ч��
					for (int i = 0; i < 20; i++)
					{
						if (!m_element_label[i]->isVisible())
						{
							m_element_label[i]->setColor(Color3B(198, 244, 243));
							m_element_label[i]->setPosition(Vec2(this->getPositionX() + m_body->getContentSize().width / 3 + rand() % 50, this->getPositionY() + m_body->getContentSize().height / 3 + rand() % 50));
							m_element_label[i]->setString("Superconducting");
							m_element_label[i]->setVisible(true);
							m_element_label[i]->runAction(Sequence::create(MoveBy::create(0.1, Vec2(0, 20)), nullptr));
							m_element_label[i]->runAction(Sequence::create(DelayTime::create(1.5), CallFunc::create([=] {m_element_label[i]->setVisible(false); }), MoveBy::create(0.1, Vec2(0, -20)), nullptr));

							break;
						}
					}
				}
				else if (m_element[Fire] > 0)
				{
					//�˺�����
					damage *= 2;
					for (int i = 0; i < 2; i++)
					{
						if (m_element_sprite[i]->isVisible() && (m_element_sprite_type[i] == Fire || m_element_sprite_type[i] == Ice))
						{
							m_element_sprite[i]->setOpacity(255);
							m_element_sprite[i]->setVisible(false);
							//��ʧ���⣬�������û��ʧ��Ԫ�ظ��ţ���������ʾ�����Ϸ�
							if (m_element_sprite[1 - i]->isVisible())
							{
								m_element_sprite[1 - i]->setPosition(Vec2(0, m_body->getContentSize().height / 3));
							}
						}
					}
					m_element[Fire] = 0;
					m_element[Ice] = 0;

					//������Ч
					Effects* effect = Effects::create();
					//�Ŵ�2��
					effect->setScale(2);
					//λ������������
					effect->setPosition(this->getPosition());
					//�󶨵�����
					this->getParent()->addChild(effect);
					effect->EffectsAnimation(effect->Evaporate, 0);

					//��ʾЧ��
					for (int i = 0; i < 20; i++)
					{
						if (!m_element_label[i]->isVisible())
						{
							m_element_label[i]->setColor(Color3B(198, 244, 243));
							m_element_label[i]->setPosition(Vec2(this->getPositionX() + m_body->getContentSize().width / 3 + rand() % 50, this->getPositionY() + m_body->getContentSize().height / 3 + rand() % 50));
							m_element_label[i]->setString("Melt");
							m_element_label[i]->setVisible(true);
							m_element_label[i]->runAction(Sequence::create(MoveBy::create(0.1, Vec2(0, 20)), nullptr));
							m_element_label[i]->runAction(Sequence::create(DelayTime::create(1.5), CallFunc::create([=] {m_element_label[i]->setVisible(false); }), MoveBy::create(0.1, Vec2(0, -20)), nullptr));

							break;
						}
					}
				}
				else
				{
					if (m_element[Ice] == 0)
					{
						//����Ԫ�ظ���
						setElementSprite(damge_type);
					}
					m_element[Ice] = 5;
				}


				break;
			default:
				break;
			}
		}
		float real_defense;//ʵ�ʷ���ֵ
		real_defense = m_defense + m_superconductivity;





		int real_damage = int(float(damage) - float(damage) * real_defense);//ʵ���˺�=�˺�ֵ-����ֵ*�˺�ֵ
		//���˺�������ʾ
		for (int i = 0; i < 20; i++)
		{
			if (!m_damage_label[i]->isVisible())
			{
				//�˺�������ɫ�����˺����͸ı�
				switch (damge_type)
				{
					//����������˺����˺�����Ϊ��ɫ
				case Physical:
					m_damage_label[i]->setColor(Color3B::WHITE);
					if (m_immune[Physical])
					{
						//��ɫ������ʾ���ߺ������˳�
						m_damage_label[i]->setColor(Color3B::GRAY);
						m_damage_label[i]->setPosition(Vec2(this->getPositionX() - m_body->getContentSize().width / 6 + rand() % 70, this->getPositionY() - m_body->getContentSize().height / 6 + rand() % 70));
						m_damage_label[i]->setVisible(true);
						//���ϸ���
						m_damage_label[i]->runAction(Sequence::create(MoveBy::create(0.1, Vec2(0, 20)), nullptr));//����һ���������У����˺��������ϸ��֣�����0.1��
						//1.5�������m_damage_label[i]���ɼ������ɼ��������ƶ�20������
						m_damage_label[i]->runAction(Sequence::create(DelayTime::create(1.5), CallFunc::create([=] {m_damage_label[i]->setVisible(false); }), MoveBy::create(0.1, Vec2(0, -20)), nullptr));
						m_damage_label[i]->setString("Immune");
						return;
					}
					break;
					//����Ƿ������˺����˺�����Ϊ����ɫ��RGBΪ23,236,175
				case Wind:
					m_damage_label[i]->setColor(Color3B(23, 236, 175));
					break;
					//������������˺����˺�����Ϊ�ػ�ɫ��RGBΪ248,226,57
				case Rock:
					m_damage_label[i]->setColor(Color3B(248, 226, 57));
					break;
					//������������˺����˺�����Ϊ��ɫ��RGBΪ172,43,231
				case Thunder:
					m_damage_label[i]->setColor(Color3B(172, 43, 231));
					if (m_immune[Thunder])
					{
						//��ɫ������ʾ���ߺ������˳�
						m_damage_label[i]->setColor(Color3B::GRAY);
						m_damage_label[i]->setPosition(Vec2(this->getPositionX() - m_body->getContentSize().width / 6 + rand() % 70, this->getPositionY() - m_body->getContentSize().height / 6 + rand() % 70));
						m_damage_label[i]->setVisible(true);
						//���ϸ���
						m_damage_label[i]->runAction(Sequence::create(MoveBy::create(0.1, Vec2(0, 20)), nullptr));//����һ���������У����˺��������ϸ��֣�����0.1��
						//1.5�������m_damage_label[i]���ɼ������ɼ��������ƶ�20������
						m_damage_label[i]->runAction(Sequence::create(DelayTime::create(1.5), CallFunc::create([=] {m_damage_label[i]->setVisible(false); }), MoveBy::create(0.1, Vec2(0, -20)), nullptr));
						m_damage_label[i]->setString("Immune");
						return;
					}
					break;
					//����ǲ������˺����˺�����Ϊ��ɫ��RGBΪ42,204,21
				case Grass:
					m_damage_label[i]->setColor(Color3B(42, 204, 21));
					break;
					//�����ˮ�����˺����˺�����Ϊ��ɫ��RGBΪ11,214,245
				case Water:
					m_damage_label[i]->setColor(Color3B(11, 214, 245));
					if (m_immune[Water])
					{
						//��ɫ������ʾ���ߺ������˳�
						m_damage_label[i]->setColor(Color3B::GRAY);
						m_damage_label[i]->setPosition(Vec2(this->getPositionX() - m_body->getContentSize().width / 6 + rand() % 70, this->getPositionY() - m_body->getContentSize().height / 6 + rand() % 70));
						m_damage_label[i]->setVisible(true);
						//���ϸ���
						m_damage_label[i]->runAction(Sequence::create(MoveBy::create(0.1, Vec2(0, 20)), nullptr));//����һ���������У����˺��������ϸ��֣�����0.1��
						//1.5�������m_damage_label[i]���ɼ������ɼ��������ƶ�20������
						m_damage_label[i]->runAction(Sequence::create(DelayTime::create(1.5), CallFunc::create([=] {m_damage_label[i]->setVisible(false); }), MoveBy::create(0.1, Vec2(0, -20)), nullptr));
						m_damage_label[i]->setString("Immune");
						return;
					}
					break;
					//����ǻ������˺����˺�����Ϊ��ɫ��RGBΪ249,85,9
				case Fire:
					m_damage_label[i]->setColor(Color3B(249, 85, 9));
					if (m_immune[Fire])
					{
						//��ɫ������ʾ���ߺ������˳�
						m_damage_label[i]->setColor(Color3B::GRAY);
						m_damage_label[i]->setPosition(Vec2(this->getPositionX() - m_body->getContentSize().width / 6 + rand() % 70, this->getPositionY() - m_body->getContentSize().height / 6 + rand() % 70));
						m_damage_label[i]->setVisible(true);
						//���ϸ���
						m_damage_label[i]->runAction(Sequence::create(MoveBy::create(0.1, Vec2(0, 20)), nullptr));//����һ���������У����˺��������ϸ��֣�����0.1��
						//1.5�������m_damage_label[i]���ɼ������ɼ��������ƶ�20������
						m_damage_label[i]->runAction(Sequence::create(DelayTime::create(1.5), CallFunc::create([=] {m_damage_label[i]->setVisible(false); }), MoveBy::create(0.1, Vec2(0, -20)), nullptr));
						m_damage_label[i]->setString("Immune");
						return;
					}
					break;
					//����Ǳ������˺����˺�����Ϊ����ɫ��RGBΪ198,244,243
				case Ice:
					m_damage_label[i]->setColor(Color3B(198, 244, 243));
					if (m_immune[Ice])
					{
						//��ɫ������ʾ���ߺ������˳�
						m_damage_label[i]->setColor(Color3B::GRAY);
						m_damage_label[i]->setPosition(Vec2(this->getPositionX() - m_body->getContentSize().width / 6 + rand() % 70, this->getPositionY() - m_body->getContentSize().height / 6 + rand() % 70));
						m_damage_label[i]->setVisible(true);
						//���ϸ���
						m_damage_label[i]->runAction(Sequence::create(MoveBy::create(0.1, Vec2(0, 20)), nullptr));//����һ���������У����˺��������ϸ��֣�����0.1��
						//1.5�������m_damage_label[i]���ɼ������ɼ��������ƶ�20������
						m_damage_label[i]->runAction(Sequence::create(DelayTime::create(1.5), CallFunc::create([=] {m_damage_label[i]->setVisible(false); }), MoveBy::create(0.1, Vec2(0, -20)), nullptr));
						m_damage_label[i]->setString("Immune");
						return;
					}
					break;
				}






				m_damage_label[i]->setPosition(Vec2(this->getPositionX() - m_body->getContentSize().width / 6 + rand() % 70, this->getPositionY() - m_body->getContentSize().height / 6 + rand() % 70));//rand()��ʹ�÷�����rand()%n����ʾ����һ��0��n-1�������
				m_damage_label[i]->setVisible(true);
				//���ϸ���
				m_damage_label[i]->runAction(Sequence::create(MoveBy::create(0.1, Vec2(0, 20)), nullptr));//����һ���������У����˺��������ϸ��֣�����0.1��
				//1.5�������m_damage_label[i]���ɼ������ɼ��������ƶ�20������
				m_damage_label[i]->runAction(Sequence::create(DelayTime::create(1.5), CallFunc::create([=] {m_damage_label[i]->setVisible(false); }), MoveBy::create(0.1, Vec2(0, -20)), nullptr));


				m_damage_label[i]->setString(std::to_string(real_damage));
				break;
			}
		}
		//�ȿۻ���
		if (m_shield > 0)
		{
			if (m_shield >= real_damage)
			{
				m_shield -= real_damage;
				real_damage = 0;
			}
			else
			{
				real_damage -= m_shield;
				m_shield = 0;
			}
		}

		m_hp -= real_damage;
		if (m_hp <= 0)
		{
			isDead = true;
			m_hp = 0;
		}

		//��setColor������RGB��죬һ���ָ�
		m_body->setColor(Color3B::RED);
		this->runAction(Sequence::create(DelayTime::create(0.1), CallFunc::create([=] {m_body->setColor(Color3B::WHITE); }), nullptr));


	}
}

void BasePlayer::setElementSprite(int elemtype)
{
	//���Ԫ�ظ�������
	int count = 0;
	for (int i = 0; i < 2; i++)
	{
		if (m_element_sprite[i]->isVisible())
		{
			count++;
		}
	}


	//���ҵ�ǰ�Ƿ���Ԫ�ظ��ţ�����оͿ����Ƿ�Ӧ������
	//�ȿ�0��λ�Ƿ���Ԫ�ظ��ţ�û�о�ֱ�Ӹ���
	if (count==0)
	{
		//͸���Ȼָ�
		m_element_sprite[0]->setOpacity(255);
		m_element_sprite[0]->setVisible(true);
		//����Ԫ�ظ��ŵ�λ��
		m_element_sprite[0]->setPosition(Vec2(0, m_body->getContentSize().height / 3));
		//����Ԫ�ظ��ŵ�ͼƬ
		m_element_sprite_type[0] = elemtype;
		switch (elemtype)
		{
		case Wind:
			m_element_sprite[0]->setTexture("Effects/Element/Wind.png");
			break;
		case Rock:
			m_element_sprite[0]->setTexture("Effects/Element/Rock.png");
			break;
		case Thunder:
			m_element_sprite[0]->setTexture("Effects/Element/Thunder.png");
			break;
		case Grass:
			m_element_sprite[0]->setTexture("Effects/Element/Grass.png");
			break;
		case Water:
			m_element_sprite[0]->setTexture("Effects/Element/Water.png");
			break;
		case Fire:
			m_element_sprite[0]->setTexture("Effects/Element/Fire.png");
			break;
		case Ice:
			m_element_sprite[0]->setTexture("Effects/Element/Ice.png");
			break;
		default:
			break;
		}
	}
	//����ǰ����0��1�ŵ�Ԫ�ظ��Ų�һ��
	else
	{

		//�Ȱ�0��ͼƬ���õ����Ϸ������
		m_element_sprite[0]->setPosition(Vec2(-20, m_body->getContentSize().height / 3));
		//�ٰ�1��ͼƬ���õ����Ϸ����Ҳ�
		m_element_sprite[1]->setVisible(true);
		m_element_sprite[1]->setPosition(Vec2(20, m_body->getContentSize().height / 3));



		//͸���Ȼָ�
		m_element_sprite[1]->setOpacity(255);
		m_element_sprite_type[1] = elemtype;
		//����Ԫ�ظ��ŵ�ͼƬ
		switch (elemtype)
		{
		case Wind:
			m_element_sprite[1]->setTexture("Effects/Element/Wind.png");
			break;
		case Rock:
			m_element_sprite[1]->setTexture("Effects/Element/Rock.png");
			break;
		case Thunder:
			m_element_sprite[1]->setTexture("Effects/Element/Thunder.png");
			break;
		case Grass:
			m_element_sprite[1]->setTexture("Effects/Element/Grass.png");
			break;
		case Water:
			m_element_sprite[1]->setTexture("Effects/Element/Water.png");
			break;
		case Fire:
			m_element_sprite[1]->setTexture("Effects/Element/Fire.png");
			break;
		case Ice:
			m_element_sprite[1]->setTexture("Effects/Element/Ice.png");
			break;
		default:
			break;
		}
	}
}

void BasePlayer::effectTrigger(std::string effect_type)
{
	if (effect_type == "shock")
	{
		hurt(2, Thunder, false);
		//������Ч
		Effects* effect = Effects::create();
		//�Ŵ�2��
		effect->setScale(2);
		//λ������������
		effect->setPosition(this->getPosition());
		//�󶨵�����
		this->getParent()->addChild(effect);
		effect->EffectsAnimation(effect->Shocked, 0);

		//��ʾЧ��
		for (int i = 0; i < 20; i++)
		{
			if (!m_element_label[i]->isVisible())
			{
				m_element_label[i]->setColor(Color3B(172, 43, 231));
				m_element_label[i]->setPosition(Vec2(this->getPositionX() + m_body->getContentSize().width / 3 + rand() % 50, this->getPositionY() + m_body->getContentSize().height / 3 + rand() % 50));
				m_element_label[i]->setString("Shokced");
				m_element_label[i]->setVisible(true);
				m_element_label[i]->runAction(Sequence::create(MoveBy::create(0.1, Vec2(0, 20)), nullptr));
				m_element_label[i]->runAction(Sequence::create(DelayTime::create(1.5), CallFunc::create([=] {m_element_label[i]->setVisible(false); }), MoveBy::create(0.1, Vec2(0, -20)), nullptr));

				break;
			}
		}
	}
}

