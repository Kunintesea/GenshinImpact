#include "BasePlayer.h"

void BasePlayer::moveAnimation(Vector<SpriteFrame*> frame, int actionTag) {
	//动画
	if (m_body->getActionByTag(actionTag) == 0)
	{
		m_body->stopAllActions();//停止所有动作
		auto action = RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(frame, 0.2f))); // 导入动画帧
		action->setTag(actionTag);//设置标签
		m_body->runAction((action));//执行这个动画
	}
}

//攻击判定函数，在有某个人进行了攻击时候调用，参数有两个，一个是攻击者，一个是被攻击者
bool BasePlayer::PlayerAttack(Sprite* me, Sprite* other)
{
	//获取玩家精灵和目标精灵的包围盒
	Rect playerRect = me->getBoundingBox();
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


//伤害计算式：实际伤害=伤害值-防御值*伤害值，若人物处于闪避状态直接返回0
void BasePlayer::hurt(int damage, int damge_type, bool reaction)
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
						if (m_element_sprite[i]->isVisible() && (m_element_sprite_type[i] == Fire || m_element_sprite_type[i] == Thunder))
						{
							m_element_sprite[i]->setOpacity(255);
							m_element_sprite[i]->setVisible(false);
							//消失后检测，如果还有没消失的元素附着，就让其显示在正上方
							if (m_element_sprite[1 - i]->isVisible())
							{
								m_element_sprite[1 - i]->setPosition(Vec2(0, m_body->getContentSize().height / 3));
							}
						}
					}

					//超载效果
					//造成火元素伤害
					hurt(5, Fire, false);


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
				else if (m_element[Ice] > 0)
				{
					//超导效果
					//造成冰元素伤害
					hurt(5, Ice, false);
					m_superconductivity = -0.2;//超导下防御下降20%


					//把冰或雷元素附着图标消失
					for (int i = 0; i < 2; i++)
					{
						if (m_element_sprite[i]->isVisible() && (m_element_sprite_type[i] == Ice || m_element_sprite_type[i] == Thunder))
						{
							m_element_sprite[i]->setOpacity(255);
							m_element_sprite[i]->setVisible(false);
							//消失后检测，如果还有没消失的元素附着，就让其显示在正上方
							if (m_element_sprite[1 - i]->isVisible())
							{
								m_element_sprite[1 - i]->setPosition(Vec2(0, m_body->getContentSize().height / 3));
							}
						}
					}
					//雷元素消失
					m_element[Thunder] = 0;
					m_element[Ice] = 0;

					//防御下降状态
					for (int i = 0; i < 99; i++)
					{
						if (m_statement[i].name == "def_down")
						{
							m_statement[i].time = 5;
							break;
						}
						else if (m_statement[i].name == "")
						{
							m_statement[i].name = "def_down";
							m_statement[i].time = 5;
							break;
						}
					}

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
							m_element_sprite[i]->setOpacity(255);
							m_element_sprite[i]->setVisible(false);
							//消失后检测，如果还有没消失的元素附着，就让其显示在正上方
							if (m_element_sprite[1 - i]->isVisible())
							{
								m_element_sprite[1 - i]->setPosition(Vec2(0, m_body->getContentSize().height / 3));
							}
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
					effect->EffectsAnimation(effect->Shocked, 0);

					//显示效果
					for (int i = 0; i < 20; i++)
					{
						if (!m_element_label[i]->isVisible())
						{
							m_element_label[i]->setColor(Color3B(172, 43, 231));
							m_element_label[i]->setPosition(Vec2(this->getPositionX() + m_body->getContentSize().width / 3 + rand() % 50, this->getPositionY() + m_body->getContentSize().height / 3 + rand() % 50));
							m_element_label[i]->setString("Shokced");
							m_element_label[i]->setVisible(true);
							m_element_label[i]->runAction(Sequence::create(MoveBy::create(0.1, Vec2(0, 20)), nullptr));
							m_element_label[i]->runAction(Sequence::create(DelayTime::create(1.5), CallFunc::create([=] {m_element_label[i]->setVisible(false); }), MoveBy::create(0.1, Vec2(0, -20)), nullptr));

							break;
						}
					}
					//进入感电状态。在m_statement这个vector中查找，如果找到了shock就让持续时间变成5，否则就添加shock
					for (int i = 0; i < 99; i++)
					{
						if (m_statement[i].name == "shock")
						{
							m_statement[i].time = 5;
							break;
						}
						else if (m_statement[i].name == "")
						{
							m_statement[i].name = "shock";
							m_statement[i].time = 5;
							break;

						}
						
					}




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

				if (m_element[Thunder] > 0)
				{
					//造成雷元素伤害
					hurt(2, Thunder, false);
					m_element[Thunder] = 5;

					//把水或雷元素附着图标消失
					for (int i = 0; i < 2; i++)
					{
						if (m_element_sprite[i]->isVisible() && (m_element_sprite_type[i] == Water || m_element_sprite_type[i] == Thunder))
						{
							m_element_sprite[i]->setOpacity(255);
							m_element_sprite[i]->setVisible(false);
							//消失后检测，如果还有没消失的元素附着，就让其显示在正上方
							if (m_element_sprite[1 - i]->isVisible())
							{
								m_element_sprite[1 - i]->setPosition(Vec2(0, m_body->getContentSize().height / 3));
							}
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
					effect->EffectsAnimation(effect->Shocked, 0);

					//显示效果
					for (int i = 0; i < 20; i++)
					{
						if (!m_element_label[i]->isVisible())
						{
							m_element_label[i]->setColor(Color3B(172, 43, 231));
							m_element_label[i]->setPosition(Vec2(this->getPositionX() + m_body->getContentSize().width / 3 + rand() % 50, this->getPositionY() + m_body->getContentSize().height / 3 + rand() % 50));
							m_element_label[i]->setString("Shokced");
							m_element_label[i]->setVisible(true);
							m_element_label[i]->runAction(Sequence::create(MoveBy::create(0.1, Vec2(0, 20)), nullptr));
							m_element_label[i]->runAction(Sequence::create(DelayTime::create(1.5), CallFunc::create([=] {m_element_label[i]->setVisible(false); }), MoveBy::create(0.1, Vec2(0, -20)), nullptr));

							break;
						}
					}
					//进入感电状态。在m_statement这个vector中查找，如果找到了shock就让持续时间变成5，否则就添加shock
					for (int i = 0; i < 99; i++)
					{
						if (m_statement[i].name == "shock")
						{
							m_statement[i].time = 5;

							break;
						}
						else if (m_statement[i].name == "")
						{
							m_statement[i].name = "shock";
							m_statement[i].time = 5;
							break;

						}

					}
				}
				else if (m_element[Fire] > 0)
				{
					//伤害翻倍
					damage *= 3;
					for (int i = 0; i < 2; i++)
					{
						if (m_element_sprite[i]->isVisible() && (m_element_sprite_type[i] == Water || m_element_sprite_type[i] == Fire))
						{
							m_element_sprite[i]->setOpacity(255);
							m_element_sprite[i]->setVisible(false);
							//消失后检测，如果还有没消失的元素附着，就让其显示在正上方
							if (m_element_sprite[1 - i]->isVisible())
							{
								m_element_sprite[1 - i]->setPosition(Vec2(0, m_body->getContentSize().height / 3));
							}
						}
					}
					m_element[Fire] = 0;
					m_element[Water] = 0;

					//播放特效
					Effects* effect = Effects::create();
					//放大2倍
					effect->setScale(2);
					//位置在人物身上
					effect->setPosition(this->getPosition());
					//绑定到场景
					this->getParent()->addChild(effect);
					effect->EffectsAnimation(effect->Evaporate, 0);

					//显示效果
					for (int i = 0; i < 20; i++)
					{
						if (!m_element_label[i]->isVisible())
						{
							m_element_label[i]->setColor(Color3B(11, 214, 245));
							m_element_label[i]->setPosition(Vec2(this->getPositionX() + m_body->getContentSize().width / 3 + rand() % 50, this->getPositionY() + m_body->getContentSize().height / 3 + rand() % 50));
							m_element_label[i]->setString("Evaporation");
							m_element_label[i]->setVisible(true);
							m_element_label[i]->runAction(Sequence::create(MoveBy::create(0.1, Vec2(0, 20)), nullptr));
							m_element_label[i]->runAction(Sequence::create(DelayTime::create(1.5), CallFunc::create([=] {m_element_label[i]->setVisible(false); }), MoveBy::create(0.1, Vec2(0, -20)), nullptr));

							break;
						}
					}
				}
				else if (m_element[Water] == 0)
				{
					//设置元素附着
					setElementSprite(damge_type);
					m_element[Water] = 5;

				}
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
							m_element_sprite[i]->setOpacity(255);
							m_element_sprite[i]->setVisible(false);
							//消失后检测，如果还有没消失的元素附着，就让其显示在正上方
							if (m_element_sprite[1 - i]->isVisible())
							{
								m_element_sprite[1 - i]->setPosition(Vec2(0, m_body->getContentSize().height / 3));
							}
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
				else if (m_element[Water] > 0)
				{
					//伤害翻倍
					damage *= 3;
					for (int i = 0; i < 2; i++)
					{
						if (m_element_sprite[i]->isVisible() && (m_element_sprite_type[i] == Fire || m_element_sprite_type[i] == Water))
						{
							m_element_sprite[i]->setOpacity(255);
							m_element_sprite[i]->setVisible(false);
							//消失后检测，如果还有没消失的元素附着，就让其显示在正上方
							if (m_element_sprite[1 - i]->isVisible())
							{
								m_element_sprite[1 - i]->setPosition(Vec2(0, m_body->getContentSize().height / 3));
							}
						}
					}
					m_element[Fire] = 0;
					m_element[Water] = 0;

					//播放特效
					Effects* effect = Effects::create();
					//放大2倍
					effect->setScale(2);
					//位置在人物身上
					effect->setPosition(this->getPosition());
					//绑定到场景
					this->getParent()->addChild(effect);
					effect->EffectsAnimation(effect->Evaporate, 0);

					//显示效果
					for (int i = 0; i < 20; i++)
					{
						if (!m_element_label[i]->isVisible())
						{
							m_element_label[i]->setColor(Color3B(249, 85, 9));
							m_element_label[i]->setPosition(Vec2(this->getPositionX() + m_body->getContentSize().width / 3 + rand() % 50, this->getPositionY() + m_body->getContentSize().height / 3 + rand() % 50));
							m_element_label[i]->setString("Evaporation");
							m_element_label[i]->setVisible(true);
							m_element_label[i]->runAction(Sequence::create(MoveBy::create(0.1, Vec2(0, 20)), nullptr));
							m_element_label[i]->runAction(Sequence::create(DelayTime::create(1.5), CallFunc::create([=] {m_element_label[i]->setVisible(false); }), MoveBy::create(0.1, Vec2(0, -20)), nullptr));

							break;
						}
					}
				}
				else if (m_element[Ice] > 0)
				{
					//伤害翻倍
					damage *= 2;
					for (int i = 0; i < 2; i++)
					{
						if (m_element_sprite[i]->isVisible() && (m_element_sprite_type[i] == Fire || m_element_sprite_type[i] == Ice))
						{
							m_element_sprite[i]->setOpacity(255);
							m_element_sprite[i]->setVisible(false);
							//消失后检测，如果还有没消失的元素附着，就让其显示在正上方
							if (m_element_sprite[1 - i]->isVisible())
							{
								m_element_sprite[1 - i]->setPosition(Vec2(0, m_body->getContentSize().height / 3));
							}
						}
					}
					m_element[Fire] = 0;
					m_element[Ice] = 0;

					//播放特效
					Effects* effect = Effects::create();
					//放大2倍
					effect->setScale(2);
					//位置在人物身上
					effect->setPosition(this->getPosition());
					//绑定到场景
					this->getParent()->addChild(effect);
					effect->EffectsAnimation(effect->Evaporate, 0);

					//显示效果
					for (int i = 0; i < 20; i++)
					{
						if (!m_element_label[i]->isVisible())
						{
							m_element_label[i]->setColor(Color3B(249, 85, 9));
							m_element_label[i]->setPosition(Vec2(this->getPositionX() + m_body->getContentSize().width / 3 + rand() % 50, this->getPositionY() + m_body->getContentSize().height / 3 + rand() % 50));
							m_element_label[i]->setString("Melt");
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
					m_superconductivity = -0.2;//超导下防御下降20%
					//把冰或雷元素附着图标消失
					for (int i = 0; i < 2; i++)
					{
						if (m_element_sprite[i]->isVisible() && (m_element_sprite_type[i] == Ice || m_element_sprite_type[i] == Thunder))
						{
							m_element_sprite[i]->setOpacity(255);
							m_element_sprite[i]->setVisible(false);
							//消失后检测，如果还有没消失的元素附着，就让其显示在正上方
							if (m_element_sprite[1 - i]->isVisible())
							{
								m_element_sprite[1 - i]->setPosition(Vec2(0, m_body->getContentSize().height / 3));
							}
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
				else if (m_element[Fire] > 0)
				{
					//伤害翻倍
					damage *= 2;
					for (int i = 0; i < 2; i++)
					{
						if (m_element_sprite[i]->isVisible() && (m_element_sprite_type[i] == Fire || m_element_sprite_type[i] == Ice))
						{
							m_element_sprite[i]->setOpacity(255);
							m_element_sprite[i]->setVisible(false);
							//消失后检测，如果还有没消失的元素附着，就让其显示在正上方
							if (m_element_sprite[1 - i]->isVisible())
							{
								m_element_sprite[1 - i]->setPosition(Vec2(0, m_body->getContentSize().height / 3));
							}
						}
					}
					m_element[Fire] = 0;
					m_element[Ice] = 0;

					//播放特效
					Effects* effect = Effects::create();
					//放大2倍
					effect->setScale(2);
					//位置在人物身上
					effect->setPosition(this->getPosition());
					//绑定到场景
					this->getParent()->addChild(effect);
					effect->EffectsAnimation(effect->Evaporate, 0);

					//显示效果
					for (int i = 0; i < 20; i++)
					{
						if (!m_element_label[i]->isVisible())
						{
							m_element_label[i]->setColor(Color3B(198, 244, 243));
							m_element_label[i]->setPosition(Vec2(this->getPositionX() + m_body->getContentSize().width / 3 + rand() % 50, this->getPositionY() + m_body->getContentSize().height / 3 + rand() % 50));
							m_element_label[i]->setString("Melt");
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
		float real_defense;//实际防御值
		real_defense = m_defense + m_superconductivity;





		int real_damage = int(float(damage) - float(damage) * real_defense);//实际伤害=伤害值-防御值*伤害值
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
					if (m_immune[Physical])
					{
						//灰色字体显示免疫后立刻退出
						m_damage_label[i]->setColor(Color3B::GRAY);
						m_damage_label[i]->setPosition(Vec2(this->getPositionX() - m_body->getContentSize().width / 6 + rand() % 70, this->getPositionY() - m_body->getContentSize().height / 6 + rand() % 70));
						m_damage_label[i]->setVisible(true);
						//向上浮现
						m_damage_label[i]->runAction(Sequence::create(MoveBy::create(0.1, Vec2(0, 20)), nullptr));//创建一个动作序列，让伤害数字向上浮现，持续0.1秒
						//1.5秒后先让m_damage_label[i]不可见，不可见后向下移动20个像素
						m_damage_label[i]->runAction(Sequence::create(DelayTime::create(1.5), CallFunc::create([=] {m_damage_label[i]->setVisible(false); }), MoveBy::create(0.1, Vec2(0, -20)), nullptr));
						m_damage_label[i]->setString("Immune");
						return;
					}
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
					if (m_immune[Thunder])
					{
						//灰色字体显示免疫后立刻退出
						m_damage_label[i]->setColor(Color3B::GRAY);
						m_damage_label[i]->setPosition(Vec2(this->getPositionX() - m_body->getContentSize().width / 6 + rand() % 70, this->getPositionY() - m_body->getContentSize().height / 6 + rand() % 70));
						m_damage_label[i]->setVisible(true);
						//向上浮现
						m_damage_label[i]->runAction(Sequence::create(MoveBy::create(0.1, Vec2(0, 20)), nullptr));//创建一个动作序列，让伤害数字向上浮现，持续0.1秒
						//1.5秒后先让m_damage_label[i]不可见，不可见后向下移动20个像素
						m_damage_label[i]->runAction(Sequence::create(DelayTime::create(1.5), CallFunc::create([=] {m_damage_label[i]->setVisible(false); }), MoveBy::create(0.1, Vec2(0, -20)), nullptr));
						m_damage_label[i]->setString("Immune");
						return;
					}
					break;
					//如果是草属性伤害，伤害数字为绿色，RGB为42,204,21
				case Grass:
					m_damage_label[i]->setColor(Color3B(42, 204, 21));
					break;
					//如果是水属性伤害，伤害数字为蓝色，RGB为11,214,245
				case Water:
					m_damage_label[i]->setColor(Color3B(11, 214, 245));
					if (m_immune[Water])
					{
						//灰色字体显示免疫后立刻退出
						m_damage_label[i]->setColor(Color3B::GRAY);
						m_damage_label[i]->setPosition(Vec2(this->getPositionX() - m_body->getContentSize().width / 6 + rand() % 70, this->getPositionY() - m_body->getContentSize().height / 6 + rand() % 70));
						m_damage_label[i]->setVisible(true);
						//向上浮现
						m_damage_label[i]->runAction(Sequence::create(MoveBy::create(0.1, Vec2(0, 20)), nullptr));//创建一个动作序列，让伤害数字向上浮现，持续0.1秒
						//1.5秒后先让m_damage_label[i]不可见，不可见后向下移动20个像素
						m_damage_label[i]->runAction(Sequence::create(DelayTime::create(1.5), CallFunc::create([=] {m_damage_label[i]->setVisible(false); }), MoveBy::create(0.1, Vec2(0, -20)), nullptr));
						m_damage_label[i]->setString("Immune");
						return;
					}
					break;
					//如果是火属性伤害，伤害数字为红色，RGB为249,85,9
				case Fire:
					m_damage_label[i]->setColor(Color3B(249, 85, 9));
					if (m_immune[Fire])
					{
						//灰色字体显示免疫后立刻退出
						m_damage_label[i]->setColor(Color3B::GRAY);
						m_damage_label[i]->setPosition(Vec2(this->getPositionX() - m_body->getContentSize().width / 6 + rand() % 70, this->getPositionY() - m_body->getContentSize().height / 6 + rand() % 70));
						m_damage_label[i]->setVisible(true);
						//向上浮现
						m_damage_label[i]->runAction(Sequence::create(MoveBy::create(0.1, Vec2(0, 20)), nullptr));//创建一个动作序列，让伤害数字向上浮现，持续0.1秒
						//1.5秒后先让m_damage_label[i]不可见，不可见后向下移动20个像素
						m_damage_label[i]->runAction(Sequence::create(DelayTime::create(1.5), CallFunc::create([=] {m_damage_label[i]->setVisible(false); }), MoveBy::create(0.1, Vec2(0, -20)), nullptr));
						m_damage_label[i]->setString("Immune");
						return;
					}
					break;
					//如果是冰属性伤害，伤害数字为淡蓝色，RGB为198,244,243
				case Ice:
					m_damage_label[i]->setColor(Color3B(198, 244, 243));
					if (m_immune[Ice])
					{
						//灰色字体显示免疫后立刻退出
						m_damage_label[i]->setColor(Color3B::GRAY);
						m_damage_label[i]->setPosition(Vec2(this->getPositionX() - m_body->getContentSize().width / 6 + rand() % 70, this->getPositionY() - m_body->getContentSize().height / 6 + rand() % 70));
						m_damage_label[i]->setVisible(true);
						//向上浮现
						m_damage_label[i]->runAction(Sequence::create(MoveBy::create(0.1, Vec2(0, 20)), nullptr));//创建一个动作序列，让伤害数字向上浮现，持续0.1秒
						//1.5秒后先让m_damage_label[i]不可见，不可见后向下移动20个像素
						m_damage_label[i]->runAction(Sequence::create(DelayTime::create(1.5), CallFunc::create([=] {m_damage_label[i]->setVisible(false); }), MoveBy::create(0.1, Vec2(0, -20)), nullptr));
						m_damage_label[i]->setString("Immune");
						return;
					}
					break;
				}






				m_damage_label[i]->setPosition(Vec2(this->getPositionX() - m_body->getContentSize().width / 6 + rand() % 70, this->getPositionY() - m_body->getContentSize().height / 6 + rand() % 70));//rand()的使用方法是rand()%n，表示生成一个0到n-1的随机数
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
		this->runAction(Sequence::create(DelayTime::create(0.1), CallFunc::create([=] {m_body->setColor(Color3B::WHITE); }), nullptr));


	}
}

void BasePlayer::setElementSprite(int elemtype)
{
	//检测元素附着数量
	int count = 0;
	for (int i = 0; i < 2; i++)
	{
		if (m_element_sprite[i]->isVisible())
		{
			count++;
		}
	}


	//查找当前是否有元素附着，如果有就考虑是否反应的问题
	//先看0号位是否有元素附着，没有就直接附着
	if (count==0)
	{
		//透明度恢复
		m_element_sprite[0]->setOpacity(255);
		m_element_sprite[0]->setVisible(true);
		//设置元素附着的位置
		m_element_sprite[0]->setPosition(Vec2(0, m_body->getContentSize().height / 3));
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
		m_element_sprite[0]->setPosition(Vec2(-20, m_body->getContentSize().height / 3));
		//再把1号图片设置到正上方的右侧
		m_element_sprite[1]->setVisible(true);
		m_element_sprite[1]->setPosition(Vec2(20, m_body->getContentSize().height / 3));



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

void BasePlayer::effectTrigger(std::string effect_type)
{
	if (effect_type == "shock")
	{
		hurt(2, Thunder, false);
		//播放特效
		Effects* effect = Effects::create();
		//放大2倍
		effect->setScale(2);
		//位置在人物身上
		effect->setPosition(this->getPosition());
		//绑定到场景
		this->getParent()->addChild(effect);
		effect->EffectsAnimation(effect->Shocked, 0);

		//显示效果
		for (int i = 0; i < 20; i++)
		{
			if (!m_element_label[i]->isVisible())
			{
				m_element_label[i]->setColor(Color3B(172, 43, 231));
				m_element_label[i]->setPosition(Vec2(this->getPositionX() + m_body->getContentSize().width / 3 + rand() % 50, this->getPositionY() + m_body->getContentSize().height / 3 + rand() % 50));
				m_element_label[i]->setString("Shokced");
				m_element_label[i]->setVisible(true);
				m_element_label[i]->runAction(Sequence::create(MoveBy::create(0.1, Vec2(0, 20)), nullptr));
				m_element_label[i]->runAction(Sequence::create(DelayTime::create(1.5), CallFunc::create([=] {m_element_label[i]->setVisible(false); }), MoveBy::create(0.1, Vec2(0, -20)), nullptr));

				break;
			}
		}
	}
}

