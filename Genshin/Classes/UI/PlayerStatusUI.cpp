#include "PlayerStatusUI.h"




bool PlayerStatusUI::init()
{
	//设置人物名字的内容
	//Player_Name = Label::createWithTTF("Player", "fonts/Marker Felt.ttf", 24);//设置内容为“Player”，字体为“Marker Felt”，大小为24
	//Player_Name->setPosition(Vec2(0, 0));//设置位置
	//this->addChild(Player_Name);//将人物名字添加到节点

	//加入背景板，在左上角
	Background = Sprite::create("Me/InfoUI/BackGround.png");//创建一个精灵
	//重设背景大小。设为宽500，高250
	Background->setScaleX(500 / Background->getContentSize().width);
	Background->setScaleY(250 / Background->getContentSize().height);

	//设置位置到屏幕左上角。横坐标是精灵的宽度的一半，纵坐标是屏幕高度减去精灵的高度的一半
	Background->setPosition(Vec2(Background->getContentSize().width / 2, Director::getInstance()->getVisibleSize().height - Background->getContentSize().height / 2));

	//在屏幕上显示人物血条


	this->addChild(Background);//将背景板添加到节点


	Player_Image = Sprite::create("HelloWorld.png");//创建一个精灵
	Player_Image->setPosition(Vec2(100, 100));//设置位置
	this->addChild(Player_Image);//将精灵添加到节点
	/*
	
	//让人物信息UI显示在屏幕上，设定显示在左上角
	//D:\Github_Document\GenshinImpact\Genshin\Resources\Me\InfoUI
	playerUI.Player_hpBar = ProgressTimer::create(Sprite::create("Me/InfoUI/hp_bar.png"));//创建一个血条
	playerUI.Player_hpBar->setType(ProgressTimer::Type::BAR);//设置血条的类型为条形
	playerUI.Player_hpBar->setMidpoint(Vec2(0, 0.5));//设置血条的起点
	playerUI.Player_hpBar->setPercentage(m_hp / m_max_hp * 100);//让血条的百分比等于当前血量除以最大血量
	playerUI.Player_hpBar->setBarChangeRate(Vec2(1, 0));//设置血条的变化率
	playerUI.Player_hpBar->setPosition(Vec2(0, 0));//设置血条的位置
	//设置血条的大小，长宽分别是100，10
	playerUI.Player_hpBar->setScaleX(100 / playerUI.Player_hpBar->getContentSize().width);
	playerUI.Player_hpBar->setScaleY(10 / playerUI.Player_hpBar->getContentSize().height);
	this->addChild(playerUI.Player_hpBar);//将滑血条添加到节点

	*/


	return true;
}