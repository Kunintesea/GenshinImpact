#include "boxtest.h"


Treasurebox* Treasurebox::create(const std::string& closedImage, const std::string& openedImage)
{
    Treasurebox* chest = new (std::nothrow) Treasurebox();
    if (chest && chest->init(closedImage, openedImage))
    {
        chest->autorelease();
        return chest;
    }
    delete chest;
    return nullptr;
}

// 初始化方法
bool Treasurebox::init(const std::string& closedImage, const std::string& openedImage)
{
    if (!Node::init())
    {
        return false;
    }

    // 设置贴图路径
    _closedImage = closedImage;
    _openedImage = openedImage;
    _isOpen = false;

    // 创建精灵并加载关闭状态图片
    _chestSprite = Sprite::create(_closedImage);
    if (!_chestSprite)
    {
        return false;
    }

    // 将精灵添加为子节点
    this->addChild(_chestSprite);

	if (!Node::init())
	{
		return false;
	}
	//加入调度器
	this->scheduleUpdate();//调度器，每帧调用一次update函数


	//创建精灵
	m_body = Sprite::create("box/chest_close.png");
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
		m_element_sprite[i]->setPosition(Vec2(this->getPositionX(), this->getPositionY() + m_body->getContentSize().height * 2));
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
	Enemy_hpBar_bg->setPosition(Vec2(0, this->getPositionY() + m_body->getContentSize().height));


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


void Treasurebox::update(float t)
{
	log("dxcgfvhbjn");
	//更新血条
	Enemy_hpBar->setPercentage(float(m_hp) / float(m_max_hp) * 100);
	//更新血量
	Enemy_hpLabel->setString(std::to_string(m_hp) + "/" + std::to_string(m_max_hp));

	//如果死亡了直接把状态全部清空
	if (isDead)
	{
		for (int i = 0; i < 99; i++)
		{
			m_statement[i].name = "";
			m_statement_time[i] = 0;
		}
		open();
	}

}

// 打开宝箱
void Treasurebox::open()
{
    if (!_isOpen)
    {
        _chestSprite->setTexture(_openedImage);
        _isOpen = true;
        // 此处添加打开后逻辑！！！！




        CCLOG("宝箱已打开");
    }
}

// 关闭宝箱
void Treasurebox::close()
{
    if (_isOpen)
    {
        _chestSprite->setTexture(_closedImage);
        _isOpen = false;
        // 可添加关闭动画或音效
        CCLOG("宝箱已关闭");
    }
}

// 检查宝箱是否打开
bool Treasurebox::isOpen() const
{
    return _isOpen;
}
