#include "BasePlayer.h"



void BasePlayer::hurt(int damage, int damge_type, bool reaction)
{
	if (isDodge) return;
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
					//����Ч��
					//��ɻ�Ԫ���˺�
					hurt(5, Fire, false);


					//��Ԫ����ʧ
					m_element[Fire] = 0;

					//���ų�����Ч
					Effects* effect = Effects::create();
					//�Ŵ�2��
					effect->setScale(2);
					//λ������������
					effect->setPosition(Vec2(0, 0));
					//�󶨵�����
					this->addChild(effect);
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
				else
				{
					m_element[Thunder] = 5;
				}
				break;
			case Grass:
				m_element[Grass] = 5;
				break;
			case Water:
				m_element[Water] = 5;
				break;
			case Fire:
				if (m_element[Thunder] > 0)
				{
					//����Ч��
					//�˺�ֵ����
					damage *= 2;
					//��Ԫ����ʧ
					m_element[Thunder] = 0;

					//���ų�����Ч
					Effects* effect = Effects::create();
					//�Ŵ�2��
					effect->setScale(2);
					//λ������������
					effect->setPosition(Vec2(0, 0));
					//�󶨵�����
					this->addChild(effect);
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
				else
				{
					m_element[Fire] = 5;
				}
				break;
			case Ice:
				m_element[Ice] = 5;
				break;
			default:
				break;
			}
		}







		int real_damage = int(float(damage) - float(damage) * m_defense);//ʵ���˺�=�˺�ֵ-����ֵ*�˺�ֵ
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
					break;
					//����ǲ������˺����˺�����Ϊ��ɫ��RGBΪ42,204,21
				case Grass:
					m_damage_label[i]->setColor(Color3B(42, 204, 21));
					break;
					//�����ˮ�����˺����˺�����Ϊ��ɫ��RGBΪ11,214,245
				case Water:
					m_damage_label[i]->setColor(Color3B(11, 214, 245));
					break;
					//����ǻ������˺����˺�����Ϊ��ɫ��RGBΪ249,85,9
				case Fire:
					m_damage_label[i]->setColor(Color3B(249, 85, 9));
					break;
					//����Ǳ������˺����˺�����Ϊ����ɫ��RGBΪ198,244,243
				case Ice:
					m_damage_label[i]->setColor(Color3B(198, 244, 243));
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
		m_hp -= real_damage;
		if (m_hp <= 0)
		{
			isDead = true;
			m_hp = 0;
		}

		//��setColor������RGB��죬0.1���ָ�
		m_body->setColor(Color3B::RED);
		this->runAction(Sequence::create(DelayTime::create(0.1), CallFunc::create([=] {m_body->setColor(Color3B::WHITE); }), nullptr));


	}
}