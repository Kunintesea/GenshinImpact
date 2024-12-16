#include "Player.h"

/*
关于动作：由m_body上的tag决定，由getNumberOfRunningActionsByTag获取。
1：向左
2：向右
3：向上
4：向下
*/
//伤害计算式：实际伤害=伤害值-防御值*伤害值，若人物处于闪避状态直接返回0



bool Player::init()
{
	if (!Node::init())
	{
		return false;
	}
	//创建精灵
	m_body = Sprite::create("Me/Saber/Walk/front.png");
	//将精灵添加到节点
	this->addChild(m_body);


	//人物头顶显示元素附着
	//初始化元素附着。如果只有一个元素附着就显示在正上方，如果有两个则会在正上方的左右两侧
	for (int i = 0; i < 2; i++)
	{
		m_element_sprite[i] = Sprite::create("Effects/Element/Rock.png");
		m_element_sprite[i]->setScale(0.4);

		m_element_sprite[i]->setVisible(false);
		//默认设置在正上方
		m_element_sprite[i]->setPosition(Vec2(this->getPositionX(), this->getPositionY() + m_body->getContentSize().height / 3));
		this->addChild(m_element_sprite[i]);
	}





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
	angleSpeed = 5;


	m_head = Sprite::create("me/head.png");
	//缩小5倍
	m_head->setScale(0.2);
	//设置位置到身体右边
	m_head->setPosition(Vec2(m_body->getContentSize().width / 2, 0));
	this->addChild(m_head);

	//设置武器
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
	//m_weapon_light->setVisible(false);  // 隐藏精灵

	//RGB设置为红色
	//m_weapon_light->setColor(Color3B(255, 0, 0));

	//this->addChild(m_weapon_light);//添加到场景中
	//设置一个攻击类型的tag，有Physical, Wind, Rock, Thunder, Grass, Water, Fire, Ice
	//m_weapon_light->setTag(Physical);

	// 加载动画
	// 静止动画帧
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

	//运动动画帧
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

	//加入调度器
	this->scheduleUpdate();

	//对扣血的监听
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
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventLLL, this);//把监听器加入到事件分发器中，传入监听器与其绑定的对象。这里的优先级设定为精灵的优先级

	//对鼠标右键闪避的监听
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
					//闪避的方向是朝着鼠标的方向
					EventMouse* mousePosition = dynamic_cast<EventMouse*>(event);
					float x = mousePosition->getCursorX();
					float y = mousePosition->getCursorY();
					// 转换为世界坐标
					Vec2 worldPosition = Vec2(x, y);
					//朝着鼠标方向冲刺
					this->dodge(worldPosition);
				}
			}
		};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(DodgeListener, this);//把监听器加入到事件分发器中，传入监听器与其绑定的对象。这里的优先级设定为精灵的优先级

	//对鼠标左键发动普通攻击的监听
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
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(oridinaryAttack, this);//把监听器加入到事件分发器中，传入监听器与其绑定的对象。这里的优先级设定为精灵的优先级

	//键盘事件监听
	auto keyboardListener = EventListenerKeyboard::create();
	//按键按下时调用
	keyboardListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event)
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
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);//把监听器加入到事件分发器中，传入监听器与其绑定的对象。这里的优先级设定为精灵的优先级

	//鼠标事件监听
	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseMove = [this](Event* event)
		{
			EventMouse* mousePosition = dynamic_cast<EventMouse*>(event);
			float x = mousePosition->getCursorX();
			float y = mousePosition->getCursorY();
			// 转换为世界坐标
			Vec2 worldPosition = Vec2(x, y);
			this->getPlayerOrientation(worldPosition);
			if (!isWeapon)this->weaponRotate(worldPosition);
		};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);//把监听器加入到事件分发器中，传入监听器与其绑定的对象。这里的优先级设定为精灵的优先级

	//鼠标事件调度器，用于更新朝向
	schedule(CC_CALLBACK_0(Player::updatePlayerOrientation, this), "mouse1");
	//鼠标事件调度器，用于更新武器方向
	schedule(CC_CALLBACK_1(Player::updateWeaponRotation, this), "mouse2");
	//键盘事件调度器，用于更新位置
	schedule(CC_CALLBACK_1(Player::updatePlayerPosition, this), "keyboard");



	return true;
}

void Player::updatePlayerPosition(float dt)
{
	if (keyMap[EventKeyboard::KeyCode::KEY_LEFT_ARROW])//如果左键按下
	{
		float Position = this->getPositionX() - speed;
		// 检测是否碰到墙壁
		for (int i = 1; i <= speed; ++i) {
			Vec2 nextPosition = this->getPosition() + Vec2(-i, 0);
			// 获取到地图管理器
			mapManager* map = (mapManager*)this->getParent()->getChildByName("mapManager");
			// 发生了碰撞
			if (map->isCollision(nextPosition + Vec2(-40, -40))
				|| map->isCollision(nextPosition + Vec2(-40, 40))
				|| map->isCollision(nextPosition + Vec2(-40, -20))
				|| map->isCollision(nextPosition + Vec2(-40, 20)))
			{
				// 如果碰撞了，就不再移动
				Position = nextPosition.x + 1;
				break;
			}
		}
		this->setPositionX(Position);//向左移动10个像素
	}
	if (keyMap[EventKeyboard::KeyCode::KEY_RIGHT_ARROW])//如果右键按下
	{
		float Position = this->getPositionX() + speed;
		// 检测是否碰到墙壁
		for (int i = 1; i <= speed; ++i) {
			Vec2 nextPosition = this->getPosition() + Vec2(i, 0);
			// 获取到地图管理器
			mapManager* map = (mapManager*)this->getParent()->getChildByName("mapManager");
			// 发生了碰撞
			if (map->isCollision(nextPosition + Vec2(40, -40))
				|| map->isCollision(nextPosition + Vec2(40, 40))
				|| map->isCollision(nextPosition + Vec2(40, -20))
				|| map->isCollision(nextPosition + Vec2(40, 20)))
			{
				// 如果碰撞了，就不再移动
				Position = nextPosition.x - 1;
				break;
			}
		}
		this->setPositionX(Position);//向右移动10个像素
	}
	if (keyMap[EventKeyboard::KeyCode::KEY_UP_ARROW])//如果上键按下
	{
		float Position = this->getPositionY() + speed;
		// 检测是否碰到墙壁
		for (int i = 1; i <= speed; ++i) {
			Vec2 nextPosition = this->getPosition() + Vec2(0, i);
			// 获取到地图管理器
			mapManager* map = (mapManager*)this->getParent()->getChildByName("mapManager");
			// 发生了碰撞
			if (map->isCollision(nextPosition + Vec2(-40, 40))
				|| map->isCollision(nextPosition + Vec2(40, 40))
				|| map->isCollision(nextPosition + Vec2(-20, 40))
				|| map->isCollision(nextPosition + Vec2(20, 40)))
			{
				// 如果碰撞了，就不再移动
				Position = nextPosition.y - 1;
				break;
			}
		}
		this->setPositionY(Position);//向上移动10个像素
	}
	if (keyMap[EventKeyboard::KeyCode::KEY_DOWN_ARROW])//如果下键按下
	{
		float Position = this->getPositionY() - speed;
		// 检测是否碰到墙壁
		for (int i = 1; i <= speed; ++i) {
			Vec2 nextPosition = this->getPosition() + Vec2(0, -i);
			// 获取到地图管理器
			mapManager* map = (mapManager*)this->getParent()->getChildByName("mapManager");
			// 发生了碰撞
			if (map->isCollision(nextPosition + Vec2(-40, -40))
				|| map->isCollision(nextPosition + Vec2(40, -40))
				|| map->isCollision(nextPosition + Vec2(-20, -40))
				|| map->isCollision(nextPosition + Vec2(20, -40)))
			{
				// 如果碰撞了，就不再移动
				Position = nextPosition.y + 1;
				break;
			}
		}
		this->setPositionY(Position);//向下移动10个像素
	}
	if (!keyMap[EventKeyboard::KeyCode::KEY_LEFT_ARROW] && !keyMap[EventKeyboard::KeyCode::KEY_RIGHT_ARROW] && !keyMap[EventKeyboard::KeyCode::KEY_UP_ARROW] && !keyMap[EventKeyboard::KeyCode::KEY_DOWN_ARROW])//如果没有按键按下
	{
		if (this->mouseState[2]) // 如果正在向左走
			m_body->setSpriteFrame(staticForwards.at(2));
		else if (this->mouseState[3]) // 如果正在向右走
			m_body->setSpriteFrame(staticForwards.at(3));
		else if (this->mouseState[0]) // 如果正在向上走
			m_body->setSpriteFrame(staticForwards.at(1));
		else if (this->mouseState[1])
			m_body->setSpriteFrame(staticForwards.at(0));
	}


	
}


void Player::dodge(Vec2 position)
{
	//计算区域斜率
	//获得角色贴图尺寸
	auto playerSize = this->m_body->getContentSize();
	float k = playerSize.height / playerSize.width;

	//获得屏幕尺寸
	auto visibleSize = Director::getInstance()->getVisibleSize();
	//获得鼠标坐标相对于屏幕的坐标
	Vec2 mouseWorldPosition = position;
	//获得精灵的世界坐标
	Vec2 spriteWorldPosition = this->getPosition();
	auto temp = this->myCamera->getCameraPostionChange();
	spriteWorldPosition = spriteWorldPosition - this->myCamera->getCameraPostionChange()
		+ Vec2(visibleSize.width / 2, visibleSize.height / 2);
	//计算
	Vec2 mouseLocalPosition = Vec2(mouseWorldPosition.x - spriteWorldPosition.x, mouseWorldPosition.y - spriteWorldPosition.y);

	//计算角度
	float angle = atan2(mouseLocalPosition.y, mouseLocalPosition.x);
	//冲刺距离
	float distance = 100;

	// 判断碰撞
	if (cos(angle) >= 0 && sin(angle) >= 0) {
		for (int i = 1; i <= distance; ++i) {
			Vec2 nextPosition = this->getPosition() + Vec2(i * cos(angle), i * sin(angle));
			// 获取到地图管理器
			mapManager* map = (mapManager*)this->getParent()->getChildByName("mapManager");
			// 发生了碰撞
			if (map->isCollision(nextPosition + Vec2(-40, 40)) // 上
				|| map->isCollision(nextPosition + Vec2(40, 40))
				|| map->isCollision(nextPosition + Vec2(-20, 40))
				|| map->isCollision(nextPosition + Vec2(20, 40))
				|| map->isCollision(nextPosition + Vec2(40, -40)) // 右
				|| map->isCollision(nextPosition + Vec2(40, 40))
				|| map->isCollision(nextPosition + Vec2(40, -20))
				|| map->isCollision(nextPosition + Vec2(40, 20))
				)
			{
				// 如果碰撞了，就不再移动
				distance = i - 1;
				break;
			}
		}
	}
	else if (cos(angle) >= 0 && sin(angle) < 0) {
		for (int i = 1; i <= distance; ++i) {
			Vec2 nextPosition = this->getPosition() + Vec2(i * cos(angle), i * sin(angle));
			// 获取到地图管理器
			mapManager* map = (mapManager*)this->getParent()->getChildByName("mapManager");
			// 发生了碰撞
			if (map->isCollision(nextPosition + Vec2(-40, -40)) // 下
				|| map->isCollision(nextPosition + Vec2(40, -40))
				|| map->isCollision(nextPosition + Vec2(-20, -40))
				|| map->isCollision(nextPosition + Vec2(20, -40))
				|| map->isCollision(nextPosition + Vec2(40, -40)) // 右
				|| map->isCollision(nextPosition + Vec2(40, 40))
				|| map->isCollision(nextPosition + Vec2(40, -20))
				|| map->isCollision(nextPosition + Vec2(40, 20))
				)
			{
				// 如果碰撞了，就不再移动
				distance = i - 1;
				break;
			}
		}
	}
	else if (cos(angle) < 0 && sin(angle) >= 0) {
		for (int i = 1; i <= distance; ++i) {
			Vec2 nextPosition = this->getPosition() + Vec2(i * cos(angle), i * sin(angle));
			// 获取到地图管理器
			mapManager* map = (mapManager*)this->getParent()->getChildByName("mapManager");
			// 发生了碰撞
			if (map->isCollision(nextPosition + Vec2(-40, 40)) // 上
				|| map->isCollision(nextPosition + Vec2(40, 40))
				|| map->isCollision(nextPosition + Vec2(-20, 40))
				|| map->isCollision(nextPosition + Vec2(20, 40))
				|| map->isCollision(nextPosition + Vec2(-40, -40)) // 左
				|| map->isCollision(nextPosition + Vec2(-40, 40))
				|| map->isCollision(nextPosition + Vec2(-40, -20))
				|| map->isCollision(nextPosition + Vec2(-40, 20))
				)
			{
				// 如果碰撞了，就不再移动
				distance = i - 1;
				break;
			}
		}
	}
	else {
		for (int i = 1; i <= distance; ++i) {
			Vec2 nextPosition = this->getPosition() + Vec2(i * cos(angle), i * sin(angle));
			// 获取到地图管理器
			mapManager* map = (mapManager*)this->getParent()->getChildByName("mapManager");
			// 发生了碰撞
			if (map->isCollision(nextPosition + Vec2(-40, -40)) // 下
				|| map->isCollision(nextPosition + Vec2(40, -40))
				|| map->isCollision(nextPosition + Vec2(-20, -40))
				|| map->isCollision(nextPosition + Vec2(20, -40))
				|| map->isCollision(nextPosition + Vec2(-40, -40)) // 左
				|| map->isCollision(nextPosition + Vec2(-40, 40))
				|| map->isCollision(nextPosition + Vec2(-40, -20))
				|| map->isCollision(nextPosition + Vec2(-40, 20))
				)
			{
				// 如果碰撞了，就不再移动
				distance = i - 1;
				break;
			}
		}
	}

	//冲刺速度
	float dodgeSpeed = 1000;
	//冲刺方向
	Vec2 dodgeDirection = Vec2(cos(angle), sin(angle));
	//开始冲刺
	this->runAction(Sequence::create(MoveBy::create(distance / dodgeSpeed, dodgeDirection * distance), CallFunc::create([=] {isDodge = false; }), nullptr));

}

//根据鼠标位置来确定人物朝向
void Player::getPlayerOrientation(Vec2 position)
{
	//计算区域斜率
	//获得角色贴图尺寸
	auto playerSize = this->m_body->getContentSize();
	float k = playerSize.height / playerSize.width;

	//获得屏幕尺寸
	auto visibleSize = Director::getInstance()->getVisibleSize();
	//获得鼠标坐标相对于屏幕的坐标
	Vec2 mouseWorldPosition = position;
	//获得精灵的世界坐标
	Vec2 spriteWorldPosition = this->getPosition();
	auto temp = this->myCamera->getCameraPostionChange();
	spriteWorldPosition = spriteWorldPosition - this->myCamera->getCameraPostionChange()
		+ Vec2(visibleSize.width / 2, visibleSize.height / 2);

	//计算
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

	//播放特效
	Effects* m_weapon_light = Effects::create();
	m_weapon_light->setAnchorPoint(Vec2(0.5, 0));
	//位置在人物身上
	m_weapon_light->setPosition(this->getPosition());
	//绑定到场景
	this->getParent()->addChild(m_weapon_light);
	m_weapon_light->EffectsAnimation(m_weapon_light->saber_normal, 0);


	m_weapon_light->setRotation(this->weaponAngle);//让武器的角度等于鼠标的角度
	//攻击范围
	float attackDistance = 150.0f;
	//攻击速度
	float attackSpeed = 1200.0f;
	//旋转速度
	float rotateSpeed = 700.0f;
	//旋转角度
	float rotateAngle1 = 45;
	float rotateAngle2 = 90;
	//获得角度
	auto currentAngle = (m_weapon->getRotation() / 180) * PI;
	//攻击方向
	Vec2 attackDirection = Vec2(sin(currentAngle), cos(currentAngle));
	//开始攻击
	//武器：挥砍
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
	//延时
	auto delayTime = DelayTime::create(rotateAngle1 / rotateSpeed);
	//剑气：移动
	float length = -150;
	m_weapon_light->setVisible(true);
	//m_weapon_light->setPosition(Vec2(this->getPosition().x + length * sin((weaponAngle / 180) * PI), this->getPosition().y + length * cos((weaponAngle / 180) * PI)));
	auto fadeInAction = FadeIn::create(0.05);//淡入
	auto fadeOutAction = FadeOut::create(0.05);//淡出
	auto moveAction = MoveBy::create(attackDistance / attackSpeed, Vec2(attackDistance * sin((weaponAngle / 180) * PI), attackDistance * cos((weaponAngle / 180) * PI)));//移动函数。起点是当前位置，终点是当前位置加上一个向量
	m_weapon_light->runAction(Sequence::create(delayTime, fadeInAction, moveAction, fadeOutAction, CallFunc::create([=] {isflying = false; }), nullptr));
}

void Player::weaponRotate(Vec2 position)
{
	//获得屏幕尺寸
	auto visibleSize = Director::getInstance()->getVisibleSize();
	//获得鼠标坐标相对于屏幕的坐标
	Vec2 mouseWorldPosition = position;
	//获得武器的世界坐标
	Vec2 spriteWorldPosition = this->getPosition();
	auto temp = this->myCamera->getCameraPostionChange();
	spriteWorldPosition = spriteWorldPosition - this->myCamera->getCameraPostionChange()
		+ Vec2(visibleSize.width / 2, visibleSize.height / 2);
	//计算
	Vec2 mouseLocalPosition = Vec2(mouseWorldPosition.x - spriteWorldPosition.x, mouseWorldPosition.y - spriteWorldPosition.y);

	//计算角度
	float angle = atan2(mouseLocalPosition.x, mouseLocalPosition.y);
	this->weaponAngle = (angle / PI) * 180;
}

void Player::updateWeaponRotation(float dt)
{
	if (!isWeapon)
	{
		m_weapon->setRotation(this->weaponAngle);//让武器的角度等于鼠标的角度
		//	m_weapon_light->setRotation(this->weaponAngle);//让武器的角度等于鼠标的角度
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
	//每帧（0.016秒）恢复0.01点体力
	if (m_stamina < 100)
	{
		m_stamina += 0.15;
	}
	else if (m_stamina > 100)
	{
		m_stamina = 100;
	}
	//所有元素附着效果持续时间减少
	for (int i = 0; i < 8; i++)
	{
		if (m_element[i] > 0)
		{
			m_element[i] -= 0.016;
		}
		//如果还差2秒且其元素附着图标没淡化，让其半透明化
		if (m_element[i] < 2&& m_element[i]>0)
		{
			//检测其Opaqity是否为255，如果是就让其半透明化
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
			//元素附着图标消失
			for (int j = 0; j < 2; j++)
			{
				if (m_element_sprite[j]->isVisible() && m_element_sprite_type[j] == i)
				{
					//透明度恢复
					m_element_sprite[j]->setOpacity(255);
					m_element_sprite[j]->setVisible(false);
					//消失后检测，如果还有没消失的元素附着，就让其显示在正上方
					if (m_element_sprite[1-j]->isVisible())
					{
						m_element_sprite[1 - j]->setPosition(Vec2(0, m_body->getContentSize().height / 3));
					}
				}
			}
			
			
		}
	}
	//技能冷却时间减少
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


	//对状态进行检测
	for (int i = 0; i < 99; i++)
	{
		if (m_statement[i].name != "")
		{
			m_statement[i].time -= 0.016;
			m_statement_time[i] += 0.016;
			//每一秒检测状态
			if (m_statement_time[i] > 1)
			{
				m_statement_time[i] = 0;
				//如果有感电状态
				if (m_statement[i].name == "shock" && m_statement[i].time > 0)
				{
					//触发感电效果
					effectTrigger("shock");
				}
				else if (m_statement[i].name != "" && m_statement[i].time <= 0)
				{
					//如果是超导，减防状态消失
					if (m_statement[i].name == "def_down")
					{
						m_superconductivity = 0;
					}


					m_statement[i].name = "";
					m_statement[i].time = 0;
					//后面所有的状态往前移
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
	//去整个HelloWorldScene遍历所有敌人，如果有就进行AttackHit检测看看有没有打到。敌人的tag是Enemy
	auto scene = this->getParent();
	//查找场景中tag为Enemy的对象，用name标签检索
	//如果没找到
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