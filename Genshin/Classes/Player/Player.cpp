#include "Player.h"

/*
���ڶ�������m_body�ϵ�tag��������getNumberOfRunningActionsByTag��ȡ��
1������
2������
3������
4������
*/
//�˺�����ʽ��ʵ���˺�=�˺�ֵ-����ֵ*�˺�ֵ�������ﴦ������״ֱ̬�ӷ���0
void Player::hurt(int damage,int damge_type)
{ 
	if (isDodge) return;
	else
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
			if (m_element[Fire])
			{
				//����Ч��
				//�˺�ֵ����
				damage *= 2;
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
						m_element_label[i]->setPosition(Vec2(this->getPositionX() + rand() % 50, this->getPositionY()  + rand() % 50));
						m_element_label[i]->setString("Explode");
						m_element_label[i]->setVisible(true);
						m_element_label[i]->runAction(Sequence::create(MoveBy::create(0.1, Vec2(0, 20)), nullptr));
						m_element_label[i]->runAction(Sequence::create(DelayTime::create(1.5), CallFunc::create([=] {m_element_label[i]->setVisible(false); }), MoveBy::create(0.1, Vec2(0, -20)), nullptr));
						
						break;
					}
				}
			}
			break;
		case Grass:
			break;
		case Water:
			break;
		case Fire:
			m_element[Fire] = 1;
			break;
		case Ice:
			break;
		default:
			break;
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





				
				m_damage_label[i]->setPosition(Vec2(this->getPositionX () - m_body->getContentSize().width/2  + rand() % 50, this->getPositionY() -m_body->getContentSize().height/2  + rand() % 50));//rand()��ʹ�÷�����rand()%n����ʾ����һ��0��n-1�������
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
	}
}

bool Player::init()
{
	if (!Node::init())
	{
		return false;
	}
	//��������
	m_body = Sprite::create("Me/Saber/Walk/front.png");
	//��������ӵ��ڵ�
	this->addChild(m_body);

	//ͨ����ȡxml�ļ�����ȡԪ�ط�Ӧ���֣�֧������
	//CCDictionary* chnStrings = CCDictionary::createWithContentsOfFile("Text/Ԫ�ط�Ӧ����.xml");
	//const char* username = ((CCString*)chnStrings->objectForKey("username"))->getCString();

	//��ʼ������
	//m_name = "Me";

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
	//"D:\Github_Document\GenshinImpact\Genshin\Resources\Me\Saber\Walk\walk_back2.png"
	SpriteFrame* front = SpriteFrame::create("Me/Saber/Walk/front.png", Rect(0, 0, bodySize.width, bodySize.height));
	SpriteFrame* back = SpriteFrame::create("Me/Saber/Walk/back.png", Rect(0, 0, bodySize.width, bodySize.height));
	SpriteFrame* left = SpriteFrame::create("Me/Saber/Walk/left.png", Rect(0, 0, bodySize.width, bodySize.height));
	SpriteFrame* right = SpriteFrame::create("Me/Saber/Walk/right.png", Rect(0, 0, bodySize.width, bodySize.height));
	//SpriteFrame* dead = SpriteFrame::create("Me/Saber/Walk/dead.png", Rect(0, 0, bodySize.width, bodySize.height));
	staticForwards.pushBack(front);
	staticForwards.pushBack(back);
	staticForwards.pushBack(left);
	staticForwards.pushBack(right);
	//staticForwards.pushBack(dead);

	//�˶�����֡
	SpriteFrame* walk_back1 = SpriteFrame::create("Me/Saber/Walk/walk_back1.png", Rect(0, 0, bodySize.width, bodySize.height));
	SpriteFrame* walk_back2 = SpriteFrame::create("Me/Saber/Walk/walk_back2.png", Rect(0, 0, bodySize.width, bodySize.height));
	walk_back.pushBack(walk_back1);
	walk_back.pushBack(walk_back2);
	SpriteFrame* walk_front1 = SpriteFrame::create("Me/Saber/Walk/walk_front1.png", Rect(0, 0, bodySize.width, bodySize.height));
	SpriteFrame* walk_front2 = SpriteFrame::create("Me/Saber/Walk/walk_front2.png", Rect(0, 0, bodySize.width, bodySize.height));
	walk_front.pushBack(walk_front1);
	walk_front.pushBack(walk_front2);
	SpriteFrame* walk_left1 = SpriteFrame::create("Me/Saber/Walk/walk_left1.png", Rect(0, 0, bodySize.width, bodySize.height));
	SpriteFrame* walk_left2 = SpriteFrame::create("Me/Saber/Walk/walk_left2.png", Rect(0, 0, bodySize.width, bodySize.height));
	walk_left.pushBack(walk_left1);
	walk_left.pushBack(walk_left2);
	SpriteFrame* walk_right1 = SpriteFrame::create("Me/Saber/Walk/walk_right1.png", Rect(0, 0, bodySize.width, bodySize.height));
	SpriteFrame* walk_right2 = SpriteFrame::create("Me/Saber/Walk/walk_right2.png", Rect(0, 0, bodySize.width, bodySize.height));
	walk_right.pushBack(walk_right1);
	walk_right.pushBack(walk_right2);

	//���������
	this->scheduleUpdate();

	//�Կ�Ѫ�ļ���
	auto eventLLL = EventListenerKeyboard::create();
	eventLLL->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event)
		{
			switch (keyCode)
			{
			case EventKeyboard::KeyCode::KEY_O:
				hurt(1,Fire);
				break;
			case EventKeyboard::KeyCode::KEY_P:
				hurt(1, Thunder);
				break;
			default:
				break;
			}
		};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventLLL, this);//�Ѽ��������뵽�¼��ַ����У��������������󶨵Ķ�����������ȼ��趨Ϊ��������ȼ�

	//������Ҽ����ܵļ���
	auto DodgeListener = EventListenerMouse::create();
	DodgeListener->onMouseDown = [=](Event* event)
		{
			auto mouseEvent = static_cast<EventMouse*>(event);
			if (mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_RIGHT)
			{
				isDodge = true;
				//���ܵķ����ǳ������ķ���
				EventMouse* mousePosition = dynamic_cast<EventMouse*>(event);
				float x = mousePosition->getCursorX();
				float y = mousePosition->getCursorY();
				// ת��Ϊ��������
				Vec2 worldPosition = Vec2(x, y);
				//������귽����
				this->dodge(worldPosition);


			}
		};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(DodgeListener, this);//�Ѽ��������뵽�¼��ַ����У��������������󶨵Ķ�����������ȼ��趨Ϊ��������ȼ�



	//�����¼�����
	auto keyboardListener = EventListenerKeyboard::create();
	//��������ʱ����
	keyboardListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event)
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
	keyboardListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event)
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
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);//�Ѽ��������뵽�¼��ַ����У��������������󶨵Ķ�����������ȼ��趨Ϊ��������ȼ�

	//����¼�����
	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseMove = [this](Event* event)
		{
			log("!!!!!!!mouse!!!!!!!");
			EventMouse* mousePosition = dynamic_cast<EventMouse*>(event);
			float x = mousePosition->getCursorX();
			float y = mousePosition->getCursorY();
			// ת��Ϊ��������
			Vec2 worldPosition = Vec2(x, y);
			log("mouseWorldPosition x = %f", x);
			log("mouseWorldPosition y = %f", y);
			this->getPlayerOrientation(worldPosition);
		};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);//�Ѽ��������뵽�¼��ַ����У��������������󶨵Ķ�����������ȼ��趨Ϊ��������ȼ�

	//����¼������������ڸ��³���
	schedule(CC_CALLBACK_0(Player::updatePlayerOrientation, this), "mouse");
	//�����¼������������ڸ���λ��
	schedule(CC_CALLBACK_1(Player::updatePlayerPosition, this), "keyboard");

	return true;
}

void Player::updatePlayerPosition(float dt)
{
	if (keyMap[EventKeyboard::KeyCode::KEY_LEFT_ARROW])//����������
	{
	      //moveAnimation(walk_left, 1);
	      this->setPositionX(this->getPositionX() - speed);//�����ƶ�10������
	}
	if (keyMap[EventKeyboard::KeyCode::KEY_RIGHT_ARROW])//����Ҽ�����
	{
	      //moveAnimation(walk_right, 2);
	      this->setPositionX(this->getPositionX() + speed);//�����ƶ�10������
	}
	if (keyMap[EventKeyboard::KeyCode::KEY_UP_ARROW])//����ϼ�����
	{
	      //moveAnimation(walk_back, 4);
	      this->setPositionY(this->getPositionY() + speed);//�����ƶ�10������
	}
	if (keyMap[EventKeyboard::KeyCode::KEY_DOWN_ARROW])//����¼�����
	{
	      //moveAnimation(walk_front, 3);
	      this->setPositionY(this->getPositionY() - speed);//�����ƶ�10������
	}
	if (!keyMap[EventKeyboard::KeyCode::KEY_LEFT_ARROW] && !keyMap[EventKeyboard::KeyCode::KEY_RIGHT_ARROW] && !keyMap[EventKeyboard::KeyCode::KEY_UP_ARROW] && !keyMap[EventKeyboard::KeyCode::KEY_DOWN_ARROW])//���û�а�������
	{
		//if (m_body->getNumberOfRunningActionsByTag(1) != 0) // �������������
		  //m_body->setSpriteFrame(staticForwards.at(2));
		//else if (m_body->getNumberOfRunningActionsByTag(2) != 0) // �������������
		  //m_body->setSpriteFrame(staticForwards.at(3));
	   // else if (m_body->getNumberOfRunningActionsByTag(4) != 0) // �������������
		  //m_body->setSpriteFrame(staticForwards.at(1));
	   // else
		  //m_body->setSpriteFrame(staticForwards.at(0));

		if (this->mouseState[2]) // �������������
			m_body->setSpriteFrame(staticForwards.at(2));
		else if (this->mouseState[3]) // �������������
			m_body->setSpriteFrame(staticForwards.at(3));
		else if (this->mouseState[0]) // �������������
			m_body->setSpriteFrame(staticForwards.at(1));
		else if (this->mouseState[1])
			m_body->setSpriteFrame(staticForwards.at(0));
	}

	//�����⵽�Ҽ���������귽����
	//if (isDodge)
	//{
	//	//����귽����
	//	//��ȡ���λ��
	//	auto mousePosition = Director::getInstance()->getOpenGLView()->getMousePosition();
	//}

	
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
void Player::dodge(Vec2 position)
{
	//��������б��
	//��ý�ɫ��ͼ�ߴ�
	auto playerSize = this->m_body->getContentSize();
	float k = playerSize.height / playerSize.width;

	//�����Ļ�ߴ�
	auto visibleSize = Director::getInstance()->getVisibleSize();
	//�����������������Ļ������
	Vec2 mouseWorldPosition = position;
	//��þ������������
	Vec2 spriteWorldPosition = this->getPosition();
	auto temp = this->myCamera->getCameraPostionChange();
	spriteWorldPosition = spriteWorldPosition - this->myCamera->getCameraPostionChange()
		+ Vec2(visibleSize.width / 2, visibleSize.height / 2);
	//����
	Vec2 mouseLocalPosition = Vec2(mouseWorldPosition.x - spriteWorldPosition.x, mouseWorldPosition.y - spriteWorldPosition.y);

	//����Ƕ�
	float angle = atan2(mouseLocalPosition.y, mouseLocalPosition.x);
	//��̾���
	float distance = 100;
	//����ٶ�
	float dodgeSpeed = 1000;
	//��̷���
	Vec2 dodgeDirection = Vec2(cos(angle), sin(angle));
	//��ʼ���
	this->runAction(Sequence::create(MoveBy::create(distance / dodgeSpeed, dodgeDirection * distance), CallFunc::create([=] {isDodge = false; }), nullptr));

}

//�������λ����ȷ�����ﳯ��
void Player::getPlayerOrientation(Vec2 position)
{
	//��������б��
	//��ý�ɫ��ͼ�ߴ�
	auto playerSize = this->m_body->getContentSize();
	float k = playerSize.height / playerSize.width;
	log("height = %f", playerSize.height);
	log("width = %f", playerSize.width);

	log("!!!!!!k = %f", k);

	//�����Ļ�ߴ�
	auto visibleSize = Director::getInstance()->getVisibleSize();
	//�����������������Ļ������
	Vec2 mouseWorldPosition = position;
	//��þ������������
	Vec2 spriteWorldPosition = this->getPosition();
	auto temp = this->myCamera->getCameraPostionChange();
	spriteWorldPosition = spriteWorldPosition - this->myCamera->getCameraPostionChange()
		+ Vec2(visibleSize.width / 2, visibleSize.height / 2);

	log("spriteWorldPosition x = %f", spriteWorldPosition.x);
	log("spriteWorldPosition y = %f", spriteWorldPosition.y);
	//����
	Vec2 mouseLocalPosition = Vec2(mouseWorldPosition.x - spriteWorldPosition.x, mouseWorldPosition.y - spriteWorldPosition.y);
	log("mouseLocalPosition x = %f", mouseLocalPosition.x);
	log("mouseLocalPosition y = %f", mouseLocalPosition.y);

	if (mouseLocalPosition.y > mouseLocalPosition.x * k
		&& mouseLocalPosition.y > mouseLocalPosition.x * -k)
	{
		this->mouseState[0] = true;
		this->mouseState[1] = false;
		this->mouseState[2] = false;
		this->mouseState[3] = false;
	}
	else if (mouseLocalPosition.y < mouseLocalPosition.x * k
		&& mouseLocalPosition.y < mouseLocalPosition.x * -k)
	{
		this->mouseState[0] = false;
		this->mouseState[1] = true;
		this->mouseState[2] = false;
		this->mouseState[3] = false;
	}
	else if (mouseLocalPosition.y > mouseLocalPosition.x * k
		&& mouseLocalPosition.y < mouseLocalPosition.x * -k)
	{
		this->mouseState[0] = false;
		this->mouseState[1] = false;
		this->mouseState[2] = true;
		this->mouseState[3] = false;
	}
	else if (mouseLocalPosition.y < mouseLocalPosition.x * k
		&& mouseLocalPosition.y > mouseLocalPosition.x * -k)
	{
		this->mouseState[0] = false;
		this->mouseState[1] = false;
		this->mouseState[2] = false;
		this->mouseState[3] = true;
	}
}



void Player::updatePlayerOrientation()
{
	if (this->mouseState[0])
	{
		moveAnimation(walk_back, 4);
	}
	else if (this->mouseState[1])
	{
		moveAnimation(walk_front, 3);
	}
	else if (this->mouseState[2])
	{
		moveAnimation(walk_left, 1);
	}
	else if (this->mouseState[3])
	{
		moveAnimation(walk_right, 2);
	}
}


