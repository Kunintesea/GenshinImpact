#include "Player.h"

/*
关于动作：由m_body上的tag决定，由getNumberOfRunningActionsByTag获取。
1：向左
2：向右
3：向上
4：向下
*/
//伤害计算式：实际伤害=伤害值-防御值*伤害值，若人物处于闪避状态直接返回0
void Player::hurt(int damage,int damge_type,bool reaction)
{ 
	if (isDodge)
	{
		//显示闪避
		for (int i = 0; i < 20; i++)
		{
			if (!m_element_label[i]->isVisible())
			{
				m_element_label[i]->setColor(Color3B::WHITE);
				m_element_label[i]->setPosition(Vec2(this->getPositionX() + m_body->getContentSize().width / 3 + rand() % 50, this->getPositionY() + m_body->getContentSize().height / 3 + rand() % 50));
				m_element_label[i]->setString("Dodge");
				m_element_label[i]->setVisible(true);
				m_element_label[i]->runAction(Sequence::create(MoveBy::create(0.1, Vec2(0, 20)), nullptr));
				m_element_label[i]->runAction(Sequence::create(DelayTime::create(1.5), CallFunc::create([=] {m_element_label[i]->setVisible(false); }), MoveBy::create(0.1, Vec2(0, -20)), nullptr));

				break;
			}
		}
		return;
	}
	else
	{
		if (reaction)
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
				if (m_element[Fire] > 0)
				{

					//把火或雷元素附着图标消失
					for (int i = 0; i < 2; i++)
					{
						if (m_element_sprite[i]->isVisible()&&(m_element_sprite_type[i]==Fire || m_element_sprite_type[i] == Thunder))
						{
							m_element_sprite[i]->setVisible(false);
						}
					}


					//超载效果
					//造成火元素伤害
					hurt(5, Fire,false);


					//火元素消失
					m_element[Fire] = 0;
					m_element[Thunder] = 0;

					//播放超载特效
					Effects* effect = Effects::create();
					//位置在人物身上
					effect->setPosition(this->getPosition());
					//绑定到场景
					this->getParent()->addChild(effect);
				
					//播放超载特效
					effect->EffectsAnimation(effect->Explode, 0);

					//显示超载效果
					for (int i = 0; i < 20; i++)
					{
						if (!m_element_label[i]->isVisible())
						{
							m_element_label[i]->setColor(Color3B(249, 85, 9));
							m_element_label[i]->setPosition(Vec2(this->getPositionX() + m_body->getContentSize().width / 3 + rand() % 50, this->getPositionY() + m_body->getContentSize().height / 3+ rand() % 50));
							m_element_label[i]->setString("Explode");
							m_element_label[i]->setVisible(true);
							m_element_label[i]->runAction(Sequence::create(MoveBy::create(0.1, Vec2(0, 20)), nullptr));
							m_element_label[i]->runAction(Sequence::create(DelayTime::create(1.5), CallFunc::create([=] {m_element_label[i]->setVisible(false); }), MoveBy::create(0.1, Vec2(0, -20)), nullptr));

							break;
						}
					}
				}
				else if (m_element[Ice] > 0)
				{
					//超导效果
					//造成冰元素伤害
					hurt(5, Ice, false);


					//把冰或雷元素附着图标消失
					for (int i = 0; i < 2; i++)
					{
						if (m_element_sprite[i]->isVisible() && (m_element_sprite_type[i] == Ice || m_element_sprite_type[i] == Thunder))
						{
							m_element_sprite[i]->setVisible(false);
						}
					}
					//雷元素消失
					m_element[Thunder] = 0;
					m_element[Ice] = 0;

					//播放超载特效
					Effects* effect = Effects::create();
					//放大2倍
					effect->setScale(2);
					//位置在人物身上
					effect->setPosition(this->getPosition());
					//绑定到场景
					this->getParent()->addChild(effect);
					//播放超载特效
					effect->EffectsAnimation(effect->Superconducting, 0);

					//显示超载效果
					for (int i = 0; i < 20; i++)
					{
						if (!m_element_label[i]->isVisible())
						{
							m_element_label[i]->setColor(Color3B(198, 244, 243));
							m_element_label[i]->setPosition(Vec2(this->getPositionX() + m_body->getContentSize().width / 3 + rand() % 50, this->getPositionY() + m_body->getContentSize().height / 3 + rand() % 50));
							m_element_label[i]->setString("Superconducting");
							m_element_label[i]->setVisible(true);
							m_element_label[i]->runAction(Sequence::create(MoveBy::create(0.1, Vec2(0, 20)), nullptr));
							m_element_label[i]->runAction(Sequence::create(DelayTime::create(1.5), CallFunc::create([=] {m_element_label[i]->setVisible(false); }), MoveBy::create(0.1, Vec2(0, -20)), nullptr));

							break;
						}
					}
				}
				else if (m_element[Water] > 0)
				{
					//造成雷元素伤害
					hurt(2, Thunder, false);
					m_element[Thunder] = 5;

					//把水或雷元素附着图标消失
					for (int i = 0; i < 2; i++)
					{
						if (m_element_sprite[i]->isVisible() && (m_element_sprite_type[i] == Water || m_element_sprite_type[i] == Thunder))
						{
							m_element_sprite[i]->setVisible(false);
						}
					}
					//雷元素消失
					m_element[Thunder] = 0;
					m_element[Water] = 0;



					//播放特效
					Effects* effect = Effects::create();
					//放大2倍
					effect->setScale(2);
					//位置在人物身上
					effect->setPosition(this->getPosition());
					//绑定到场景
					this->getParent()->addChild(effect);
					effect->EffectsAnimation(effect->Superconducting, 0);

					//显示效果
					for (int i = 0; i < 20; i++)
					{
						if (!m_element_label[i]->isVisible())
						{
							m_element_label[i]->setColor(Color3B(198, 244, 243));
							m_element_label[i]->setPosition(Vec2(this->getPositionX() + m_body->getContentSize().width / 3 + rand() % 50, this->getPositionY() + m_body->getContentSize().height / 3 + rand() % 50));
							m_element_label[i]->setString("Shokced");
							m_element_label[i]->setVisible(true);
							m_element_label[i]->runAction(Sequence::create(MoveBy::create(0.1, Vec2(0, 20)), nullptr));
							m_element_label[i]->runAction(Sequence::create(DelayTime::create(1.5), CallFunc::create([=] {m_element_label[i]->setVisible(false); }), MoveBy::create(0.1, Vec2(0, -20)), nullptr));

							break;
						}
					}
					//进入感电状态。在m_statement这个vector中查找，如果找到了shock就让持续时间变成5，否则就添加shock
					//auto it = find(m_statement.begin(), m_statement.end(), "shock");
					//if (it != m_statement.end())
					//{
					//	m_statement[it - m_statement.begin()].time = 5;
					//}
					//else
					//{
					//	statement temp;
					//	temp.name = "shock";
					//	temp.time = 5;
					//	m_statement.push_back(temp);
					//}



				}
				else
				{
					if (m_element[Thunder] == 0)
					{
						//设置元素附着
						setElementSprite(damge_type);
					}
					m_element[Thunder] = 5;
				}
				break;
			case Grass:
				if (m_element[Grass] == 0)
				{
					//设置元素附着
					setElementSprite(damge_type);
				}
				m_element[Grass] = 5;
				break;
			case Water:
				if (m_element[Water] == 0)
				{
					//设置元素附着
					setElementSprite(damge_type);
				}
				m_element[Water] = 5;
				break;
			case Fire:
				if (m_element[Thunder] > 0)
				{
					//超载效果
					//造成火元素伤害
					hurt(5, Fire, false);

					//把火或雷元素附着图标消失
					for (int i = 0; i < 2; i++)
					{
						if (m_element_sprite[i]->isVisible() && (m_element_sprite_type[i] == Fire || m_element_sprite_type[i] == Thunder))
						{
							m_element_sprite[i]->setVisible(false);
						}
					}
					//火元素消失
					m_element[Fire] = 0;
					m_element[Thunder] = 0;

					//播放超载特效
					Effects* effect = Effects::create();
					//位置在人物身上
					effect->setPosition(this->getPosition());
					//绑定到场景
					this->getParent()->addChild(effect);
					//播放超载特效
					effect->EffectsAnimation(effect->Explode, 0);

					//显示超载效果
					for (int i = 0; i < 20; i++)
					{
						if (!m_element_label[i]->isVisible())
						{
							m_element_label[i]->setColor(Color3B(249, 85, 9));
							m_element_label[i]->setPosition(Vec2(this->getPositionX() + m_body->getContentSize().width / 3 + rand() % 50, this->getPositionY() + m_body->getContentSize().height / 3 + rand() % 50));
							m_element_label[i]->setString("Explode");
							m_element_label[i]->setVisible(true);
							m_element_label[i]->runAction(Sequence::create(MoveBy::create(0.1, Vec2(0, 20)), nullptr));
							m_element_label[i]->runAction(Sequence::create(DelayTime::create(1.5), CallFunc::create([=] {m_element_label[i]->setVisible(false); }), MoveBy::create(0.1, Vec2(0, -20)), nullptr));

							break;
						}
					}
				}
				else
				{
					if (m_element[Fire] == 0)
					{
						//设置元素附着
						setElementSprite(damge_type);
					}
					m_element[Fire] = 5;
				}
				break;
			case Ice:
				if (m_element[Thunder] > 0)
				{
					//超导效果
					//造成冰元素伤害
					hurt(5, Ice, false);

					//把冰或雷元素附着图标消失
					for (int i = 0; i < 2; i++)
					{
						if (m_element_sprite[i]->isVisible() && (m_element_sprite_type[i] == Ice || m_element_sprite_type[i] == Thunder))
						{
							m_element_sprite[i]->setVisible(false);
						}
					}
					//雷元素消失
					m_element[Thunder] = 0;
					m_element[Ice] = 0;

					//播放超载特效
					Effects* effect = Effects::create();
					//放大2倍
					effect->setScale(2);
					//位置在人物身上
					effect->setPosition(this->getPosition());
					//绑定到场景
					this->getParent()->addChild(effect);
					//播放超载特效
					effect->EffectsAnimation(effect->Superconducting, 0);

					//显示超载效果
					for (int i = 0; i < 20; i++)
					{
						if (!m_element_label[i]->isVisible())
						{
							m_element_label[i]->setColor(Color3B(198, 244, 243));
							m_element_label[i]->setPosition(Vec2(this->getPositionX() + m_body->getContentSize().width / 3 + rand() % 50, this->getPositionY() + m_body->getContentSize().height / 3 + rand() % 50));
							m_element_label[i]->setString("Superconducting");
							m_element_label[i]->setVisible(true);
							m_element_label[i]->runAction(Sequence::create(MoveBy::create(0.1, Vec2(0, 20)), nullptr));
							m_element_label[i]->runAction(Sequence::create(DelayTime::create(1.5), CallFunc::create([=] {m_element_label[i]->setVisible(false); }), MoveBy::create(0.1, Vec2(0, -20)), nullptr));

							break;
						}
					}
				}
				else
				{
					if (m_element[Ice] == 0)
					{
						//设置元素附着
						setElementSprite(damge_type);
					}
					m_element[Ice] = 5;
				}


				break;
			default:
				break;
			}
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





				
				m_damage_label[i]->setPosition(Vec2(this->getPositionX () - m_body->getContentSize().width /6+ rand() % 70, this->getPositionY() - m_body->getContentSize().height / 6 + rand() % 70));//rand()的使用方法是rand()%n，表示生成一个0到n-1的随机数
				m_damage_label[i]->setVisible(true);
				//向上浮现
				m_damage_label[i]->runAction(Sequence::create(MoveBy::create(0.1, Vec2(0, 20)), nullptr));//创建一个动作序列，让伤害数字向上浮现，持续0.1秒
				//1.5秒后先让m_damage_label[i]不可见，不可见后向下移动20个像素
				m_damage_label[i]->runAction(Sequence::create(DelayTime::create(1.5), CallFunc::create([=] {m_damage_label[i]->setVisible(false); }), MoveBy::create(0.1, Vec2(0, -20)), nullptr));


				m_damage_label[i]->setString(std::to_string(real_damage));
				break;
			}
		}
		//先扣护盾
		if (m_shield > 0)
		{
			if (m_shield >= real_damage)
			{
				m_shield -= real_damage;
				real_damage = 0;
			}
			else
			{
				real_damage -= m_shield;
				m_shield = 0;
			}
		}

		m_hp -= real_damage;
		if (m_hp <= 0)
		{
			isDead = true;
			m_hp = 0;
		}

		//用setColor让人物RGB变红，一秒后恢复
		m_body->setColor(Color3B::RED);
		m_head->setColor(Color3B::RED);
		this->runAction(Sequence::create(DelayTime::create(0.1), CallFunc::create([=] {m_body->setColor(Color3B::WHITE); m_head->setColor(Color3B::WHITE); }), nullptr));


	}
}

//void Player::effectTrigger(std::string effect_type)
//{
//	if (effect_type == "感电")
//	{
//		hurt(2, Thunder, false);
//		//播放特效
//		Effects* effect = Effects::create();
//		//放大2倍
//		effect->setScale(2);
//		//位置在人物身上
//		effect->setPosition(this->getPosition());
//		//绑定到场景
//		this->getParent()->addChild(effect);
//		effect->EffectsAnimation(effect->Superconducting, 0);
//
//		//显示效果
//		for (int i = 0; i < 20; i++)
//		{
//			if (!m_element_label[i]->isVisible())
//			{
//				m_element_label[i]->setColor(Color3B(198, 244, 243));
//				m_element_label[i]->setPosition(Vec2(this->getPositionX() + m_body->getContentSize().width / 3 + rand() % 50, this->getPositionY() + m_body->getContentSize().height / 3 + rand() % 50));
//				m_element_label[i]->setString("Shokced");
//				m_element_label[i]->setVisible(true);
//				m_element_label[i]->runAction(Sequence::create(MoveBy::create(0.1, Vec2(0, 20)), nullptr));
//				m_element_label[i]->runAction(Sequence::create(DelayTime::create(1.5), CallFunc::create([=] {m_element_label[i]->setVisible(false); }), MoveBy::create(0.1, Vec2(0, -20)), nullptr));
//
//				break;
//			}
//		}
//	}
//}

void Player::setElementSprite(int elemtype)
{
	//查找当前是否有元素附着，如果有就考虑是否反应的问题
	//先看0号位是否有元素附着，没有就直接附着
	if (!m_element_sprite[0]->isVisible())
	{
		//透明度恢复
		m_element_sprite[0]->setOpacity(255);
		m_element_sprite[0]->setVisible(true);
		//设置元素附着的位置
		m_element_sprite[0]->setPosition(Vec2(0,  m_body->getContentSize().height / 3));
		//设置元素附着的图片
		m_element_sprite_type[0] = elemtype;
		switch (elemtype)
		{
		case Wind:
			m_element_sprite[0]->setTexture("Effects/Element/Wind.png");
			break;
		case Rock:
			m_element_sprite[0]->setTexture("Effects/Element/Rock.png");
			break;
		case Thunder:
			m_element_sprite[0]->setTexture("Effects/Element/Thunder.png");
			break;
		case Grass:
			m_element_sprite[0]->setTexture("Effects/Element/Grass.png");
			break;
		case Water:
			m_element_sprite[0]->setTexture("Effects/Element/Water.png");
			break;
		case Fire:
			m_element_sprite[0]->setTexture("Effects/Element/Fire.png");
			break;
		case Ice:
			m_element_sprite[0]->setTexture("Effects/Element/Ice.png");
			break;
		default:
			break;
		}
	}
	//否则，前提是0和1号的元素附着不一样
	else 
	{

		//先把0号图片设置到正上方的左侧
		m_element_sprite[0]->setPosition(Vec2( - 20,  m_body->getContentSize().height / 3));
		//再把1号图片设置到正上方的右侧
		m_element_sprite[1]->setVisible(true);
		m_element_sprite[1]->setPosition(Vec2( 20, m_body->getContentSize().height / 3));



		//透明度恢复
		m_element_sprite[1]->setOpacity(255);
		m_element_sprite_type[1] = elemtype;
		//设置元素附着的图片
		switch (elemtype)
		{
		case Wind:
			m_element_sprite[1]->setTexture("Effects/Element/Wind.png");
			break;
		case Rock:
			m_element_sprite[1]->setTexture("Effects/Element/Rock.png");
			break;
		case Thunder:
			m_element_sprite[1]->setTexture("Effects/Element/Thunder.png");
			break;
		case Grass:
			m_element_sprite[1]->setTexture("Effects/Element/Grass.png");
			break;
		case Water:
			m_element_sprite[1]->setTexture("Effects/Element/Water.png");
			break;
		case Fire:
			m_element_sprite[1]->setTexture("Effects/Element/Fire.png");
			break;
		case Ice:
			m_element_sprite[1]->setTexture("Effects/Element/Ice.png");
			break;
		default:
			break;
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
	m_body = Sprite::create("Me/Saber/Walk/front.png");
	//将精灵添加到节点
	this->addChild(m_body);

	Sprite* cameraSprite = Sprite::create("HelloWorld.png");
	cameraSprite->setOpacity(100);
	float X = 80 / cameraSprite->getContentSize().width;
	float Y = 80 / cameraSprite->getContentSize().height;

	cameraSprite->setScaleX(X);
	cameraSprite->setScaleY(Y);
	this->addChild(cameraSprite);

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
	m_weapon_light = Sprite::create("Me/Saber/Weapon/sword_light.png");
	m_weapon_light->setAnchorPoint(Vec2(0.5, 0));
	m_weapon_light->setVisible(false);  // 隐藏精灵
	this->addChild(m_weapon_light);

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
		    mapManager* map = (mapManager*) this->getParent()->getChildByName("mapManager");
		    // 发生了碰撞
		    if ( map->isCollision(nextPosition + Vec2(-40,-40))
			 || map->isCollision(nextPosition + Vec2(-40, 40))
			  || map->isCollision(nextPosition + Vec2(-40, -20))
			   || map->isCollision(nextPosition + Vec2(-40, 20)) )
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
		    mapManager* map = (mapManager*) this->getParent()->getChildByName("mapManager");
		    // 发生了碰撞
		    if (map->isCollision(nextPosition + Vec2(40, -40))
			  || map->isCollision(nextPosition + Vec2(40, 40))
			  || map->isCollision(nextPosition + Vec2(40, -20))
			  || map->isCollision(nextPosition + Vec2(40, 20)) )
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
		    mapManager* map = (mapManager*) this->getParent()->getChildByName("mapManager");
		    // 发生了碰撞
		    if (map->isCollision(nextPosition + Vec2(-40, 40))
			  || map->isCollision(nextPosition + Vec2(40, 40))
			  || map->isCollision(nextPosition + Vec2(-20, 40))
			  || map->isCollision(nextPosition + Vec2(20, 40)) )
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
		    mapManager* map = (mapManager*) this->getParent()->getChildByName("mapManager");
		    // 发生了碰撞
		    if (map->isCollision(nextPosition + Vec2(-40, -40))
			  || map->isCollision(nextPosition + Vec2(40, -40))
			  || map->isCollision(nextPosition + Vec2(-20, -40))
			  || map->isCollision(nextPosition + Vec2(20, -40)) )
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
	if (cos(angle) >= 0 && sin(angle) >= 0){
	      for (int i = 1; i <= distance; ++ i) {
		    Vec2 nextPosition = this->getPosition() + Vec2(i * cos(angle), i * sin(angle));
		    // 获取到地图管理器
		    mapManager * map = (mapManager*)this->getParent()->getChildByName("mapManager");
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
		    mapManager * map = (mapManager*)this->getParent()->getChildByName("mapManager");
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
	else if (cos(angle) < 0 && sin(angle) >= 0){
	      for (int i = 1; i <= distance; ++i) {
		    Vec2 nextPosition = this->getPosition() + Vec2(i * cos(angle), i * sin(angle));
		    // 获取到地图管理器
		    mapManager * map = (mapManager*)this->getParent()->getChildByName("mapManager");
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
	m_weapon_light->setPosition(Vec2(weaponPosition.x + length * sin((weaponAngle / 180) * PI), weaponPosition.y + length * cos((weaponAngle / 180) * PI)));
	auto fadeInAction = FadeIn::create(0.05);
	auto fadeOutAction = FadeOut::create(0.05);
	auto moveAction = MoveBy::create(attackDistance / attackSpeed, Vec2(attackDistance * sin((weaponAngle / 180) * PI), attackDistance * cos((weaponAngle / 180) * PI)));
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
		m_weapon->setRotation(this->weaponAngle);
		m_weapon_light->setRotation(this->weaponAngle);
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

float m_time = 0;
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


	//每一秒检测一次状态m_statement这个vector，如果遇到感电就触发感电效果

	//每一秒检测
	//m_time += 0.016;
	//if (m_time > 1)
	//{
	//	m_time = 0;
	//	//检测状态
	//	if (m_statement.size() > 0)
	//	{
	//		for (int i = 0; i < m_statement.size(); i++)
	//		{
	//			if (m_statement[i].name == "感电")
	//			{
	//				effectTrigger("感电");
	//			}
	//		}
	//		m_statement.clear();
	//	}
	//}


	


}

bool Player::testCol(Sprite* other)
{
	//获取玩家精灵和目标精灵的包围盒
	Rect playerRect = this->getBoundingBox();
	Rect targetRect = other->getBoundingBox();


	// 检测两个精灵的包围盒是否相交
	if (playerRect.intersectsRect(targetRect))
	{

		CCLOG("Collision detected!");
		// 执行碰撞后的逻辑
		log("Collision detected!");
		return true;
	}

	return false;
}
