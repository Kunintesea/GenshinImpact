#include "Player.h"

/*
���ڶ�������m_body�ϵ�tag��������getNumberOfRunningActionsByTag��ȡ��
1������
2������
3������
4������
*/


bool Player::init()
{
	if (!Node::init())
	{
		return false;
	}
	//��������
	m_body = Sprite::create("me/front.png");
	//��������ӵ��ڵ�
	this->addChild(m_body);






	// �����ٶ�
	speed = 5;

	m_head = Sprite::create("me/head.png");
	//��С5��
	m_head->setScale(0.2);
	//����λ�õ������ұ�
	m_head->setPosition(Vec2(m_body->getContentSize().width / 2, 0));
	this->addChild(m_head);

	// ���ض���
	// ��ֹ����֡
	Size bodySize = m_body->getContentSize();
	SpriteFrame* front = SpriteFrame::create("me/front.png", Rect(0, 0, bodySize.width, bodySize.height));
	SpriteFrame* back = SpriteFrame::create("me/back.png", Rect(0, 0, bodySize.width, bodySize.height));
	SpriteFrame* left = SpriteFrame::create("me/left.png", Rect(0, 0, bodySize.width, bodySize.height));
	SpriteFrame* right = SpriteFrame::create("me/right.png", Rect(0, 0, bodySize.width, bodySize.height));
	SpriteFrame* dead = SpriteFrame::create("me/dead.png", Rect(0, 0, bodySize.width, bodySize.height));
	staticForwards.pushBack(front);
	staticForwards.pushBack(back);
	staticForwards.pushBack(left);
	staticForwards.pushBack(right);
	staticForwards.pushBack(dead);

	//�˶�����֡
	SpriteFrame* walk_back1 = SpriteFrame::create("me/walk_back1.png", Rect(0, 0, bodySize.width, bodySize.height));
	SpriteFrame* walk_back2 = SpriteFrame::create("me/walk_back2.png", Rect(0, 0, bodySize.width, bodySize.height));
	walk_back.pushBack(walk_back1);
	walk_back.pushBack(walk_back2);
	SpriteFrame* walk_front1 = SpriteFrame::create("me/walk_front1.png", Rect(0, 0, bodySize.width, bodySize.height));
	SpriteFrame* walk_front2 = SpriteFrame::create("me/walk_front2.png", Rect(0, 0, bodySize.width, bodySize.height));
	walk_front.pushBack(walk_front1);
	walk_front.pushBack(walk_front2);
	SpriteFrame* walk_left1 = SpriteFrame::create("me/walk_left1.png", Rect(0, 0, bodySize.width, bodySize.height));
	SpriteFrame* walk_left2 = SpriteFrame::create("me/walk_left2.png", Rect(0, 0, bodySize.width, bodySize.height));
	walk_left.pushBack(walk_left1);
	walk_left.pushBack(walk_left2);
	SpriteFrame* walk_right1 = SpriteFrame::create("me/walk_right1.png", Rect(0, 0, bodySize.width, bodySize.height));
	SpriteFrame* walk_right2 = SpriteFrame::create("me/walk_right2.png", Rect(0, 0, bodySize.width, bodySize.height));
	walk_right.pushBack(walk_right1);
	walk_right.pushBack(walk_right2);

	//���������
	this->scheduleUpdate();

	//�����¼�����
	auto eventListener = EventListenerKeyboard::create();
	//��������ʱ����
	eventListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event)
		{
			switch (keyCode)//ͬʱ֧��WASD�ͷ����
			{
			case EventKeyboard::KeyCode::KEY_A:
			case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
				keyMap[EventKeyboard::KeyCode::KEY_LEFT_ARROW] = true;
				break;
			case EventKeyboard::KeyCode::KEY_D:
			case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
				keyMap[EventKeyboard::KeyCode::KEY_RIGHT_ARROW] = true;
				break;
			case EventKeyboard::KeyCode::KEY_W:
			case EventKeyboard::KeyCode::KEY_UP_ARROW:
				keyMap[EventKeyboard::KeyCode::KEY_UP_ARROW] = true;
				break;
			case EventKeyboard::KeyCode::KEY_S:
			case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
				keyMap[EventKeyboard::KeyCode::KEY_DOWN_ARROW] = true;
				break;
			default:
				break;
			}
		};
	//����̧��ʱ����
	eventListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event)
		{
			switch (keyCode)
			{
			case EventKeyboard::KeyCode::KEY_A:
			case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
				keyMap[EventKeyboard::KeyCode::KEY_LEFT_ARROW] = false;
				break;
			case EventKeyboard::KeyCode::KEY_D:
			case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
				keyMap[EventKeyboard::KeyCode::KEY_RIGHT_ARROW] = false;
				break;
			case EventKeyboard::KeyCode::KEY_W:
			case EventKeyboard::KeyCode::KEY_UP_ARROW:
				keyMap[EventKeyboard::KeyCode::KEY_UP_ARROW] = false;
				break;
			case EventKeyboard::KeyCode::KEY_S:
			case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
				keyMap[EventKeyboard::KeyCode::KEY_DOWN_ARROW] = false;
				break;
			default:
				break;
			}
		};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, this);//�Ѽ��������뵽�¼��ַ����У��������������󶨵Ķ�����������ȼ��趨Ϊ��������ȼ�

	return true;
}

void Player::update(float dt)
{
	if (keyMap[EventKeyboard::KeyCode::KEY_LEFT_ARROW])//����������
	{
	      moveAnimation(walk_left, 1);
	      this->setPositionX(this->getPositionX() - speed);//�����ƶ�10������
	}
	if (keyMap[EventKeyboard::KeyCode::KEY_RIGHT_ARROW])//����Ҽ�����
	{
	      moveAnimation(walk_right, 2);
	      this->setPositionX(this->getPositionX() + speed);//�����ƶ�10������
	}
	if (keyMap[EventKeyboard::KeyCode::KEY_UP_ARROW])//����ϼ�����
	{
	      moveAnimation(walk_back, 4);
	      this->setPositionY(this->getPositionY() + speed);//�����ƶ�10������
	}
	if (keyMap[EventKeyboard::KeyCode::KEY_DOWN_ARROW])//����¼�����
	{
	      moveAnimation(walk_front, 3);
	      this->setPositionY(this->getPositionY() - speed);//�����ƶ�10������
	}
	if (!keyMap[EventKeyboard::KeyCode::KEY_LEFT_ARROW] && !keyMap[EventKeyboard::KeyCode::KEY_RIGHT_ARROW] && !keyMap[EventKeyboard::KeyCode::KEY_UP_ARROW] && !keyMap[EventKeyboard::KeyCode::KEY_DOWN_ARROW])//���û�а�������
	{
	      if (m_body->getNumberOfRunningActionsByTag(1) != 0) // �������������
		    m_body->setSpriteFrame(staticForwards.at(2));
	      else if (m_body->getNumberOfRunningActionsByTag(2) != 0) // �������������
		    m_body->setSpriteFrame(staticForwards.at(3));
	      else if (m_body->getNumberOfRunningActionsByTag(4) != 0) // �������������
		    m_body->setSpriteFrame(staticForwards.at(1));
	      else
		    m_body->setSpriteFrame(staticForwards.at(0));
	}
}

void Player::moveAnimation(Vector<SpriteFrame*> frame, int actionTag) {
      //����
      if (m_body->getActionByTag(actionTag) == 0)
      {
	    m_body->stopAllActions();//ֹͣ���ж���
	    auto action = RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(frame, 0.2f))); // ���붯��֡
	    action->setTag(actionTag);//���ñ�ǩ
	    m_body->runAction((action));//ִ���������
      }
}

