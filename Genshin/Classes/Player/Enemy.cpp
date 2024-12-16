#include "Enemy.h"

USING_NS_CC;


bool Enemy::init()
{
	if (!Node::init())
	{
		return false;
	}
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