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
bool BasePlayer::PlayerAttack(Effects* me, BasePlayer* other)
{
      //�趨other��m_bodyRect�İ�Χ�У���other->m_body��λ�úʹ�С������������������ģ���С��m_body��
      other->m_bodyRect = Rect(other->getPositionX() - other->m_body->getContentSize().width / 2, other->getPositionY() - other->m_body->getContentSize().height / 2, other->m_body->getContentSize().width, other->m_body->getContentSize().height);

      //��Χ�еĴ�С����effect�Ĵ�С��λ�����������������
      me->effectRect = Rect(me->getPositionX() - me->getContentSize().width / 2, me->getPositionY() - me->getContentSize().height / 2, me->effect->getContentSize().width, me->effect->getContentSize().height);

      //��ȡ��Ҿ����Ŀ�꾫��İ�Χ��
      Rect playerRect = me->effectRect;
      //����m_body�İ�Χ��
      Rect targetRect = other->m_bodyRect;

      //��Ӧλ�û��������α��ڵ���
      DrawNode* drawNode = DrawNode::create();
      drawNode->drawRect(Vec2(playerRect.getMinX(), playerRect.getMinY()), Vec2(playerRect.getMaxX(), playerRect.getMaxY()), Color4F(1, 0, 0, 1));
      this->getParent()->addChild(drawNode, 1000);

      DrawNode* drawNode2 = DrawNode::create();
      drawNode2->drawRect(Vec2(targetRect.getMinX(), targetRect.getMinY()), Vec2(targetRect.getMaxX(), targetRect.getMaxY()), Color4F(1, 0, 0, 1));
      this->getParent()->addChild(drawNode2, 1000);





      // �����������İ�Χ���Ƿ��ཻ
      if (playerRect.intersectsRect(targetRect))
      {

	    CCLOG("Collision detected!");
	    // ִ����ײ����߼�
	    log("Collision detected!");
	    //��other����Hurt����
	    //other->hurt(10, 0, true);

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
						m_element_sprite[1 - i]->setPosition(Vec2(0, m_body->getContentSize().height));
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
						m_element_sprite[1 - i]->setPosition(Vec2(0, m_body->getContentSize().height));
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
						m_element_sprite[1 - i]->setPosition(Vec2(0, m_body->getContentSize().height));
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
						m_element_sprite[1 - i]->setPosition(Vec2(0, m_body->getContentSize().height));
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
						m_element_sprite[1 - i]->setPosition(Vec2(0, m_body->getContentSize().height));
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
						m_element_sprite[1 - i]->setPosition(Vec2(0, m_body->getContentSize().height));
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
						m_element_sprite[1 - i]->setPosition(Vec2(0, m_body->getContentSize().height));
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
						m_element_sprite[1 - i]->setPosition(Vec2(0, m_body->getContentSize().height));
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
						m_element_sprite[1 - i]->setPosition(Vec2(0, m_body->getContentSize().height));
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
						m_element_sprite[1 - i]->setPosition(Vec2(0, m_body->getContentSize().height));
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
	    //�洢m_hp��ֵ
	    UserDefault::getInstance()->setIntegerForKey("m_hp", m_hp);

	    if (m_hp <= 0)
	    {
		  isDead = true;
		  m_hp = 0;
	    }

	    //��setColor������RGB��죬һ���ָ�
	    m_body->setColor(Color3B::RED);
	    this->runAction(Sequence::create(DelayTime::create(0.1), CallFunc::create([=] {m_body->setColor(Color3B::WHITE); }), nullptr));

	    if (m_hp <= 0)
	    {
		  isDead = true;
	    }

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
      if (count == 0)
      {
	    //͸���Ȼָ�
	    m_element_sprite[0]->setOpacity(255);
	    m_element_sprite[0]->setVisible(true);
	    //����Ԫ�ظ��ŵ�λ��
	    m_element_sprite[0]->setPosition(Vec2(0, m_body->getContentSize().height));
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

void BasePlayer::initData()
{
      //�������
      if (m_name == "Bat_Fire")
      {


	    //�Ȱ�m_body����Ϊ�������ͼƬ
	    m_body->setTexture("Enemy/Bat_Fire/down_1.png");//setTexture������ͼƬ�ĺ�����������ͼƬ��·�����޸��Ժ�ͼ�εĴ�С����ͼƬ�Ĵ�С

	    speed = 10;
	    //��ֵ��ʼ��
	    m_hp = 100;
	    m_max_hp = 100;
	    m_mp = 50;
	    m_max_mp = 100;
	    //������Ϊ5
	    m_attack = 5;

	    // ���ض���
	    Size bodySize = m_body->getContentSize();
	    //�˶�����֡
	    bodySize = Sprite::create("Enemy/Bat_Fire/up_1.png")->getContentSize();
	    SpriteFrame* up_1 = SpriteFrame::create("Enemy/Bat_Fire/up_1.png", Rect(0, 0, bodySize.width, bodySize.height));
	    bodySize = Sprite::create("Enemy/Bat_Fire/up_2.png")->getContentSize();
	    SpriteFrame* up_2 = SpriteFrame::create("Enemy/Bat_Fire/up_2.png", Rect(0, 0, bodySize.width, bodySize.height));
	    walk_up.pushBack(up_1);
	    walk_up.pushBack(up_2);
	    bodySize = Sprite::create("Enemy/Bat_Fire/down_1.png")->getContentSize();
	    SpriteFrame* down_1 = SpriteFrame::create("Enemy/Bat_Fire/down_1.png", Rect(0, 0, bodySize.width, bodySize.height));
	    bodySize = Sprite::create("Enemy/Bat_Fire/down_2.png")->getContentSize();
	    SpriteFrame* down_2 = SpriteFrame::create("Enemy/Bat_Fire/down_2.png", Rect(0, 0, bodySize.width, bodySize.height));
	    walk_down.pushBack(down_1);
	    walk_down.pushBack(down_2);
	    bodySize = Sprite::create("Enemy/Bat_Fire/left_1.png")->getContentSize();
	    SpriteFrame* left_1 = SpriteFrame::create("Enemy/Bat_Fire/left_1.png", Rect(0, 0, bodySize.width, bodySize.height));
	    bodySize = Sprite::create("Enemy/Bat_Fire/left_2.png")->getContentSize();
	    SpriteFrame* left_2 = SpriteFrame::create("Enemy/Bat_Fire/left_2.png", Rect(0, 0, bodySize.width, bodySize.height));
	    walk_left.pushBack(left_1);
	    walk_left.pushBack(left_2);
	    bodySize = Sprite::create("Enemy/Bat_Fire/right_1.png")->getContentSize();
	    SpriteFrame* right_1 = SpriteFrame::create("Enemy/Bat_Fire/right_1.png", Rect(0, 0, bodySize.width, bodySize.height));
	    bodySize = Sprite::create("Enemy/Bat_Fire/right_2.png")->getContentSize();
	    SpriteFrame* right_2 = SpriteFrame::create("Enemy/Bat_Fire/right_2.png", Rect(0, 0, bodySize.width, bodySize.height));
	    walk_right.pushBack(right_1);
	    walk_right.pushBack(right_2);

      }
      else if (m_name == "Bat_Ice")
      {
	    //�Ȱ�m_body����Ϊ�������ͼƬ
	    m_body->setTexture("Enemy/Bat_Ice/down_1.png");//setTexture������ͼƬ�ĺ�����������ͼƬ��·�����޸��Ժ�ͼ�εĴ�С����ͼƬ�Ĵ�С

	    //��ֵ��ʼ��
	    m_hp = 100;
	    m_max_hp = 100;
	    m_mp = 50;
	    m_max_mp = 100;
	    //������Ϊ5
	    m_attack = 5;
	    speed = 10;

	    // ���ض���
	    Size bodySize = m_body->getContentSize();
	    //�˶�����֡
	    //"D:\Github_Document\GenshinImpact\Genshin\Resources\Enemy\Bat_Ice\right_3.png"
	    bodySize = Sprite::create("Enemy/Bat_Ice/up_1.png")->getContentSize();
	    SpriteFrame* up_1 = SpriteFrame::create("Enemy/Bat_Ice/up_1.png", Rect(0, 0, bodySize.width, bodySize.height));
	    bodySize = Sprite::create("Enemy/Bat_Ice/up_2.png")->getContentSize();
	    SpriteFrame* up_2 = SpriteFrame::create("Enemy/Bat_Ice/up_2.png", Rect(0, 0, bodySize.width, bodySize.height));
	    bodySize = Sprite::create("Enemy/Bat_Ice/up_3.png")->getContentSize();
	    SpriteFrame* up_3 = SpriteFrame::create("Enemy/Bat_Ice/up_3.png", Rect(0, 0, bodySize.width, bodySize.height));
	    bodySize = Sprite::create("Enemy/Bat_Ice/up_4.png")->getContentSize();
	    SpriteFrame* up_4 = SpriteFrame::create("Enemy/Bat_Ice/up_4.png", Rect(0, 0, bodySize.width, bodySize.height));
	    walk_up.pushBack(up_1);
	    walk_up.pushBack(up_2);
	    walk_up.pushBack(up_3);
	    walk_up.pushBack(up_4);
	    bodySize = Sprite::create("Enemy/Bat_Ice/down_1.png")->getContentSize();
	    SpriteFrame* down_1 = SpriteFrame::create("Enemy/Bat_Ice/down_1.png", Rect(0, 0, bodySize.width, bodySize.height));
	    bodySize = Sprite::create("Enemy/Bat_Ice/down_2.png")->getContentSize();
	    SpriteFrame* down_2 = SpriteFrame::create("Enemy/Bat_Ice/down_2.png", Rect(0, 0, bodySize.width, bodySize.height));
	    bodySize = Sprite::create("Enemy/Bat_Ice/down_3.png")->getContentSize();
	    SpriteFrame* down_3 = SpriteFrame::create("Enemy/Bat_Ice/down_3.png", Rect(0, 0, bodySize.width, bodySize.height));
	    bodySize = Sprite::create("Enemy/Bat_Ice/down_4.png")->getContentSize();
	    SpriteFrame* down_4 = SpriteFrame::create("Enemy/Bat_Ice/down_4.png", Rect(0, 0, bodySize.width, bodySize.height));
	    walk_down.pushBack(down_1);
	    walk_down.pushBack(down_2);
	    walk_down.pushBack(down_3);
	    walk_down.pushBack(down_4);
	    bodySize = Sprite::create("Enemy/Bat_Ice/left_1.png")->getContentSize();
	    SpriteFrame* left_1 = SpriteFrame::create("Enemy/Bat_Ice/left_1.png", Rect(0, 0, bodySize.width, bodySize.height));
	    bodySize = Sprite::create("Enemy/Bat_Ice/left_2.png")->getContentSize();
	    SpriteFrame* left_2 = SpriteFrame::create("Enemy/Bat_Ice/left_2.png", Rect(0, 0, bodySize.width, bodySize.height));
	    bodySize = Sprite::create("Enemy/Bat_Ice/left_3.png")->getContentSize();
	    SpriteFrame* left_3 = SpriteFrame::create("Enemy/Bat_Ice/left_3.png", Rect(0, 0, bodySize.width, bodySize.height));
	    bodySize = Sprite::create("Enemy/Bat_Ice/left_4.png")->getContentSize();
	    SpriteFrame* left_4 = SpriteFrame::create("Enemy/Bat_Ice/left_4.png", Rect(0, 0, bodySize.width, bodySize.height));

	    walk_left.pushBack(left_1);
	    walk_left.pushBack(left_2);
	    walk_left.pushBack(left_3);
	    walk_left.pushBack(left_4);
	    bodySize = Sprite::create("Enemy/Bat_Ice/right_1.png")->getContentSize();
	    SpriteFrame* right_1 = SpriteFrame::create("Enemy/Bat_Ice/right_1.png", Rect(0, 0, bodySize.width, bodySize.height));
	    bodySize = Sprite::create("Enemy/Bat_Ice/right_2.png")->getContentSize();
	    SpriteFrame* right_2 = SpriteFrame::create("Enemy/Bat_Ice/right_2.png", Rect(0, 0, bodySize.width, bodySize.height));
	    bodySize = Sprite::create("Enemy/Bat_Ice/right_3.png")->getContentSize();
	    SpriteFrame* right_3 = SpriteFrame::create("Enemy/Bat_Ice/right_3.png", Rect(0, 0, bodySize.width, bodySize.height));
	    bodySize = Sprite::create("Enemy/Bat_Ice/right_4.png")->getContentSize();
	    SpriteFrame* right_4 = SpriteFrame::create("Enemy/Bat_Ice/right_4.png", Rect(0, 0, bodySize.width, bodySize.height));
	    walk_right.pushBack(right_1);
	    walk_right.pushBack(right_2);
	    walk_right.pushBack(right_3);
	    walk_right.pushBack(right_4);



      }
      //����Ȯ
      else if (m_name == "HellDog")
      {
	    //�Ȱ�m_body����Ϊ����Ȯ��ͼƬ
	    m_body->setTexture("Enemy/HellDog/down_1.png");//setTexture������ͼƬ�ĺ�����������ͼƬ��·�����޸��Ժ�ͼ�εĴ�С����ͼƬ�Ĵ�С
	    //ͼ��Ŵ�5������ײ��ҲҪ�Ŵ�5��
	    m_body->setScale(5);
	    //m_body->setPhysicsBody(PhysicsBody::createBox(m_body->getContentSize()));//����һ����������ĺ���

	    //Ѫ��λ���ƶ�����Ļ�·����ҷŴ�5��
	    //X�Ŵ�5����Y�Ŵ�2��
	    Enemy_hpBar->setScale(5, 0.3);



	    //��ֵ��ʼ��
	    m_hp = 2000;
	    m_max_hp = 2000;
	    m_mp = 50;
	    m_max_mp = 100;
	    //�ٶ�
	    speed = 3;

	    //������Ϊ10
	    m_attack = 10;
	    // ���ض���
	    Size bodySize = m_body->getContentSize();
	    //�˶�����֡
	    //"D:\Github_Document\GenshinImpact\Genshin\Resources\Enemy\HellDog\up_1.png"��ȡͼƬ����ȡ�Ĵ�С�������ͼƬ�Ĵ�С
	    //�ȶ�ȡĿ��ͼƬ��С,"D:\Github_Document\GenshinImpact\Genshin\Resources\Enemy\HellDog\up_1.png"��ȡͼƬ
	    bodySize = Sprite::create("Enemy/HellDog/up_1.png")->getContentSize();
	    SpriteFrame* up_1 = SpriteFrame::create("Enemy/HellDog/up_1.png", Rect(0, 0, bodySize.width, bodySize.height));
	    bodySize = Sprite::create("Enemy/HellDog/up_2.png")->getContentSize();
	    SpriteFrame* up_2 = SpriteFrame::create("Enemy/HellDog/up_2.png", Rect(0, 0, bodySize.width, bodySize.height));
	    bodySize = Sprite::create("Enemy/HellDog/up_3.png")->getContentSize();
	    SpriteFrame* up_3 = SpriteFrame::create("Enemy/HellDog/up_3.png", Rect(0, 0, bodySize.width, bodySize.height));
	    bodySize = Sprite::create("Enemy/HellDog/up_4.png")->getContentSize();
	    SpriteFrame* up_4 = SpriteFrame::create("Enemy/HellDog/up_4.png", Rect(0, 0, bodySize.width, bodySize.height));
	    walk_up.pushBack(up_1);
	    walk_up.pushBack(up_2);
	    walk_up.pushBack(up_3);
	    walk_up.pushBack(up_4);

	    bodySize = Sprite::create("Enemy/HellDog/down_1.png")->getContentSize();
	    SpriteFrame* down_1 = SpriteFrame::create("Enemy/HellDog/down_1.png", Rect(0, 0, bodySize.width, bodySize.height));
	    bodySize = Sprite::create("Enemy/HellDog/down_2.png")->getContentSize();
	    SpriteFrame* down_2 = SpriteFrame::create("Enemy/HellDog/down_2.png", Rect(0, 0, bodySize.width, bodySize.height));
	    bodySize = Sprite::create("Enemy/HellDog/down_3.png")->getContentSize();
	    SpriteFrame* down_3 = SpriteFrame::create("Enemy/HellDog/down_3.png", Rect(0, 0, bodySize.width, bodySize.height));
	    bodySize = Sprite::create("Enemy/HellDog/down_4.png")->getContentSize();
	    SpriteFrame* down_4 = SpriteFrame::create("Enemy/HellDog/down_4.png", Rect(0, 0, bodySize.width, bodySize.height));
	    walk_down.pushBack(down_1);
	    walk_down.pushBack(down_2);
	    walk_down.pushBack(down_3);
	    walk_down.pushBack(down_4);

	    bodySize = Sprite::create("Enemy/HellDog/left_1.png")->getContentSize();
	    SpriteFrame* left_1 = SpriteFrame::create("Enemy/HellDog/left_1.png", Rect(0, 0, bodySize.width, bodySize.height));
	    bodySize = Sprite::create("Enemy/HellDog/left_2.png")->getContentSize();
	    SpriteFrame* left_2 = SpriteFrame::create("Enemy/HellDog/left_2.png", Rect(0, 0, bodySize.width, bodySize.height));
	    bodySize = Sprite::create("Enemy/HellDog/left_3.png")->getContentSize();
	    SpriteFrame* left_3 = SpriteFrame::create("Enemy/HellDog/left_3.png", Rect(0, 0, bodySize.width, bodySize.height));
	    bodySize = Sprite::create("Enemy/HellDog/left_4.png")->getContentSize();
	    SpriteFrame* left_4 = SpriteFrame::create("Enemy/HellDog/left_4.png", Rect(0, 0, bodySize.width, bodySize.height));
	    walk_left.pushBack(left_1);
	    walk_left.pushBack(left_2);
	    walk_left.pushBack(left_3);
	    walk_left.pushBack(left_4);

	    bodySize = Sprite::create("Enemy/HellDog/right_1.png")->getContentSize();
	    SpriteFrame* right_1 = SpriteFrame::create("Enemy/HellDog/right_1.png", Rect(0, 0, bodySize.width, bodySize.height));
	    bodySize = Sprite::create("Enemy/HellDog/right_2.png")->getContentSize();
	    SpriteFrame* right_2 = SpriteFrame::create("Enemy/HellDog/right_2.png", Rect(0, 0, bodySize.width, bodySize.height));
	    bodySize = Sprite::create("Enemy/HellDog/right_3.png")->getContentSize();
	    SpriteFrame* right_3 = SpriteFrame::create("Enemy/HellDog/right_3.png", Rect(0, 0, bodySize.width, bodySize.height));
	    bodySize = Sprite::create("Enemy/HellDog/right_4.png")->getContentSize();
	    SpriteFrame* right_4 = SpriteFrame::create("Enemy/HellDog/right_4.png", Rect(0, 0, bodySize.width, bodySize.height));
	    walk_right.pushBack(right_1);
	    walk_right.pushBack(right_2);
	    walk_right.pushBack(right_3);
	    walk_right.pushBack(right_4);
      }

}