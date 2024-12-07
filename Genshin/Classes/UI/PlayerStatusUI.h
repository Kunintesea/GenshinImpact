#ifndef __PLAYERSTATUSUI_NODE_H__
#define __PLAYERSTATUSUI_NODE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <string>

using namespace std;
USING_NS_CC;

class PlayerStatusUI : public Node
{
public:
	friend class Player;//友元类
	virtual bool init();
	//更新UI的函数，传入player类，根据其数据更新UI
	void updateUI(Player& player);

	CREATE_FUNC(PlayerStatusUI);
private:
	Sprite* Background;//信息板的背景
	Label* Player_Name;//人物名字
	ProgressTimer* Player_hpBar;//血条
	Sprite* Player_hpBar_bg;//血条背景
	Label* Player_hpLabel;//血量标签
	//球形的元素能量条，从下往上增长
	ProgressTimer* Player_mpBar;//能量条
	Sprite* Player_mpBar_bg;//能量条背景
	Label* Player_Q_CD;//Q技能冷却时间

	Sprite* Player_Image;//头像

};

#endif 