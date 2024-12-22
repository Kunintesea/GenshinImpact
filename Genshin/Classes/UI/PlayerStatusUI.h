#ifndef __PLAYERSTATUSUI_NODE_H__
#define __PLAYERSTATUSUI_NODE_H__

#include "cocos2d.h"
#include "Player\Player.h"
#include "ui/CocosGUI.h"
#include "Scene/MapScene.h"
#include <string>
#include <vector>

using namespace std;
USING_NS_CC;
using namespace std;
using namespace ui;

class PlayerStatusUI : public Node
{
public:
	friend class Player;//友元类
	virtual bool init();
	//更新UI的函数，传入player类，根据其数据更新UI
	void updateUI(Player& player);
	void updateInteractUI(Player& player);
	void interact(int tag);

	CREATE_FUNC(PlayerStatusUI);
private:
	Sprite* Background;//信息板的背景
	Label* Player_Name;//人物名字
	Label* Player_Level;//人物等级
	ProgressTimer* Player_hpBar;//血条
	Sprite* Player_hpBar_bg;//血条背景
	Label* Player_hpLabel;//血量标签

	Sprite* TaskUI;//任务UI

	ProgressTimer* Player_staminaBar;//体力条
	Sprite* Player_staminaBar_bg;//体力条背景
	ProgressTimer* Player_expBar;//经验条
	Sprite* Player_expBar_bg;//经验条背景


	ProgressTimer* Player_shieldBar;//护盾条

	Sprite* m_statement_sprite[99];//状态图标
	string m_statement_sprite_name[99];//状态图标名称

	//球形的元素能量条，从下往上增长
	ProgressTimer* Player_mpBar;//能量条
	Sprite* Player_mpBar_bg;//能量条背景
	//球形的E技能显示
	ProgressTimer* Player_E;
	Sprite* Player_E_bg;


	Label* Player_Q_CD;//Q技能冷却时间
	Label* Player_E_CD;//E技能冷却时间

	Sprite* Player_Image;//头像

	Button* Interact_1;//交互图标
	Button* Interact_2;//交互图标
};

#endif 