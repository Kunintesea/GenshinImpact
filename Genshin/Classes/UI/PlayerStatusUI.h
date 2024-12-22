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
	friend class Player;//��Ԫ��
	virtual bool init();
	//����UI�ĺ���������player�࣬���������ݸ���UI
	void updateUI(Player& player);
	void updateInteractUI(Player& player);
	void interact(int tag);

	CREATE_FUNC(PlayerStatusUI);
private:
	Sprite* Background;//��Ϣ��ı���
	Label* Player_Name;//��������
	Label* Player_Level;//����ȼ�
	ProgressTimer* Player_hpBar;//Ѫ��
	Sprite* Player_hpBar_bg;//Ѫ������
	Label* Player_hpLabel;//Ѫ����ǩ

	Sprite* TaskUI;//����UI

	ProgressTimer* Player_staminaBar;//������
	Sprite* Player_staminaBar_bg;//����������
	ProgressTimer* Player_expBar;//������
	Sprite* Player_expBar_bg;//����������


	ProgressTimer* Player_shieldBar;//������

	Sprite* m_statement_sprite[99];//״̬ͼ��
	string m_statement_sprite_name[99];//״̬ͼ������

	//���ε�Ԫ����������������������
	ProgressTimer* Player_mpBar;//������
	Sprite* Player_mpBar_bg;//����������
	//���ε�E������ʾ
	ProgressTimer* Player_E;
	Sprite* Player_E_bg;


	Label* Player_Q_CD;//Q������ȴʱ��
	Label* Player_E_CD;//E������ȴʱ��

	Sprite* Player_Image;//ͷ��

	Button* Interact_1;//����ͼ��
	Button* Interact_2;//����ͼ��
};

#endif 