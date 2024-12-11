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
	//����UI�ĺ���������player�࣬���������ݸ���UI
	void updateUI(Player& player);

	CREATE_FUNC(PlayerStatusUI);
private:
	Sprite* Background;//��Ϣ��ı���
	Label* Player_Name;//��������
	ProgressTimer* Player_hpBar;//Ѫ��
	Sprite* Player_hpBar_bg;//Ѫ������
	Label* Player_hpLabel;//Ѫ����ǩ

	ProgressTimer* Player_staminaBar;//������
	Sprite* Player_staminaBar_bg;//����������
	

	ProgressTimer* Player_shieldBar;//������


	//���ε�Ԫ����������������������
	ProgressTimer* Player_mpBar;//������
	Sprite* Player_mpBar_bg;//����������
	//���ε�E������ʾ
	ProgressTimer* Player_E;
	Sprite* Player_E_bg;


	Label* Player_Q_CD;//Q������ȴʱ��
	Label* Player_E_CD;//E������ȴʱ��

	Sprite* Player_Image;//ͷ��

};

#endif 