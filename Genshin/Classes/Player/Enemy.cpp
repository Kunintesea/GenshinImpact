#include "Enemy.h"




bool Enemy::init()
{
	if (!Node::init())
	{
		return false;
	}
	//加入调度器
	this->scheduleUpdate();//调度器，每帧调用一次update函数


	//创建精灵
	m_body = Sprite::create("Enemy/Bat_Fire/up_1.png");
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



	//角色血条
	//创建一个血条
	Enemy_hpBar = ProgressTimer::create(Sprite::create("Me/InfoUI/hp_bar.png"));
	Enemy_hpBar_bg = Sprite::create("Me/InfoUI/hp_bar_bg.png");
	//设置血条的类型为条形
	Enemy_hpBar->setType(ProgressTimer::Type::BAR);
	//设置血条的起点，从左往右
	Enemy_hpBar->setMidpoint(Vec2(0, 0.5));//传入两个参数，0表示x轴，0.5表示y轴，表示血条的起点在左边中间
	//设置血条的变化率
	Enemy_hpBar->setBarChangeRate(Vec2(1, 0));
	//设置血条的大小，长宽分别是200，30
	Enemy_hpBar->setScaleX(100 / Enemy_hpBar->getContentSize().width);
	Enemy_hpBar->setScaleY(10 / Enemy_hpBar->getContentSize().height);
	Enemy_hpBar_bg->setScaleX(100 / Enemy_hpBar_bg->getContentSize().width);
	Enemy_hpBar_bg->setScaleY(10 / Enemy_hpBar_bg->getContentSize().height);
	//设置血条的位置，就在人物头顶
	Enemy_hpBar->setPosition(Vec2(0, this->getPositionY() + m_body->getContentSize().height));
	Enemy_hpBar_bg->setPosition(Vec2(0, this->getPositionY() + m_body->getContentSize().height ));


	this->addChild(Enemy_hpBar_bg);//将血条背景添加到节点
	this->addChild(Enemy_hpBar);//将滑血条添加到节点

	//血条标签
	Enemy_hpLabel = Label::createWithTTF("100/100", "fonts/Marker Felt.ttf", 12);//设置内容为“100/100”，字体为“Marker Felt”，大小为24
	//加入黑色描边
	Enemy_hpLabel->enableOutline(Color4B::BLACK, 2);
	//设置位置，与血条的位置一样
	Enemy_hpLabel->setPosition(Vec2(0, this->getPositionY() + m_body->getContentSize().height));
	this->addChild(Enemy_hpLabel);//将血量标签添加到节点




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

	// 加载动画
	Size bodySize = m_body->getContentSize();
	//运动动画帧
	//"D:\Github_Document\GenshinImpact\Genshin\Resources\Enemy\Bat_Fire\up_1.png"
	SpriteFrame* up_1 = SpriteFrame::create("Enemy/Bat_Fire/up_1.png", Rect(0, 0, bodySize.width, bodySize.height));
	SpriteFrame* up_2 = SpriteFrame::create("Enemy/Bat_Fire/up_2.png", Rect(0, 0, bodySize.width, bodySize.height));
	walk_up.pushBack(up_1);
	walk_up.pushBack(up_2);
	SpriteFrame* down_1 = SpriteFrame::create("Enemy/Bat_Fire/down_1.png", Rect(0, 0, bodySize.width, bodySize.height));
	SpriteFrame* down_2 = SpriteFrame::create("Enemy/Bat_Fire/down_2.png", Rect(0, 0, bodySize.width, bodySize.height));
	walk_down.pushBack(down_1);
	walk_down.pushBack(down_2);
	SpriteFrame* left_1 = SpriteFrame::create("Enemy/Bat_Fire/left_1.png", Rect(0, 0, bodySize.width, bodySize.height));
	SpriteFrame* left_2 = SpriteFrame::create("Enemy/Bat_Fire/left_2.png", Rect(0, 0, bodySize.width, bodySize.height));
	walk_left.pushBack(left_1);
	walk_left.pushBack(left_2);
	SpriteFrame* right_1 = SpriteFrame::create("Enemy/Bat_Fire/right_1.png", Rect(0, 0, bodySize.width, bodySize.height));
	SpriteFrame* right_2 = SpriteFrame::create("Enemy/Bat_Fire/right_2.png", Rect(0, 0, bodySize.width, bodySize.height));
	walk_right.pushBack(right_1);
	walk_right.pushBack(right_2);

	//加入调度器

	return true;

}


void Enemy::update(float t)
{
	walktime += 0.016;//每帧增加0.016



	//每3秒随机往一个方向移动
	if (walktime >= 1)
	{
		walktime = 0;
		//获取场景的时间，即Enemy的父节点，从而生成种子以生成随机数




		srand(time(NULL));
		//实现一个真正随机的int随机数
		int direction = rand() % 4;


		switch (direction)
		{
		case 0:

			//移动，用moveBy函数，移动到一个点
			this->runAction(MoveBy::create(1, Vec2(0, 50)));

			//动画
			moveAnimation(walk_up, 4);
			break;
		case 1:
			this->runAction(MoveBy::create(1, Vec2(0, -50)));
			moveAnimation(walk_down, 3);
			break;
		case 2:
			this->runAction(MoveBy::create(1, Vec2(-50, 0)));
			moveAnimation(walk_left, 2);
			break;
		case 3:
			this->runAction(MoveBy::create(1, Vec2(50, 0)));
			moveAnimation(walk_right, 1);
			break;
		}
		
	}


	//更新血条
	Enemy_hpBar->setPercentage(float(m_hp) / float(m_max_hp) * 100);
	//更新血量
	Enemy_hpLabel->setString(std::to_string(m_hp) + "/"+ std::to_string(m_max_hp));

}