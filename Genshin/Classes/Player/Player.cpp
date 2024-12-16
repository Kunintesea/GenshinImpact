#include "Player.h"

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
	//��������
	m_body = Sprite::create("Me/Saber/Walk/front.png");
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
	


	// �����ٶ�
	speed = 5;
	angleSpeed = 5;


	m_head = Sprite::create("me/head.png");
	//��С5��
	m_head->setScale(0.2);
	//����λ�õ������ұ�
	m_head->setPosition(Vec2(m_body->getContentSize().width / 2, 0));
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
			if (mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_RIGHT)
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
			if (mouseAttack->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT && !isWeapon)
			{
				isWeapon = true;
				isflying = true;
				this->ordinaryAttack();
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
			EventMouse* mousePosition = dynamic_cast<EventMouse*>(event);
			float x = mousePosition->getCursorX();
			float y = mousePosition->getCursorY();
			// ת��Ϊ��������
			Vec2 worldPosition = Vec2(x, y);
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
	if (keyMap[EventKeyboard::KeyCode::KEY_LEFT_ARROW])//����������
	{
		float Position = this->getPositionX() - speed;
		// ����Ƿ�����ǽ��
		for (int i = 1; i <= speed; ++i) {
			Vec2 nextPosition = this->getPosition() + Vec2(-i, 0);
			// ��ȡ����ͼ������
			mapManager* map = (mapManager*)this->getParent()->getChildByName("mapManager");
			// ��������ײ
			if (map->isCollision(nextPosition + Vec2(-40, -40))
				|| map->isCollision(nextPosition + Vec2(-40, 40))
				|| map->isCollision(nextPosition + Vec2(-40, -20))
				|| map->isCollision(nextPosition + Vec2(-40, 20)))
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
			mapManager* map = (mapManager*)this->getParent()->getChildByName("mapManager");
			// ��������ײ
			if (map->isCollision(nextPosition + Vec2(40, -40))
				|| map->isCollision(nextPosition + Vec2(40, 40))
				|| map->isCollision(nextPosition + Vec2(40, -20))
				|| map->isCollision(nextPosition + Vec2(40, 20)))
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
			mapManager* map = (mapManager*)this->getParent()->getChildByName("mapManager");
			// ��������ײ
			if (map->isCollision(nextPosition + Vec2(-40, 40))
				|| map->isCollision(nextPosition + Vec2(40, 40))
				|| map->isCollision(nextPosition + Vec2(-20, 40))
				|| map->isCollision(nextPosition + Vec2(20, 40)))
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
			mapManager* map = (mapManager*)this->getParent()->getChildByName("mapManager");
			// ��������ײ
			if (map->isCollision(nextPosition + Vec2(-40, -40))
				|| map->isCollision(nextPosition + Vec2(40, -40))
				|| map->isCollision(nextPosition + Vec2(-20, -40))
				|| map->isCollision(nextPosition + Vec2(20, -40)))
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
			m_body->setSpriteFrame(staticForwards.at(2));
		else if (this->mouseState[3]) // �������������
			m_body->setSpriteFrame(staticForwards.at(3));
		else if (this->mouseState[0]) // �������������
			m_body->setSpriteFrame(staticForwards.at(1));
		else if (this->mouseState[1])
			m_body->setSpriteFrame(staticForwards.at(0));
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

	// �ж���ײ
	if (cos(angle) >= 0 && sin(angle) >= 0) {
		for (int i = 1; i <= distance; ++i) {
			Vec2 nextPosition = this->getPosition() + Vec2(i * cos(angle), i * sin(angle));
			// ��ȡ����ͼ������
			mapManager* map = (mapManager*)this->getParent()->getChildByName("mapManager");
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
			mapManager* map = (mapManager*)this->getParent()->getChildByName("mapManager");
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
	else if (cos(angle) < 0 && sin(angle) >= 0) {
		for (int i = 1; i <= distance; ++i) {
			Vec2 nextPosition = this->getPosition() + Vec2(i * cos(angle), i * sin(angle));
			// ��ȡ����ͼ������
			mapManager* map = (mapManager*)this->getParent()->getChildByName("mapManager");
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

void Player::ordinaryAttack()
{

	//������Ч
	Effects* m_weapon_light = Effects::create();
	m_weapon_light->setAnchorPoint(Vec2(0.5, 0));
	//λ������������
	m_weapon_light->setPosition(this->getPosition());
	//�󶨵�����
	this->getParent()->addChild(m_weapon_light);
	m_weapon_light->EffectsAnimation(m_weapon_light->saber_normal, 0);


	m_weapon_light->setRotation(this->weaponAngle);//�������ĽǶȵ������ĽǶ�
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
	//�������ƶ�
	float length = -150;
	m_weapon_light->setVisible(true);
	//m_weapon_light->setPosition(Vec2(this->getPosition().x + length * sin((weaponAngle / 180) * PI), this->getPosition().y + length * cos((weaponAngle / 180) * PI)));
	auto fadeInAction = FadeIn::create(0.05);//����
	auto fadeOutAction = FadeOut::create(0.05);//����
	auto moveAction = MoveBy::create(attackDistance / attackSpeed, Vec2(attackDistance * sin((weaponAngle / 180) * PI), attackDistance * cos((weaponAngle / 180) * PI)));//�ƶ�����������ǵ�ǰλ�ã��յ��ǵ�ǰλ�ü���һ������
	m_weapon_light->runAction(Sequence::create(delayTime, fadeInAction, moveAction, fadeOutAction, CallFunc::create([=] {isflying = false; }), nullptr));
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
	if (!isWeapon)
	{
		m_weapon->setRotation(this->weaponAngle);//�������ĽǶȵ������ĽǶ�
		//	m_weapon_light->setRotation(this->weaponAngle);//�������ĽǶȵ������ĽǶ�
	}
}


void Player::updatePlayerOrientation()
{
	if (this->mouseState[0])
	{
		weaponPosition = Vec2(m_body->getPosition().x - 2.25, m_body->getPosition().y + m_weapon->getContentSize().height / (1.25));
		moveAnimation(walk_back, 4);
	}
	else if (this->mouseState[1])
	{
		weaponPosition = Vec2(m_body->getPosition().x - 2.25, m_body->getPosition().y - m_weapon->getContentSize().height / (1.75));
		moveAnimation(walk_front, 3);
	}
	else if (this->mouseState[2])
	{
		weaponPosition = Vec2(m_body->getPosition().x - m_weapon->getContentSize().width / (1.85), m_body->getPosition().y);
		moveAnimation(walk_left, 1);
	}
	else if (this->mouseState[3])
	{
		weaponPosition = Vec2(m_body->getPosition().x + m_weapon->getContentSize().width / (1.85), m_body->getPosition().y);
		moveAnimation(walk_right, 2);
	}
	if (!isWeapon)
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
						m_element_sprite[1 - j]->setPosition(Vec2(0, m_body->getContentSize().height / 3));
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
							m_statement[j+1].name = "";
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