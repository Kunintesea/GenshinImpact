#ifndef __PLAYERSTATUSUI_NODE_H__
#define __PLAYERSTATUSUI_NODE_H__

#include "cocos2d.h"
#include "Player\Player.h"
#include "ui/CocosGUI.h"
#include <string>

using namespace std;
USING_NS_CC;
class PlayerStatusUI : public Node
{
public:
	friend class Player;//友元类
	virtual bool init();

	CREATE_FUNC(PlayerStatusUI);
private:
	Sprite* Background;//信息板的背景
	Label* Player_Name;//人物名字
	ProgressTimer* Player_hpBar;//血条
	//Slider* Player_mpBar;//蓝条
	//Slider* Player_expBar;//经验条
	Sprite* Player_Image;//头像

};

#endif 