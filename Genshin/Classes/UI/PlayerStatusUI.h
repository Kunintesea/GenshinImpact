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
	friend class Player;//��Ԫ��
	virtual bool init();

	CREATE_FUNC(PlayerStatusUI);
private:
	Sprite* Background;//��Ϣ��ı���
	Label* Player_Name;//��������
	ProgressTimer* Player_hpBar;//Ѫ��
	//Slider* Player_mpBar;//����
	//Slider* Player_expBar;//������
	Sprite* Player_Image;//ͷ��

};

#endif 