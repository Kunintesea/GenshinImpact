#include "BasePlayer.h"



void BasePlayer::hurt(int damage, int damge_type, bool reaction)
{
	if (isDodge) return;
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
					//超载效果
					//造成火元素伤害
					hurt(5, Fire, false);


					//火元素消失
					m_element[Fire] = 0;

					//播放超载特效
					Effects* effect = Effects::create();
					//放大2倍
					effect->setScale(2);
					//位置在人物身上
					effect->setPosition(Vec2(0, 0));
					//绑定到人物
					this->addChild(effect);
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
					m_element[Thunder] = 5;
				}
				break;
			case Grass:
				m_element[Grass] = 5;
				break;
			case Water:
				m_element[Water] = 5;
				break;
			case Fire:
				if (m_element[Thunder] > 0)
				{
					//超载效果
					//伤害值翻倍
					damage *= 2;
					//火元素消失
					m_element[Thunder] = 0;

					//播放超载特效
					Effects* effect = Effects::create();
					//放大2倍
					effect->setScale(2);
					//位置在人物身上
					effect->setPosition(Vec2(0, 0));
					//绑定到人物
					this->addChild(effect);
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
					m_element[Fire] = 5;
				}
				break;
			case Ice:
				m_element[Ice] = 5;
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
		m_hp -= real_damage;
		if (m_hp <= 0)
		{
			isDead = true;
			m_hp = 0;
		}

		//用setColor让人物RGB变红，0.1秒后恢复
		m_body->setColor(Color3B::RED);
		this->runAction(Sequence::create(DelayTime::create(0.1), CallFunc::create([=] {m_body->setColor(Color3B::WHITE); }), nullptr));


	}
}