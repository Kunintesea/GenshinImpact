#include "Player.h"
#include "Enemy.h"
/*
���ڶ�������m_body�ϵ�tag��������getNumberOfRunningActionsByTag��ȡ��
1������
2������
3������
4������
*/
//�˺�����ʽ��ʵ���˺�=�˺�ֵ-����ֵ*�˺�ֵ�������ﴦ������״ֱ̬�ӷ���0
bool Player::init()
{
	if (!Node::init())
	{
		return false;
	}

	this->m_name = "swordPlayer";

	//��������
	m_body = Sprite::create("Me/Saber/Walk/front1.png");
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
		m_element_sprite[i]->setPosition(Vec2(this->getPositionX(), this->getPositionY() + m_body->getContentSize().height ));
		this->addChild(m_element_sprite[i]);
	}


	//��ȡ�����Ѫ������UserDefault
	//m_hp = UserDefault::getInstance()->getIntegerForKey("hp", m_hp);




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
	angleSpeed = 5;
	m_attack = 1000;

	m_head = Sprite::create("me/head.png");
	//��С5��
	m_head->setScale(0.2);
	//����λ�õ������ұ�
	m_head->setPosition(Vec2(m_body->getContentSize().width, 0));
	this->addChild(m_head);

	//��������
	m_weapon = Sprite::create("Me/Saber/Weapon/sword.png");
	m_weapon->setAnchorPoint(Vec2(0.5, 0));
	if (!isWeapon)
	{
		weaponPosition = Vec2(m_body->getPosition().x + m_weapon->getContentSize().width / (1.25), m_body->getPosition().y);
		m_weapon->setPosition(weaponPosition);
	}
	this->addChild(m_weapon);
	//m_weapon_light = Sprite::create("Me/Saber/Weapon/sword_light.png");
	//m_weapon_light->setAnchorPoint(Vec2(0.5, 0));
	//m_weapon_light->setVisible(false);  // ���ؾ���

	//RGB����Ϊ��ɫ
	//m_weapon_light->setColor(Color3B(255, 0, 0));

	//this->addChild(m_weapon_light);//��ӵ�������
	//����һ���������͵�tag����Physical, Wind, Rock, Thunder, Grass, Water, Fire, Ice
	//m_weapon_light->setTag(Physical);

		//e����
	m_e = Sprite::create("Me/Saber/Weapon/e2.png");
	m_e->setAnchorPoint(Vec2(0.5, 0));
	m_e->setVisible(false);  // ���ؾ���
	this->addChild(m_e);

	// ���ض���
	// ��ֹ����֡
	Size bodySize = m_body->getContentSize();
	//"D:\Github_Document\GenshinImpact\Genshin\Resources\Me\Saber\Walk\walk_back2.png"
	SpriteFrame* sword_front = SpriteFrame::create("Me/Saber/Walk/front1.png", Rect(0, 0, bodySize.width, bodySize.height));
	SpriteFrame* sword_back = SpriteFrame::create("Me/Saber/Walk/back1.png", Rect(0, 0, bodySize.width, bodySize.height));
	SpriteFrame* sword_left = SpriteFrame::create("Me/Saber/Walk/left1.png", Rect(0, 0, bodySize.width, bodySize.height));
	SpriteFrame* sword_right = SpriteFrame::create("Me/Saber/Walk/right1.png", Rect(0, 0, bodySize.width, bodySize.height));
	//SpriteFrame* dead = SpriteFrame::create("Me/Saber/Walk/dead.png", Rect(0, 0, bodySize.width, bodySize.height));
	sword_staticForwards.pushBack(sword_front);
	sword_staticForwards.pushBack(sword_back);
	sword_staticForwards.pushBack(sword_left);
	sword_staticForwards.pushBack(sword_right);
	//staticForwards.pushBack(dead);
	SpriteFrame* bow_front = SpriteFrame::create("Me/Saber/Walk/front2.png", Rect(0, 0, bodySize.width, bodySize.height));
	SpriteFrame* bow_back = SpriteFrame::create("Me/Saber/Walk/back2.png", Rect(0, 0, bodySize.width, bodySize.height));
	SpriteFrame* bow_left = SpriteFrame::create("Me/Saber/Walk/left2.png", Rect(0, 0, bodySize.width, bodySize.height));
	SpriteFrame* bow_right = SpriteFrame::create("Me/Saber/Walk/right2.png", Rect(0, 0, bodySize.width, bodySize.height));
	//SpriteFrame* dead = SpriteFrame::create("Me/Saber/Walk/dead.png", Rect(0, 0, bodySize.width, bodySize.height));
	bow_staticForwards.pushBack(bow_front);
	bow_staticForwards.pushBack(bow_back);
	bow_staticForwards.pushBack(bow_left);
	bow_staticForwards.pushBack(bow_right);
	//staticForwards.pushBack(dead);

	//�˶�����֡
	SpriteFrame* sword_walk_back1 = SpriteFrame::create("Me/Saber/Walk/back1_walk1.png", Rect(0, 0, bodySize.width, bodySize.height));
	SpriteFrame* sword_walk_back2 = SpriteFrame::create("Me/Saber/Walk/back1_walk2.png", Rect(0, 0, bodySize.width, bodySize.height));
	sword_walk_back.pushBack(sword_walk_back1);
	sword_walk_back.pushBack(sword_walk_back2);
	SpriteFrame* sword_walk_front1 = SpriteFrame::create("Me/Saber/Walk/front1_walk1.png", Rect(0, 0, bodySize.width, bodySize.height));
	SpriteFrame* sword_walk_front2 = SpriteFrame::create("Me/Saber/Walk/front1_walk2.png", Rect(0, 0, bodySize.width, bodySize.height));
	sword_walk_front.pushBack(sword_walk_front1);
	sword_walk_front.pushBack(sword_walk_front2);
	SpriteFrame* sword_walk_left1 = SpriteFrame::create("Me/Saber/Walk/left1_walk1.png", Rect(0, 0, bodySize.width, bodySize.height));
	SpriteFrame* sword_walk_left2 = SpriteFrame::create("Me/Saber/Walk/left1_walk2.png", Rect(0, 0, bodySize.width, bodySize.height));
	sword_walk_left.pushBack(sword_walk_left1);
	sword_walk_left.pushBack(sword_walk_left2);
	SpriteFrame* sword_walk_right1 = SpriteFrame::create("Me/Saber/Walk/right1_walk1.png", Rect(0, 0, bodySize.width, bodySize.height));
	SpriteFrame* sword_walk_right2 = SpriteFrame::create("Me/Saber/Walk/right1_walk2.png", Rect(0, 0, bodySize.width, bodySize.height));
	sword_walk_right.pushBack(sword_walk_right1);
	sword_walk_right.pushBack(sword_walk_right2);

	SpriteFrame* bow_walk_back1 = SpriteFrame::create("Me/Saber/Walk/back2_walk1.png", Rect(0, 0, bodySize.width, bodySize.height));
	SpriteFrame* bow_walk_back2 = SpriteFrame::create("Me/Saber/Walk/back2_walk2.png", Rect(0, 0, bodySize.width, bodySize.height));
	bow_walk_back.pushBack(bow_walk_back1);
	bow_walk_back.pushBack(bow_walk_back2);
	SpriteFrame* bow_walk_front1 = SpriteFrame::create("Me/Saber/Walk/front2_walk1.png", Rect(0, 0, bodySize.width, bodySize.height));
	SpriteFrame* bow_walk_front2 = SpriteFrame::create("Me/Saber/Walk/front2_walk2.png", Rect(0, 0, bodySize.width, bodySize.height));
	bow_walk_front.pushBack(bow_walk_front1);
	bow_walk_front.pushBack(bow_walk_front2);
	SpriteFrame* bow_walk_left1 = SpriteFrame::create("Me/Saber/Walk/left2_walk1.png", Rect(0, 0, bodySize.width, bodySize.height));
	SpriteFrame* bow_walk_left2 = SpriteFrame::create("Me/Saber/Walk/left2_walk2.png", Rect(0, 0, bodySize.width, bodySize.height));
	bow_walk_left.pushBack(bow_walk_left1);
	bow_walk_left.pushBack(bow_walk_left2);
	SpriteFrame* bow_walk_right1 = SpriteFrame::create("Me/Saber/Walk/right2_walk1.png", Rect(0, 0, bodySize.width, bodySize.height));
	SpriteFrame* bow_walk_right2 = SpriteFrame::create("Me/Saber/Walk/right2_walk2.png", Rect(0, 0, bodySize.width, bodySize.height));
	bow_walk_right.pushBack(bow_walk_right1);
	bow_walk_right.pushBack(bow_walk_right2);


	//���������
	this->scheduleUpdate();

	//�Կ�Ѫ�ļ���
	auto eventLLL = EventListenerKeyboard::create();
	eventLLL->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event)
		{
			switch (keyCode)
			{
			case EventKeyboard::KeyCode::KEY_O:
				hurt(1,Fire,true);
				break;
			case EventKeyboard::KeyCode::KEY_P:
				hurt(1, Thunder,true);
				break;
			case EventKeyboard::KeyCode::KEY_I:
				hurt(1, Ice, true);
				break;
			case EventKeyboard::KeyCode::KEY_U:
				hurt(1, Water, true);
				break;
			case EventKeyboard::KeyCode::KEY_E:
				if (m_E_CD == 0)
				{
					m_E_CD = m_max_E_CD;
				}
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
			if (mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_RIGHT && !isE)
			{
				if (m_stamina > 10)
				{
					m_stamina -= 10;
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
			}
		};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(DodgeListener, this);//�Ѽ��������뵽�¼��ַ����У��������������󶨵Ķ�����������ȼ��趨Ϊ��������ȼ�

	//��������������ͨ�����ļ���
	auto oridinaryAttack = EventListenerMouse::create();
	oridinaryAttack->onMouseDown = [this](Event* event)
		{
			auto mouseAttack = static_cast<EventMouse*>(event);
			if (mouseAttack->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT && !isWeapon && !isE)
			{
				isWeapon = true;
				isflying = true;
				if (this->getNaming() == "swordPlayer")this->swordOrdinaryAttack();
				else if (this->getNaming() == "bowPlayer")this->bowOrdinaryAttack();
			}
		};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(oridinaryAttack, this);//�Ѽ��������뵽�¼��ַ����У��������������󶨵Ķ�����������ȼ��趨Ϊ��������ȼ�

	//�����¼�����
	auto keyboardListener = EventListenerKeyboard::create();
	//��������ʱ����
	keyboardListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event)
		{
			switch (keyCode)//ͬʱ֧��WASD�ͷ����
			{
			case EventKeyboard::KeyCode::KEY_A:
			case EventKeyboard::KeyCode::KEY_LEFT_ARROW:

			      if (!isE)keyMap[EventKeyboard::KeyCode::KEY_LEFT_ARROW] = true;
				break;
			case EventKeyboard::KeyCode::KEY_D:
			case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			      if (!isE)keyMap[EventKeyboard::KeyCode::KEY_RIGHT_ARROW] = true;
				break;
			case EventKeyboard::KeyCode::KEY_W:
			case EventKeyboard::KeyCode::KEY_UP_ARROW:
			      if (!isE)keyMap[EventKeyboard::KeyCode::KEY_UP_ARROW] = true;
			      break;
			case EventKeyboard::KeyCode::KEY_S:
			case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			      if (!isE)keyMap[EventKeyboard::KeyCode::KEY_DOWN_ARROW] = true;
				break;
			case EventKeyboard::KeyCode::KEY_M:
			      keyMap[EventKeyboard::KeyCode::KEY_M] = true;
			      break;
			case EventKeyboard::KeyCode::KEY_F:
			      keyMap[EventKeyboard::KeyCode::KEY_F] = true;
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
			case EventKeyboard::KeyCode::KEY_M:
				keyMap[EventKeyboard::KeyCode::KEY_M] = false;
				break;
			default:
				break;
			}
		};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);//�Ѽ��������뵽�¼��ַ����У��������������󶨵Ķ�����������ȼ��趨Ϊ��������ȼ�

	//�����¼�������qԪ�ر���
	auto qListener = EventListenerKeyboard::create();
	//��������ʱ����
	qListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event)
	      {
		    if (keyCode == EventKeyboard::KeyCode::KEY_Q)
		    {
			  q();
		    }
	      };
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(qListener, this);//�Ѽ��������뵽�¼��ַ����У��������������󶨵Ķ�����������ȼ��趨Ϊ��������ȼ�

	//�����¼�������eԪ��ս�����
	auto eListener = EventListenerKeyboard::create();
	//��������ʱ����
	eListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event)
	      {
		    if (keyCode == EventKeyboard::KeyCode::KEY_E)
		    {
			  isE = true;
			  e();
		    }
	      };
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eListener, this);//�Ѽ��������뵽�¼��ַ����У��������������󶨵Ķ�����������ȼ��趨Ϊ��������ȼ�



	//����¼�����
	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseMove = [this](Event* event)
		{
			EventMouse* mousePosition = dynamic_cast<EventMouse*>(event);
			float x = mousePosition->getCursorX();
			float y = mousePosition->getCursorY();
			// ת��Ϊ��������
			worldPosition = Vec2(x, y);
			this->getPlayerOrientation(worldPosition);
			if (!isWeapon)this->weaponRotate(worldPosition);
		};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);//�Ѽ��������뵽�¼��ַ����У��������������󶨵Ķ�����������ȼ��趨Ϊ��������ȼ�

	//����¼������������ڸ��³���
	schedule(CC_CALLBACK_0(Player::updatePlayerOrientation, this), "mouse1");
	//����¼������������ڸ�����������
	schedule(CC_CALLBACK_1(Player::updateWeaponRotation, this), "mouse2");
	//�����¼������������ڸ���λ��
	schedule(CC_CALLBACK_1(Player::updatePlayerPosition, this), "keyboard");

	return true;
}

void Player::updatePlayerPosition(float dt)
{
      if (keyMap[EventKeyboard::KeyCode::KEY_M])
      {
	    // ȡ�����԰�������״̬
	    clearKeyBoardState();
	    MapScene* map = MapScene::create();
	    Director::getInstance()->pushScene(map);
	    // ���ݵ�ͼ���͵õ���λ�ã���������λ��
      }
	if (keyMap[EventKeyboard::KeyCode::KEY_LEFT_ARROW])//����������
	{
	      float Position = this->getPositionX() - speed;
	      // ����Ƿ�����ǽ��
	      for (int i = 1; i <= speed; ++i) {
		    Vec2 nextPosition = this->getPosition() + Vec2(-i, 0);
		    // ��ȡ����ͼ������
		    mapManager* map = (mapManager*) this->getParent()->getChildByName("mapManager");
		    // ��������ײ
		    if ( map->isCollision(nextPosition + Vec2(-22,-36))
			 || map->isCollision(nextPosition + Vec2(-22, 36))
			  || map->isCollision(nextPosition + Vec2(-22, -18))
			   || map->isCollision(nextPosition + Vec2(-22, 18))
			      || map->isCollision(nextPosition + Vec2(-22, 0)))
		    {
			  // �����ײ�ˣ��Ͳ����ƶ�
			  Position = nextPosition.x + 1;
			  break;
		    }
	      }
	      this->setPositionX(Position);//�����ƶ�10������
	}
	if (keyMap[EventKeyboard::KeyCode::KEY_RIGHT_ARROW])//����Ҽ�����
	{
	      float Position = this->getPositionX() + speed;
	      // ����Ƿ�����ǽ��
	      for (int i = 1; i <= speed; ++i) {
		    Vec2 nextPosition = this->getPosition() + Vec2(i, 0);
		    // ��ȡ����ͼ������
		    mapManager* map = (mapManager*) this->getParent()->getChildByName("mapManager");
		    // ��������ײ
		    if (map->isCollision(nextPosition + Vec2(22, -36))
			  || map->isCollision(nextPosition + Vec2(22, 36))
			  || map->isCollision(nextPosition + Vec2(22, -18))
			  || map->isCollision(nextPosition + Vec2(22, 18))
			  || map->isCollision(nextPosition + Vec2(22, 0)))
		    {
			  // �����ײ�ˣ��Ͳ����ƶ�
			  Position = nextPosition.x - 1;
			  break;
		    }
	      }
	      this->setPositionX(Position);//�����ƶ�10������
	}
	if (keyMap[EventKeyboard::KeyCode::KEY_UP_ARROW])//����ϼ�����
	{
	      float Position = this->getPositionY() + speed;
	      // ����Ƿ�����ǽ��
	      for (int i = 1; i <= speed; ++i) {
		    Vec2 nextPosition = this->getPosition() + Vec2(0, i);
		    // ��ȡ����ͼ������
		    mapManager* map = (mapManager*) this->getParent()->getChildByName("mapManager");
		    // ��������ײ
		    if (map->isCollision(nextPosition + Vec2(-22, 36))
			  || map->isCollision(nextPosition + Vec2(22, 36))
			  || map->isCollision(nextPosition + Vec2(-11, 36))
			  || map->isCollision(nextPosition + Vec2(11, 36))
			  || map->isCollision(nextPosition + Vec2(0, 36)))
		    {
			  // �����ײ�ˣ��Ͳ����ƶ�
			  Position = nextPosition.y - 1;
			  break;
		    }
	      }
	      this->setPositionY(Position);//�����ƶ�10������
	}
	if (keyMap[EventKeyboard::KeyCode::KEY_DOWN_ARROW])//����¼�����
	{
	      float Position = this->getPositionY() - speed;
	      // ����Ƿ�����ǽ��
	      for (int i = 1; i <= speed; ++i) {
		    Vec2 nextPosition = this->getPosition() + Vec2(0, -i);
		    // ��ȡ����ͼ������
		    mapManager* map = (mapManager*) this->getParent()->getChildByName("mapManager");
		    // ��������ײ
		    if (map->isCollision(nextPosition + Vec2(-22, -36))
			  || map->isCollision(nextPosition + Vec2(22, -36))
			  || map->isCollision(nextPosition + Vec2(-11, -36))
			  || map->isCollision(nextPosition + Vec2(11, -36))
			  || map->isCollision(nextPosition + Vec2(0, -36)) )
		    {
			  // �����ײ�ˣ��Ͳ����ƶ�
			  Position = nextPosition.y + 1;
			  break;
		    }
	      }
	      this->setPositionY(Position);//�����ƶ�10������
	}
	if (!keyMap[EventKeyboard::KeyCode::KEY_LEFT_ARROW] && !keyMap[EventKeyboard::KeyCode::KEY_RIGHT_ARROW] && !keyMap[EventKeyboard::KeyCode::KEY_UP_ARROW] && !keyMap[EventKeyboard::KeyCode::KEY_DOWN_ARROW])//���û�а�������
	{
	      if (this->mouseState[2]) // �������������
	      {
		    if (this->getNaming() == "swordPlayer")m_body->setSpriteFrame(sword_staticForwards.at(2));
		    if (this->getNaming() == "bowPlayer")m_body->setSpriteFrame(bow_staticForwards.at(2));
	      }
	      else if (this->mouseState[3]) // �������������
	      {
		    if (this->getNaming() == "swordPlayer")m_body->setSpriteFrame(sword_staticForwards.at(3));
		    if (this->getNaming() == "bowPlayer")m_body->setSpriteFrame(bow_staticForwards.at(3));
	      }
	      else if (this->mouseState[0]) // �������������
	      {
		    if (this->getNaming() == "swordPlayer")m_body->setSpriteFrame(sword_staticForwards.at(1));
		    if (this->getNaming() == "bowPlayer")m_body->setSpriteFrame(bow_staticForwards.at(1));
	      }
	      else if (this->mouseState[1])
	      {
		    if (this->getNaming() == "swordPlayer")m_body->setSpriteFrame(sword_staticForwards.at(0));
		    if (this->getNaming() == "bowPlayer")m_body->setSpriteFrame(bow_staticForwards.at(0));
	      }
	      else if (this->mouseState[0] == false && this->mouseState[1] == false && this->mouseState[2] == false && this->mouseState[3] == false)
	      {
		    if (this->getNaming() == "swordPlayer")m_body->setSpriteFrame(sword_staticForwards.at(0));
		    if (this->getNaming() == "bowPlayer")m_body->setSpriteFrame(bow_staticForwards.at(0));
	      }
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
	float distance = 200;
	
	// �ж���ײ
	if (cos(angle) >= 0 && sin(angle) >= 0){
	      for (int i = 1; i <= distance; ++ i) {
		    Vec2 nextPosition = this->getPosition() + Vec2(i * cos(angle), i * sin(angle));
		    // ��ȡ����ͼ������
		    mapManager * map = (mapManager*)this->getParent()->getChildByName("mapManager");
		    // ��������ײ
		    if (map->isCollision(nextPosition + Vec2(-40, 40)) // ��
			  || map->isCollision(nextPosition + Vec2(40, 40))
			  || map->isCollision(nextPosition + Vec2(-20, 40))
			  || map->isCollision(nextPosition + Vec2(20, 40))
			  || map->isCollision(nextPosition + Vec2(40, -40)) // ��
			  || map->isCollision(nextPosition + Vec2(40, 40))
			  || map->isCollision(nextPosition + Vec2(40, -20))
			  || map->isCollision(nextPosition + Vec2(40, 20))
			  )
		    {
			  // �����ײ�ˣ��Ͳ����ƶ�
			  distance = i - 1;
			  break;
		    }
	      }
	}
	else if (cos(angle) >= 0 && sin(angle) < 0) {
	      for (int i = 1; i <= distance; ++i) {
		    Vec2 nextPosition = this->getPosition() + Vec2(i * cos(angle), i * sin(angle));
		    // ��ȡ����ͼ������
		    mapManager * map = (mapManager*)this->getParent()->getChildByName("mapManager");
		    // ��������ײ
		    if (map->isCollision(nextPosition + Vec2(-40, -40)) // ��
			  || map->isCollision(nextPosition + Vec2(40, -40))
			  || map->isCollision(nextPosition + Vec2(-20, -40))
			  || map->isCollision(nextPosition + Vec2(20, -40))
			  || map->isCollision(nextPosition + Vec2(40, -40)) // ��
			  || map->isCollision(nextPosition + Vec2(40, 40))
			  || map->isCollision(nextPosition + Vec2(40, -20))
			  || map->isCollision(nextPosition + Vec2(40, 20))
			  )
		    {
			  // �����ײ�ˣ��Ͳ����ƶ�
			  distance = i - 1;
			  break;
		    }
	      }
	}
	else if (cos(angle) < 0 && sin(angle) >= 0){
	      for (int i = 1; i <= distance; ++i) {
		    Vec2 nextPosition = this->getPosition() + Vec2(i * cos(angle), i * sin(angle));
		    // ��ȡ����ͼ������
		    mapManager * map = (mapManager*)this->getParent()->getChildByName("mapManager");
		    // ��������ײ
		    if (map->isCollision(nextPosition + Vec2(-40, 40)) // ��
			  || map->isCollision(nextPosition + Vec2(40, 40))
			  || map->isCollision(nextPosition + Vec2(-20, 40))
			  || map->isCollision(nextPosition + Vec2(20, 40))
			  || map->isCollision(nextPosition + Vec2(-40, -40)) // ��
			  || map->isCollision(nextPosition + Vec2(-40, 40))
			  || map->isCollision(nextPosition + Vec2(-40, -20))
			  || map->isCollision(nextPosition + Vec2(-40, 20))
			  )
		    {
			  // �����ײ�ˣ��Ͳ����ƶ�
			  distance = i - 1;
			  break;
		    }
	      }
        }
	else {
	      for (int i = 1; i <= distance; ++i) {
		    Vec2 nextPosition = this->getPosition() + Vec2(i * cos(angle), i * sin(angle));
		    // ��ȡ����ͼ������
		    mapManager* map = (mapManager*)this->getParent()->getChildByName("mapManager");
		    // ��������ײ
		    if (map->isCollision(nextPosition + Vec2(-40, -40)) // ��
			  || map->isCollision(nextPosition + Vec2(40, -40))
			  || map->isCollision(nextPosition + Vec2(-20, -40))
			  || map->isCollision(nextPosition + Vec2(20, -40))
			  || map->isCollision(nextPosition + Vec2(-40, -40)) // ��
			  || map->isCollision(nextPosition + Vec2(-40, 40))
			  || map->isCollision(nextPosition + Vec2(-40, -20))
			  || map->isCollision(nextPosition + Vec2(-40, 20))
			  )
		    {
			  // �����ײ�ˣ��Ͳ����ƶ�
			  distance = i - 1;
			  break;
		    }
	      }
	}

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

void Player::swordOrdinaryAttack()
{
	//������Χ
	float attackDistance = 150.0f;
	//�����ٶ�
	float attackSpeed = 1200.0f;
	//��ת�ٶ�
	float rotateSpeed = 700.0f;
	//��ת�Ƕ�
	float rotateAngle1 = 45;
	float rotateAngle2 = 90;
	//��ýǶ�
	auto currentAngle = (m_weapon->getRotation() / 180) * PI;
	//��������
	Vec2 attackDirection = Vec2(sin(currentAngle), cos(currentAngle));
	//��ʼ����
	//�������ӿ�
	if (mouseState[1] || mouseState[3] || mouseState[0])
	{
		auto rotateUp = RotateBy::create(rotateAngle1 / rotateSpeed, -rotateAngle1);
		auto rotateDown = RotateBy::create(rotateAngle2 / rotateSpeed, rotateAngle2);
		m_weapon->runAction(Sequence::create(rotateUp, rotateDown, CallFunc::create([=] {isWeapon = false; }), nullptr));
	}
	else if (mouseState[2])
	{
		auto rotateUp = RotateBy::create(rotateAngle1 / rotateSpeed, rotateAngle1);
		auto rotateDown = RotateBy::create(rotateAngle2 / rotateSpeed, -rotateAngle2);
		m_weapon->runAction(Sequence::create(rotateUp, rotateDown, CallFunc::create([=] {isWeapon = false; }), nullptr));
	}
	//��ʱ
	auto delayTime = DelayTime::create(rotateAngle1 / rotateSpeed);

	//������Ч
	Effects* m_weapon_light = Effects::create();
	m_weapon_light->setAnchorPoint(Vec2(0.5, 0));
	//λ������������
	m_weapon_light->setPosition(this->getPosition());
	m_weapon_light->setRotation(this->weaponAngle);//�������ĽǶȵ������ĽǶ�
	//�󶨵�����
	this->getParent()->addChild(m_weapon_light, 1);
	m_weapon_light->EffectsAnimation(m_weapon_light->saber_normal, 0);

	float length = -150;
	m_weapon_light->setVisible(true);
	//���뵽��Ч����
	for (int i = 0; i < 20; i++)
	{
	      if (m_effect[i] == nullptr)
	      {
		    m_effect[i] = m_weapon_light;
		    //���������ֱ�ǩΪi
		    m_weapon_light->setTag(i);
		    //m_effect_count[i] = i;
		    //m_effect_index
		    for (int j = 0; j < 20; j++)
		    {
			  m_effect_index[i][j] = 1;
		    }
		    break;
	      }
	}

	//m_weapon_light->setPosition(Vec2(this->getPosition().x + length * sin((weaponAngle / 180) * PI), this->getPosition().y + length * cos((weaponAngle / 180) * PI)));
	auto fadeInAction = FadeIn::create(0.05);//����
	auto fadeOutAction = FadeOut::create(0.05);//����
	auto moveAction = MoveBy::create(attackDistance / attackSpeed, Vec2(attackDistance * sin((weaponAngle / 180) * PI), attackDistance * cos((weaponAngle / 180) * PI)));//�ƶ�����������ǵ�ǰλ�ã��յ��ǵ�ǰλ�ü���һ������
	//ִ������������ѽڵ��Ƴ������Ұ������Ӧλ�ã�ͨ��tag��ȡ���ÿ�
	auto removeSelf = CallFunc::create([=] {m_weapon_light->setVisible(false); m_effect[m_weapon_light->getTag()] = nullptr; });

	//ִ�ж���
	m_weapon_light->runAction(Sequence::create(fadeInAction, moveAction, fadeOutAction, removeSelf, nullptr));



}
void Player::bowOrdinaryAttack()
{
      //������Χ
      float attackDistance = 500.0f;
      //�����ٶ�
      float attackSpeed = 1500.0f;
      //��ת�ٶ�
      float rotateSpeed = 700.0f;
      //��ת�Ƕ�
      float rotateAngle1 = 45;
      float rotateAngle2 = 90;
      //��ýǶ�
      auto currentAngle = (m_weapon->getRotation() / 180) * PI;
      //��������
      Vec2 attackDirection = Vec2(sin(currentAngle), cos(currentAngle));
      //��ʼ����
      //�������ӿ�
      if (mouseState[1] || mouseState[3] || mouseState[0])
      {
	    auto rotateUp = RotateBy::create(rotateAngle1 / rotateSpeed, -rotateAngle1);
	    auto rotateDown = RotateBy::create(rotateAngle2 / rotateSpeed, rotateAngle2);
	    m_weapon->runAction(Sequence::create(rotateUp, rotateDown, CallFunc::create([=] {isWeapon = false; }), nullptr));
      }
      else if (mouseState[2])
      {
	    auto rotateUp = RotateBy::create(rotateAngle1 / rotateSpeed, rotateAngle1);
	    auto rotateDown = RotateBy::create(rotateAngle2 / rotateSpeed, -rotateAngle2);
	    m_weapon->runAction(Sequence::create(rotateUp, rotateDown, CallFunc::create([=] {isWeapon = false; }), nullptr));
      }
      //��ʱ
      auto delayTime = DelayTime::create(rotateAngle1 / rotateSpeed);

      //������Ч
      Effects* m_weapon_light = Effects::create();
      m_weapon_light->setAnchorPoint(Vec2(0.5, 0));
      //λ������������
      m_weapon_light->setPosition(this->getPosition());
      m_weapon_light->setRotation(this->weaponAngle);//�������ĽǶȵ������ĽǶ�
      //�󶨵�����
      this->getParent()->addChild(m_weapon_light, 1);
      m_weapon_light->EffectsAnimation(m_weapon_light->bow_normal, 0);

      //�������ƶ�
      auto fadeInAction = FadeIn::create(0.05);//����
      auto fadeOutAction = FadeOut::create(0.05);//����
      auto moveAction = MoveBy::create(attackDistance / attackSpeed, Vec2(attackDistance * sin((weaponAngle / 180) * PI), attackDistance * cos((weaponAngle / 180) * PI)));//�ƶ�����������ǵ�ǰλ�ã��յ��ǵ�ǰλ�ü���һ������
      //ִ������������ѽڵ��Ƴ������Ұ������Ӧλ�ã�ͨ��tag��ȡ���ÿ�
      auto removeSelf = CallFunc::create([=] {m_weapon_light->setVisible(false); m_effect[m_weapon_light->getTag()] = nullptr; });
      m_weapon_light->runAction(Sequence::create(delayTime, fadeInAction, moveAction, fadeOutAction, removeSelf, nullptr));
}

void Player::e()
{
      if (this->getNaming() == "swordPlayer")
      {
	    //��̾���
	    float distance = 500;
	    //����ٶ�
	    float dodgeSpeed = 1000;
	    //��ýǶ�
	    auto currentAngle = (m_weapon->getRotation() / 180) * PI;
	    //��̷���
	    Vec2 dodgeDirection = Vec2(sin(currentAngle), cos(currentAngle));
	    float length = 0;
	    m_e->setVisible(true);
	    m_e->setPosition(Vec2(weaponPosition.x + length * sin((weaponAngle / 180) * PI), weaponPosition.y + length * cos((weaponAngle / 180) * PI)));
	auto fadeInAction = FadeIn::create(0.05);
	auto delayTime = DelayTime::create(distance / dodgeSpeed - 0.05);
	auto fadeOutAction = FadeOut::create(0.05);
	m_e->runAction(Sequence::create(fadeInAction, delayTime, fadeOutAction, CallFunc::create([=] {isE = false; }), nullptr));
	//��ʼ���
	this->runAction(Sequence::create(MoveBy::create(distance / dodgeSpeed, dodgeDirection * distance), nullptr));
}
      else if (this->getNaming() == "bowPlayer")
      {
	    isWeapon = true;
	    //������Χ
	    float attackDistance = 500.0f;
	    //�����ٶ�
	    float attackSpeed = 1500.0f;
	    //��ת�ٶ�
	    float rotateSpeed = 700.0f;
	    //��ת�Ƕ�
	    float rotateAngle1 = 45;
	    float rotateAngle2 = 90;
	    //��ýǶ�
	    auto currentAngle = (m_weapon->getRotation() / 180) * PI;
	    //��������
	    Vec2 attackDirection = Vec2(sin(currentAngle), cos(currentAngle));
	    //��ʼ����
	    //�������ӿ�
	    if (mouseState[1] || mouseState[3] || mouseState[0])
	    {
		  auto rotateUp = RotateBy::create(rotateAngle1 / rotateSpeed, -rotateAngle1);
		  auto rotateDown = RotateBy::create(rotateAngle2 / rotateSpeed, rotateAngle2);
		  m_weapon->runAction(Sequence::create(rotateUp, rotateDown, CallFunc::create([=] {isWeapon = false; }), nullptr));
	    }
	    else if (mouseState[2])
	    {
		  auto rotateUp = RotateBy::create(rotateAngle1 / rotateSpeed, rotateAngle1);
		  auto rotateDown = RotateBy::create(rotateAngle2 / rotateSpeed, -rotateAngle2);
		  m_weapon->runAction(Sequence::create(rotateUp, rotateDown, CallFunc::create([=] {isWeapon = false; }), nullptr));
	    }
	    //��ʱ
	    auto delayTime1 = DelayTime::create(rotateAngle1 / rotateSpeed);

	    //������Ч1
	    Effects* m_weapon_light1 = Effects::create();
	    m_weapon_light1->setAnchorPoint(Vec2(0.5, 0));
	    //λ������������
	    m_weapon_light1->setPosition(this->getPosition());
	    m_weapon_light1->setRotation(this->weaponAngle);//�������ĽǶȵ������ĽǶ�
	    //�󶨵�����
	    this->getParent()->addChild(m_weapon_light1, 1);
	    m_weapon_light1->EffectsAnimation(m_weapon_light1->bow_normal, 0);

	    //�������ƶ�
	    auto fadeInAction = FadeIn::create(0.05);//����
	    auto fadeOutAction = FadeOut::create(0.05);//����
	    auto moveAction = MoveBy::create(attackDistance / attackSpeed, Vec2(attackDistance * sin((weaponAngle / 180) * PI), attackDistance * cos((weaponAngle / 180) * PI)));//�ƶ�����������ǵ�ǰλ�ã��յ��ǵ�ǰλ�ü���һ������
	    //ִ������������ѽڵ��Ƴ������Ұ������Ӧλ�ã�ͨ��tag��ȡ���ÿ�
	    auto removeSelf1 = CallFunc::create([=] {m_weapon_light1->setVisible(false); m_effect[m_weapon_light1->getTag()] = nullptr; });
	    m_weapon_light1->runAction(Sequence::create(delayTime1, fadeInAction, moveAction, fadeOutAction, nullptr));
	    auto delayTime2 = DelayTime::create((rotateAngle1 / rotateSpeed) * 4);
	    //������Ч2
	    Effects* m_weapon_light2 = Effects::create();
	    m_weapon_light2->setAnchorPoint(Vec2(0.5, 0));
	    //λ������������
	    m_weapon_light2->setPosition(this->getPosition());
	    m_weapon_light2->setRotation(this->weaponAngle);//�������ĽǶȵ������ĽǶ�
	    //�󶨵�����
	    this->getParent()->addChild(m_weapon_light2, 1);
	    m_weapon_light2->EffectsAnimation(m_weapon_light2->bow_normal, 0);
	    //ִ������������ѽڵ��Ƴ������Ұ������Ӧλ�ã�ͨ��tag��ȡ���ÿ�
	    auto removeSelf2 = CallFunc::create([=] {m_weapon_light2->setVisible(false); m_effect[m_weapon_light2->getTag()] = nullptr; });
	    m_weapon_light2->runAction(Sequence::create(delayTime2, fadeInAction, moveAction, fadeOutAction, nullptr));

	    auto delayTime3 = DelayTime::create((rotateAngle1 / rotateSpeed) * 8);
	    //������Ч3
	    Effects* m_weapon_light3 = Effects::create();
	    m_weapon_light3->setAnchorPoint(Vec2(0.5, 0));
	    //λ������������
	    m_weapon_light3->setPosition(this->getPosition());
	    m_weapon_light3->setRotation(this->weaponAngle);//�������ĽǶȵ������ĽǶ�
	    //�󶨵�����
	    this->getParent()->addChild(m_weapon_light3, 1);
	    m_weapon_light3->EffectsAnimation(m_weapon_light3->bow_normal, 0);
	    //ִ������������ѽڵ��Ƴ������Ұ������Ӧλ�ã�ͨ��tag��ȡ���ÿ�
	    auto removeSelf3 = CallFunc::create([=] {m_weapon_light3->setVisible(false); m_effect[m_weapon_light2->getTag()] = nullptr; });
	    m_weapon_light3->runAction(Sequence::create(delayTime3, fadeInAction, moveAction, fadeOutAction, removeSelf3, CallFunc::create([=] {isE = false; }), nullptr));
	    isE = false;
      }
}

void Player::q()
{
      if (this->getNaming() == "swordPlayer")
      {
	    //������Ч
	    Effects* qEffect = Effects::create();
	    //λ������������
	    qEffect->setPosition(this->getPosition());
	    //�󶨵�����
	    this->getParent()->addChild(qEffect, -1);
	    qEffect->EffectsAnimation(qEffect->q, 0);
      }
      else if (this->getNaming() == "bowPlayer")
      {
	    isWeapon = true;
	    //��ת�ٶ�
	    float rotateSpeed = 700.0f;
	    //��ת�Ƕ�
	    float rotateAngle1 = 45;
	    float rotateAngle2 = 90;
	    //��ýǶ�
	    auto currentAngle = (m_weapon->getRotation() / 180) * PI;
	    //��������
	    Vec2 attackDirection = Vec2(sin(currentAngle), cos(currentAngle));
	    //��ʼ����
	    //�������ӿ�
	    if (mouseState[1] || mouseState[3] || mouseState[0])
	    {
		  auto rotateUp = RotateBy::create(rotateAngle1 / rotateSpeed, -rotateAngle1);
		  auto rotateDown = RotateBy::create(rotateAngle2 / rotateSpeed, rotateAngle2);
		  m_weapon->runAction(Sequence::create(rotateUp, rotateDown, CallFunc::create([=] {isWeapon = false; }), nullptr));
	    }
	    else if (mouseState[2])
	    {
		  auto rotateUp = RotateBy::create(rotateAngle1 / rotateSpeed, rotateAngle1);
		  auto rotateDown = RotateBy::create(rotateAngle2 / rotateSpeed, -rotateAngle2);
		  m_weapon->runAction(Sequence::create(rotateUp, rotateDown, CallFunc::create([=] {isWeapon = false; }), nullptr));
	    }
	    //�����Ļ�ߴ�
	    auto visibleSize = Director::getInstance()->getVisibleSize();
	    //������Ч1
	    Effects* m_weapon_light1 = Effects::create();
	    m_weapon_light1->setAnchorPoint(Vec2(0.5, 0));
	    //λ�������λ�����Ϸ�
	    Vec2 effectPosition = worldPosition + this->myCamera->getCameraPostionChange()
		  - Vec2(visibleSize.width / 2, visibleSize.height / 2) + Vec2(0, 75);
	    m_weapon_light1->setPosition(effectPosition);
	    //�󶨵�����
	    this->getParent()->addChild(m_weapon_light1, 1);
	    m_weapon_light1->EffectsAnimation(m_weapon_light1->q_bow, 0);

      }
}

void Player::weaponRotate(Vec2 position)
{
	//�����Ļ�ߴ�
	auto visibleSize = Director::getInstance()->getVisibleSize();
	//�����������������Ļ������
	Vec2 mouseWorldPosition = position;
	//�����������������
	Vec2 spriteWorldPosition = this->getPosition();
	auto temp = this->myCamera->getCameraPostionChange();
	spriteWorldPosition = spriteWorldPosition - this->myCamera->getCameraPostionChange()
		+ Vec2(visibleSize.width / 2, visibleSize.height / 2);
	//����
	Vec2 mouseLocalPosition = Vec2(mouseWorldPosition.x - spriteWorldPosition.x, mouseWorldPosition.y - spriteWorldPosition.y);

	//����Ƕ�
	float angle = atan2(mouseLocalPosition.x, mouseLocalPosition.y);
	this->weaponAngle = (angle / PI) * 180;
}

void Player::updateWeaponRotation(float dt)
{
	if (isWeapon)
	{
	      log("isWeapon");
	}
	if (isE)
	{
	      log("isE");
	}
	if (!isWeapon && !isE)
	{
		m_weapon->setRotation(this->weaponAngle);
	}
	if (!isE)
	{
	      m_e->setRotation(this->weaponAngle);
	}
}


void Player::updatePlayerOrientation()
{
	if (this->mouseState[0])
	{
		weaponPosition = Vec2(m_body->getPosition().x - 2.25, m_body->getPosition().y + m_weapon->getContentSize().height / (1.25));
		if (this->getNaming() == "swordPlayer")
		{
		      moveAnimation(sword_walk_back, 4);
		}
		else if (this->getNaming() == "bowPlayer")
		{
		      moveAnimation(bow_walk_back, 4);
		};
	}
	else if (this->mouseState[1])
	{
	      weaponPosition = Vec2(m_body->getPosition().x - 2.25, m_body->getPosition().y - m_weapon->getContentSize().height / (1.75));
	      if (this->getNaming() == "swordPlayer")
	      {
		    moveAnimation(sword_walk_front, 3);
	      }
	      else if (this->getNaming() == "bowPlayer")
	      {
		    moveAnimation(bow_walk_front, 3);
	      };
	}
	else if (this->mouseState[2])
	{
		weaponPosition = Vec2(m_body->getPosition().x - m_weapon->getContentSize().width / (1.85), m_body->getPosition().y);
		if (this->getNaming() == "swordPlayer")
		{
		      moveAnimation(sword_walk_left, 1);
		}
		else if (this->getNaming() == "bowPlayer")
		{
		      moveAnimation(bow_walk_left, 1);
		};
	}
	else if (this->mouseState[3])
	{
		weaponPosition = Vec2(m_body->getPosition().x + m_weapon->getContentSize().width / (1.85), m_body->getPosition().y);
		if (this->getNaming() == "swordPlayer")
		{
		      moveAnimation(sword_walk_right, 2);
		}
		else if (this->getNaming() == "bowPlayer")
		{
		      moveAnimation(bow_walk_right, 2);
		};
	}
	if (!isWeapon && !isE)
	{
		m_weapon->setPosition(weaponPosition);
	}
}


void Player::update(float dt)
{
	//ÿ֡��0.016�룩�ָ�0.01������
	if (m_stamina < 100)
	{
		m_stamina += 0.15;
	}
	else if (m_stamina > 100)
	{
		m_stamina = 100;
	}
	//����Ԫ�ظ���Ч������ʱ�����
	for (int i = 0; i < 8; i++)
	{
		if (m_element[i] > 0)
		{
			m_element[i] -= 0.016;
		}
		//�������2������Ԫ�ظ���ͼ��û�����������͸����
		if (m_element[i] < 2&& m_element[i]>0)
		{
			//�����Opaqity�Ƿ�Ϊ255������Ǿ������͸����
			for (int j = 0; j < 2; j++)
			{
				if (m_element_sprite[j]->isVisible() && m_element_sprite_type[j] == i&& m_element_sprite[j]->getOpacity() == 255)
				{
					m_element_sprite[j]->setOpacity(78);
				}
			}
		}
		if (m_element[i] < 0)
		{
			m_element[i] = 0;
			
		}
		if (m_element[i] == 0)
		{
			//Ԫ�ظ���ͼ����ʧ
			for (int j = 0; j < 2; j++)
			{
				if (m_element_sprite[j]->isVisible() && m_element_sprite_type[j] == i)
				{
					//͸���Ȼָ�
					m_element_sprite[j]->setOpacity(255);
					m_element_sprite[j]->setVisible(false);
					//��ʧ���⣬�������û��ʧ��Ԫ�ظ��ţ���������ʾ�����Ϸ�
					if (m_element_sprite[1-j]->isVisible())
					{
						m_element_sprite[1 - j]->setPosition(Vec2(0, m_body->getContentSize().height));
					}
				}
			}
			
			
		}
	}
	//������ȴʱ�����
	if (m_E_CD > 0)
	{
		m_E_CD -= 0.016;
	}
	else if (m_E_CD < 0)
	{
		m_E_CD = 0;
	}
	if (m_Q_CD > 0)
	{
		m_Q_CD -= 0.016;
	}
	else if (m_Q_CD < 0)
	{
		m_Q_CD = 0;
	}


	//��״̬���м��
	for (int i = 0; i < 99; i++)
	{
	      if (m_statement[i].name != "")
	      {
		    m_statement[i].time -= 0.016;
		    m_statement_time[i] += 0.016;
		    //ÿһ����״̬
		    if (m_statement_time[i] > 1)
		    {
			  m_statement_time[i] = 0;
			  //����ие�״̬
			  if (m_statement[i].name == "shock" && m_statement[i].time > 0)
			  {
				//�����е�Ч��
				effectTrigger("shock");
			  }
			  else if (m_statement[i].name != "" && m_statement[i].time <= 0)
			  {
				//����ǳ���������״̬��ʧ
				if (m_statement[i].name == "def_down")
				{
				      m_superconductivity = 0;
				}


				m_statement[i].name = "";
				m_statement[i].time = 0;
				//�������е�״̬��ǰ��
				for (int j = i; j < 99; j++)
				{
				      if (m_statement[j + 1].name != "")
				      {
					    m_statement[j] = m_statement[j + 1];
					    m_statement[j + 1].name = "";
					    m_statement[j + 1].time = 0;
				      }
				      else
				      {
					    break;
				      }
				}

			  }
		    }
	      }
	      else
	      {
		    break;
	      }



	}

	mapManager* map = (mapManager*)this->getParent()->getChildByName("mapManager");
	int BackGroundGid = map->getBackgroundTag(this->getPosition());
	if (BackGroundGid == 1)
	      this->speed = 2.5;
	else if (BackGroundGid == 2)
	{
	      this->speed = 1;
	      m_stamina -= 0.2;
	      m_stamina  = m_stamina < 0 ? 0 : m_stamina;
	}
	else
	      this->speed = 5;


}

void Player::attackEnemy()
{
      //ȥ����HelloWorldScene�������е��ˣ�����оͽ���AttackHit��⿴����û�д򵽡����˵�tag��Enemy
      auto scene = this->getParent();
      //���ҳ�����tagΪEnemy�Ķ�����name��ǩ����
      //���û�ҵ�
      if (scene->getChildByName("Enemy") == nullptr)
      {
	    return;
      }
      else
      {
	    auto enemy = scene->getChildByName("Enemy");
	    //AttackHit(enemy);

      }


}