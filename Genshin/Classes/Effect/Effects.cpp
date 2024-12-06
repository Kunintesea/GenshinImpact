//#include "Effects.h"
//
//
//
//bool Effects::init()
//{
//	if (!Node::init())
//	{
//		return false;
//	}
//	
//	// ���ض���
//	// ��ֹ����֡
//	Size bodySize = effect->getContentSize();
//	//"D:\Github_Document\GenshinImpact\Genshin\Resources\Effects\Ԫ�ط�Ӧ\����\����1.png"
//	SpriteFrame* Explode1 = SpriteFrame::create("Effects/Ԫ�ط�Ӧ/����/����1.png", Rect(0, 0, bodySize.width, bodySize.height));
//	SpriteFrame* Explode2 = SpriteFrame::create("Effects/Ԫ�ط�Ӧ/����/����2.png", Rect(0, 0, bodySize.width, bodySize.height));
//	SpriteFrame* Explode3 = SpriteFrame::create("Effects/Ԫ�ط�Ӧ/����/����3.png", Rect(0, 0, bodySize.width, bodySize.height));
//	SpriteFrame* Explode4 = SpriteFrame::create("Effects/Ԫ�ط�Ӧ/����/����4.png", Rect(0, 0, bodySize.width, bodySize.height));
//	Explode.pushBack(Explode1);
//	Explode.pushBack(Explode2);
//	Explode.pushBack(Explode3);
//	Explode.pushBack(Explode4);
//
//
//
//	SpriteFrame* front = SpriteFrame::create("me/front.png", Rect(0, 0, bodySize.width, bodySize.height));
//	SpriteFrame* back = SpriteFrame::create("me/back.png", Rect(0, 0, bodySize.width, bodySize.height));
//	SpriteFrame* left = SpriteFrame::create("me/left.png", Rect(0, 0, bodySize.width, bodySize.height));
//	SpriteFrame* right = SpriteFrame::create("me/right.png", Rect(0, 0, bodySize.width, bodySize.height));
//	SpriteFrame* dead = SpriteFrame::create("me/dead.png", Rect(0, 0, bodySize.width, bodySize.height));
//	staticForwards.pushBack(front);
//	staticForwards.pushBack(back);
//	staticForwards.pushBack(left);
//	staticForwards.pushBack(right);
//	staticForwards.pushBack(dead);
//
//	//�˶�����֡
//	SpriteFrame* walk_back1 = SpriteFrame::create("me/walk_back1.png", Rect(0, 0, bodySize.width, bodySize.height));
//	SpriteFrame* walk_back2 = SpriteFrame::create("me/walk_back2.png", Rect(0, 0, bodySize.width, bodySize.height));
//	walk_back.pushBack(walk_back1);
//	walk_back.pushBack(walk_back2);
//	SpriteFrame* walk_front1 = SpriteFrame::create("me/walk_front1.png", Rect(0, 0, bodySize.width, bodySize.height));
//	SpriteFrame* walk_front2 = SpriteFrame::create("me/walk_front2.png", Rect(0, 0, bodySize.width, bodySize.height));
//	walk_front.pushBack(walk_front1);
//	walk_front.pushBack(walk_front2);
//	SpriteFrame* walk_left1 = SpriteFrame::create("me/walk_left1.png", Rect(0, 0, bodySize.width, bodySize.height));
//	SpriteFrame* walk_left2 = SpriteFrame::create("me/walk_left2.png", Rect(0, 0, bodySize.width, bodySize.height));
//	walk_left.pushBack(walk_left1);
//	walk_left.pushBack(walk_left2);
//	SpriteFrame* walk_right1 = SpriteFrame::create("me/walk_right1.png", Rect(0, 0, bodySize.width, bodySize.height));
//	SpriteFrame* walk_right2 = SpriteFrame::create("me/walk_right2.png", Rect(0, 0, bodySize.width, bodySize.height));
//	walk_right.pushBack(walk_right1);
//	walk_right.pushBack(walk_right2);
//
//	//���������
//	
//	return true;
//}
//
//void Effects::update(float dt)
//{
//	if (keyMap[EventKeyboard::KeyCode::KEY_LEFT_ARROW])//����������
//	{
//		moveAnimation(walk_left, 1);
//		this->setPositionX(this->getPositionX() - speed);//�����ƶ�10������
//	}
//	if (keyMap[EventKeyboard::KeyCode::KEY_RIGHT_ARROW])//����Ҽ�����
//	{
//		moveAnimation(walk_right, 2);
//		this->setPositionX(this->getPositionX() + speed);//�����ƶ�10������
//	}
//	if (keyMap[EventKeyboard::KeyCode::KEY_UP_ARROW])//����ϼ�����
//	{
//		moveAnimation(walk_back, 4);
//		this->setPositionY(this->getPositionY() + speed);//�����ƶ�10������
//	}
//	if (keyMap[EventKeyboard::KeyCode::KEY_DOWN_ARROW])//����¼�����
//	{
//		moveAnimation(walk_front, 3);
//		this->setPositionY(this->getPositionY() - speed);//�����ƶ�10������
//	}
//	if (!keyMap[EventKeyboard::KeyCode::KEY_LEFT_ARROW] && !keyMap[EventKeyboard::KeyCode::KEY_RIGHT_ARROW] && !keyMap[EventKeyboard::KeyCode::KEY_UP_ARROW] && !keyMap[EventKeyboard::KeyCode::KEY_DOWN_ARROW])//���û�а�������
//	{
//		if (m_body->getNumberOfRunningActionsByTag(1) != 0) // �������������
//			m_body->setSpriteFrame(staticForwards.at(2));
//		else if (m_body->getNumberOfRunningActionsByTag(2) != 0) // �������������
//			m_body->setSpriteFrame(staticForwards.at(3));
//		else if (m_body->getNumberOfRunningActionsByTag(4) != 0) // �������������
//			m_body->setSpriteFrame(staticForwards.at(1));
//		else
//			m_body->setSpriteFrame(staticForwards.at(0));
//	}
//
//	//�����⵽�Ҽ���������귽����
//	//if (isDodge)
//	//{
//	//	//����귽����
//	//	//��ȡ���λ��
//	//	auto mousePosition = Director::getInstance()->getOpenGLView()->getMousePosition();
//	//}
//
//
//}
//
//void Effects::moveAnimation(Vector<SpriteFrame*> frame, int actionTag) {
//	//����
//	if (m_body->getActionByTag(actionTag) == 0)
//	{
//		m_body->stopAllActions();//ֹͣ���ж���
//		auto action = RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(frame, 0.2f))); // ���붯��֡
//		action->setTag(actionTag);//���ñ�ǩ
//		m_body->runAction((action));//ִ���������
//	}
//}
//
