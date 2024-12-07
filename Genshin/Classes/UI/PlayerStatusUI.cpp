#include "UI/PlayerStatusUI.h"
#include "Player/Player.h"

bool PlayerStatusUI::init()
{
	//加入背景板，在左上角
	Background = Sprite::create("Me/InfoUI/BackGround.png");//创建一个精灵
	//重设背景大小。设为宽500，高250
	Background->setScaleX(800 / Background->getContentSize().width);
	Background->setScaleY(250 / Background->getContentSize().height);



	//设置位置到屏幕左上角。横坐标是精灵的宽度的一半，纵坐标是屏幕高度减去精灵的高度的一半
	Background->setPosition(Vec2(Background->getContentSize().width / 2, Director::getInstance()->getVisibleSize().height - Background->getContentSize().height / 2));
	this->addChild(Background);//将背景板添加到节点

	//创建角色头像
	Player_Image = Sprite::create("HelloWorld.png");//创建一个精灵
	//设置头像大小，宽高都是100
	Player_Image->setScaleX(100 / Player_Image->getContentSize().width);
	Player_Image->setScaleY(100 / Player_Image->getContentSize().height);
	Player_Image->setPosition(Vec2(Background->getContentSize().width / 2, Director::getInstance()->getVisibleSize().height - Background->getContentSize().height / 2));
	this->addChild(Player_Image);//将精灵添加到节点

	//设置人物名字的内容
	Player_Name = Label::createWithTTF("Player", "fonts/HarmonyOS_Sans_SC_Medium.TTF", 24);//设置内容为“Player”，字体为“Marker Felt”，大小为24
	//位置设在头像下面
	Player_Name->setPosition(Vec2(Background->getContentSize().width / 2, Director::getInstance()->getVisibleSize().height - Background->getContentSize().height / 2 - 70));
	//描边
	Player_Name->enableOutline(Color4B::BLACK, 2);


	this->addChild(Player_Name);//将人物名字添加到节点



	//角色血条
	//创建一个血条
	Player_hpBar = ProgressTimer::create(Sprite::create("Me/InfoUI/hp_bar.png"));
	Player_hpBar_bg = Sprite::create("Me/InfoUI/hp_bar_bg.png");
	//设置血条的类型为条形
	Player_hpBar->setType(ProgressTimer::Type::BAR);
	//设置血条的起点，从左往右
	Player_hpBar->setMidpoint(Vec2(0, 0.5));//传入两个参数，0表示x轴，0.5表示y轴，表示血条的起点在左边中间
	//设置血条的变化率
	Player_hpBar->setBarChangeRate(Vec2(1, 0));
	//设置血条的大小，长宽分别是300，30
	Player_hpBar->setScaleX(300 / Player_hpBar->getContentSize().width);
	Player_hpBar->setScaleY(30 / Player_hpBar->getContentSize().height);
	Player_hpBar_bg->setScaleX(300 / Player_hpBar_bg->getContentSize().width);
	Player_hpBar_bg->setScaleY(30 / Player_hpBar_bg->getContentSize().height);
	//设置血条的位置
	Player_hpBar->setPosition(Vec2(Player_hpBar->getContentSize().width / 2+220, Director::getInstance()->getVisibleSize().height - Player_hpBar->getContentSize().height / 2+20));
	Player_hpBar_bg->setPosition(Vec2(Player_hpBar->getContentSize().width / 2 + 220, Director::getInstance()->getVisibleSize().height - Player_hpBar->getContentSize().height / 2 + 20));

	this->addChild(Player_hpBar_bg);//将血条背景添加到节点
	this->addChild(Player_hpBar);//将滑血条添加到节点

	//血量标签
	Player_hpLabel = Label::createWithTTF("100/100", "fonts/Marker Felt.ttf", 24);//设置内容为“100/100”，字体为“Marker Felt”，大小为24
	Player_hpLabel->setPosition(Vec2(Player_hpBar->getPosition().x, Player_hpBar->getPosition().y));//设置位置
	this->addChild(Player_hpLabel);//将血量标签添加到节点

	//UI\Player_Skill
	//元素能量条
	//创建一个能量条
	Player_mpBar = ProgressTimer::create(Sprite::create("UI/Player_Skill/Q.png"));//创建一个滑动条
	Player_mpBar_bg = Sprite::create("UI/Player_Skill/BackGround.png");//创建一个背景
	//设置能量条的类型为球形
	Player_mpBar->setType(ProgressTimer::Type::BAR);
	//设置能量条从下往上显示
	Player_mpBar->setMidpoint(Vec2(0.5, 0));//传入两个参数，0.5表示x轴，0表示y轴，表示能量条的起点在下边中间


	//设置能量条的变化率
	Player_mpBar->setBarChangeRate(Vec2(0, 1));
	//设置能量条的大小，宽高都是100
	Player_mpBar->setScaleX(100 / Player_mpBar->getContentSize().width);
	Player_mpBar->setScaleY(100 / Player_mpBar->getContentSize().height);
	Player_mpBar_bg->setScaleX(100 / Player_mpBar_bg->getContentSize().width);
	Player_mpBar_bg->setScaleY(100 / Player_mpBar_bg->getContentSize().height);
	//设置能量条的位置
	Player_mpBar->setPosition(Vec2(Background->getContentSize().width+250, Director::getInstance()->getVisibleSize().height - Background->getContentSize().height / 2 - 50));
	Player_mpBar_bg->setPosition(Vec2(Background->getContentSize().width+250, Director::getInstance()->getVisibleSize().height - Background->getContentSize().height / 2 - 50));

	this->addChild(Player_mpBar_bg);//将能量条背景添加到节点
	this->addChild(Player_mpBar);//将能量条添加到节点



	return true;
}

void PlayerStatusUI::updateUI(Player& player)
{
	//更新血条
	Player_hpBar->setPercentage(float(player.m_hp) / float(player.m_max_hp) * 100);
	//更新血量
	Player_hpLabel->setString(to_string(player.m_hp) + "/" + to_string(player.m_max_hp));
	//更新能量条
	Player_mpBar->setPercentage(float(player.m_mp) / float(player.m_max_mp) * 100);
	//更新人物名字
	Player_Name->setString(player.m_name);
}