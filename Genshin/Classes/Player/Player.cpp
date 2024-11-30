#include "Player.h"

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

	//加入调度器
	this->scheduleUpdate();

	//让相机始终跟随精灵
	//auto follow = Follow::create(m_body);
	//this->runAction(follow);

	//键盘事件监听
	auto eventListener = EventListenerKeyboard::create();
	//按键按下时调用
	eventListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event)
		{
			switch (keyCode)
			{
			case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
				keyMap[EventKeyboard::KeyCode::KEY_LEFT_ARROW] = true;
				break;
			case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
				keyMap[EventKeyboard::KeyCode::KEY_RIGHT_ARROW] = true;
				break;
			case EventKeyboard::KeyCode::KEY_UP_ARROW:
				keyMap[EventKeyboard::KeyCode::KEY_UP_ARROW] = true;
				break;
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
			case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
				keyMap[EventKeyboard::KeyCode::KEY_LEFT_ARROW] = false;
				break;
			case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
				keyMap[EventKeyboard::KeyCode::KEY_RIGHT_ARROW] = false;
				break;
			case EventKeyboard::KeyCode::KEY_UP_ARROW:
				keyMap[EventKeyboard::KeyCode::KEY_UP_ARROW] = false;
				break;
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
	//实现按键控制精灵移动
	auto left = EventKeyboard::KeyCode::KEY_LEFT_ARROW;//左键
	auto right = EventKeyboard::KeyCode::KEY_RIGHT_ARROW;//右键
	auto up = EventKeyboard::KeyCode::KEY_UP_ARROW;//上键
	auto down = EventKeyboard::KeyCode::KEY_DOWN_ARROW;//下键

	if (keyMap[left])//如果左键按下
	{
		if (m_body->getNumberOfRunningActionsByTag(1) == 0)
		{
			m_body->stopAllActions();//停止所有动作
			//动画
			auto animation_left = Animation::create();
			animation_left->setDelayPerUnit(0.2f);//设置每一帧的时间间隔
			animation_left->addSpriteFrameWithFile("me/walk_left1.png");//添加一帧
			animation_left->addSpriteFrameWithFile("me/walk_left2.png");//添加一帧
			animation_left->setLoops(-1);//设置循环次数，-1表示无限循环
			Animate* animate = Animate::create(animation_left);//创建一个动画，传入一个animation
			animate->setTag(1);//设置标签
			m_body->runAction(animate);//执行这个动画
		}
		this->setPositionX(this->getPositionX() - 5);//向左移动10个像素
	}
	if (keyMap[right])//如果右键按下
	{
		if (m_body->getNumberOfRunningActionsByTag(2) == 0)
		{
			m_body->stopAllActions();//停止所有动作
			//动画
			auto animation_right = Animation::create();
			animation_right->setDelayPerUnit(0.2f);//设置每一帧的时间间隔
			animation_right->addSpriteFrameWithFile("me/walk_right1.png");//添加一帧
			animation_right->addSpriteFrameWithFile("me/walk_right2.png");//添加一帧
			animation_right->setLoops(-1);//设置循环次数，-1表示无限循环
			Animate* animate = Animate::create(animation_right);//创建一个动画，传入一个animation
			animate->setTag(2);//设置标签
			m_body->runAction(animate);//执行这个动画
		}
		this->setPositionX(this->getPositionX() + 5);//向右移动10个像素
	}
	if (keyMap[up])//如果上键按下
	{
		if (m_body->getNumberOfRunningActionsByTag(3) == 0)
		{
			m_body->stopAllActions();//停止所有动作
			//动画
			auto animation_up = Animation::create();
			animation_up->setDelayPerUnit(0.2f);//设置每一帧的时间间隔
			animation_up->addSpriteFrameWithFile("me/walk_back1.png");//添加一帧
			animation_up->addSpriteFrameWithFile("me/walk_back2.png");//添加一帧
			animation_up->setLoops(-1);//设置循环次数，-1表示无限循环
			Animate* animate = Animate::create(animation_up);//创建一个动画，传入一个animation
			animate->setTag(3);//设置标签
			m_body->runAction(animate);//执行这个动画
		}
		this->setPositionY(this->getPositionY() + 5);//向上移动10个像素
	}
	if (keyMap[down])//如果下键按下
	{
		if (m_body->getNumberOfRunningActionsByTag(4) == 0)
		{
			m_body->stopAllActions();//停止所有动作
			//动画
			auto animation_down = Animation::create();
			animation_down->setDelayPerUnit(0.2f);//设置每一帧的时间间隔
			animation_down->addSpriteFrameWithFile("me/walk_front1.png");//添加一帧
			animation_down->addSpriteFrameWithFile("me/walk_front2.png");//添加一帧
			animation_down->setLoops(-1);//设置循环次数，-1表示无限循环
			Animate* animate = Animate::create(animation_down);//创建一个动画，传入一个animation
			animate->setTag(4);//设置标签
			m_body->runAction(animate);//执行这个动画
		}
		this->setPositionY(this->getPositionY() - 5);//向下移动10个像素
	}
}