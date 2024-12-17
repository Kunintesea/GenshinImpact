#include "Player.h"
#include "bag/bag.h"
/*
关于动作：由m_body上的tag决定，由getNumberOfRunningActionsByTag获取。
1：向左
2：向右
3：向上
4：向下
*/
//伤害计算式：实际伤害=伤害值-防御值*伤害值，若人物处于闪避状态直接返回0
void Player::hurt(int damage,int damge_type)
{ 
	if (isDodge) return;
	else
	{
		//对元素反应的处理
		switch (damge_type)
		{

		case Wind:
			break;
		case Rock:
			break;
		case Thunder:
			//如果是雷属性伤害，且玩家身上有火元素，触发超载效果
			if (m_element[Fire])
			{
				//超载效果
				//伤害值翻倍
				damage *= 2;
				//火元素消失
				m_element[Fire] = 0;
				//显示超载效果
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





		
		int real_damage = int(float(damage) - float(damage) * m_defense);//实际伤害=伤害值-防御值*伤害值
		//让伤害数字显示
		for (int i = 0; i < 20; i++)
		{
			if (!m_damage_label[i]->isVisible())
			{
				//伤害数字颜色根据伤害类型改变
				switch (damge_type)
				{
					//如果是物理伤害，伤害数字为白色
				case Physical:
					m_damage_label[i]->setColor(Color3B::WHITE);
					break;
					//如果是风属性伤害，伤害数字为青绿色，RGB为23,236,175
				case Wind:
					m_damage_label[i]->setColor(Color3B(23, 236, 175));
					break;
					//如果是岩属性伤害，伤害数字为棕黄色，RGB为248,226,57
				case Rock:
					m_damage_label[i]->setColor(Color3B(248, 226, 57));
					break;
					//如果是雷属性伤害，伤害数字为紫色，RGB为172,43,231
				case Thunder:
					m_damage_label[i]->setColor(Color3B(172, 43, 231));
					break;
					//如果是草属性伤害，伤害数字为绿色，RGB为42,204,21
				case Grass:
					m_damage_label[i]->setColor(Color3B(42, 204, 21));
					break;
					//如果是水属性伤害，伤害数字为蓝色，RGB为11,214,245
				case Water:
					m_damage_label[i]->setColor(Color3B(11, 214, 245));
					break;
					//如果是火属性伤害，伤害数字为红色，RGB为249,85,9
				case Fire:
					m_damage_label[i]->setColor(Color3B(249, 85, 9));
					break;
					//如果是冰属性伤害，伤害数字为淡蓝色，RGB为198,244,243
				case Ice:
					m_damage_label[i]->setColor(Color3B(198, 244, 243));
					break;
				}





				
				m_damage_label[i]->setPosition(Vec2(this->getPositionX () - m_body->getContentSize().width/2  + rand() % 50, this->getPositionY() -m_body->getContentSize().height/2  + rand() % 50));//rand()的使用方法是rand()%n，表示生成一个0到n-1的随机数
				m_damage_label[i]->setVisible(true);
				//向上浮现
				m_damage_label[i]->runAction(Sequence::create(MoveBy::create(0.1, Vec2(0, 20)), nullptr));//创建一个动作序列，让伤害数字向上浮现，持续0.1秒
				//1.5秒后先让m_damage_label[i]不可见，不可见后向下移动20个像素
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
	//创建精灵
	m_body = Sprite::create("Me/front.png");
	//将精灵添加到节点
	this->addChild(m_body);



	//通过读取xml文件，获取元素反应文字，支持中文
	//CCDictionary* chnStrings = CCDictionary::createWithContentsOfFile("Text/元素反应文字.xml");
	//const char* username = ((CCString*)chnStrings->objectForKey("username"))->getCString();

	//初始化名字
	//m_name = "Me";

	//把伤害数字与元素反应文字初始化
	for (int i = 0; i < 20; i++)
	{
		//初始化元素反应文字，支持中文
		m_element_label[i] = Label::createWithTTF("反应", "fonts/HarmonyOS_Sans_SC_Medium.TTF", 40);
		m_damage_label[i] = Label::createWithTTF("0", "fonts/HarmonyOS_Sans_SC_Medium.TTF", 30);


		//加黑色描边
		m_element_label[i]->enableOutline(Color4B::BLACK, 2);
		m_damage_label[i]->enableOutline(Color4B::BLACK, 2);
		m_element_label[i]->setVisible(false);//设置不可见
		m_damage_label[i]->setVisible(false);//设置不可见
	}
	


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

	//对扣血的监听
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
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventLLL, this);//把监听器加入到事件分发器中，传入监听器与其绑定的对象。这里的优先级设定为精灵的优先级

	//对鼠标右键闪避的监听
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
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(DodgeListener, this);//把监听器加入到事件分发器中，传入监听器与其绑定的对象。这里的优先级设定为精灵的优先级



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

	//如果检测到右键，就向鼠标方向冲刺
	//if (isDodge)
	//{
	//	//向鼠标方向冲刺
	//	//获取鼠标位置
	//	auto mousePosition = Director::getInstance()->getOpenGLView()->getMousePosition();
	//}

	
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

