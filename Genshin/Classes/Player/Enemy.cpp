#include "Enemy.h"
//#include "HelloWorldScene.h"



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


	}


	//数值初始化




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








	//加入调度器

	return true;

}

float tttime;
void Enemy::update(float t)
{
	walktime += 0.016;//每帧增加0.016
	tttime += 0.016;

	//E技能冷却
	if (m_E_CD > 0)
	{
		m_E_CD -= 0.016;
	}
	else if (m_E_CD < 0)
	{
		m_E_CD = 0;
	}
	//Q技能冷却
	if (m_Q_CD > 0)
	{
		m_Q_CD -= 0.016;
	}
	else if (m_Q_CD < 0)
	{
		m_Q_CD = 0;
	}
	//1技能冷却
	if (m_1_CD > 0)
	{
		m_1_CD -= 0.016;
	}
	else if (m_1_CD < 0)
	{
		m_1_CD = 0;
	}


	//更新血条
	Enemy_hpBar->setPercentage(float(m_hp) / float(m_max_hp) * 100);
	//更新血量
	Enemy_hpLabel->setString(std::to_string(m_hp) + "/" + std::to_string(m_max_hp));
	

	//每秒随机往一个方向移动
	if (walktime >= 1&&leisure)
	{
		walktime = 0;

		//有规律地上下左右移动，每次的移动由direction决定
		if (direction == 0)
		{
			//移动，用moveBy函数，移动到一个点
			this->runAction(MoveBy::create(1, Vec2(0, 50)));
			//动画
			moveAnimation(walk_up, 4);
			direction = 3;
		}
		else if (direction == 1)
		{
			this->runAction(MoveBy::create(1, Vec2(0, -50)));
			moveAnimation(walk_down, 3);
			direction = 2;
		}
		else if (direction == 2)
		{
			this->runAction(MoveBy::create(1, Vec2(-50, 0)));
			moveAnimation(walk_left, 2);
			direction =0;	
		}
		else if (direction == 3)
		{
			this->runAction(MoveBy::create(1, Vec2(50, 0)));
			moveAnimation(walk_right, 1);
			direction = 1;
		}




		//srand(time(NULL));
		////实现一个真正随机的int随机数
		//int direction = rand() % 4;


		//switch (direction)
		//{
		//case 0:

		//	//移动，用moveBy函数，移动到一个点
		//	this->runAction(MoveBy::create(1, Vec2(0, 50)));

		//	//动画
		//	moveAnimation(walk_up, 4);
		//	break;
		//case 1:
		//	this->runAction(MoveBy::create(1, Vec2(0, -50)));
		//	moveAnimation(walk_down, 3);
		//	break;
		//case 2:
		//	this->runAction(MoveBy::create(1, Vec2(-50, 0)));
		//	moveAnimation(walk_left, 2);
		//	break;
		//case 3:
		//	this->runAction(MoveBy::create(1, Vec2(50, 0)));
		//	moveAnimation(walk_right, 1);
		//	break;
		//}
		
	}
	else if (!leisure)
	{
		//从地图上获取玩家的位置
		auto player = this->getParent()->getChildByName("Me");
		//没获取到直接返回
		if (player == nullptr)
		{
			return;
		}
		//获取玩家的位置
		Vec2 playerPosition = player->getPosition();



		//如果是地狱犬
		if (m_name == "HellDog")
		{


			//只要Q好了就放Q
			if (m_Q_CD <= 0)
			{

				//朝着玩家冲刺
				//锁定位置直接冲刺
				//冲刺速度
				float dodgeSpeed = 1000;
				//冲刺距离
				float distance = 500;
				//冲刺方向
				Vec2 dodgeDirection = playerPosition - this->getPosition();
				//冲刺方向单位化
				dodgeDirection.normalize();
				//开始冲刺
				this->runAction(Sequence::create(MoveBy::create(distance / dodgeSpeed, dodgeDirection* distance), CallFunc::create([=] {leisure = true; }), nullptr));

				//创建一个特效
				Effects* effect = Effects::create();
				//位置在人物身上
				effect->setPosition(this->getPosition());
				//绑定到场景
				this->getParent()->addChild(effect);
				//damage_type为火
				effect->damage_type = Thunder;
				//倍率翻倍damage_rate
				effect->damage_rate = 4;
				//加入m_effect数组
				for (int i = 0;i < 20;i++)
				{
					if (m_effect[i] == nullptr)
					{
						m_effect[i] = effect;
						//设置其数字标签为i
						effect->setTag(i);
						for (int j = 0; j < 20; j++)
						{
							m_effect_index[i][j] = 1;
						}
						break;
					}
				}
				effect->EffectsAnimation(effect->HellDog_q_explosion, 0);
				//执行上述动作后把节点移除，并且把数组对应位置（通过tag获取）置空
				//auto removeSelf = CallFunc::create([=] {m_weapon_light->setVisible(false); m_effect[m_weapon_light->getTag()] = nullptr; });
				effect->runAction(Sequence::create(DelayTime::create(0.8), CallFunc::create([=] {effect->removeFromParent(); m_effect[effect->getTag()] = nullptr; }), nullptr));
				//Q技能冷却时间
				m_Q_CD =8;


			}


			//如果距离玩家超过300，在原地释放技能
			if (playerPosition.getDistance(this->getPosition()) > 300&& m_E_CD <= 0)
			{
				//先在玩家位置创建一个预警图标，2秒后释放技能
				



				//创建一个预警图标
				Sprite* warning = Sprite::create("Effects/Warning.png");
				//设置位置
				warning->setPosition(playerPosition);
				//绑定到场景，图层在50
				this->getParent()->addChild(warning, 50);

				warning->runAction(Sequence::create(DelayTime::create(0.5), CallFunc::create([=] {warning->removeFromParent(); }), nullptr));

				//以下内容延时1秒执行
				//延时
				this->runAction(Sequence::create(DelayTime::create(0.5), CallFunc::create([=] {
					//创建一个特效
					Effects* effect = Effects::create();
					//位置在人物身上
					effect->setPosition(playerPosition);
					//绑定到场景
					this->getParent()->addChild(effect);
					//damage_type为火
					effect->damage_type = Fire;
					//倍率翻倍damage_rate
					effect->damage_rate = 2;
					//加入m_effect数组
					for (int i = 0;i < 20;i++)
					{
						if (m_effect[i] == nullptr)
						{
							m_effect[i] = effect;
							//设置其数字标签为i
							effect->setTag(i);
							for (int j = 0; j < 20; j++)
							{
								m_effect_index[i][j] = 1;
							}
							break;
						}
					}
					effect->EffectsAnimation(effect->HellDog_explosion, 0);
					//执行上述动作后把节点移除，并且把数组对应位置（通过tag获取）置空
					//auto removeSelf = CallFunc::create([=] {m_weapon_light->setVisible(false); m_effect[m_weapon_light->getTag()] = nullptr; });
					effect->runAction(Sequence::create(DelayTime::create(1), CallFunc::create([=] {effect->removeFromParent(); m_effect[effect->getTag()] = nullptr; }), nullptr));
						}), nullptr));

			

				//E技能冷却时间
				m_E_CD = 0.5;



				//技能释放完后，回到原地
				leisure = true;
			}
			else
			{

				//检测要往哪个方向移动
				//如果玩家在上方
				if (playerPosition.y > this->getPositionY() + 200)
				{
					//动画
					moveAnimation(walk_up, 4);
					//重设碰撞箱大小，等于动画第一帧walk_up.at(0);getBoundingBox()
					//this->setBoundingBox(walk_up.at(0)->getBoundingBox());



				}
				//如果玩家在下方
				else if (playerPosition.y < this->getPositionY() - 200)
				{
					//动画
					moveAnimation(walk_down, 3);
					log("down");
				}
				//如果玩家在左方
				else if (playerPosition.x < this->getPositionX())
				{
					//动画
					moveAnimation(walk_left, 2);
					log("left");
				}
				//如果玩家在右方
				else if (playerPosition.x > this->getPositionX())
				{
					//动画
					moveAnimation(walk_right, 1);

					//log
					log("right");
				}
				//往玩家的方向移动，每次移动50
				//方向
				Vec2 direction = playerPosition - this->getPosition();
				//单位化
				direction.normalize();
				//移动
				this->runAction(MoveBy::create(1, direction * getSpeed()));//1是时间，指的是1秒，direction是方向，*10是速度
			}
		}
		else
		{

			//检测要往哪个方向移动
			//如果玩家在上方
			if (playerPosition.y > this->getPositionY() + 200)
			{
				//动画
				moveAnimation(walk_up, 4);
				//重设碰撞箱大小，等于动画第一帧walk_up.at(0);getBoundingBox()
				//this->setBoundingBox(walk_up.at(0)->getBoundingBox());



			}
			//如果玩家在下方
			else if (playerPosition.y < this->getPositionY() - 200)
			{
				//动画
				moveAnimation(walk_down, 3);
				log("down");
			}
			//如果玩家在左方
			else if (playerPosition.x < this->getPositionX())
			{
				//动画
				moveAnimation(walk_left, 2);
				log("left");
			}
			//如果玩家在右方
			else if (playerPosition.x > this->getPositionX())
			{
				//动画
				moveAnimation(walk_right, 1);

				//log
				log("right");
			}
			//往玩家的方向移动，每次移动50
			//方向
			Vec2 direction = playerPosition - this->getPosition();
			//单位化
			direction.normalize();
			//移动
			this->runAction(MoveBy::create(1, direction * getSpeed()));//1是时间，指的是1秒，direction是方向，*10是速度
			}



		//移动到玩家的位置



	}

	//身体碰撞
	if (m_effect[0])
	{
		//让判定框始终跟着身体走，再绑定到场景
		m_effect[0]->setPosition(this->getPosition());
		//每过1秒让m_effect_count[0]回到1
		if (tttime >= 1)
		{
			tttime = 0;
			for (int i = 0;i < 20; i++)
			{
				m_effect_index[0][i] = 1;
			}
		}

	}



}