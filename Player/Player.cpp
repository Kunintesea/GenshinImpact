#include "Player.h"
#include<iostream>

/*
���ڶ�������m_body�ϵ�tag��������getNumberOfRunningActionsByTag��ȡ��
1������
2������
3������
4������
*/
//�˺�����ʽ��ʵ���˺�=�˺�ֵ-����ֵ*�˺�ֵ�������ﴦ������״ֱ̬�ӷ���0
void Player::hurt(int damage, int damge_type)
{
	if (isDodge)
	{
		log("Dodge!");
		return;
	}
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
				//��ʾ����Ч��
				for (int i = 0; i < 20; i++)
				{
					if (!m_element_label[i]->isVisible())
					{
						m_element_label[i]->setColor(Color3B(249, 85, 9));
						m_element_label[i]->setPosition(Vec2(this->getPositionX() + rand() % 50, this->getPositionY() + rand() % 50));
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






				m_damage_label[i]->setPosition(Vec2(this->getPositionX() - m_body->getContentSize().width / 2 + rand() % 50, this->getPositionY() - m_body->getContentSize().height / 2 + rand() % 50));//rand()��ʹ�÷�����rand()%n����ʾ����һ��0��n-1�������
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
	m_body = Sprite::create("Me/front.png");
	//���������ӵ��ڵ�
	this->addChild(m_body);



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

	//�Կ�Ѫ�ļ���
	auto eventLLL = EventListenerKeyboard::create();
	eventLLL->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event)
		{
			switch (keyCode)
			{
			case EventKeyboard::KeyCode::KEY_O:
				hurt(1, Fire);
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
				auto dodgeAction = Sequence::create(MoveBy::create(0.5, Vec2(0, 100)), MoveBy::create(0.5, Vec2(0, -100)), CallFunc::create([=] {isDodge = false; }), nullptr);
				this->runAction(dodgeAction);
			}
		};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(DodgeListener, this);//�Ѽ��������뵽�¼��ַ����У��������������󶨵Ķ�����������ȼ��趨Ϊ��������ȼ�



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

bool Player::testCol(Sprite* other)
{
	//��ȡ��Ҿ����Ŀ�꾫��İ�Χ��
	Rect playerRect = this->getBoundingBox();
	Rect targetRect = other->getBoundingBox();


	// �����������İ�Χ���Ƿ��ཻ
	if (playerRect.intersectsRect(targetRect))
	{

		CCLOG("Collision detected!"); 
		// ִ����ײ����߼�
		this->hurt(1, 3);
		return true;
	}

	return false;
}////������ײ���

bool Player::testCol(TMXTiledMap* map, TMXLayer* layer) {
	if (!layer||!map) {
		return false;
	}
	
	auto playerPosition = this->getPosition();
	int PositionX = playerPosition.x;
	int PositionY = playerPosition.y;

	int TileWide = layer->getMapTileSize().width;
	int TileHeight = layer->getMapTileSize().height;

	int playerTileX = playerPosition.x / layer->getMapTileSize().width;
	int playerTileY = playerPosition.y / layer->getMapTileSize().height;

	int mapHeight = map->getMapSize().height;
	int mapWidth = map->getMapSize().width;
	
	log("PositionX:%d", PositionX);
	log("PositionY:%d", PositionY);

	log("TileWide:%d", TileWide);
	log("TileWide:%d", TileHeight);

	log("playerTileX:%d", playerTileX);
	log("playerTileY:%d", playerTileY);

	log("mapHeight:%d", mapHeight);
	log("mapWidth:%d", mapWidth);
	
	int x = playerTileX;
	int y = mapHeight - playerTileY ;//

	/*log("x:%d", x);
	log("y:%d", y);*/

	//int gid = layer->getTileGIDAt(Vec2(playerTileX, playerTileY));
	int gid = layer->getTileGIDAt(Vec2(x, y));

	int gid_up = layer->getTileGIDAt(Vec2(x, y-1));
	int gid_down = layer->getTileGIDAt(Vec2(x, y+1));
	int gid_left = layer->getTileGIDAt(Vec2(x-1, y));
	int gid_right = layer->getTileGIDAt(Vec2(x+1, y));

	if (gid_up != 0)
	{
		log("noup!!!");
		return true;
	}
	if (gid_down != 0)
	{
		log("nodown!!!");
		return true;
	}
	if (gid_left != 0)
	{
		log("noleft!!!");
		return true;
	}
	if (gid_right != 0)
	{
		log("noright!!!");
		return true;
	}

	return false;


}//��ͼ��ײ���

bool Player::testCol_up(TMXTiledMap* map, TMXLayer* layer)
{
	if (!layer || !map) {
		return false;
	}

	auto playerPosition = this->getPosition();

	int playerTileX = playerPosition.x / layer->getMapTileSize().width;
	int playerTileY = playerPosition.y / layer->getMapTileSize().height;

	int mapHeight = map->getMapSize().height;

	int x = playerTileX;
	int y = mapHeight - playerTileY;

	int gid_up = layer->getTileGIDAt(Vec2(x, y - 1));
	if (gid_up != 0)
	{
		log("noup!!!");
		return true;
	}

	return false;
}
bool Player::testCol_down(TMXTiledMap* map, TMXLayer* layer)
{
	if (!layer || !map) {
		return false;
	}

	auto playerPosition = this->getPosition();

	int playerTileX = playerPosition.x / layer->getMapTileSize().width;
	int playerTileY = playerPosition.y / layer->getMapTileSize().height;

	int mapHeight = map->getMapSize().height;

	int x = playerTileX;
	int y = mapHeight - playerTileY;

	int gid_up = layer->getTileGIDAt(Vec2(x, y + 1));
	if (gid_up != 0)
	{
		log("nodown!!!");
		return true;
	}

	return false;
}
bool Player::testCol_left(TMXTiledMap* map, TMXLayer* layer)
{
	if (!layer || !map) {
		return false;
	}

	auto playerPosition = this->getPosition();

	int playerTileX = playerPosition.x / layer->getMapTileSize().width;
	int playerTileY = playerPosition.y / layer->getMapTileSize().height;

	int mapHeight = map->getMapSize().height;

	int x = playerTileX;
	int y = mapHeight - playerTileY;

	int gid_up = layer->getTileGIDAt(Vec2(x - 1, y));
	if (gid_up != 0)
	{
		log("noleft!!!");
		return true;
	}

	return false;
}
bool Player::testCol_right(TMXTiledMap* map, TMXLayer* layer)
{
	if (!layer || !map) {
		return false;
	}

	auto playerPosition = this->getPosition();

	int playerTileX = playerPosition.x / layer->getMapTileSize().width;
	int playerTileY = playerPosition.y / layer->getMapTileSize().height;

	int mapHeight = map->getMapSize().height;

	int x = playerTileX;
	int y = mapHeight - playerTileY;

	int gid_up = layer->getTileGIDAt(Vec2(x + 1, y));
	if (gid_up != 0)
	{
		log("noright!!!");
		return true;
	}

	return false;
}
