#include "Player.h"

/*
关于动作：由m_body上的tag决定，由getNumberOfRunningActionsByTag获取。
1：向左
2：向右
3：向上
4：向下
*/


bool Player::init()
{
	if (!Node::init())
	{
		return false;
	}
	//创建精灵
	m_body = Sprite::create("me/front.png");
	//将精灵添加到节点
	this->addChild(m_body);






	// 设置速度
	speed = 5;

	m_head = Sprite::create("me/head.png");
	//缩小5倍
	m_head->setScale(0.2);
	//设置位置到身体右边
	m_head->setPosition(Vec2(m_body->getContentSize().width / 2, 0));
	this->addChild(m_head);

	// 加载动画
	// 静止动画帧
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

	//运动动画帧
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

	//加入调度器
	this->scheduleUpdate();

	//键盘事件监听
	auto eventListener = EventListenerKeyboard::create();
	//按键按下时调用
	eventListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event)
		{
			switch (keyCode)//同时支持WASD和方向键
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
	//按键抬起时调用
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
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, this);//把监听器加入到事件分发器中，传入监听器与其绑定的对象。这里的优先级设定为精灵的优先级

	return true;
}

void Player::update(float dt)
{
	if (keyMap[EventKeyboard::KeyCode::KEY_LEFT_ARROW])//如果左键按下
	{
	      moveAnimation(walk_left, 1);
	      this->setPositionX(this->getPositionX() - speed);//向左移动10个像素
	}
	if (keyMap[EventKeyboard::KeyCode::KEY_RIGHT_ARROW])//如果右键按下
	{
	      moveAnimation(walk_right, 2);
	      this->setPositionX(this->getPositionX() + speed);//向右移动10个像素
	}
	if (keyMap[EventKeyboard::KeyCode::KEY_UP_ARROW])//如果上键按下
	{
	      moveAnimation(walk_back, 4);
	      this->setPositionY(this->getPositionY() + speed);//向上移动10个像素
	}
	if (keyMap[EventKeyboard::KeyCode::KEY_DOWN_ARROW])//如果下键按下
	{
	      moveAnimation(walk_front, 3);
	      this->setPositionY(this->getPositionY() - speed);//向下移动10个像素
	}
	if (!keyMap[EventKeyboard::KeyCode::KEY_LEFT_ARROW] && !keyMap[EventKeyboard::KeyCode::KEY_RIGHT_ARROW] && !keyMap[EventKeyboard::KeyCode::KEY_UP_ARROW] && !keyMap[EventKeyboard::KeyCode::KEY_DOWN_ARROW])//如果没有按键按下
	{
	      if (m_body->getNumberOfRunningActionsByTag(1) != 0) // 如果正在向左走
		    m_body->setSpriteFrame(staticForwards.at(2));
	      else if (m_body->getNumberOfRunningActionsByTag(2) != 0) // 如果正在向右走
		    m_body->setSpriteFrame(staticForwards.at(3));
	      else if (m_body->getNumberOfRunningActionsByTag(4) != 0) // 如果正在向上走
		    m_body->setSpriteFrame(staticForwards.at(1));
	      else
		    m_body->setSpriteFrame(staticForwards.at(0));
	}
}

void Player::moveAnimation(Vector<SpriteFrame*> frame, int actionTag) {
      //动画
      if (m_body->getActionByTag(actionTag) == 0)
      {
	    m_body->stopAllActions();//停止所有动作
	    auto action = RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(frame, 0.2f))); // 导入动画帧
	    action->setTag(actionTag);//设置标签
	    m_body->runAction((action));//执行这个动画
      }
}

