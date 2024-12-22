#include "Player.h"
#include "Enemy.h"
#include "HelloWorldScene.h"
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



	//��������
	m_weapon = Sprite::create("Me/Saber/Weapon/sword.png");
	m_weapon->setAnchorPoint(Vec2(0.5, 0));
	if (!isWeapon)
	{
		weaponPosition = Vec2(m_body->getPosition().x + m_weapon->getContentSize().width / (1.25), m_body->getPosition().y);
		m_weapon->setPosition(weaponPosition);
	}
	this->addChild(m_weapon);

	//��ʼ����ť����
	for (int i = 0; i < 6; i++)
	{
	      if (i == 0 || i == 2)
	      {
		    swordButtons[i].button = ui::Button::create("Me/Saber/change/selectedBoard.png",
			  "Me/Saber/change/emptyBoard.png",
			  "Me/Saber/change/selectedBoard.png");
		    bowButtons[i].button = ui::Button::create("Me/Saber/change/selectedBoard.png",
			  "Me/Saber/change/emptyBoard.png",
			  "Me/Saber/change/selectedBoard.png");
		    swordButtons[i].isEmpty = false;
		    bowButtons[i].isEmpty = false;
		    swordButtons[i].isSelected = true;
		    bowButtons[i].isSelected = true;
		    swordButtons[i].button->setEnabled(false);
		    bowButtons[i].button->setEnabled(false);
	      }
	      else
	      {
		    swordButtons[i].button = ui::Button::create("Me/Saber/change/emptyBoard.png",
			  "Me/Saber/change/selectedBoard.png",
			  "Me/Saber/change/emptyBoard.png");
		    bowButtons[i].button = ui::Button::create("Me/Saber/change/emptyBoard.png",
			  "Me/Saber/change/selectedBoard.png",
			  "Me/Saber/change/emptyBoard.png");
		    swordButtons[i].isEmpty = true;
		    bowButtons[i].isEmpty = true;
		    swordButtons[i].isSelected = false;
		    bowButtons[i].isSelected = false;
		    swordButtons[i].button->setEnabled(false);
		    bowButtons[i].button->setEnabled(false);
	      }

	      switch (i)
	      {
	      case 0:
		    swordButtons[i].item = Sprite::create("Me/Saber/change/swordPlayer1.png");
		    swordButtons[i].item->setVisible(false);
		    this->addChild(swordButtons[i].item, 100);
		    bowButtons[i].item = Sprite::create("Me/Saber/change/bowPlayer1.png");
		    bowButtons[i].item->setVisible(false);
		    this->addChild(bowButtons[i].item, 100);
		    break;
	      case 1:
		    swordButtons[i].item = Sprite::create("Me/Saber/change/swordPlayer2.png");
		    swordButtons[i].item->setVisible(false);
		    this->addChild(swordButtons[i].item, 100);
		    bowButtons[i].item = Sprite::create("Me/Saber/change/bowPlayer2.png");
		    bowButtons[i].item->setVisible(false);
		    this->addChild(bowButtons[i].item, 100);
		    break;
	      case 2:
		    swordButtons[i].item = Sprite::create("Me/Saber/change/sword1.png");
		    swordButtons[i].item->setVisible(false);
		    this->addChild(swordButtons[i].item, 100);
		    bowButtons[i].item = Sprite::create("Me/Saber/change/bow1.png");
		    bowButtons[i].item->setVisible(false);
		    this->addChild(bowButtons[i].item, 100);
		    break;
	      case 3:
		    swordButtons[i].item = Sprite::create("Me/Saber/change/sword2.png");
		    swordButtons[i].item->setVisible(false);
		    this->addChild(swordButtons[i].item, 100);
		    bowButtons[i].item = Sprite::create("Me/Saber/change/bow2.png");
		    bowButtons[i].item->setVisible(false);
		    this->addChild(bowButtons[i].item, 100);
		    break;
	      case 4:
		    swordButtons[i].item = Sprite::create("Me/Saber/change/bug.png");
		    swordButtons[i].item->setVisible(false);
		    this->addChild(swordButtons[i].item, 100);
		    bowButtons[i].item = Sprite::create("Me/Saber/change/bug.png");
		    bowButtons[i].item->setVisible(false);
		    this->addChild(bowButtons[i].item, 100);
		    break;
	      case 5:
		    swordButtons[i].item = Sprite::create("Me/Saber/change/win.png");
		    swordButtons[i].item->setVisible(false);
		    this->addChild(swordButtons[i].item, 100);
		    bowButtons[i].item = Sprite::create("Me/Saber/change/win.png");
		    bowButtons[i].item->setVisible(false);
		    this->addChild(bowButtons[i].item, 100);
		    break;
	      default:
		    break;
	      }

	      swordButtons[i].button->setVisible(false);
	      bowButtons[i].button->setVisible(false);
	      swordButtons[i].button->setTag(i);
	      bowButtons[i].button->setTag(i);
	      swordButtons[i].item->setPosition(this->getPosition() + Vec2(300, 300) + Vec2(256 * (i % 2), -256 * (i / 2)));
	      bowButtons[i].item->setPosition(this->getPosition() + Vec2(300, 300) + Vec2(256 * (i % 2), -256 * (i / 2)));
	      swordButtons[i].button->setPosition(this->getPosition() + Vec2(300, 300) + Vec2(256 * (i % 2), -256 * (i / 2)));
	      bowButtons[i].button->setPosition(this->getPosition() + Vec2(300, 300) + Vec2(256 * (i % 2), -256 * (i / 2)));
	      swordButtons[i].button->addClickEventListener(CC_CALLBACK_1(Player::selectButton, this));
	      bowButtons[i].button->addClickEventListener(CC_CALLBACK_1(Player::selectButton, this));
	      this->addChild(swordButtons[i].button, 50);
	      this->addChild(bowButtons[i].button, 50);
	}

	//������ť
	for (int i = 0; i < 4; i++)
	{
	      upgrade[i] = ui::Button::create("Me/Saber/change/upgrade.png",
		    "Me/Saber/change/upgrade.png",
		    "Me/Saber/change/unabledUpgrade.png");
	      if (i == 0 || i == 2)
	      {
		    upgrade[i]->setEnabled(true);
	      }
	      else
	      {
		    upgrade[i]->setEnabled(false);
	      }
	      upgrade[i]->setVisible(false);
	      this->addChild(upgrade[i], 50);
	      upgrade[i]->setTag(i);
	      upgrade[i]->addClickEventListener(CC_CALLBACK_1(Player::upgradeEquipment, this));
	}
	upgrade[0]->setPosition(this->getPosition() + Vec2(300, 300) + Vec2(-163, 0));
	upgrade[1]->setPosition(this->getPosition() + Vec2(300, 300) + Vec2(420, 0));
	upgrade[2]->setPosition(this->getPosition() + Vec2(300, 300) + Vec2(-163, -256));
	upgrade[3]->setPosition(this->getPosition() + Vec2(300, 300) + Vec2(420, -256));

	//��ʾ�ȼ�
	for (int i = 0; i < 4; i++)
	{
	      upgradeSwordLevel[i].showLevel = Label::createWithTTF(std::to_string(upgradeSwordLevel[i].weaponLevel), "fonts/arial.ttf", 40);
	      upgradeSwordLevel[i].showLevel->setPosition(this->getPosition() + Vec2(300, 300) + Vec2(256 * (i % 2), -256 * (i / 2)) + Vec2(75, 0));
	      upgradeSwordLevel[i].showLevel->setVisible(false);
	      upgradeSwordLevel[i].showLevel->setTextColor(Color4B::BLACK);
	      upgradeBowLevel[i].showLevel = Label::createWithTTF(std::to_string(upgradeBowLevel[i].weaponLevel), "fonts/arial.ttf", 40);
	      upgradeBowLevel[i].showLevel->setPosition(this->getPosition() + Vec2(300, 300) + Vec2(256 * (i % 2), -256 * (i / 2)) + Vec2(75, 0));
	      upgradeBowLevel[i].showLevel->setVisible(false);
	      upgradeBowLevel[i].showLevel->setTextColor(Color4B::BLACK);
	      this->addChild(upgradeSwordLevel[i].showLevel, 200);
	      this->addChild(upgradeBowLevel[i].showLevel, 200);
	}
	bowButtons[3].isEmpty = false;
	swordButtons[3].isEmpty = true;
	bowButtons[3].isSelected = false;
	swordButtons[3].isSelected = false;
	// ���ض���
	// ��ֹ����֡
	Size bodySize = m_body->getContentSize();
	//"D:\Github_Document\GenshinImpact\Genshin\Resources\Me\Saber\Walk\walk_back2.png"
	SpriteFrame* sword1_front = SpriteFrame::create("Me/Saber/Walk/front1.png", Rect(0, 0, bodySize.width, bodySize.height));
	SpriteFrame* sword1_back = SpriteFrame::create("Me/Saber/Walk/back1.png", Rect(0, 0, bodySize.width, bodySize.height));
	SpriteFrame* sword1_left = SpriteFrame::create("Me/Saber/Walk/left1.png", Rect(0, 0, bodySize.width, bodySize.height));
	SpriteFrame* sword1_right = SpriteFrame::create("Me/Saber/Walk/right1.png", Rect(0, 0, bodySize.width, bodySize.height));
	//SpriteFrame* dead = SpriteFrame::create("Me/Saber/Walk/dead.png", Rect(0, 0, bodySize.width, bodySize.height));
	sword1_staticForwards.pushBack(sword1_front);
	sword1_staticForwards.pushBack(sword1_back);
	sword1_staticForwards.pushBack(sword1_left);
	sword1_staticForwards.pushBack(sword1_right);
	//staticForwards.pushBack(dead);
	SpriteFrame* bow1_front = SpriteFrame::create("Me/Saber/Walk/front2.png", Rect(0, 0, bodySize.width, bodySize.height));
	SpriteFrame* bow1_back = SpriteFrame::create("Me/Saber/Walk/back2.png", Rect(0, 0, bodySize.width, bodySize.height));
	SpriteFrame* bow1_left = SpriteFrame::create("Me/Saber/Walk/left2.png", Rect(0, 0, bodySize.width, bodySize.height));
	SpriteFrame* bow1_right = SpriteFrame::create("Me/Saber/Walk/right2.png", Rect(0, 0, bodySize.width, bodySize.height));
	//SpriteFrame* dead = SpriteFrame::create("Me/Saber/Walk/dead.png", Rect(0, 0, bodySize.width, bodySize.height));
	bow1_staticForwards.pushBack(bow1_front);
	bow1_staticForwards.pushBack(bow1_back);
	bow1_staticForwards.pushBack(bow1_left);
	bow1_staticForwards.pushBack(bow1_right);
	//staticForwards.pushBack(dead);

	//�˶�����֡
	SpriteFrame* sword1_walk_back1 = SpriteFrame::create("Me/Saber/Walk/back1_walk1.png", Rect(0, 0, bodySize.width, bodySize.height));
	SpriteFrame* sword1_walk_back2 = SpriteFrame::create("Me/Saber/Walk/back1_walk2.png", Rect(0, 0, bodySize.width, bodySize.height));
	sword1_walk_back.pushBack(sword1_walk_back1);
	sword1_walk_back.pushBack(sword1_walk_back2);
	SpriteFrame* sword1_walk_front1 = SpriteFrame::create("Me/Saber/Walk/front1_walk1.png", Rect(0, 0, bodySize.width, bodySize.height));
	SpriteFrame* sword1_walk_front2 = SpriteFrame::create("Me/Saber/Walk/front1_walk2.png", Rect(0, 0, bodySize.width, bodySize.height));
	sword1_walk_front.pushBack(sword1_walk_front1);
	sword1_walk_front.pushBack(sword1_walk_front2);
	SpriteFrame* sword1_walk_left1 = SpriteFrame::create("Me/Saber/Walk/left1_walk1.png", Rect(0, 0, bodySize.width, bodySize.height));
	SpriteFrame* sword1_walk_left2 = SpriteFrame::create("Me/Saber/Walk/left1_walk2.png", Rect(0, 0, bodySize.width, bodySize.height));
	sword1_walk_left.pushBack(sword1_walk_left1);
	sword1_walk_left.pushBack(sword1_walk_left2);
	SpriteFrame* sword1_walk_right1 = SpriteFrame::create("Me/Saber/Walk/right1_walk1.png", Rect(0, 0, bodySize.width, bodySize.height));
	SpriteFrame* sword1_walk_right2 = SpriteFrame::create("Me/Saber/Walk/right1_walk2.png", Rect(0, 0, bodySize.width, bodySize.height));
	sword1_walk_right.pushBack(sword1_walk_right1);
	sword1_walk_right.pushBack(sword1_walk_right2);

	SpriteFrame* bow1_walk_back1 = SpriteFrame::create("Me/Saber/Walk/back2_walk1.png", Rect(0, 0, bodySize.width, bodySize.height));
	SpriteFrame* bow1_walk_back2 = SpriteFrame::create("Me/Saber/Walk/back2_walk2.png", Rect(0, 0, bodySize.width, bodySize.height));
	bow1_walk_back.pushBack(bow1_walk_back1);
	bow1_walk_back.pushBack(bow1_walk_back2);
	SpriteFrame* bow1_walk_front1 = SpriteFrame::create("Me/Saber/Walk/front2_walk1.png", Rect(0, 0, bodySize.width, bodySize.height));
	SpriteFrame* bow1_walk_front2 = SpriteFrame::create("Me/Saber/Walk/front2_walk2.png", Rect(0, 0, bodySize.width, bodySize.height));
	bow1_walk_front.pushBack(bow1_walk_front1);
	bow1_walk_front.pushBack(bow1_walk_front2);
	SpriteFrame* bow1_walk_left1 = SpriteFrame::create("Me/Saber/Walk/left2_walk1.png", Rect(0, 0, bodySize.width, bodySize.height));
	SpriteFrame* bow1_walk_left2 = SpriteFrame::create("Me/Saber/Walk/left2_walk2.png", Rect(0, 0, bodySize.width, bodySize.height));
	bow1_walk_left.pushBack(bow1_walk_left1);
	bow1_walk_left.pushBack(bow1_walk_left2);
	SpriteFrame* bow1_walk_right1 = SpriteFrame::create("Me/Saber/Walk/right2_walk1.png", Rect(0, 0, bodySize.width, bodySize.height));
	SpriteFrame* bow1_walk_right2 = SpriteFrame::create("Me/Saber/Walk/right2_walk2.png", Rect(0, 0, bodySize.width, bodySize.height));
	bow1_walk_right.pushBack(bow1_walk_right1);
	bow1_walk_right.pushBack(bow1_walk_right2);

	//"D:\Github_Document\GenshinImpact\Genshin\Resources\Me\Saber\Walk\walk_back2.png"
	SpriteFrame* sword2_front = SpriteFrame::create("Me/Saber/Walk/front3.png", Rect(0, 0, bodySize.width, bodySize.height));
	SpriteFrame* sword2_back = SpriteFrame::create("Me/Saber/Walk/back3.png", Rect(0, 0, bodySize.width, bodySize.height));
	SpriteFrame* sword2_left = SpriteFrame::create("Me/Saber/Walk/left3.png", Rect(0, 0, bodySize.width, bodySize.height));
	SpriteFrame* sword2_right = SpriteFrame::create("Me/Saber/Walk/right3.png", Rect(0, 0, bodySize.width, bodySize.height));
	//SpriteFrame* dead = SpriteFrame::create("Me/Saber/Walk/dead.png", Rect(0, 0, bodySize.width, bodySize.height));
	sword2_staticForwards.pushBack(sword2_front);
	sword2_staticForwards.pushBack(sword2_back);
	sword2_staticForwards.pushBack(sword2_left);
	sword2_staticForwards.pushBack(sword2_right);
	//staticForwards.pushBack(dead);
	SpriteFrame* bow2_front = SpriteFrame::create("Me/Saber/Walk/front4.png", Rect(0, 0, bodySize.width, bodySize.height));
	SpriteFrame* bow2_back = SpriteFrame::create("Me/Saber/Walk/back4.png", Rect(0, 0, bodySize.width, bodySize.height));
	SpriteFrame* bow2_left = SpriteFrame::create("Me/Saber/Walk/left4.png", Rect(0, 0, bodySize.width, bodySize.height));
	SpriteFrame* bow2_right = SpriteFrame::create("Me/Saber/Walk/right4.png", Rect(0, 0, bodySize.width, bodySize.height));
	//SpriteFrame* dead = SpriteFrame::create("Me/Saber/Walk/dead.png", Rect(0, 0, bodySize.width, bodySize.height));
	bow2_staticForwards.pushBack(bow2_front);
	bow2_staticForwards.pushBack(bow2_back);
	bow2_staticForwards.pushBack(bow2_left);
	bow2_staticForwards.pushBack(bow2_right);
	//staticForwards.pushBack(dead);

	//�˶�����֡
	SpriteFrame* sword2_walk_back1 = SpriteFrame::create("Me/Saber/Walk/back3_walk1.png", Rect(0, 0, bodySize.width, bodySize.height));
	SpriteFrame* sword2_walk_back2 = SpriteFrame::create("Me/Saber/Walk/back3_walk2.png", Rect(0, 0, bodySize.width, bodySize.height));
	sword2_walk_back.pushBack(sword2_walk_back1);
	sword2_walk_back.pushBack(sword2_walk_back2);
	SpriteFrame* sword2_walk_front1 = SpriteFrame::create("Me/Saber/Walk/front3_walk1.png", Rect(0, 0, bodySize.width, bodySize.height));
	SpriteFrame* sword2_walk_front2 = SpriteFrame::create("Me/Saber/Walk/front3_walk2.png", Rect(0, 0, bodySize.width, bodySize.height));
	sword2_walk_front.pushBack(sword2_walk_front1);
	sword2_walk_front.pushBack(sword2_walk_front2);
	SpriteFrame* sword2_walk_left1 = SpriteFrame::create("Me/Saber/Walk/left3_walk1.png", Rect(0, 0, bodySize.width, bodySize.height));
	SpriteFrame* sword2_walk_left2 = SpriteFrame::create("Me/Saber/Walk/left3_walk2.png", Rect(0, 0, bodySize.width, bodySize.height));
	sword2_walk_left.pushBack(sword2_walk_left1);
	sword2_walk_left.pushBack(sword2_walk_left2);
	SpriteFrame* sword2_walk_right1 = SpriteFrame::create("Me/Saber/Walk/right3_walk1.png", Rect(0, 0, bodySize.width, bodySize.height));
	SpriteFrame* sword2_walk_right2 = SpriteFrame::create("Me/Saber/Walk/right3_walk2.png", Rect(0, 0, bodySize.width, bodySize.height));
	sword2_walk_right.pushBack(sword2_walk_right1);
	sword2_walk_right.pushBack(sword2_walk_right2);

	SpriteFrame* bow2_walk_back1 = SpriteFrame::create("Me/Saber/Walk/back4_walk1.png", Rect(0, 0, bodySize.width, bodySize.height));
	SpriteFrame* bow2_walk_back2 = SpriteFrame::create("Me/Saber/Walk/back4_walk2.png", Rect(0, 0, bodySize.width, bodySize.height));
	bow2_walk_back.pushBack(bow2_walk_back1);
	bow2_walk_back.pushBack(bow2_walk_back2);
	SpriteFrame* bow2_walk_front1 = SpriteFrame::create("Me/Saber/Walk/front4_walk1.png", Rect(0, 0, bodySize.width, bodySize.height));
	SpriteFrame* bow2_walk_front2 = SpriteFrame::create("Me/Saber/Walk/front4_walk2.png", Rect(0, 0, bodySize.width, bodySize.height));
	bow2_walk_front.pushBack(bow2_walk_front1);
	bow2_walk_front.pushBack(bow2_walk_front2);
	SpriteFrame* bow2_walk_left1 = SpriteFrame::create("Me/Saber/Walk/left4_walk1.png", Rect(0, 0, bodySize.width, bodySize.height));
	SpriteFrame* bow2_walk_left2 = SpriteFrame::create("Me/Saber/Walk/left4_walk2.png", Rect(0, 0, bodySize.width, bodySize.height));
	bow2_walk_left.pushBack(bow2_walk_left1);
	bow2_walk_left.pushBack(bow2_walk_left2);
	SpriteFrame* bow2_walk_right1 = SpriteFrame::create("Me/Saber/Walk/right4_walk1.png", Rect(0, 0, bodySize.width, bodySize.height));
	SpriteFrame* bow2_walk_right2 = SpriteFrame::create("Me/Saber/Walk/right4_walk2.png", Rect(0, 0, bodySize.width, bodySize.height));
	bow2_walk_right.pushBack(bow2_walk_right1);
	bow2_walk_right.pushBack(bow2_walk_right2);


	//���������
	this->scheduleUpdate();

	////�Կ�Ѫ�ļ���
	//auto eventLLL = EventListenerKeyboard::create();
	//eventLLL->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event)
	//	{
	//		switch (keyCode)
	//		{
	//		case EventKeyboard::KeyCode::KEY_O:
	//			hurt(1,Fire,true);
	//			break;
	//		case EventKeyboard::KeyCode::KEY_P:
	//			hurt(1, Thunder,true);
	//			break;
	//		case EventKeyboard::KeyCode::KEY_I:
	//			hurt(1, Ice, true);
	//			break;
	//		case EventKeyboard::KeyCode::KEY_U:
	//			hurt(1, Water, true);
	//			break;

	//		default:
	//			break;
	//		}
	//	};
	//Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventLLL, this);//�Ѽ��������뵽�¼��ַ����У��������������󶨵Ķ�����������ȼ��趨Ϊ��������ȼ�
	//������Ҽ����ܵļ���
	auto DodgeListener = EventListenerMouse::create();
	DodgeListener->onMouseDown = [=](Event* event)
		{
		    if (!isdialog)
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
		    }

		};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(DodgeListener, this);//�Ѽ��������뵽�¼��ַ����У��������������󶨵Ķ�����������ȼ��趨Ϊ��������ȼ�

	//��������������ͨ�����ļ���
	auto oridinaryAttack = EventListenerMouse::create();
	oridinaryAttack->onMouseDown = [this](Event* event)
		{
			auto mouseAttack = static_cast<EventMouse*>(event);
			if (mouseAttack->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT && !isWeapon && !isE && !isOnBoard && !isdialog)
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
		    if (!isdialog)
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
				  clearKeyBoardState();
			      keyMap[EventKeyboard::KeyCode::KEY_F] = true;
			      break;
			case EventKeyboard::KeyCode::KEY_L:
			      keyMap[EventKeyboard::KeyCode::KEY_L] = true;
			      break;
			default:
				break;
			}
		    }

		};
	//����̧��ʱ����
	keyboardListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event)
		{
		    if (!isdialog)
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
			case EventKeyboard::KeyCode::KEY_F:
			      keyMap[EventKeyboard::KeyCode::KEY_F] = false;
			      break;
			case EventKeyboard::KeyCode::KEY_L:
			      keyMap[EventKeyboard::KeyCode::KEY_L] = false;
			      break;
			default:
				break;
			}
		    }

		};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);//�Ѽ��������뵽�¼��ַ����У��������������󶨵Ķ�����������ȼ��趨Ϊ��������ȼ�

	//�����¼�������qԪ�ر���
	auto qListener = EventListenerKeyboard::create();
	//��������ʱ����
	qListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event)
	      {
		    if (keyCode == EventKeyboard::KeyCode::KEY_Q && !isdialog)
		    {
			  if (m_Q_CD <= 0 && m_mp >= m_max_mp && haveQ)
			  {
				m_Q_CD = m_max_Q_CD;
				m_mp = 0;
				q();
			  }
		    }
	      };
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(qListener, this);//�Ѽ��������뵽�¼��ַ����У��������������󶨵Ķ�����������ȼ��趨Ϊ��������ȼ�

	//�����¼�������eԪ��ս�����
	auto eListener = EventListenerKeyboard::create();
	//��������ʱ����
	eListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event)
	      {
		    if (keyCode == EventKeyboard::KeyCode::KEY_E && !isdialog)
		    {
			  if (m_E_CD <= 0 && haveE)
			  {
				m_E_CD = m_max_E_CD;
				isE = true;
				e();
			  }
		    }
	      };
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eListener, this);//�Ѽ��������뵽�¼��ַ����У��������������󶨵Ķ�����������ȼ��趨Ϊ��������ȼ�

	//�����¼������������ﻻװ��
	auto playerListener = EventListenerKeyboard::create();
	//��������ʱ����
	playerListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event)
	      {
		    if (keyCode == EventKeyboard::KeyCode::KEY_B && !isdialog)
		    {
			  if (isOnBoard)
			  {
				isOnBoard = false;
				for (int i = 0; i < 6; i++)
				{
				      swordButtons[i].button->setVisible(false);
				      bowButtons[i].button->setVisible(false);
				      swordButtons[i].item->setVisible(false);
				      bowButtons[i].item->setVisible(false);
				}
				for (int i = 0; i < 4; i++)
				{
				      upgrade[i]->setVisible(false);
				      upgradeSwordLevel[i].showLevel->setVisible(false);
				      upgradeBowLevel[i].showLevel->setVisible(false);
				}
			  }
			  else
			  {
				isOnBoard = true;
				if (this->getNaming() == "swordPlayer")
				{
				      for (int i = 0; i < 4; i++)
				      {
					    if (!swordButtons[i].isEmpty)
					    {
						  upgradeSwordLevel[i].showLevel->setVisible(true);
					    }
				      }
				for (int i = 0; i < 6; i++)
				{
				      swordButtons[i].button->setVisible(true);
				      if (!swordButtons[i].isEmpty)
				      {
					    swordButtons[i].item->setVisible(true);
					    if (!swordButtons[i].isSelected)
					    {
						  swordButtons[i].button->setEnabled(true);
					    }
				      }
				}
				for (int i = 0; i < 4; i++)
				{
				      upgrade[i]->setVisible(true);
				      if (!swordButtons[i].isEmpty)
				      {
					    upgrade[i]->setEnabled(true);
				      }
				      else
				      {
					    upgrade[i]->setEnabled(false);
				      }
				}
			  }
				else if (this->getNaming() == "bowPlayer")
				{
			  for (int i = 0; i < 4; i++)
			  {
				if (!swordButtons[i].isEmpty)
				{
				      upgradeBowLevel[i].showLevel->setVisible(true);
				}
			  }
			  for (int i = 0; i < 6; i++)
			  {
				bowButtons[i].button->setVisible(true);
				if (!bowButtons[i].isEmpty)
				{
				      bowButtons[i].item->setVisible(true);
				      if (!bowButtons[i].isSelected)
				      {
					    bowButtons[i].button->setEnabled(true);
				      }
				}
			  }
			  for (int i = 0; i < 4; i++)
			  {
				upgrade[i]->setVisible(true);
				if (!bowButtons[i].isEmpty)
				{
				      upgrade[i]->setEnabled(true);
				}
				else
				{
				      upgrade[i]->setEnabled(false);
				}
			  }
		    }
		    }
	      }
		};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(playerListener, this);//�Ѽ��������뵽�¼��ַ����У��������������󶨵Ķ�����������ȼ��趨Ϊ��������ȼ�

	//����¼�����
	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseMove = [this](Event* event)
	      {
		    if (!isdialog)
		    {
			  EventMouse* mousePosition = dynamic_cast<EventMouse*>(event);
			  float x = mousePosition->getCursorX();
			  float y = mousePosition->getCursorY();
			  // ת��Ϊ��������
			  worldPosition = Vec2(x, y);
			  if (!isE)this->getPlayerOrientation(worldPosition);
			  if (!isWeapon)this->weaponRotate(worldPosition);
		    }

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
	// �����������ƶ�����ʼλ�ã�Ѫ������120
	if (m_hp <= 0)
	{
		// ȡ�����԰�������״̬
		clearKeyBoardState();
		auto tiledSize = ((mapManager*)this->getParent()->getChildByName("mapManager"))->getTileSize();
		((HelloWorld*)this->getParent())->set_New_Teleport_position(Vec2(7.5313f, 29.6080f) * tiledSize);
		m_hp = 120;
		m_mp = 0;
		m_stamina = 100;
		m_Q_CD = 0;
		m_E_CD = 0;
	}
      if (keyMap[EventKeyboard::KeyCode::KEY_M])
      {
	    // ȡ�����԰�������״̬
	    clearKeyBoardState();
	    MapScene* map = MapScene::create();
	    Director::getInstance()->pushScene(map);
	    // ���ݵ�ͼ���͵õ���λ�ã���������λ��
      }

      if (keyMap[EventKeyboard::KeyCode::KEY_L])
      {
	    this->setPosition(Vec2(0, 0));
      }

      if (keyMap[EventKeyboard::KeyCode::KEY_F])
      {
	    clearKeyBoardState();

	    Vec2 position = this->getPosition();

	    // �жϱ߽���Ƿ��ཻ
	    if (position.x > 450 && position.x < 550 && position.y>450 && position.y < 550)
	    {
		  log("dfghjkl");
		  ((HelloWorld*)(this->getParent()))->getchest1()->open();
	    }
	    if (position.x > -550 && position.x < -450 && position.y>-550 && position.y < -450)
	    {
		  ((HelloWorld*)(this->getParent()))->getchest2()->open();
	    }


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
			  || map->isCollision(nextPosition + Vec2(-22, -18))
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
			  || map->isCollision(nextPosition + Vec2(22, -18))
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
			if (map->isCollision(nextPosition + Vec2(-22, 0))
				|| map->isCollision(nextPosition + Vec2(22, 0))
				|| map->isCollision(nextPosition + Vec2(-11, 0))
				|| map->isCollision(nextPosition + Vec2(11, 0))
				|| map->isCollision(nextPosition + Vec2(0, 0)))
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
		    if (this->getNaming() == "swordPlayer")
		    {
			  if (swordButtons[0].isSelected)m_body->setSpriteFrame(sword1_staticForwards.at(2));
			  if (swordButtons[1].isSelected)m_body->setSpriteFrame(sword2_staticForwards.at(2));
		    }
		    if (this->getNaming() == "bowPlayer")
		    {
			  if (bowButtons[0].isSelected)m_body->setSpriteFrame(bow1_staticForwards.at(2));
			  if (bowButtons[1].isSelected)m_body->setSpriteFrame(bow2_staticForwards.at(2));
		    }

	      }
	      else if (this->mouseState[3]) // �������������
	      {
		    if (this->getNaming() == "swordPlayer")
		    {
			  if (swordButtons[0].isSelected)m_body->setSpriteFrame(sword1_staticForwards.at(3));
			  if (swordButtons[1].isSelected)m_body->setSpriteFrame(sword2_staticForwards.at(3));
		    }
		    if (this->getNaming() == "bowPlayer")
		    {
			  if (bowButtons[0].isSelected)m_body->setSpriteFrame(bow1_staticForwards.at(3));
			  if (bowButtons[1].isSelected)m_body->setSpriteFrame(bow2_staticForwards.at(3));
		    }
	      }
	      else if (this->mouseState[0]) // �������������
	      {
		    if (this->getNaming() == "swordPlayer")
		    {
			  if (swordButtons[0].isSelected)m_body->setSpriteFrame(sword1_staticForwards.at(1));
			  if (swordButtons[1].isSelected)m_body->setSpriteFrame(sword2_staticForwards.at(1));
		    }
		    if (this->getNaming() == "bowPlayer")
		    {
			  if (bowButtons[0].isSelected)m_body->setSpriteFrame(bow1_staticForwards.at(1));
			  if (bowButtons[1].isSelected)m_body->setSpriteFrame(bow2_staticForwards.at(1));
		    }
	      }
	      else if (this->mouseState[1])
	      {
		    if (this->getNaming() == "swordPlayer")
		    {
			  if (swordButtons[0].isSelected)m_body->setSpriteFrame(sword1_staticForwards.at(0));
			  if (swordButtons[1].isSelected)m_body->setSpriteFrame(sword2_staticForwards.at(0));
		    }
		    if (this->getNaming() == "bowPlayer")
		    {
			  if (bowButtons[0].isSelected)m_body->setSpriteFrame(bow1_staticForwards.at(0));
			  if (bowButtons[1].isSelected)m_body->setSpriteFrame(bow2_staticForwards.at(0));
		    }
	      }
	      else if (this->mouseState[0] == false && this->mouseState[1] == false && this->mouseState[2] == false && this->mouseState[3] == false)
	      {
		    if (this->getNaming() == "swordPlayer")
		    {
			  if (swordButtons[0].isSelected)m_body->setSpriteFrame(sword1_staticForwards.at(0));
			  if (swordButtons[1].isSelected)m_body->setSpriteFrame(sword2_staticForwards.at(0));
		    }
		    if (this->getNaming() == "bowPlayer")
		    {
			  if (bowButtons[0].isSelected)m_body->setSpriteFrame(bow1_staticForwards.at(0));
			  if (bowButtons[1].isSelected)m_body->setSpriteFrame(bow2_staticForwards.at(0));
		    }
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
	//auto temp = this->myCamera->getCameraPostionChange();
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
      //����"D:\Github_Document\GenshinImpact\Genshin\Resources\Sound\saber_a.MP3"
      //CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Music/test.wav", true);
      CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/saber_a.wav", false);


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
	m_weapon_light->runAction(Sequence::create(delayTime, fadeInAction, moveAction, fadeOutAction, removeSelf, nullptr));
}
void Player::bowOrdinaryAttack()
{
      CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/bow_a.wav", false);
      //������Χ
      float attackDistance = 450.0f;
      //�����ٶ�
      float attackSpeed = 3600.0f;
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
		  for (int j = 0; j < 20; j++)
		  {
			m_effect_index[i][j] = 1;
		  }
		  break;
	    }
      }
      auto fadeInAction = FadeIn::create(0.05);//����
      auto fadeOutAction = FadeOut::create(0.05);//����
      auto moveAction = MoveBy::create(attackDistance / attackSpeed, Vec2(attackDistance * sin((weaponAngle / 180) * PI), attackDistance * cos((weaponAngle / 180) * PI)));//�ƶ�����������ǵ�ǰλ�ã��յ��ǵ�ǰλ�ü���һ������
      //ִ������������ѽڵ��Ƴ������Ұ������Ӧλ�ã�ͨ��tag��ȡ���ÿ�
      auto removeSelf = CallFunc::create([=] {m_weapon_light->setVisible(false); m_effect[m_weapon_light->getTag()] = nullptr; });

      //ִ�ж���
      m_weapon_light->runAction(Sequence::create(fadeInAction, moveAction, fadeOutAction, removeSelf, nullptr));


}

void Player::e()
{
      if (this->getNaming() == "swordPlayer")
      {
	    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/saber_e.wav", false);


	    //��̾���
	    float distance = 500;
	    //����ٶ�
	    float dodgeSpeed = 1500;
	    //��ýǶ�
	    auto currentAngle = (m_weapon->getRotation() / 180) * PI;
	    //��̷���
	    Vec2 dodgeDirection = Vec2(sin(currentAngle), cos(currentAngle));






	    //������Χ
	    float attackDistance = 500;
	    //�����ٶ�
	    float attackSpeed = 4000;
	    //��ת�ٶ�
	    float rotateSpeed = 700.0f;
	    //��ת�Ƕ�
	    float rotateAngle1 = 45;
	    float rotateAngle2 = 90;
	    //��������
	    Vec2 attackDirection = Vec2(sin(currentAngle), cos(currentAngle));

	    //��ʱ
	    auto delayTime = DelayTime::create(rotateAngle1 / rotateSpeed);

	    //������Ч
	    Effects* m_weapon_light = Effects::create();

	    //damage_typeΪ��
	    m_weapon_light->damage_type = Fire;
	    //����3��
	    m_weapon_light->damage_rate = 2;
	    //setColor(Color3B(249, 85, 9));
	    m_weapon_light->effect->setColor(Color3B(249, 85, 9));

	    m_weapon_light->setAnchorPoint(Vec2(0.5, 0));
	    //λ������������
	    m_weapon_light->setPosition(this->getPosition());
	    m_weapon_light->setRotation(this->weaponAngle);//�������ĽǶȵ������ĽǶ�
	    //�󶨵�����
	    this->getParent()->addChild(m_weapon_light, 1);
	    m_weapon_light->EffectsAnimation(m_weapon_light->e, 0);

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
	    m_weapon_light->runAction(Sequence::create(delayTime, fadeInAction, moveAction, fadeOutAction, removeSelf, nullptr));




	    length = 100;

	    //��������תΪ����
	    auto moveAction1 = MoveBy::create(distance / dodgeSpeed, dodgeDirection * distance);
	    //ִ�ж���
	    this->runAction(Sequence::create(moveAction1, CallFunc::create([=] {isE = false; }), nullptr));

      }
      else if (this->getNaming() == "bowPlayer")
      {
	    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/bow_a.wav", false);
	    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/bow_e.wav", false);

	    isWeapon = true;
	    //������Χ
	    float attackDistance = 450.0f;
	    //�����ٶ�
	    float attackSpeed = 3600.0f;
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

	    //damage_typeΪˮ
	    m_weapon_light->damage_type = Water;
	    m_weapon_light->damage_rate = 2;
	    //RGBsetColor(Color3B(11, 214, 245));
	    m_weapon_light->effect->setColor(Color3B(11, 214, 245));


	    m_weapon_light->setAnchorPoint(Vec2(0.5, 0));
	    //λ������������
	    m_weapon_light->setPosition(this->getPosition());
	    m_weapon_light->setRotation(this->weaponAngle);//�������ĽǶȵ������ĽǶ�
	    //�󶨵�����
	    this->getParent()->addChild(m_weapon_light, 1);
	    m_weapon_light->EffectsAnimation(m_weapon_light->bow_normal, 0);

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
			for (int j = 0; j < 20; j++)
			{
			      m_effect_index[i][j] = 1;
			}
			break;
		  }
	    }

	    auto fadeInAction = FadeIn::create(0.05);//����
	    auto fadeOutAction = FadeOut::create(0.05);//����
	    auto moveAction = MoveBy::create(attackDistance / attackSpeed, Vec2(attackDistance * sin((weaponAngle / 180) * PI), attackDistance * cos((weaponAngle / 180) * PI)));//�ƶ�����������ǵ�ǰλ�ã��յ��ǵ�ǰλ�ü���һ������
	    //ִ������������ѽڵ��Ƴ������Ұ������Ӧλ�ã�ͨ��tag��ȡ���ÿ�
	    auto removeSelf = CallFunc::create([=] {m_weapon_light->setVisible(false); m_effect[m_weapon_light->getTag()] = nullptr; });

	    //ִ�ж���
	    m_weapon_light->runAction(Sequence::create(fadeInAction, moveAction, fadeOutAction, removeSelf, nullptr));


	    isE = false;
      }
}

void Player::q()
{
      if (this->getNaming() == "swordPlayer")
      {
	    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/saber_q.wav", false);
	    //������Ч
	    Effects* qEffect = Effects::create();
	    //λ������������
	    qEffect->setPosition(this->getPosition());
	    //�󶨵�����
	    this->getParent()->addChild(qEffect, -1);
	    qEffect->EffectsAnimation(qEffect->q, 0);
	    //��������״̬3��
	    this->isDodge = true;
	    //3�����
	    auto removeDodge = Sequence::create(DelayTime::create(3), CallFunc::create([=] {isDodge = false; }), nullptr);
	    this->runAction(removeDodge);



	    //Ԫ��Ϊ��
	    qEffect->damage_type = Ice;
	    //����2��
	    qEffect->damage_rate = 3;
	    //RGBsetColor(Color3B(198, 244, 243));
	    qEffect->effect->setColor(Color3B(198, 244, 243));

	    //���뵽��Ч����
	    for (int i = 0; i < 20; i++)
	    {
		  if (m_effect[i] == nullptr)
		  {
			m_effect[i] = qEffect;
			//���������ֱ�ǩΪi
			qEffect->setTag(i);
			for (int j = 0; j < 20; j++)
			{
			      m_effect_index[i][j] = 1;
			}
			break;
		  }
	    }
	    //ִ������������ѽڵ��Ƴ������Ұ������Ӧλ�ã�ͨ��tag��ȡ���ÿ�
	    auto removeSelf = Sequence::create(DelayTime::create(0.2), CallFunc::create([=] {qEffect->setVisible(false); m_effect[qEffect->getTag()] = nullptr; }), nullptr);
	    //ִ�ж���
	    qEffect->runAction(Sequence::create(removeSelf, nullptr));

      }
      else if (this->getNaming() == "bowPlayer")
      {
	    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/explosion_thunder.wav", false);
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

	    //damage_typeΪ
	    m_weapon_light1->damage_type = Thunder;
	    //����3��
	    m_weapon_light1->damage_rate = 3;

	    float length = -150;
	    m_weapon_light1->setVisible(true);
	    //���뵽��Ч����
	    for (int i = 0; i < 20; i++)
	    {
		  if (m_effect[i] == nullptr)
		  {
			m_effect[i] = m_weapon_light1;
			//���������ֱ�ǩΪi
			m_weapon_light1->setTag(i);
			for (int j = 0; j < 20; j++)
			{
			      m_effect_index[i][j] = 1;
			}
			break;
		  }
	    }
	    //ִ������������ѽڵ��Ƴ������Ұ������Ӧλ�ã�ͨ��tag��ȡ���ÿ�
	    auto removeSelf = Sequence::create(DelayTime::create(0.2), CallFunc::create([=] {m_weapon_light1->setVisible(false); m_effect[m_weapon_light1->getTag()] = nullptr; }), nullptr);
	    //ִ�ж���
	    m_weapon_light1->runAction(Sequence::create(removeSelf, nullptr));

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
	if (!isWeapon && !isE)
	{
		m_weapon->setRotation(this->weaponAngle);
	}
}


void Player::updatePlayerOrientation()
{
      if (this->mouseState[0] && !isE)
	{
		weaponPosition = Vec2(m_body->getPosition().x - 2.25, m_body->getPosition().y + m_weapon->getContentSize().height / (1.25));
		if (this->getNaming() == "swordPlayer")
		{
		      if (swordButtons[0].isSelected)moveAnimation(sword1_walk_back, 4);
		      if (swordButtons[1].isSelected)moveAnimation(sword2_walk_back, 4);
		}
		else if (this->getNaming() == "bowPlayer")
		{
		      if (bowButtons[0].isSelected)moveAnimation(bow1_walk_back, 4);
		      if (bowButtons[1].isSelected)moveAnimation(bow2_walk_back, 4);
		};
	}
      else if (this->mouseState[1] && !isE)
	{
	      weaponPosition = Vec2(m_body->getPosition().x - 2.25, m_body->getPosition().y - m_weapon->getContentSize().height / (1.75));
	      if (this->getNaming() == "swordPlayer")
	      {
		    if (swordButtons[0].isSelected)moveAnimation(sword1_walk_front, 3);
		    if (swordButtons[1].isSelected)moveAnimation(sword2_walk_front, 3);
	      }
	      else if (this->getNaming() == "bowPlayer")
	      {
		    if (bowButtons[0].isSelected)moveAnimation(bow1_walk_front, 3);
		    if (bowButtons[1].isSelected)moveAnimation(bow2_walk_front, 3);
	      };
	}
      else if (this->mouseState[2] && !isE)
	{
		weaponPosition = Vec2(m_body->getPosition().x - m_weapon->getContentSize().width / (1.85), m_body->getPosition().y);
		if (this->getNaming() == "swordPlayer")
		{
		      if (swordButtons[0].isSelected)moveAnimation(sword1_walk_left, 1);
		      if (swordButtons[1].isSelected)moveAnimation(sword2_walk_left, 1);
		}
		else if (this->getNaming() == "bowPlayer")
		{
		      if (bowButtons[0].isSelected)moveAnimation(bow1_walk_left, 1);
		      if (bowButtons[1].isSelected)moveAnimation(bow2_walk_left, 1);
		};
      }
      else if (this->mouseState[3] && !isE)
	{
		weaponPosition = Vec2(m_body->getPosition().x + m_weapon->getContentSize().width / (1.85), m_body->getPosition().y);
		if (this->getNaming() == "swordPlayer")
		{
		      if (swordButtons[0].isSelected)moveAnimation(sword1_walk_right, 2);
		      if (swordButtons[1].isSelected)moveAnimation(sword2_walk_right, 2);
		}
		else if (this->getNaming() == "bowPlayer")
		{
		      if (bowButtons[0].isSelected)moveAnimation(bow1_walk_right, 2);
		      if (bowButtons[1].isSelected)moveAnimation(bow2_walk_right, 2);
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
	//����Ƿ�������
	if (m_exp >= m_max_exp)
	{
	      level++;
	      //�������5��������E����
	      if (level >= 5 && !haveE)
	      {
		    haveE = true;
	      }
	      //�������10��������Q����
	      if (level >= 10 && !haveQ)
	      {
		    haveQ = true;
	      }

	      m_exp -= m_max_exp;
	      //���¼���attack��defense��max_hp
		      //��ҵĹ��������㹫ʽ��base_attack*1.1*level+extra_attack
		      //��ҵķ��������㹫ʽ��base_defense*1.1*level+extra_defense
		      //��ҵ�����ֵ���㹫ʽ��base_hp*1.1*level+extra_hp
	      m_attack = int(double(base_attack) * 1.1 * double(level) + extra_attack);
	      m_defense = int(double(base_defense) * 1.1 * double(level) + extra_defense);
	      m_max_hp = int(double(base_hp) * 1.1 * double(level) + extra_hp);


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

void Player::selectButton(Ref* sender)
{
      //�� sender ת��Ϊ ui::Button ����
      auto clickedButton = dynamic_cast<ui::Button*>(sender);
      int buttonTag = clickedButton->getTag();
      //�ȼ���Ƿ�����Ʒ
      //����Ʒ����Ե��
      //����Ʒ�򲻿ɵ��
      if (this->getNaming() == "swordPlayer")
      {
	    if (!swordButtons[buttonTag].isEmpty)
	    {
		  //����Ʒ���������Ƿ��Ѿ�ѡ��
		  //��δѡ�У�����Ե��
		  //����ѡ�У��򲻿ɵ��
		  if (!swordButtons[buttonTag].isSelected)
		  {
			if (buttonTag % 2 == 0)
			{
			      swordButtons[buttonTag + 1].button->loadTextures("Me/Saber/change/emptyBoard.png", "Me/Saber/change/selectedBoard.png", "Me/Saber/change/emptyBoard.png");
			      swordButtons[buttonTag + 1].isSelected = false;
			      swordButtons[buttonTag + 1].button->setEnabled(true);
			}
			else
			{
			      swordButtons[buttonTag - 1].button->loadTextures("Me/Saber/change/emptyBoard.png", "Me/Saber/change/selectedBoard.png", "Me/Saber/change/emptyBoard.png");
			      swordButtons[buttonTag - 1].isSelected = false;
			      swordButtons[buttonTag - 1].button->setEnabled(true);
			}
			swordButtons[buttonTag].button->loadTextures("Me/Saber/change/selectedBoard.png", "Me/Saber/change/emptyBoard.png", "Me/Saber/change/selectedBoard.png");
			swordButtons[buttonTag].isSelected = true;
			swordButtons[buttonTag].button->setEnabled(false);

			if (buttonTag == 2)
			{
			      m_weapon->setTexture("Me/Saber/Weapon/sword.png");
			}
			else if (buttonTag == 3)
			{
			      m_weapon->setTexture("Me/Saber/Weapon/sword3.png");
			}
		  }
	    }
      }
      else if (this->getNaming() == "bowPlayer")
      {
	    if (!bowButtons[buttonTag].isEmpty)
	    {
		  //����Ʒ���������Ƿ��Ѿ�ѡ��
		  //��δѡ�У�����Ե��
		  //����ѡ�У��򲻿ɵ��
		  if (!bowButtons[buttonTag].isSelected)
		  {
			if (buttonTag % 2 == 0)
			{
			      bowButtons[buttonTag + 1].button->loadTextures("Me/Saber/change/emptyBoard.png", "Me/Saber/change/selectedBoard.png", "Me/Saber/change/emptyBoard.png");
			      bowButtons[buttonTag + 1].isSelected = false;
			      bowButtons[buttonTag + 1].button->setEnabled(true);
			}
			else
			{
			      bowButtons[buttonTag - 1].button->loadTextures("Me/Saber/change/emptyBoard.png", "Me/Saber/change/selectedBoard.png", "Me/Saber/change/emptyBoard.png");
			      bowButtons[buttonTag - 1].isSelected = false;
			      bowButtons[buttonTag - 1].button->setEnabled(true);
			}
			bowButtons[buttonTag].button->loadTextures("Me/Saber/change/selectedBoard.png", "Me/Saber/change/emptyBoard.png", "Me/Saber/change/selectedBoard.png");
			bowButtons[buttonTag].isSelected = true;
			bowButtons[buttonTag].button->setEnabled(false);

			if (buttonTag == 2)
			{
			      m_weapon->setTexture("Me/Saber/Weapon/bow1.png");
			}
			else if (buttonTag == 3)
			{
			      m_weapon->setTexture("Me/Saber/Weapon/bow4.png");
			}
		  }
	    }
      }

      m_body->stopAllActions();
}

void Player::upgradeEquipment(Ref * sender)
{
      //�� sender ת��Ϊ ui::Button ����
      auto clickedButton = dynamic_cast<ui::Button*>(sender);
      int buttonTag = clickedButton->getTag();
      if (this->getNaming() == "swordPlayer")
      {
	    int exp = this->m_exp - this->cost_exp + upgradeSwordLevel[buttonTag].nowExpCost;
	    upgradeSwordLevel[buttonTag].weaponLevel += exp / upgradeSwordLevel[buttonTag].needExpCost;
	    upgradeSwordLevel[buttonTag].nowExpCost = exp % upgradeSwordLevel[buttonTag].needExpCost;
	    upgradeSwordLevel[buttonTag].showLevel->setString(std::to_string(upgradeSwordLevel[buttonTag].weaponLevel));
	    this->cost_exp = m_exp;
      }
      else if (this->getNaming() == "bowPlayer")
      {
	    int exp = this->m_exp - this->cost_exp + upgradeBowLevel[buttonTag].nowExpCost;
	    upgradeBowLevel[buttonTag].weaponLevel += exp / upgradeBowLevel[buttonTag].needExpCost;
	    upgradeBowLevel[buttonTag].nowExpCost = exp % upgradeBowLevel[buttonTag].needExpCost;
	    upgradeBowLevel[buttonTag].showLevel->setString(std::to_string(upgradeBowLevel[buttonTag].weaponLevel));
	    this->cost_exp = m_exp;
      }
}
